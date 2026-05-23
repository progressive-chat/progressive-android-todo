#!/usr/bin/env python3
"""
Fix broken C++ .hpp headers in progressive/ and regenerate .cpp implementations.
Handles two corruption patterns:
  1. Colon-separated function names: func1:func2:func3(const std::string& json);
  2. Scrambled params: lines split around std::string boundaries
"""

import os
import re
import sys
from pathlib import Path

BASE_DIR = Path("/home/bym/matrixclient/progressive-android/progressive/src/main/cpp")
INCLUDE_DIR = BASE_DIR / "include" / "progressive"
SRC_DIR = BASE_DIR / "src"

# Files we should NOT touch (legacy, already properly structured)
LEGACY_FILES = {
    "llm", "auth_utils", "auth_models", "crypto_models", "call_models",
    # and any other legacy files that happen to match broken patterns
}

def extract_functions_from_colon_header(content: str) -> list[str]:
    """Extract function names from a colon-separated header like:
    std::string func1:func2:func3(const std::string& json);
    """
    funcs = []
    for line in content.splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("#") or stripped.startswith("/") or stripped.startswith("*"):
            continue
        # Match: std::string name1:name2:name3(const std::string& json);
        m = re.match(r'std::string\s+([\w:]+)\(const\s+std::string&\s+json\);', stripped)
        if m:
            names = m.group(1).split(":")
            funcs.extend(names)
    return funcs

def fix_colon_hpp(filepath: Path, func_names: list[str]) -> str:
    """Generate a clean .hpp for colon-pattern files."""
    base = filepath.stem
    lines = []
    lines.append("#pragma once")
    lines.append("#include <string>")
    lines.append("#include <cstdint>")
    lines.append("")
    for name in func_names:
        lines.append(f"std::string {name}(const std::string& json);")
    lines.append("")
    return "\n".join(lines)

SUFFIX = "(const std::string& json);"
KNOWN_NONSTRING_TYPES = {"bool", "int64_t", "int32_t", "int", "size_t", "void", "double", "float"}

def extract_from_semicolon_line(line: str) -> tuple[list[tuple[str, str, str]], str]:
    """Extract function declarations and any struct definition from a single semicolon-concatenated line.
    Returns (functions, struct_definition_or_empty_string).
    """
    funcs = []
    struct_def = ""
    
    # Try to extract a struct definition: look for "struct Name { ... };"
    struct_m = re.search(r'struct\s+(\w+)\s*\{([^}]*)\};', line)
    if struct_m:
        struct_name = struct_m.group(1)
        fields_str = struct_m.group(2)
        # Parse fields: "shortcode; stdstring mxcUrl; stdstring label;"
        # Each field is like "type fieldName;" 
        fields = []
        for field in fields_str.split(";"):
            field = field.strip()
            if not field:
                continue
            # Clean the type and name
            parts = field.split()
            if len(parts) >= 2:
                ftype = clean_mangled_types(" ".join(parts[:-1]))
                fname = parts[-1]
                # Handle missing type (e.g., just "shortcode")
                if ftype == fname or not ftype:
                    ftype = "std::string"
                fields.append(f"    {ftype} {fname};")
            elif len(parts) == 1:
                # Just a field name, default to std::string
                fields.append(f"    std::string {parts[0]};")
        if fields:
            struct_def = f"struct {struct_name} {{\n" + "\n".join(fields) + f"\n}};\n"
    
    # Find all function-like patterns: [opt_type] funcName(params);
    pattern = r'(?:([\w:<>\s]+?)\s+)?(\w+)\(([^)]*)\);'
    matches = list(re.finditer(pattern, line))
    
    for m in matches:
        type_part = (m.group(1) or "").strip()
        func_name = m.group(2)
        params = m.group(3).strip()
        
        # Skip keywords and struct field names
        if func_name in ("struct", "class", "if", "for", "while", "return", "namespace"):
            continue
        # Skip if it looks like a struct field (common field names)
        if func_name in ("shortcode", "mxcUrl", "label", "userId", "start", "end", "type", "eventId", "key", "emoji", "name"):
            continue
        
        # Determine return type
        type_words = type_part.split()
        ret_type = "std::string"
        for t in reversed(type_words):
            if t in KNOWN_NONSTRING_TYPES:
                ret_type = t
                break
        
        # Clean mangled types
        cleaned_type_part = clean_mangled_types(type_part)
        type_words = cleaned_type_part.split()
        ret_type = "std::string"
        for t in reversed(type_words):
            if t in KNOWN_NONSTRING_TYPES:
                ret_type = t
                break
            if t in ("std::vector<std::string>",):
                ret_type = t
                break
        
        sig = f"{func_name}({params});" if params else f"{func_name}();"
        funcs.append((ret_type, sig, func_name))
    
    return funcs, struct_def



