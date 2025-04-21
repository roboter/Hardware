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
#include "kernel_list.h"

/***************************************************************************************************************************************//**

    Initializes a doubly linked list.

    @param[in]  list        A pointer to a caller allocated list to be initialized.

    @return     None.
    @module     kernel-list

*******************************************************************************************************************************************/
void LIST_Init(LIST* list) 
{
    list->first = NULL;                                 /* Initialize the first and last nodes */
    list->last = NULL;
    list->count = 0;                                    /* Initialize the count */
}

/***************************************************************************************************************************************//**

    Initializes a node for a linked list. 

    @param[in]  node        A pointer to a caller allocated node to be initialized.

    @return     None.
    @module     kernel-list

*******************************************************************************************************************************************/
void LIST_InitNode(NODE* node)
{
    node->list = NULL;                                  /* Initialize all of the links for the node */
    node->next = NULL;
    node->prev = NULL;
    node->value = NULL;
}

/***************************************************************************************************************************************//**

    Removes all nodes from a linked list.

    @param[in]  list        A pointer to the list to be cleared.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
void LIST_Clear(LIST* list)
{
    list->first = NULL;                                 /* Clear the first and last */
    list->last = NULL;
    list->count = 0;                                    /* Reset the count */
}

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
void LIST_AddFirst(LIST* list, NODE* node, void* value)
{
    if (list->first) {                                          /* Does the list already contain a node? */
   
        node->next = list->first;                               /* Insert the node before the first node */
        node->prev = NULL;
        list->first->prev = node;
        
    } else {
                 
        list->last = node;                                      /* List is empty. The node is first into the list */
        node->next = NULL;
        node->prev = NULL;
    }
    list->first = node;                                         /* The new node is the first in the list */
    node->list = list;
    node->value = value;
    list->count++;                                              /* Keep total count of items within the list */
}

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
void LIST_AddLast(LIST* list, NODE* node, void* value)
{
    if (list->first) {                            /* Check if the list contains at least one node */
        node->next = NULL;                       /* Append the node as the last of the list */
        node->prev = list->last;
        list->last->next = node;
        list->last = node;
    } else {
        list->first = node;                       /* List is empty, so the node will be the first node in the list */
        list->last = node;
        node->next = NULL;
        node->prev = NULL;
    }
    node->value = value;
    node->list = list;
    list->count++;                               /* Keep total count of items within the list */
}

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
void LIST_AddBefore(LIST* list, NODE* node, NODE* newnode, void* value)
{
    newnode->prev = node->prev;
    newnode->next = node;

    if (node->prev) {
        node->prev->next = newnode;
    } else {
        list->first = newnode;
    }

    node->prev = newnode;
    newnode->value = value;
    newnode->list = list;
    list->count++;
}

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
void LIST_AddAfter(LIST* list, NODE* node, NODE* newnode, void* value)
{
    newnode->prev = node;
    newnode->next = node->next;

    if (node->next) {
        node->next->prev = newnode;
    } else {
        list->last = newnode;
    }

    node->next = newnode;
    newnode->value = value;
    newnode->list = list;
    list->count++;
}

/***************************************************************************************************************************************//**

    Returns the value of the first node within a list.

    @param[in]  list        A pointer to the list that contains the value to be returned.

    @return     A pointer to the value for the first node within the specified list. NULL if the list is empty.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
void* LIST_First(LIST* list)
{
    if (list->first) {
        return list->first->value;
    }
    
    return NULL;
}

/***************************************************************************************************************************************//**

    Returns the value of the last node within a list.

    @param[in]  list        A pointer to the list that contains the value to be returned.

    @return     A pointer to the value for the last node within the specified list. NULL if the list is empty.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
void* LIST_Last(LIST* list)
{
    if (list->last) {
        return list->last->value;
    }
    
    return NULL;
}

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
NODE* LIST_Node(LIST* list, UINT32 idx)
{
    NODE* node;
    UINT32 cnt;
    
    
    cnt = 0;
    
    LIST_Foreach(node, list) {
        if (cnt == idx) {
            return node;
        } else {
            cnt++;
        }
    }
    
    return NULL;
}

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
void* LIST_Value(LIST* list, UINT32 idx)
{
    NODE* node;
    UINT32 cnt;

    
    cnt = 0;
    
    LIST_Foreach(node, list) {              /* Walk through the list */
        if (cnt == idx) {                   /* At the specified index? */
            return node->value;             /* Return the node's value */
        } else {
            cnt++;
        }
    }
    
    return NULL;
}

