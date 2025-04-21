/*******************************************************************************************************************************************

    DZX | USB DEVICE | STRING                                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the USB device stack and provides support for working with strings.

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
#include "USB/Device/usbd_core.h"
#include <string.h>

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static UINT32 USBD_GetNextStringIdx(USBDDEVICE* stack);

/***************************************************************************************************************************************//**

    Initializes a USB device stack string.

    @param[in]  str         A pointer to the string to be initialized.

    @return     None.
    @module     usbd-string

*******************************************************************************************************************************************/
void USBD_InitString(USBDSTRING* str)
{
    str->cstr = NULL;                                           /* Initialize with no value */
    str->idx = 0;                                               /* Initialize with an invalid index */
    LIST_InitNode(&str->node);                                  /* Initialize the node used for placing the string into the stack */
}

/***************************************************************************************************************************************//**

    Assigns a new string value for a USB device stack.

    @param[in]  stack       A pointer to the USB device stack instance to receive the string.
    @param[in]  str         A pointer to a caller allocated string object used to reference the string within the stack.
    @param[in]  cstr        A pointer to the string's actual text value.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The string has been assigned the specified value.

    @module     usbd-string

*******************************************************************************************************************************************/
STATUS USBD_AssignString(USBDDEVICE* stack, USBDSTRING* str, const CHAR* cstr)
{
    if (cstr == NULL) {
        return USBD_RemoveString(stack, str);
    }
    
    str->cstr = cstr;                                           /* Assign the text value */
    
    if (str->node.list == NULL) {
        str->idx = USBD_GetNextStringIdx(stack);                /* Assign the string the next available index */ 
        LIST_AddLast(&stack->strs, &str->node, str);            /* Insert the string into the stack's list of strings */
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Removes a string from a USB device stack.

    @param[in]  stack       A pointer to the USB device stack instance that contains the string.
    @param[in]  str         A pointer to the string to be removed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The string has been removed.

    @module     usbd-string

*******************************************************************************************************************************************/
STATUS USBD_RemoveString(USBDDEVICE* stack, USBDSTRING* str)
{
    str->cstr = NULL;                                           /* Clear the strings value */
    str->idx = 0;                                               /* Indicate a non-existing value */
    
    if (str->node.list == &stack->strs) {                       /* Remove the string from the stack */
        LIST_Remove(&stack->strs, &str->node);
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the next available string index that can be used by a USB device stack.

    @param[in]  stack       A pointer to the target USB device stack.

    @return     The next available index that can be used.
    @module     internal

*******************************************************************************************************************************************/
static UINT32 USBD_GetNextStringIdx(USBDDEVICE* stack)
{
    UINT32 idx = 1;
    NODE* node;
    USBDSTRING* str;
    
    
    LIST_Foreach(node, &stack->strs) {                          /* Go through all strings and find the maximum index */
        str = node->value;
        if (str->idx > idx) {
            idx = str->idx;
        }
    }
    
    return (idx + 1);                                           /* Return the next available index */
}

/***************************************************************************************************************************************//**

    Returns the descriptor for the string at a specified index within a USB device stack.

    @param[in]  stack       A pointer to the USB device stack instance that contains the string.
    @param[in]  idx         The index of the string descriptor to be returned.
    @param[out] des         A pointer to a caller allocated string descriptor.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The string descriptor has been returned.
     ERR_NOTFOUND           | There was no string found for the specified index.
     ERR_OUTOFRANGE         | The specified buffer was not large enough to return the descriptor.

    @module     internal

*******************************************************************************************************************************************/
STATUS USBD_GetStringDescriptor(USBDDEVICE* stack, BYTE idx, void* buf, UINT32 bufsize)
{
    NODE* node;
    USBDSTRING* str;
    UINT32 len;
    UINT32 i;
    USBSTRINGDESCRIPTOR* des;
    
    
    LIST_Foreach(node, &stack->strs) {                      /* Search through all of the strings */
        str = (USBDSTRING*)node->value;
        
        if (str->idx == idx) {                              /* Is the current string the correct index? */
            
            if (str->cstr) {                                /* Is the string empty? */
                len = strlen(str->cstr);                    /* Get the length of the string */
            } else {
                len = 0;                                    /* Emtpy string */
            }

            des = (USBSTRINGDESCRIPTOR*)buf;                /* Access the specified buffer as a string descriptor */
            
            des->bLength = (len * 2) + 2;                   /* Assign the total length of the descriptor */
            if (des->bLength > bufsize) {                   /* Is the specified buffer large enough? */
                return ERR_OUTOFRANGE;                      /* No, the descriptor will not fit within the supplied buffer */
            }
            
            des->bDescriptorType = USBDESTYPESTRING;

            for (i = 0; i < len; i++) {
                des->wChar[i] = str->cstr[i];
            }
            
            return SUCCESS;
        }
    }
    
    return ERR_NOTFOUND;
}