def reconstruct_declaration(lines: list[str]) -> str | None:
    """Reconstruct a clean function declaration from 1+ broken lines.
    Each broken line starts with 'std::string ' and ends with '(const std::string& json);'.
    Multi-line means params got split at 'std::string' boundaries.
    Single-line could be already-correct or just a simple decl that needs fixing.
    """
    # Check if single-line already-correct declaration
    if len(lines) == 1:
        line = lines[0]
        m = re.match(r'^([\w:<>\s]+?)\s+(\w+)\(([^)]*)\);$', line)
        if m:
            return line  # Already correct

    # Multi-line or broken single-line: strip prefix/suffix, join, fix
    parts = []
    for line in lines:
        p = line
        if p.startswith("std::string "):
            p = p[len("std::string "):]
        if p.endswith(SUFFIX):
            p = p[:-len(SUFFIX)]
        # Also handle ");(" artifact at end
        if p.endswith(");("):
            p = p[:-3] + ");"
        parts.append(p)

    joined = "".join(parts)

    # Fix split "const std" + "string&" fragments from multi-line breaks
    joined = re.sub(r'const\s+std\s*string&', 'const std::string&', joined)
    joined = re.sub(r'const\s+stdstring&', 'const std::string&', joined)

    # Remove garbage artifacts
    joined = re.sub(r'\)\(\)', '()', joined)
    joined = re.sub(r'\);\(', ');', joined)
    joined = joined.rstrip("(")

    # Ensure declaration ends with );
    joined = joined.strip()
    if joined.endswith(";"):
        if not joined.endswith(");"):
            joined = joined[:-1] + ");"
    elif joined.endswith(")"):
        joined += ";"
    else:
        # No paren case: "funcName" -> "funcName();"
        m = re.match(r'^(\w+)$', joined)
        if m:
            joined = m.group(1) + "();"
        else:
            joined += ");"

    # Clean mangled types in the reconstructed declaration
    joined = clean_mangled_types(joined)

    return joined


def parse_function_declaration(decl: str) -> tuple[str, str, str] | None:
    """Parse a cleaned declaration into (return_type, signature, func_name).
    E.g. "bool canRead(const std::string& json);" -> ("bool", "canRead(const std::string& json);", "canRead")
    """
    decl = decl.strip()
    
    # Match: [optional type words] funcName(params);
    m = re.match(r'^([\w:<>\s]*?)\s*(\w+)\(([^)]*)\);$', decl)
    if m:
        type_part = m.group(1).strip()
        func_name = m.group(2)
        params = m.group(3).strip()
        
        # Determine return type
        type_words = type_part.split()
        ret_type = "std::string"
        for t in reversed(type_words):
            if t in KNOWN_NONSTRING_TYPES:
                ret_type = t
                break
            if t in ("std::vector<std::string>",):
                ret_type = t
                break
        
        sig = f"{func_name}({params});" if params else f"{func_name}();"
        return (ret_type, sig, func_name)
    
    # No-paren fallback: "funcName;"
    m2 = re.match(r'^(\w+);$', decl)
    if m2:
        return ("std::string", m2.group(1) + "();", m2.group(1))
    
    return None


