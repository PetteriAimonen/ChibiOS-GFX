/*
    ChibiOS/GFX - Copyright (C) 2012, 2013
                 Joel Bodenmann aka Tectu <joel@unormal.org>

    This file is part of ChibiOS/GFX.

    ChibiOS/GFX is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/GFX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file    include/gqueue/gqueue.h
 * @brief   GQUEUE header file.
 *
 * @addtogroup GQUEUE
 * @brief	GQUEUE provides queue management. There are 3 types of queues:
 * 			<ul><li><b>Asynchronous Queues (ASync) </b> - Queue operations never block</li>
 * 				<li><b>Get Synchronous Queues (GSync) </b> - Queue Get operations block until something is placed in the Queue</li>
 * 				<li><b>Put Synchronous Queues (PSync)</b> - Queue Put operations block until the element is removed from the Queue</li>
 * 				<li><b>Fully Synchronous Queues (FSync)</b> - Queue GET and Put operations block</li>
 * 			</ul>
 * 			We need 4 types of queues even though fully synchronous queues support all operations including asynchronous
 * 			operations because fully synchronous queues have the highest storage requirements. The other queue types are
 * 			optimizations. Efficiency IS important to use (particularly RAM efficiency).
 * 			In practice we only implement ASync, GSync and FSync queues as PSync queues are of dubious value.
 * @{
 */

#ifndef _GQUEUE_H
#define _GQUEUE_H

#if GFX_USE_GQUEUE || defined(__DOXYGEN__)

/**
 * @brief	A queue
 * @{
 */
typedef struct gfxQueueASync {
	struct gfxQueueASyncItem	*head;
	struct gfxQueueASyncItem	*tail;
	} gfxQueueASync;
typedef struct gfxQueueGSync {
	struct gfxQueueGSyncItem	*head;
	struct gfxQueueGSyncItem	*tail;
	gfxSem						sem;
	} gfxQueueGSync;
typedef struct gfxQueueFSync {
	struct gfxQueueFSyncItem	*head;
	struct gfxQueueFSyncItem	*tail;
	gfxSem						sem;
	} gfxQueueFSync;
/* @} */

/**
 * @brief	A queue item
 * @{
 */
typedef struct gfxQueueASyncItem {
	struct gfxQueueASyncItem	*next;
	} gfxQueueASyncItem;
typedef struct gfxQueueGSyncItem {
	struct gfxQueueGSyncItem	*next;
	} gfxQueueGSyncItem;
typedef struct gfxQueueFSyncItem {
	struct gfxQueueFSyncItem	*next;
	gfxSem						sem;
	} gfxQueueFSyncItem;
/* @} */


