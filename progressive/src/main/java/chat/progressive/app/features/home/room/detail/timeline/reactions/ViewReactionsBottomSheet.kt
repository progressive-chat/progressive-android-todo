/*
 * Copyright 2019-2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.home.room.detail.timeline.reactions

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.airbnb.mvrx.fragmentViewModel
import com.airbnb.mvrx.withState
import dagger.hilt.android.AndroidEntryPoint
import chat.progressive.app.R
import chat.progressive.app.core.extensions.cleanup
import chat.progressive.app.core.extensions.configureWith
import chat.progressive.app.core.platform.ProgressiveBottomSheet
import chat.progressive.app.databinding.BottomSheetGenericListWithTitleBinding
import chat.progressive.app.features.home.room.detail.timeline.action.EventSharedAction
import chat.progressive.app.features.home.room.detail.timeline.action.MessageSharedActionViewModel
import chat.progressive.app.features.home.room.detail.timeline.action.TimelineEventFragmentArgs
import chat.progressive.app.features.home.room.detail.timeline.item.MessageInformationData
import chat.progressive.lib.strings.CommonStrings
import javax.inject.Inject

/**
 * Bottom sheet displaying list of reactions for a given event ordered by timestamp.
 */
@AndroidEntryPoint
class ViewReactionsBottomSheet :
        ProgressiveBottomSheet<BottomSheetGenericListWithTitleBinding>(),
        ViewReactionsEpoxyController.Listener {

    private val viewModel: ViewReactionsViewModel by fragmentViewModel(ViewReactionsViewModel::class)

    private lateinit var sharedActionViewModel: MessageSharedActionViewModel

    @Inject lateinit var epoxyController: ViewReactionsEpoxyController

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): BottomSheetGenericListWithTitleBinding {
        return BottomSheetGenericListWithTitleBinding.inflate(inflater, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        sharedActionViewModel = activityViewModelProvider.get(MessageSharedActionViewModel::class.java)
        views.bottomSheetRecyclerView.configureWith(
                epoxyController,
                hasFixedSize = false,
                dividerDrawable = R.drawable.divider_horizontal_on_secondary
        )
        views.bottomSheetTitle.text = context?.getString(CommonStrings.reactions)
        epoxyController.listener = this
    }

    override fun onDestroyView() {
        views.bottomSheetRecyclerView.cleanup()
        epoxyController.listener = null
        super.onDestroyView()
    }

    override fun didSelectUser(userId: String) {
        sharedActionViewModel.post(EventSharedAction.OpenUserProfile(userId))
    }

    override fun invalidate() = withState(viewModel) {
        epoxyController.setData(it)
        super.invalidate()
    }

    companion object {
        fun newInstance(roomId: String, informationData: MessageInformationData): ViewReactionsBottomSheet {
            return ViewReactionsBottomSheet().apply {
                setArguments(
                        TimelineEventFragmentArgs(
                                eventId = informationData.eventId,
                                roomId = roomId,
                                informationData = informationData
                        )
                )
            }
        }
    }
}