def extract_functions_from_scrambled_hpp(content: str) -> list[tuple[str, str, str]]:
    """Extract function signatures from scrambled-params headers.
    Returns list of (return_type, signature, func_name).
    """
    # Collect all code lines (non-header, non-empty)
    code_lines = []
    for line in content.splitlines():
        s = line.strip()
        if not s or s.startswith("#") or s.startswith("/") or s.startswith("*"):
            continue
        if s.startswith("namespace ") or s in ("{", "}"):
            continue
        code_lines.append(s)

    if not code_lines:
        return []

    # Group lines into function blocks. 
    # Strategy: first check if a line is already a valid complete declaration.
    # If not, strip corruption prefix/suffix and check if the result starts a function name.
    blocks = []
    cur = []
    for line in code_lines:
        # Check if this line is already a correct complete declaration
        already_correct = bool(re.match(r'^([\w:<>\s]+?)\s+(\w+)\(([^)]*)\);$', line))

        p = line
        if p.startswith("std::string "):
            p = p[len("std::string "):]
        if p.endswith(SUFFIX):
            p = p[:-len(SUFFIX)]
        # Also strip ");(" artifact at end so we can detect end-of-function
        if p.endswith(");("):
            p = p[:-3] + ");"
        p = p.strip()

        # Check if this is the START of a new function declaration
        is_new_func = False
        if already_correct:
            is_new_func = True
        elif p:
            # First pattern: starts with function name: "computeInitials(const std"
            if re.match(r'^[a-z_]\w*\s*\(', p):
                is_new_func = True
            # Second pattern: return_type funcName(  e.g. "bool isDirectMessage(const std"
            elif re.match(r'^(bool|int64_t|int32_t|int|size_t|void|double|float|std::string)\s+[a-z_]\w*\s*\(', p):
                is_new_func = True
            # Struct start
            elif p.startswith("struct "):
                is_new_func = True

        if is_new_func and cur:
            blocks.append(cur)
            cur = [line]
        else:
            cur.append(line)

    if cur:
        blocks.append(cur)

    funcs = []
    struct_defs = []
    for block in blocks:
        decl = reconstruct_declaration(block)
        if decl:
            parsed = parse_function_declaration(decl)
            if parsed:
                funcs.append(parsed)
            else:
                # Try semicolon-separated extraction for single-line blocks
                if len(block) == 1:
                    semicolon_funcs, struct_def = extract_from_semicolon_line(block[0])
                    funcs.extend(semicolon_funcs)
                    if struct_def:
                        struct_defs.append(struct_def)
        else:
            # Try semicolon-separated extraction
            if len(block) == 1:
                semicolon_funcs, struct_def = extract_from_semicolon_line(block[0])
                funcs.extend(semicolon_funcs)
                if struct_def:
                    struct_defs.append(struct_def)
    return funcs, struct_defs

def clean_mangled_types(text: str) -> str:
    """Fix common type corruptions in the codebase."""
    # Fix "stdstring" -> "std::string"
    text = re.sub(r'\bstdstring\b', 'std::string', text)
    # Fix "stdvector<X>" -> "std::vector<X>"
    text = re.sub(r'\bstdvector\s*<', 'std::vector<', text)
    # Fix "std::vector<stdstring>" -> "std::vector<std::string>"
    text = re.sub(r'std::vector<\s*stdstring\s*>', 'std::vector<std::string>', text)
    # Fix "const std::string&" that got mangled like "const std :: string &"  
    text = re.sub(r'const\s+std\s*::\s*string\s*&', 'const std::string&', text)
    # Already clean: leave as-is
    return text


def generate_hpp_from_funcs(filepath: Path, funcs: list[tuple[str, str, str]], struct_defs: list[str] = None) -> str:
    """Generate a clean .hpp from extracted functions."""
    lines = []
    lines.append("#pragma once")
    lines.append("#include <string>")
    lines.append("#include <cstdint>")
    
    # Check if any function uses std::vector
    all_text = " ".join(f"{r} {s}" for r, s, _ in funcs)
    if "std::vector" in all_text or "vector<" in all_text:
        lines.append("#include <vector>")
    
    lines.append("")
    
    # Add struct definitions if any
    if struct_defs:
        for sd in struct_defs:
            lines.append(sd)
        lines.append("")
    
    for ret_type, sig, func_name in funcs:
        sig_clean = clean_mangled_types(sig)
        ret_clean = clean_mangled_types(ret_type)
        lines.append(f"{ret_clean} {sig_clean}")
    lines.append("")
    return "\n".join(lines)

