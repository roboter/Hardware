/*******************************************************************************************************************************************

    DZX | CRYPTO | CRC32                                                                                                  VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This provides support for calculating a CRC-32 checksum.

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
#include "Kernel/kernel.h"

/*******************************************************************************************************************************************
    PUBLIC FUNCTIONS
*******************************************************************************************************************************************/
/***************************************************************************************************************************************//**

    Calculates the 32-bit cyclic redundancy check (CRC) value for a set of data.

    @param[in]  initial     The initial CRC value.
    @param[in]  data        A pointer to the data used to calculate the check value.
    @param[in]  nbytes      The number of bytes of data to be calculated.

    @return     The calculated check value for the given data.
    @module     crc32

*******************************************************************************************************************************************/
extern UINT32 CRC32_Calculate(UINT32 initial, const void* data, UINT32 nbytes);