/***************************************************************************************************************************************//**

    Removes and returns the first node from a linked list.

    @param[in]  list        A pointer to the list that contains the node to be removed.

    @return     A pointer to the node that was removed from the list. NULL if the list did not contain any items.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
NODE* LIST_RemoveFirst(LIST* list)
{
    NODE* node;


    node = list->first;                         /* Capture the node being removed from the list */
    if (list->first) {                          /* Ensure the list contains at least one node */
        list->first = list->first->next;        /* Adjust the first to the next node */
        if (list->first) {                      /* Check if the list is now empty */
            list->first->prev = NULL;           /* Eliminate the link to the removed node */
        } else {
            list->last = NULL;                  /* List is now empty, so clear the last as well */
        }
        node->list = NULL;                      /* Remove the link to the list */
        node->next = NULL;                      /* Remove any links to other items for extra safety */
        node->prev = NULL;
        list->count--;                          /* Update total count of items within the list */
    }
    
    return node;
}

/***************************************************************************************************************************************//**

    Removes and returns the last node from a linked list.

    @param[in]  list        A pointer to the list that contains the node to be removed.

    @return     A pointer to the node that was removed from the list. NULL if the list did not contain any items.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
NODE* LIST_RemoveLast(LIST* list)
{
    NODE* node;


    node = list->last;                           /* Capture the node being removed from the list */
    if (list->last) {                            /* Ensure the list contains at least one node */
        list->last = list->last->prev;           /* Adjust the last to the previous node */
        
        if (list->last) {                        /* Check if the list is now empty */
            list->last->next = NULL;             /* Eliminate the link to the removed node */
        } else {
            list->first = NULL;                  /* List is now empty, so clear the first as well */
        }
        
        node->list = NULL;                       /* NULL the link to the list */
        node->next = NULL;                       /* NULL any links to other items for extra safety */
        node->prev = NULL;
        list->count--;                           /* Update total count of items within the list */
    }
    
    return node;
}

/***************************************************************************************************************************************//**

    Removes a node from a linked list.

    @param[in]  list        A pointer to the list that contains the node to be removed.
    @param[in]  node        A pointer to the node to be removed from the list.

    @return     None.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
void LIST_Remove(LIST* list, NODE* node)
{
    if (node->list == list) {                               /* Check if the node is contained within the specified list */
        node->list = NULL;                                  /* NULL the link to the list */
        
        if (node->prev) {                                   /* Check for items before the node being removed */
            ((NODE*)node->prev)->next = node->next;         /* Create link around node being removed */
        } else {
            list->first = node->next;                       /* The node was the first, assign a new first */
        }

        if (node->next) {                                   /* Check for items after the node being removed */
            ((NODE*)node->next)->prev = node->prev;         /* Create link around node being removed */
        } else {
            list->last = node->prev;                        /* The node was the last, assign a new last */
        }

        node->next = NULL;                                  /* NULL any links to other items for extra safety */
        node->prev = NULL;
        list->count--;                                      /* Update total count of items within the list */
    }
}

/***************************************************************************************************************************************//**

    Returns the total number of nodes currently contained within a list.

    @param[in]  list        A pointer to the target list.

    @return     The current number of nodes contained within the specified list.
    @remark     This is an O(1) operation.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
UINT32 LIST_Count(LIST* list)
{
    return list->count;
}

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
NODE* LIST_FindFirst(LIST* list, void* value)
{
    NODE* node;
    
    
    LIST_Foreach(node, list) {
        if (node->value == value) {
            return node;
        }
    }
    return NULL;
}

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
NODE* LIST_FindLast(LIST* list, void* value)
{
    NODE* node;
    
    
    node = list->last;
    while (node) {
        if (node->value == value) {
            return node;
        }
        node = node->prev;
    }
    
    return NULL;
}

/***************************************************************************************************************************************//**

    Determines whether a value is in a list.

    @param[in]  list        A pointer to the list to be searched for the given value.
    @param[in]  value       A pointer to the value to locate within the list.

    @return     TRUE if the value is found within the list; otherwise FALSE.
    @remark     This performs a linear search and therefore is an O(n) operation where n is the count of the list.
    @remark     Not thread safe.
    @module     kernel-list

*******************************************************************************************************************************************/
BOOLEAN LIST_Contains(LIST* list, void* value)
{
    NODE* node;
    
    
    node = list->first;
    while (node) {
        if (node->value == value) {
            return TRUE;
        }
        node = node->next;
    }
    
    return FALSE;
}

/***************************************************************************************************************************************//**

    Determines whether a node is in a list.

    @param[in]  list        A pointer to the list to be searched for the node.
    @param[in]  node        A pointer to the target node.

    @return     TRUE if the node was found within the list; otherwise FALSE.
    @remark     This is an O(1) operation.
    @remark     Not thread safe
    @module     kernel-list

*******************************************************************************************************************************************/
INLINE BOOLEAN LIST_ContainsNode(LIST* list, NODE* node)
{
    return (node->list == list);
}