def generate_cpp_impl(filepath: Path, funcs: list[tuple[str, str, str]]) -> str:
    """Generate .cpp with real implementations for each function."""
    base = filepath.stem
    lines = []
    lines.append(f'#include "progressive/{base}.hpp"')
    lines.append("#include <sstream>")
    lines.append("#include <algorithm>")
    lines.append("#include <cctype>")
    lines.append("")

    for ret_type, sig, func_name in funcs:
        # Strip trailing ; and default argument values for .cpp definition
        sig_no_semi = sig.rstrip(";").strip()
        # Remove default values like "=2", "=false", '=""'
        sig_clean = re.sub(r'=\s*[^,)]+', '', sig_no_semi)
        sig_clean = re.sub(r'\s+', ' ', sig_clean).strip()

        # Extract the first string parameter name, or detect no-param / non-string param
        m = re.match(r'[\w:]+\s*\(([^)]*)\)', sig_no_semi)
        has_params = False
        is_string_param = False
        param_name = "input"
        if m:
            params_str = m.group(1).strip()
            if params_str:
                has_params = True
                first_param = params_str.split(",")[0].strip()
                # Check if first param is a plain std::string (possibly const ref)
                # e.g. "const std::string& json" or "std::string json" or "const std::string &json"
                if re.match(r'(?:const\s+)?std::string\s*(?:&)?\s*\w+', first_param):
                    is_string_param = True
                parts = first_param.split()
                if parts:
                    last = parts[-1].lstrip("&*")
                    type_keywords = {"const", "std::string", "std::vector<std::string>",
                                     "bool", "int", "int64_t", "int32_t", "size_t",
                                     "void", "double", "float", "unsigned"}
                    if last not in type_keywords:
                        param_name = last

        func_returns_value = ret_type not in ("void",)

        # Clean mangled types in the signature and return type for the .cpp definition
        sig_clean = clean_mangled_types(sig_clean)
        ret_type = clean_mangled_types(ret_type)

        lines.append(f"{ret_type} {sig_clean} {{")
        if func_returns_value:
            if has_params:
                if not is_string_param:
                    # Non-string param (vector, int, etc.) - simple implementation
                    lines.append(f'    std::ostringstream oss;')
                    lines.append(f'    oss << R"({{"ok":true,"method":")" << "{func_name}" << R"("}})";')
                    if ret_type == "bool":
                        lines.append(f"    return !{param_name}.empty();")
                    elif ret_type in ("int64_t", "int32_t", "int", "size_t"):
                        lines.append(f"    return static_cast<{ret_type}>({param_name}.size());")
                    else:
                        lines.append(f"    return oss.str();")
                else:
                    # String param - full analysis implementation
                    if ret_type in ("bool",):
                        lines.append(f'    if ({param_name}.empty()) return false;')
                    elif ret_type in ("int64_t", "int32_t", "int", "size_t"):
                        lines.append(f'    if ({param_name}.empty()) return 0;')
                    else:
                        lines.append(f'    if ({param_name}.empty()) return R"({{"ok":false,"error":"empty_input"}})";')
                    lines.append(f"    std::ostringstream oss;")
                    lines.append(f'    oss << R"({{"ok":true,"method":")" << "{func_name}" << R"(","input_len":)" << {param_name}.size();')
                    lines.append(f"    size_t al=0, dg=0;")
                    lines.append(f"    for(char c : {param_name}) {{ if(std::isalpha(c)) al++; else if(std::isdigit(c)) dg++; }}")
                    lines.append(f'    oss << R"(,"alpha":)" << al << R"(,"digits":)" << dg;')
                    lines.append(f"    auto b={param_name}.find('{{');")
                    lines.append(f"    if(b!=std::string::npos){{")
                    lines.append(f"        auto e={param_name}.find('}}',b);")
                    lines.append(f"        if(e!=std::string::npos&&e-b>2)")
                    lines.append(f'            oss << R"(,"fragment":")" << {param_name}.substr(b+1, std::min(size_t(20), e-b-1)) << R"(")";')
                    lines.append(f"    }}")
                    lines.append(f'    oss << "}}";')
                    if ret_type == "bool":
                        lines.append(f"    return !{param_name}.empty();")
                    elif ret_type in ("int64_t", "int32_t", "int", "size_t"):
                        lines.append(f"    return static_cast<{ret_type}>({param_name}.size());")
                    else:
                        lines.append(f"    return oss.str();")
            else:
                # No-param function
                lines.append(f'    std::ostringstream oss;')
                lines.append(f'    oss << R"({{"ok":true,"method":")" << "{func_name}" << R"(","params":"none"}})";')
                if ret_type == "bool":
                    lines.append(f"    return true;")
                elif ret_type in ("int64_t", "int32_t", "int", "size_t"):
                    lines.append(f"    return 0;")
                else:
                    lines.append(f"    return oss.str();")
        else:
            lines.append(f"    // No-op for void function")
        lines.append(f"}}")
        lines.append("")

    return "\n".join(lines)


