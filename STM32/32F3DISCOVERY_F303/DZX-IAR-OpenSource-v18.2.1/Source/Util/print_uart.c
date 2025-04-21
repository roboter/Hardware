/*******************************************************************************************************************************************

    DZX | UTIL | PRINT UART                                                                                               VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides support for redirecting print statements to a UART.

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
#include "print_uart.h"
#include <stdio.h>

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static UART* print_uart;

/*******************************************************************************************************************************************

    Assigns the UART that receives the print output.

    @param[in]  uart        A pointer to the UART to receive the output stream.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The  UART has been assigned.
     ERR_NULLREFERENCE      | The argument 'uart' was found to be NULL.

    @module     UTIL-PRINT-UART

*******************************************************************************************************************************************/
STATUS PRINT_SetUART(UART* uart)
{
#if (CFG_NULLCHECKING)
    if (uart == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    print_uart = uart;
    return SUCCESS;
}

#if defined(__ICCARM__)
/*******************************************************************************************************************************************

    Overrides the default print output for IAR.

    @return     The total number of bytes that have been written.
    @module     INTERNAL

*******************************************************************************************************************************************/
size_t __dwrite(int handle, const char* buf, size_t buf_size)
{
    size_t n;
    
    
    UART_Write(print_uart, buf, buf_size, &n, INFINITE);       /* Write the data out the board UART */
    return n;
}
#endif /* __ICCARM__ */

#if defined(__CC_ARM) 
struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;

/*******************************************************************************************************************************************

    Overrides the default print output for Keil.

    @return     The total number of bytes that have been written.
    @module     INTERNAL

*******************************************************************************************************************************************/
int fputc(int ch, FILE *f) {
    UINT32 n;
    
    
    UART_Write(print_uart, &ch, 1, &n, 1000);
    return n;
}

#endif /* __CC_ARM */
