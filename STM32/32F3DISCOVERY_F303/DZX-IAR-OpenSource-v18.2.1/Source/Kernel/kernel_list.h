/*******************************************************************************************************************************************

    DZX | KERNEL | LIST                                                                                                   VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This file is part of the real-time kernel and provides the definition of routines that support doubly linked lists. 

    A linked list is a data structure that consists of a group of nodes that represent a sequence. A linked list has several benefits 
    over a conventional array such that the capacity of the list does not need to be pre-allocated and the nodes can be added or removed 
    from the list easily without reallocation or reorganization of the structure. 

    A linked list maintains links (pointers) to the first and last nodes (structure type NODE) contained within the list; while each 
    node maintains links (pointers) to the next and previous nodes within the list. The two node links allow for traversal of the list 
    in either the forward or backward direction.

    ------------------------------------------------------------------------------------------------------------------------------------

    GNU GENERAL PUBLIC LICENSE VERSION 3 (GPLv3)

    This file is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published 
    by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

    This file is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this distribution (license.txt). Please review the 
    following information to ensure all requirements of the license will be met:  
    <https://dzxdesigns.com/licensing/open.aspx> and <http://www.gnu.org/licenses/gpl-3.0.html> for more information.

    ------------------------------------------------------------------------------------------------------------------------------------
    COPYRIGHT (C) 2018 DZX DESIGNS 

*******************************************************************************************************************************************/
#ifndef KERNEL_LIST_H__
#define KERNEL_LIST_H__

#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    TYPE DEFINITIONS
*******************************************************************************************************************************************/
typedef struct LIST LIST;
typedef struct NODE NODE;

/***************************************************************************************************************************************//**

    Iterates over each node within a linked list.

    @param[out] node        A pointer to a caller allocated node to access each node within the linked list.        
    @param[in]  list        A pointer to the list to be iterated.

	@return		None.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
#define LIST_Foreach(node, list)        for (node = (list)->first; node != NULL; node = node->next)

/***************************************************************************************************************************************//**

    A node within a doubly linked list.
    @module     kernel-list

*******************************************************************************************************************************************/
struct NODE {
	LIST*   list;           /**< A pointer to the list that contains the node. */
	NODE*   next;           /**< A pointer to the next node within the linked list. */
	NODE*   prev;           /**< A pointer to the previous node within the linked list. */
    void*   value;          /**< A pointer to the value contained within the node. */
};

/***************************************************************************************************************************************//**

    A doubly linked list.
    @module     kernel-list

*******************************************************************************************************************************************/
struct LIST {
	NODE*   first;          /**< A pointer to the first node within the linked list */
	NODE*   last;           /**< A pointer to the last node within the linked list */
	UINT32  count;          /**< The current number of nodes contained within the linked list */
};

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Initializes a doubly linked list.

    @param[in]  list        A pointer to a caller allocated list to be initialized.

    @return     None.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_Init(LIST* list);