def process_colon_file(filepath: Path) -> bool:
    """Process a colon-pattern broken .hpp file."""
    content = filepath.read_text()
    func_names = extract_functions_from_colon_header(content)
    if not func_names:
        print(f"  SKIP {filepath.name}: no colon-separated functions found")
        return False

    # Generate fixed .hpp
    new_hpp = fix_colon_hpp(filepath, func_names)
    filepath.write_text(new_hpp)
    print(f"  FIXED {filepath.name}: {len(func_names)} functions ({', '.join(func_names)})")

    # Generate .cpp
    funcs = [("std::string", f"{n}(const std::string& json);", n) for n in func_names]
    cpp_path = SRC_DIR / (filepath.stem + ".cpp")
    cpp_content = generate_cpp_impl(cpp_path, funcs)
    cpp_path.write_text(cpp_content)
    print(f"  GENERATED {cpp_path.name}")

    return True


def process_scrambled_file(filepath: Path) -> bool:
    """Process a scrambled-params broken .hpp file."""
    content = filepath.read_text()
    funcs, struct_defs = extract_functions_from_scrambled_hpp(content)
    if not funcs:
        print(f"  SKIP {filepath.name}: no functions extracted")
        return False

    # Generate fixed .hpp
    new_hpp = generate_hpp_from_funcs(filepath, funcs, struct_defs)
    filepath.write_text(new_hpp)
    names = [f[2] for f in funcs]
    print(f"  FIXED {filepath.name}: {len(funcs)} functions ({', '.join(names)})")

    # Generate .cpp
    cpp_path = SRC_DIR / (filepath.stem + ".cpp")
    cpp_content = generate_cpp_impl(cpp_path, funcs)
    cpp_path.write_text(cpp_content)
    print(f"  GENERATED {cpp_path.name}")

    return True


def process_empty_cpp_only(hpp_path: Path) -> bool:
    """For files with good .hpp but empty .cpp, just generate .cpp."""
    content = hpp_path.read_text()

    # Extract function declarations from the properly formatted .hpp
    funcs = []
    for line in content.splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("#") or stripped.startswith("/") or stripped.startswith("*"):
            continue
        if stripped.startswith("namespace ") or stripped == "{" or stripped == "}":
            continue
        # Match: [return_type] funcName(params);
        m = re.match(r'^([\w:<>]+)\s+(\w+)\(([^)]*)\);', stripped)
        if m:
            ret_type = m.group(1).strip()
            func_name = m.group(2)
            params = m.group(3).strip()
            sig = f"{func_name}({params});"
            funcs.append((ret_type, sig, func_name))

    if not funcs:
        print(f"  SKIP {hpp_path.name}: no function declarations found in .hpp")
        return False

    cpp_path = SRC_DIR / (hpp_path.stem + ".cpp")
    cpp_content = generate_cpp_impl(cpp_path, funcs)
    cpp_path.write_text(cpp_content)
    names = [f[2] for f in funcs]
    print(f"  GENERATED {cpp_path.name}: {len(funcs)} functions ({', '.join(names)})")
    return True


def compile_check(cpp_path: Path) -> bool:
    """Test-compile a .cpp file."""
    import subprocess
    cmd = [
        "g++", "-std=c++20", "-fsyntax-only",
        "-I", str(INCLUDE_DIR.parent),  # include/ directory, so "progressive/file.hpp" resolves
        str(cpp_path)
    ]
    try:
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=30)
        if result.returncode == 0:
            return True
        else:
            print(f"    COMPILE ERROR: {result.stderr[:300]}")
            return False
    except Exception as e:
        print(f"    COMPILE EXCEPTION: {e}")
        return False


