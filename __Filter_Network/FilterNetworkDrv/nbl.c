#include "precomp.h"

// PACKETS RECEIVED XXXXXXXXXXXXXXXXX
_Use_decl_annotations_
VOID
FilterReceiveNetBufferLists(
    NDIS_HANDLE         FilterModuleContext,
    PNET_BUFFER_LIST    NetBufferLists,
    NDIS_PORT_NUMBER    PortNumber,
    ULONG               NumberOfNetBufferLists,
    ULONG               ReceiveFlags
)
/*++
    If provided, this function processes receive indications made by underlying
    NIC or lower level filter drivers. This function  can also be called as a
    result of loopback. If this handler is NULL, NDIS will skip calling this
    filter when processing a receive indication and will call the next higher
    driver in the stack. A filter that doesn't provide a
    FilterReceiveNetBufferLists handler cannot provide a
    FilterReturnNetBufferLists handler and cannot a initiate an original receive
    indication on its own.

    FilterModuleContext      - our filter context area.
    NetBufferLists           - a linked list of NetBufferLists
    PortNumber               - Port on which the receive is indicated
    ReceiveFlags             -

N.B.: It is important to check the ReceiveFlags in NDIS_TEST_RECEIVE_CANNOT_PEND.
    This controls whether the receive indication is an synchronous or
    asynchronous function call.
--*/
{

    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    BOOLEAN             DispatchLevel;
    ULONG               Ref;
    BOOLEAN             bFalse = FALSE;
#if DBG
    ULONG               ReturnFlags;
#endif

    //DbgPrint("NDIS \t===>ReceiveNetBufferList: NetBufferLists = %p.\n", NetBufferLists);
    do {
        DispatchLevel = NDIS_TEST_RECEIVE_AT_DISPATCH_LEVEL(ReceiveFlags);
#if DBG
        FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
        if (pFilter->State != FilterRunning) {
            FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
            if (NDIS_TEST_RECEIVE_CAN_PEND(ReceiveFlags)) {
                ReturnFlags = 0;
                if (NDIS_TEST_RECEIVE_AT_DISPATCH_LEVEL(ReceiveFlags)) {
                    NDIS_SET_RETURN_FLAG(ReturnFlags, NDIS_RETURN_FLAGS_DISPATCH_LEVEL);
                }
                NdisFReturnNetBufferLists(pFilter->FilterHandle, NetBufferLists, ReturnFlags);
            }
            break;
        }
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
#endif

        ASSERT(NumberOfNetBufferLists >= 1);

        // If you would like to drop a received packet, then you must carefully
        // modify the NBL chain as follows:
        //
        //     if NDIS_TEST_RECEIVE_CANNOT_PEND(ReceiveFlags):
        //         For each NBL that is NOT dropped, temporarily unlink it from
        //         the linked list, and indicate it up alone with 
        //         NdisFIndicateReceiveNetBufferLists and the
        //         NDIS_RECEIVE_FLAGS_RESOURCES flag set.  Then immediately
        //         relink the NBL back into the chain.  When all NBLs have been
        //         indicated up, you may return from this function.
        //     otherwise (NDIS_TEST_RECEIVE_CANNOT_PEND is FALSE):
        //         Divide the linked list of NBLs into two chains: one chain
        //         of packets to drop, and everything else in another chain.
        //         Return the first chain with NdisFReturnNetBufferLists, and
        //         indicate up the rest with NdisFIndicateReceiveNetBufferLists.
        //
        // Note: on the receive path for Ethernet packets, one NBL will have 
        // exactly one NB.  So (assuming you are receiving on Ethernet, or are 
        // attached above Native WiFi) you do not need to worry about dropping
        // one NB, but trying to indicate up the remaining NBs on the same NBL.
        // In other words, if the first NB should be dropped, drop the whole NBL.
        
        // If you would like to modify a packet, and can do so quickly, you may
        // do it here.  However, make sure you save enough information to undo
        // your modification in the FilterReturnNetBufferLists handler.

        // If necessary, queue the NetBufferLists in a local structure for later
        // processing.  However, do not queue them for "too long", or else the
        // system's performance may be degraded.  If you need to hold onto an
        // NBL for an unbounded amount of time, then allocate memory, perform a
        // deep copy, and return the original NBL.

        /// My++
        
        PNET_BUFFER_LIST nbl_ptr = NetBufferLists;
        PNET_BUFFER_LIST nbl_drop_ptrbeg = NULL;
        PNET_BUFFER_LIST nbl_keep_ptrbeg = NULL;
        PNET_BUFFER_LIST nbl_drop_ptr = nbl_drop_ptrbeg;
        PNET_BUFFER_LIST nbl_keep_ptr = nbl_keep_ptrbeg;
        ULONG               NumberOfKeepedLists = 0;

        if (NDIS_TEST_RECEIVE_CANNOT_PEND(ReceiveFlags)) {
            DbgPrint("NDIS: NDIS_TEST_RECEIVE_CANNOT_PEND\n");

            while (nbl_ptr != NULL) {
                DbgPrint("NDIS: \tinspect_list\n");
                BOOLEAN drop = inspect_list(nbl_ptr);
                if (!drop) {
                    PNET_BUFFER_LIST oldnbl_ptr = NET_BUFFER_LIST_NEXT_NBL(nbl_ptr);
                    nbl_ptr->Next = NULL;
                    NdisFReturnNetBufferLists(pFilter->FilterHandle, nbl_ptr, NDIS_RECEIVE_FLAGS_RESOURCES);
                    nbl_ptr->Next = oldnbl_ptr;
                }
                nbl_ptr = NET_BUFFER_LIST_NEXT_NBL(nbl_ptr);
            }

        } else {

            DbgPrint("NDIS: NOT NDIS_TEST_RECEIVE_CANNOT_PEND\n");
            
            while (nbl_ptr != NULL) {
            
                DbgPrint("NDIS: \tinspect_list\n");
                
                BOOLEAN drop = inspect_list(nbl_ptr);
                if(drop){

                    DbgPrint("NDIS: \t\tdrop\n");
                    
                    if(nbl_drop_ptrbeg == NULL){
                        DbgPrint("NDIS: \t\t\tnbl_drop_ptrbeg == NULL\n");
                        nbl_drop_ptrbeg = nbl_ptr;
                        PNET_BUFFER_LIST oldnbl_ptr = NET_BUFFER_LIST_NEXT_NBL(nbl_ptr);
                        nbl_drop_ptr = nbl_drop_ptrbeg;
                        //nbl_drop_ptr->Next = NULL;
                        nbl_ptr = oldnbl_ptr;
                        continue;
                    } else {
                        DbgPrint("NDIS: \t\t\tnbl_drop_ptrbeg != NULL\n");
                        nbl_drop_ptr->Next = nbl_ptr;
                        nbl_drop_ptr = nbl_drop_ptr->Next;
                        PNET_BUFFER_LIST oldnbl_ptr = NET_BUFFER_LIST_NEXT_NBL(nbl_ptr);
                        //nbl_drop_ptr->Next = NULL;
                        nbl_ptr = oldnbl_ptr;
                        continue;
                    }

                } else {
                    DbgPrint("NDIS: \t\tkeep\n");
                    NumberOfKeepedLists++;
                    if (nbl_keep_ptrbeg == NULL) {
                        DbgPrint("NDIS: \t\t\tnbl_keep_ptrbeg == NULL\n");
                        nbl_keep_ptrbeg = nbl_ptr;
                        PNET_BUFFER_LIST oldnbl_ptr = NET_BUFFER_LIST_NEXT_NBL(nbl_ptr);
                        nbl_keep_ptr = nbl_keep_ptrbeg;
                        //nbl_keep_ptr->Next = NULL;
                        nbl_ptr = oldnbl_ptr;
                        continue;
                    } else {
                        DbgPrint("NDIS: \t\t\tnbl_keep_ptrbeg != NULL\n");
                        nbl_keep_ptr->Next = nbl_ptr;
                        nbl_keep_ptr = nbl_keep_ptr->Next;
                        PNET_BUFFER_LIST oldnbl_ptr = NET_BUFFER_LIST_NEXT_NBL(nbl_ptr);
                        //nbl_keep_ptr->Next = NULL;
                        nbl_ptr = oldnbl_ptr;
                        continue;
                    }
                }
            }
            
            if (nbl_drop_ptrbeg) {
                DbgPrint("NDIS: NdisFReturnNetBufferLists\n");
                NdisFReturnNetBufferLists(pFilter->FilterHandle, nbl_drop_ptrbeg, ReceiveFlags);
            }
            if (nbl_keep_ptrbeg) {
                DbgPrint("NDIS: NdisFIndicateReceiveNetBufferLists pn= %d, nofkl= %d\n", (ULONG)PortNumber, NumberOfKeepedLists);
                NdisFIndicateReceiveNetBufferLists(pFilter->FilterHandle, nbl_keep_ptrbeg, PortNumber, NumberOfKeepedLists, ReceiveFlags);
            }
        }

        /// My--

        if (pFilter->TrackReceives) {
            FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
            pFilter->OutstandingRcvs += NumberOfNetBufferLists;
            Ref = pFilter->OutstandingRcvs;

            FILTER_LOG_RCV_REF(1, pFilter, NetBufferLists, Ref);
            FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
        }

        //NdisFIndicateReceiveNetBufferLists(
        //    pFilter->FilterHandle,
        //    NetBufferLists,
        //    PortNumber,
        //    NumberOfNetBufferLists,
        //    ReceiveFlags);

        //DbgPrint("NDIS \t pn=%d, nofnbl=%d.\n", PortNumber, NumberOfNetBufferLists);

        if (NDIS_TEST_RECEIVE_CANNOT_PEND(ReceiveFlags) && pFilter->TrackReceives) {
            FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
            pFilter->OutstandingRcvs -= NumberOfNetBufferLists;
            Ref = pFilter->OutstandingRcvs;
            FILTER_LOG_RCV_REF(2, pFilter, NetBufferLists, Ref);
            FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
        }

    } while (bFalse);

    //DbgPrint("NDIS \t<===ReceiveNetBufferList: Flags = %8x.\n", ReceiveFlags);
}