/***************************************************************************************************************************************//**

    Initializes a node for a linked list. 

    @param[in]  node        A pointer to a caller allocated node to be initialized.

    @return     None.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_InitNode(NODE* node);

/***************************************************************************************************************************************//**

    Removes all nodes from a linked list.

    @param[in]  list        A pointer to the list to be cleared.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_Clear(LIST* list);

/***************************************************************************************************************************************//**

    Adds a new node containing the given value to the start of a list.

    @param[in]  list        A pointer to the list to receive the node.
    @param[in]  node        A pointer to a caller allocated node to be added to the list.
    @param[in]  value       A pointer to the value for the node to be added.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_AddFirst(LIST* list, NODE* node, void* value);

/***************************************************************************************************************************************//**

    Adds a new node containing the given value to the end of a list.

    @param[in]  list        A pointer to the list to receive the node.
    @param[in]  node        A pointer to a caller allocated node to be added to the list.
    @param[in]  value       A pointer to the value for the node to be added.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_AddLast(LIST* list, NODE* node, void* value);

/***************************************************************************************************************************************//**

    Adds a node into a list before an existing node.

    @param[in]  list        A pointer to the list to receive the node.
    @param[in]  node        A pointer to the existing node before which to insert the new node.
    @param[in]  newnode     A pointer to the node to be added to the list.
    @param[in]  value       A pointer to the value for the node to be added.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_AddBefore(LIST* list, NODE* node, NODE* newnode, void* value);

/***************************************************************************************************************************************//**

    Adds a node into a list after an existing node.

    @param[in]  list        A pointer to the list to receive the node.
    @param[in]  node        A pointer to the existing node after which to insert the new node.
    @param[in]  newnode     A pointer to the node to be inserted into the list.
    @param[in]  value       A pointer to the value for the node to be added.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_AddAfter(LIST* list, NODE* node, NODE* newnode, void* value);

/***************************************************************************************************************************************//**

    Returns the value of the first node within a list.

    @param[in]  list        A pointer to the list that contains the value to be returned.

    @return     A pointer to the value for the first node within the specified list. NULL if the list is empty.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void* LIST_First(LIST* list);

/***************************************************************************************************************************************//**

    Returns the value of the last node within a list.

    @param[in]  list        A pointer to the list that contains the value to be returned.

    @return     A pointer to the value for the last node within the specified list. NULL if the list is empty.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void* LIST_Last(LIST* list);

/***************************************************************************************************************************************//**

    Returns the value of the node at the specified zero-based position index.

    @param[in]  list        A pointer to the list to be searched for the given index.
    @param[in]  idx         The zero-based position index of the value to be returned.

    @return     A pointer to the value at the specified index, if found; otherwise NULL.
    @remark     The list is searched forwards from first to last.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the index.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void* LIST_Value(LIST* list, UINT32 idx);

/***************************************************************************************************************************************//**

    Returns the node at the specified zero-based position index.

    @param[in]  list        A pointer to the list to be searched for the given index.
    @param[in]  idx         The zero-based position index of the node to be returned.

    @return     A pointer to the node at the specified index, if found; otherwise NULL.
    @remark     The list is searched forwards from first to last.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the index.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern NODE* LIST_Node(LIST* list, UINT32 idx);

/***************************************************************************************************************************************//**

    Removes a node from a linked list.

    @param[in]  list        A pointer to the list that contains the node to be removed.
    @param[in]  node        A pointer to the node to be removed from the list.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern void LIST_Remove(LIST* list, NODE* node);
        
/***************************************************************************************************************************************//**

    Removes and returns the first node from a linked list.

    @param[in]  list        A pointer to the list that contains the node to be removed.

    @return     A pointer to the node that was removed from the list. NULL if the list did not contain any items.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern NODE* LIST_RemoveFirst(LIST* list);

/***************************************************************************************************************************************//**

    Removes and returns the last node from a linked list.

    @param[in]  list        A pointer to the list that contains the node to be removed.

    @return     A pointer to the node that was removed from the list. NULL if the list did not contain any items.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern NODE* LIST_RemoveLast(LIST* list);

/***************************************************************************************************************************************//**

    Returns the total number of nodes currently contained within a list.

    @param[in]  list        A pointer to the target list.

    @return     The current number of nodes contained within the specified list.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern UINT32 LIST_Count(LIST* list);

/***************************************************************************************************************************************//**

    Finds the first node that contains the specified value.

    @param[in]  list        A pointer to the list to be searched for the given value.
    @param[in]  value       A pointer to the value to locate within the list.

    @return     A pointer to the first node that contained the specified value, if found; otherwise NULL.
    @remark     The list is searched forwards from first to last.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the count of the list.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern NODE* LIST_FindFirst(LIST* list, void* value);

/***************************************************************************************************************************************//**

    Finds the last node that contains the specified value.

    @param[in]  list        A pointer to the list to be searched for the given value.
    @param[in]  value       A pointer to the value to locate within the list.

    @return     A pointer to the last node that contained the specified value, if found; otherwise NULL.
    @remark     The list is searched backwards from last to first.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the count of the list.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern NODE* LIST_FindLast(LIST* list, void* value);

/***************************************************************************************************************************************//**

    Determines whether a value is in a list.

    @param[in]  list        A pointer to the list to be searched for the given value.
    @param[in]  value       A pointer to the value to locate within the list.

    @return     TRUE if the value is found within the list; otherwise FALSE.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the count of the list.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
extern BOOLEAN LIST_Contains(LIST* list, void* value);

/***************************************************************************************************************************************//**

    Determines whether a node is in a list.

    @param[in]  list        A pointer to the list to be searched for the node.
    @param[in]  node        A pointer to the target node.

    @return     TRUE if the node was found within the list; otherwise FALSE.
    @remark     This is an O(1) operation.
    @remark     Not thread safe
    @module     kernel-list

*******************************************************************************************************************************************/
extern BOOLEAN LIST_ContainsNode(LIST* list, NODE* node);

#endif /* KERNEL_LIST_H__ */