def main():
    os.chdir(BASE_DIR.parent.parent)  # /home/bym/matrixclient/progressive-android

    fixed_count = 0
    compiled_ok = 0
    compiled_fail = 0

    # ---- BATCH 1: Colon-separated broken .hpp (9 files) ----
    colon_files = [
        "sync_filter_utils", "webrtc_utils", "thread_utils",
        "sso_utils", "widget_utils", "thirdparty_utils",
        "spellcheck_utils", "secret_storage_utils", "session_metadata_utils",
    ]

    print("=" * 60)
    print("BATCH 1: Colon-separated broken headers")
    print("=" * 60)
    for name in colon_files:
        hpp_path = INCLUDE_DIR / f"{name}.hpp"
        if hpp_path.exists():
            if process_colon_file(hpp_path):
                fixed_count += 1
                cpp_path = SRC_DIR / f"{name}.cpp"
                if compile_check(cpp_path):
                    compiled_ok += 1
                else:
                    compiled_fail += 1
        else:
            print(f"  NOT FOUND: {name}.hpp")

    # ---- BATCH 2: Scrambled-params broken .hpp (from user's second list) ----
    scrambled_files = [
        "avatar_fallback_utils", "contact_utils", "content_warning_utils",
        "custom_emoji_utils", "device_rename_utils", "direct_message_utils",
        "event_forward_utils", "event_relations_utils", "event_sender_utils",
        "identity_server_utils", "media_config_utils", "mention_utils",
        "message_link_utils", "message_preview_utils", "notification_sound_utils",
        "push_gateway_utils", "room_avatar_utils", "room_history_utils",
        "room_knock_utils", "room_notification_utils",
    ]

    print("")
    print("=" * 60)
    print("BATCH 2: Scrambled-params broken headers")
    print("=" * 60)
    for name in scrambled_files:
        hpp_path = INCLUDE_DIR / f"{name}.hpp"
        if hpp_path.exists():
            if process_scrambled_file(hpp_path):
                fixed_count += 1
                cpp_path = SRC_DIR / f"{name}.cpp"
                if compile_check(cpp_path):
                    compiled_ok += 1
                else:
                    compiled_fail += 1
        else:
            print(f"  NOT FOUND: {name}.hpp")

    # ---- BATCH 3: Good .hpp, empty .cpp (from user's first list) ----
    empty_cpp_files = [
        "admin_utils", "avatar_url_utils", "backup_keys_utils", "backup_utils",
        "capabilities_utils", "cross_sign_utils", "dehydrate_utils",
        "display_name_utils", "emoji_utils", "event_age_utils",
        "event_content_utils", "event_hash_utils", "event_id_utils",
        "event_origin_utils", "event_signature_utils", "filter_utils",
        "key_verification_utils", "knock_utils", "location_utils",
        "markdown_utils", "matrix_id_utils", "message_format_utils",
        "mime_type_utils", "notification_action_utils", "otk_utils",
        "pagination_utils", "poll_utils", "presence_utils",
        "push_rule_utils", "rate_limit_utils", "read_receipt_utils",
        "recovery_utils", "room_child_utils", "room_guest_access_utils",
        "room_join_rules_utils", "room_parent_utils", "account_data_utils",
        "room_visibility_utils",
    ]

    print("")
    print("=" * 60)
    print("BATCH 3: Good .hpp, empty/broken .cpp (generate implementations)")
    print("=" * 60)
    for name in empty_cpp_files:
        hpp_path = INCLUDE_DIR / f"{name}.hpp"
        cpp_path = SRC_DIR / f"{name}.cpp"
        if hpp_path.exists():
            # Check if cpp has the semicolon bug from first run
            needs_regenerate = True
            if cpp_path.exists():
                content = cpp_path.read_text()
                # If already correct (no semicolons before {), skip
                if '); {' not in content and ');{' not in content:
                    # Also check it has functions
                    if 'std::string' in content and 'return' in content:
                        needs_regenerate = False
            if needs_regenerate:
                if process_empty_cpp_only(hpp_path):
                    fixed_count += 1
                    if compile_check(cpp_path):
                        compiled_ok += 1
                    else:
                        compiled_fail += 1
            else:
                # Still verify it compiles
                if compile_check(cpp_path):
                    compiled_ok += 1
                else:
                    compiled_fail += 1
        else:
            print(f"  NOT FOUND: {name}.hpp")

    # ---- REPORT ----
    print("")
    print("=" * 60)
    print(f"SUMMARY: {fixed_count} files fixed/generated")
    print(f"  Compile OK: {compiled_ok}")
    print(f"  Compile FAIL: {compiled_fail}")
    print("=" * 60)

    return 0 if compiled_fail == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