_Use_decl_annotations_
VOID
FilterReturnNetBufferLists(
    NDIS_HANDLE         FilterModuleContext,
    PNET_BUFFER_LIST    NetBufferLists,
    ULONG               ReturnFlags
)
/*++
    If provided, NDIS calls FilterReturnNetBufferLists to return the ownership of one or more NetBufferLists
    and their embedded NetBuffers to the filter driver. If this handler is NULL, NDIS
    will skip calling this filter when returning NetBufferLists to the underlying
    miniport and will call the next lower driver in the stack. A filter that doesn't
    provide a FilterReturnNetBufferLists handler cannot originate a receive indication
    on its own.

    FilterInstanceContext       - our filter context area
    NetBufferLists              - a linked list of NetBufferLists that this
                                  filter driver indicated in a previous call to
                                  NdisFIndicateReceiveNetBufferLists
    ReturnFlags                 - flags specifying if the caller is at DISPATCH_LEVEL
--*/
{
    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    PNET_BUFFER_LIST    CurrNbl = NetBufferLists;
    UINT                NumOfNetBufferLists = 0;
    BOOLEAN             DispatchLevel;
    ULONG               Ref;

    //DbgPrint("NDIS \t===>ReturnNetBufferLists, NetBufferLists is %p.\n", NetBufferLists);

    // If your filter injected any receive packets into the datapath to be
    // received, you must identify their NBLs here and remove them from the 
    // chain.  Do not attempt to receive-return your NBLs down to the lower
    // layer.

    // If your filter has modified any NBLs (or NBs, MDLs, etc) in your
    // FilterReceiveNetBufferLists handler, you must undo the modifications here.
    // In general, NBLs must be returned in the same condition in which you had
    // you received them.  (Exceptions: the NBLs can be re-ordered on the linked
    // list, and the scratch fields are don't-care).
    if (pFilter->TrackReceives) {
        while (CurrNbl) {
            NumOfNetBufferLists++;
            CurrNbl = NET_BUFFER_LIST_NEXT_NBL(CurrNbl);
        }
    }

    // Return the received NBLs.  If you removed any NBLs from the chain, make
    // sure the chain isn't empty (i.e., NetBufferLists!=NULL).

    NdisFReturnNetBufferLists(pFilter->FilterHandle, NetBufferLists, ReturnFlags);

    if (pFilter->TrackReceives) {
        DispatchLevel = NDIS_TEST_RETURN_AT_DISPATCH_LEVEL(ReturnFlags);
        FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);

        pFilter->OutstandingRcvs -= NumOfNetBufferLists;
        Ref = pFilter->OutstandingRcvs;
        FILTER_LOG_RCV_REF(3, pFilter, NetBufferLists, Ref);
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
    }

    //DbgPrint("NDIS \t<===ReturnNetBufferLists.\n");
}

