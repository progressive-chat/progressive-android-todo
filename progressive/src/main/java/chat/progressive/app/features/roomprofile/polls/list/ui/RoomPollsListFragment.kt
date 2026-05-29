/*
 * Copyright 2023, 2024 Progressive Chat
 *
 * SPDX-License-Identifier: AGPL-3.0-only OR LicenseRef-Progressive
 * Please see LICENSE files in the repository root for full details.
 */

package chat.progressive.app.features.roomprofile.polls.list.ui

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.core.view.isVisible
import com.airbnb.mvrx.parentFragmentViewModel
import com.airbnb.mvrx.withState
import chat.progressive.app.core.epoxy.onClick
import chat.progressive.app.core.extensions.cleanup
import chat.progressive.app.core.extensions.configureWith
import chat.progressive.app.core.platform.ProgressiveFragment
import chat.progressive.app.core.resources.StringProvider
import chat.progressive.app.databinding.FragmentRoomPollsListBinding
import chat.progressive.app.features.roomprofile.polls.RoomPollsAction
import chat.progressive.app.features.roomprofile.polls.RoomPollsLoadingError
import chat.progressive.app.features.roomprofile.polls.RoomPollsType
import chat.progressive.app.features.roomprofile.polls.RoomPollsViewEvent
import chat.progressive.app.features.roomprofile.polls.RoomPollsViewModel
import chat.progressive.app.features.roomprofile.polls.RoomPollsViewState
import javax.inject.Inject

abstract class RoomPollsListFragment :
        ProgressiveFragment<FragmentRoomPollsListBinding>(),
        RoomPollsController.Listener {

    @Inject
    lateinit var roomPollsController: RoomPollsController

    @Inject
    lateinit var stringProvider: StringProvider

    @Inject
    lateinit var viewNavigator: RoomPollsListNavigator

    private val viewModel: RoomPollsViewModel by parentFragmentViewModel(RoomPollsViewModel::class)

    override fun getBinding(inflater: LayoutInflater, container: ViewGroup?): FragmentRoomPollsListBinding {
        return FragmentRoomPollsListBinding.inflate(inflater, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        observeViewEvents()
        setupList()
        setupLoadMoreButton()
    }

    private fun observeViewEvents() {
        viewModel.observeViewEvents { viewEvent ->
            when (viewEvent) {
                RoomPollsViewEvent.LoadingError -> showErrorInSnackbar(RoomPollsLoadingError())
            }
        }
    }

    abstract fun getEmptyListTitle(canLoadMore: Boolean, nbLoadedDays: Int): String

    abstract fun getRoomPollsType(): RoomPollsType

    private fun setupList() = withState(viewModel) { viewState ->
        roomPollsController.listener = this
        views.roomPollsList.configureWith(roomPollsController)
        views.roomPollsEmptyTitle.text = getEmptyListTitle(
                canLoadMore = viewState.canLoadMore,
                nbLoadedDays = viewState.nbSyncedDays,
        )
    }

    private fun setupLoadMoreButton() {
        views.roomPollsLoadMoreWhenEmpty.onClick {
            onLoadMoreClicked()
        }
    }

    override fun onDestroyView() {
        cleanUpList()
        super.onDestroyView()
    }

    private fun cleanUpList() {
        views.roomPollsList.cleanup()
        roomPollsController.listener = null
    }

    override fun invalidate() = withState(viewModel) { viewState ->
        val filteredPolls = when (getRoomPollsType()) {
            RoomPollsType.ACTIVE -> viewState.polls.filterIsInstance(PollSummary.ActivePoll::class.java)
            RoomPollsType.ENDED -> viewState.polls.filterIsInstance(PollSummary.EndedPoll::class.java)
        }
        val updatedViewState = viewState.copy(polls = filteredPolls)
        renderList(updatedViewState)
        renderSyncingView(updatedViewState)
    }

    private fun renderSyncingView(viewState: RoomPollsViewState) {
        views.roomPollsSyncingTitle.isVisible = viewState.isSyncing
        views.roomPollsSyncingProgress.isVisible = viewState.isSyncing
    }

    private fun renderList(viewState: RoomPollsViewState) {
        roomPollsController.setData(viewState)
        views.roomPollsEmptyTitle.text = getEmptyListTitle(
                canLoadMore = viewState.canLoadMore,
                nbLoadedDays = viewState.nbSyncedDays,
        )
        views.roomPollsEmptyTitle.isVisible = !viewState.isSyncing && viewState.hasNoPolls()
        views.roomPollsLoadMoreWhenEmpty.isVisible = viewState.hasNoPollsAndCanLoadMore()
        views.roomPollsLoadMoreWhenEmpty.isEnabled = !viewState.isLoadingMore
        views.roomPollsLoadMoreWhenEmptyProgress.isVisible = viewState.hasNoPollsAndCanLoadMore() && viewState.isLoadingMore
    }

    override fun onPollClicked(pollId: String) = withState(viewModel) {
        viewNavigator.goToPollDetails(
                context = requireContext(),
                pollId = pollId,
                roomId = it.roomId,
                isEnded = getRoomPollsType() == RoomPollsType.ENDED,
        )
    }

    override fun onLoadMoreClicked() {
        viewModel.handle(RoomPollsAction.LoadMorePolls)
    }
}