/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	Initialise a queue.
 *
 * @param[in]	pqueue	A pointer to the queue
 *
 * @note	Whilst queues are normally FIFO, a GFX queue also supports push and pop operations.
 * 			A pop operation is the same as normal get from the queue but a push places the item
 * 			at the head of the queue instead of the tail (as a put would).
 *
 * @api
 * @{
 */
void gfxQueueASyncInit(gfxQueueASync *pqueue);
void gfxQueueGSyncInit(gfxQueueGSync *pqueue);
void gfxQueueFSyncInit(gfxQueueFSync *pqueue);
/* @} */

/**
 * @brief	Get an item from the head of the queue.
 * @return	NULL if the timeout expires before an item is available
 *
 * @param[in]	pqueue	A pointer to the queue
 * @param[in]	ms		The maxmimum time to wait for an item. For ASync queues this parameter is
 * 						not specified as TIME_IMMEDIATE is assumed.
 *
 * @api
 * @{
 */
gfxQueueASyncItem *gfxQueueASyncGet(gfxQueueASync *pqueue);
gfxQueueGSyncItem *gfxQueueGSyncGet(gfxQueueGSync *pqueue, delaytime_t ms);
gfxQueueFSyncItem *gfxQueueFSyncGet(gfxQueueFSync *pqueue, delaytime_t ms);
/* @} */

/**
 * @brief	Put an item on the end of the queue.
 * @return	none for ASync and GSync queues; For FSync queues - FALSE on timeout, otherwise TRUE
 *
 * @param[in]	pqueue	A pointer to the queue
 * @param[in]	pitem	A pointer to the queue item
 * @param[in]	ms		The maxmimum time to wait for an item to be removed from the queue (only for FSync queues)
 *
 * @note		FSync: Use a delay time of TIME_IMMEDIATE if you don't want to wait until the
 * 				item is removed from the queue. Note that even if the timeout occurs - the item
 * 				remains in the queue.
 *
 * @api
 * @{
 */
void gfxQueueASyncPut(gfxQueueASync *pqueue, gfxQueueASyncItem *pitem);
void gfxQueueGSyncPut(gfxQueueGSync *pqueue, gfxQueueGSyncItem *pitem);
bool_t gfxQueueFSyncPut(gfxQueueFSync *pqueue, gfxQueueFSyncItem *pitem, delaytime_t ms);
/* @} */

/**
 * @brief	Pop an item from the head of the queue.
 * @detail	This is exactly the same as the Get operation above.
 *
 * @api
 * @{
 */
#define gfxQueueASyncPop(pqueue)			gfxQueueASyncGet(pqueue)
#define gfxQueueGSyncPop(pqueue, ms)		gfxQueueGSyncGet(pqueue, ms)
#define gfxQueueFSyncPop(pqueue, ms)		gfxQueueFSyncGet(pqueue, ms)
/* @} */

/**
 * @brief	Push an item into the start of the queue.
 * @return	none for ASync and GSync queues; For FSync queues - FALSE on timeout, otherwise TRUE
 *
 * @param[in]	pqueue	A pointer to the queue
 * @param[in]	pitem	A pointer to the queue item
 * @param[in]	ms		The maxmimum time to wait for an item to be popped (only for FSync queues)
 *
 * @note		FSync: Use a delay time of TIME_IMMEDIATE if you don't want to wait until the
 * 				item is removed from the queue. Note that even if the timeout occurs - the item
 * 				remains in the queue.
 *
 * @api
 * @{
 */
void gfxQueueASyncPush(gfxQueueASync *pqueue, gfxQueueASyncItem *pitem);
void gfxQueueGSyncPush(gfxQueueGSync *pqueue, gfxQueueGSyncItem *pitem);
bool_t gfxQueueFSyncPush(gfxQueueFSync *pqueue, gfxQueueFSyncItem *pitem, delaytime_t ms);
/* @} */

/**
 * @brief	Remove an item from the queue.
 * @note	Removes the specified item from the queue where-ever it is in the queue
 *
 * @param[in]	pqueue	A pointer to the queue
 * @param[in]	pitem	A pointer to the queue item
 *
 * @note	If the item isn't in the queue the routine just returns.
 * @note	If a process is waiting on the Put/Push operation for the item, that process
 * 			will be signaled.
 *
 * @api
 * @{
 */
void gfxQueueASyncRemove(gfxQueueASync *pqueue, gfxQueueASyncItem *pitem);
void gfxQueueGSyncRemove(gfxQueueGSync *pqueue, gfxQueueGSyncItem *pitem);
void gfxQueueFSyncRemove(gfxQueueFSync *pqueue, gfxQueueFSyncItem *pitem);
/* @} */

/**
 * @brief	Is the queue empty?
 * @return	TRUE if the queue is empty
 *
 * @param[in]	pqueue	A pointer to the queue
 *
 * @api
 * @{
 */
bool_t gfxQueueASyncIsEmpty(gfxQueueASync *pqueue);
bool_t gfxQueueGSyncIsEmpty(gfxQueueGSync *pqueue);
bool_t gfxQueueFSyncIsEmpty(gfxQueueFSync *pqueue);
/* @} */

/**
 * @brief	Is an item in the queue?
 * @return	TRUE if the item is in the queue?
 *
 * @param[in]	pqueue	A pointer to the queue
 * @param[in]	pitem	A pointer to the queue item
 *
 * @note	This operation may be expensive.
 *
 * @api
 * @{
 */
bool_t gfxQueueASyncIsIn(gfxQueueASync *pqueue, gfxQueueASyncItem *pitem);
bool_t gfxQueueGSyncIsIn(gfxQueueGSync *pqueue, gfxQueueGSyncItem *pitem);
bool_t gfxQueueFSyncIsIn(gfxQueueFSync *pqueue, gfxQueueFSyncItem *pitem);
/* @} */

#ifdef __cplusplus
}
#endif

#endif /* GFX_USE_GQUEUE */
#endif /* _GQUEUE_H */
/** @} */