// PACKETS SENT XXXXXXXXXXXXXXXXX
_Use_decl_annotations_
VOID
FilterSendNetBufferLists(
    NDIS_HANDLE         FilterModuleContext,
    PNET_BUFFER_LIST    NetBufferLists,
    NDIS_PORT_NUMBER    PortNumber,
    ULONG               SendFlags
)
/*++
    If provided, NDIS will call this function to transmit a linked list of NetBuffers, described by a
    NetBufferList, over the network. If this handler is NULL, NDIS will skip calling
    this filter when sending a NetBufferList and will call the next lower
    driver in the stack.  A filter that doesn't provide a FilerSendNetBufferList
    handler can not originate a send on its own.

    FilterModuleContext     - our filter context area
    NetBufferLists          - a List of NetBufferLists to send
    PortNumber              - Port Number to which this send is targeted
    SendFlags               - specifies if the call is at DISPATCH_LEVEL
--*/
{
    PMS_FILTER          pFilter = (PMS_FILTER)FilterModuleContext;
    PNET_BUFFER_LIST    CurrNbl;
    BOOLEAN             DispatchLevel;
    BOOLEAN             bFalse = FALSE;

    //DbgPrint("NDIS \t===>SendNetBufferList: NBL = %p.\n", NetBufferLists);

    do {

        DispatchLevel = NDIS_TEST_SEND_AT_DISPATCH_LEVEL(SendFlags);
#if DBG
        // we should never get packets to send if we are not in running state
        FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);

        // If the filter is not in running state, fail the send
        if (pFilter->State != FilterRunning) {
            FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);

            CurrNbl = NetBufferLists;
            while (CurrNbl) {
                NET_BUFFER_LIST_STATUS(CurrNbl) = NDIS_STATUS_PAUSED;
                CurrNbl = NET_BUFFER_LIST_NEXT_NBL(CurrNbl);
            }
            NdisFSendNetBufferListsComplete(pFilter->FilterHandle,
                NetBufferLists,
                DispatchLevel ? NDIS_SEND_COMPLETE_FLAGS_DISPATCH_LEVEL : 0);
            break;
        }
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
#endif
        if (pFilter->TrackSends) {
            FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
            CurrNbl = NetBufferLists;
            while (CurrNbl) {
                pFilter->OutstandingSends++;
                FILTER_LOG_SEND_REF(1, pFilter, CurrNbl, pFilter->OutstandingSends);

                CurrNbl = NET_BUFFER_LIST_NEXT_NBL(CurrNbl);
            }
            FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
        }

        // If necessary, queue the NetBufferLists in a local structure for later
        // processing.  However, do not queue them for "too long", or else the
        // system's performance may be degraded.  If you need to hold onto an
        // NBL for an unbounded amount of time, then allocate memory, perform a
        // deep copy, and complete the original NBL.

        NdisFSendNetBufferLists(pFilter->FilterHandle, NetBufferLists, PortNumber, SendFlags);


    } while (bFalse);

    //DbgPrint("NDIS \t<===SendNetBufferList. \n");
}

_Use_decl_annotations_
VOID
FilterSendNetBufferListsComplete(
    NDIS_HANDLE         FilterModuleContext,
    PNET_BUFFER_LIST    NetBufferLists,
    ULONG               SendCompleteFlags
)
/*++
    Send complete handler

    This routine is invoked whenever the lower layer is finished processing
    sent NET_BUFFER_LISTs.  If the filter does not need to be involved in the
    send path, you should remove this routine and the FilterSendNetBufferLists
    routine.  NDIS will pass along send packets on behalf of your filter more
    efficiently than the filter can.

    FilterModuleContext     - our filter context
    NetBufferLists          - a chain of NBLs that are being returned to you
    SendCompleteFlags       - flags (see documentation)
--*/
{
    PMS_FILTER         pFilter = (PMS_FILTER)FilterModuleContext;
    ULONG              NumOfSendCompletes = 0;
    BOOLEAN            DispatchLevel;
    PNET_BUFFER_LIST   CurrNbl;

    //DbgPrint("NDIS \t===>SendNBLComplete, NetBufferList: %p.\n", NetBufferLists);

    // If your filter injected any send packets into the datapath to be sent,
    // you must identify their NBLs here and remove them from the chain.  Do not
    // attempt to send-complete your NBLs up to the higher layer.

    // If your filter has modified any NBLs (or NBs, MDLs, etc) in your
    // FilterSendNetBufferLists handler, you must undo the modifications here.
    // In general, NBLs must be returned in the same condition in which you had
    // you received them.  (Exceptions: the NBLs can be re-ordered on the linked
    // list, and the scratch fields are don't-care).

    if (pFilter->TrackSends) {
        CurrNbl = NetBufferLists;
        while (CurrNbl) {
            NumOfSendCompletes++;
            CurrNbl = NET_BUFFER_LIST_NEXT_NBL(CurrNbl);

        }
        DispatchLevel = NDIS_TEST_SEND_AT_DISPATCH_LEVEL(SendCompleteFlags);
        FILTER_ACQUIRE_LOCK(&pFilter->Lock, DispatchLevel);
        pFilter->OutstandingSends -= NumOfSendCompletes;
        FILTER_LOG_SEND_REF(2, pFilter, PrevNbl, pFilter->OutstandingSends);
        FILTER_RELEASE_LOCK(&pFilter->Lock, DispatchLevel);
    }

    // Send complete the NBLs.  If you removed any NBLs from the chain, make
    // sure the chain isn't empty (i.e., NetBufferLists!=NULL).

    NdisFSendNetBufferListsComplete(pFilter->FilterHandle, NetBufferLists, SendCompleteFlags);

    //DbgPrint("NDIS \t<===SendNBLComplete.\n");
}

_Use_decl_annotations_
VOID
FilterCancelSendNetBufferLists(
    NDIS_HANDLE             FilterModuleContext,
    PVOID                   CancelId
)
/*++
    This function cancels any NET_BUFFER_LISTs pended in the filter and then
    calls the NdisFCancelSendNetBufferLists to propagate the cancel operation.

    If your driver does not queue any send NBLs, you may omit this routine.
    NDIS will propagate the cancelation on your behalf more efficiently.

    FilterModuleContext      - our filter context area.
    CancelId                 - an identifier for all NBLs that should be dequeued
*/
{
    PMS_FILTER  pFilter = (PMS_FILTER)FilterModuleContext;
    NdisFCancelSendNetBufferLists(pFilter->FilterHandle, CancelId);
}


#pragma region OTHER
//if (cannot_pend) {
//    while (list) {
//        Discard = ....
//
//            if !Discard
//                NdisFIndicateReceiveNetBufferLists
//    }
//} else {
//    while (list) {
//        Discard = ....
//
//            ListToKeep...
//            ListToDrop....
//    }
//
//    NdisFIndicateReceiveNetBufferLists(ListToKeep
//        NdisFReturnNetBufferLists(ListToDrop
//}
#pragma endregion