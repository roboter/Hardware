/*******************************************************************************************************************************************

    DZX | LPC18xx | SPIFI                                                                                                 VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the SPIFI interface.

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
#include "mcu_spifi.h"
#include "mcu_irq.h"
#include "mcu_cgu.h"

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static SPIFI* mcu_spifi[1];

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static STATUS SPIFI_WaitCmd(SPIFI* spifi, UINT32 timeout);
static void SPIFI_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens and initializes the SPIFI peripheral.

    @param[in]  spifi       A pointer to a caller allocated SPIFI instance to be initialized.
    @param[in]  port        The port number to be initialized (only 0 is supported on this platform).

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was initialized.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.
     ERR_NOTSUPPORTED       | The port number is not supported.

    @remark     This does not setup the clock source to the specified SPIFI peripheral.
    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Open(SPIFI* spifi, UINT32 port)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    switch (port) {
        case 0:
            spifi->REG = REG_SPIFI0;
            IRQ_RegisterHandler(IRQ_SPIFI, SPIFI_IRQ);
            IRQ_Enable(IRQ_SPIFI);
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    
    status = MUTEX_Create(&spifi->mutex, "SPIFI", FALSE);
    if (status != SUCCESS) {
        return status;
    }
    
#if (CFG_SPIFIIRQ)
    SIGNAL_Init(&spifi->signals);
#endif

    spifi->REG->STAT.BITS.RESET = 1;
    while (spifi->REG->STAT.BITS.RESET);
    
    spifi->REG->CTRL.BITS.INTEN = 0;
    mcu_spifi[port] = spifi;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was closed.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.
     ERR_INVALIDOPERATION   | The peripheral had an unsupported port number.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Close(SPIFI* spifi) 
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    switch (spifi->port) {
        case 0:
            IRQ_Disable(IRQ_SPIFI);
            break;
        default:
            return ERR_INVALIDOPERATION;
    }
    
    status = MUTEX_Destroy(&spifi->mutex);
    if (status != SUCCESS) {
        return status;
    }
    
    mcu_spifi[spifi->port] = NULL;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Resets a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be reset.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was reset.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Reset(SPIFI* spifi)
{
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    spifi->REG->STAT.BITS.RESET = 1;
    while (spifi->REG->STAT.BITS.RESET);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Sets a SPIFI peripheral into read mode.

    @param[in]  spifi       A pointer to the SPIFI instance to be set to read mode.
    @param[in]  cmd         A pointer to the command used for reading the device.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | Read mode has been set.
     ERR_NULLREFERENCE      | The argument 'spifi' or 'cmd' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_SetReadMode(SPIFI* spifi, const SPIFICMD* cmd)
{
    STATUS status;
    

    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cmd == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = SPIFI_Reset(spifi);
    if (status != SUCCESS) {
        return status;
    }
    
    spifi->REG->IDATA = 0xFF;
    spifi->REG->ADDR = 0;
    spifi->REG->MCMD = (cmd->opcode << 24) |
                      (cmd->frame << 21) |
                      (cmd->field << 19) |
                      (cmd->intlen << 16);
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Claims exclusive access to a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be claimed.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait to acquire the claim. Use '0' to return 
                            immediately without blocking or use 'INFINITE' to block indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was claimed.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Claim(SPIFI* spifi, UINT32 timeout)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&spifi->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Releases a previous claim that was made for a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI instance to be released.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was claimed.
     ERR_NULLREFERENCE      | The argument 'spifi' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Release(SPIFI* spifi)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Release(&spifi->mutex);
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Executes a command upon a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI to execute the command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[in]  addr        An address argument for the command.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The peripheral was claimed.
     ERR_NULLREFERENCE      | The argument 'spifi' or 'cmd' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Cmd(SPIFI* spifi, const SPIFICMD* cmd, UINT32 addr, UINT32 timeout)
{
    STATUS status;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cmd == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&spifi->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
#if (CFG_SPIFIIRQ)
    SIGNAL_Clear(&spifi->signals, CFG_DRIVERSIGNAL);
    
    spifi->REG->STAT.BITS.INTRQ = 1;
    spifi->REG->CTRL.BITS.INTEN = 1;
#endif
    
    spifi->REG->IDATA = 0xFF;
    spifi->REG->ADDR = addr;
    spifi->REG->CMD = (cmd->opcode << 24) |
                      (cmd->frame << 21) |
                      (cmd->field << 19) |
                      (cmd->intlen << 16);
    
    status = SPIFI_WaitCmd(spifi, timeout);
    
    MUTEX_Release(&spifi->mutex);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Executes a read command upon a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI to execute the read command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[in]  addr        The address to be read.
    @param[out] buf         A pointer to a caller allocated buffer to receive the read data.
    @param[in]  nbytes      The total number of bytes to be read and returned.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The requested data was read and returned.
     ERR_NULLREFERENCE      | The argument 'spifi', 'cmd' or 'buf' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Read(SPIFI* spifi, const SPIFICMD* cmd, UINT32 addr, void* buf, UINT32 nbytes, UINT32 timeout)
{
    STATUS status;
    UINT32 k;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cmd == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&spifi->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
#if (CFG_SPIFIIRQ)
    SIGNAL_Clear(&spifi->signals, CFG_DRIVERSIGNAL);
    
    spifi->REG->STAT.BITS.INTRQ = 1;
    spifi->REG->CTRL.BITS.INTEN = 1;
#endif
    
    spifi->REG->IDATA = 0xFF;
    spifi->REG->ADDR = addr;
    spifi->REG->CMD = (cmd->opcode << 24) |
                      (cmd->frame << 21) |
                      (cmd->field << 19) |
                      (cmd->intlen << 16) |
                      nbytes;
        
    if (nbytes % 4) {
        for (k = 0; k < nbytes; k++) {
            ((UINT8*)buf)[k] = spifi->REG->DATA8;
        }
    } else {
        for (k = 0; k < (nbytes >> 2); k++) {
            ((UINT32*)buf)[k] = spifi->REG->DATA32;
        }
    }
    
    
    
    status = SPIFI_WaitCmd(spifi, timeout);
    
    MUTEX_Release(&spifi->mutex);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Executes a write command upon a SPIFI peripheral.

    @param[in]  spifi       A pointer to the SPIFI to execute the write command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[in]  addr        The address to be written.
    @param[in]  data        A pointer to the data to be written.
    @param[in]  nbytes      The total number of bytes to be written.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the transfer to complete. Must not be zero
                            and must be large enough to allow the transfer to complete; based upon clock rate and amount of data being
                            transferred. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The requested data was written.
     ERR_NULLREFERENCE      | The argument 'spifi', 'cmd' or 'data' was found to be NULL.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_Write(SPIFI* spifi, const SPIFICMD* cmd, UINT32 addr, const void* data, UINT32 nbytes, UINT32 timeout)
{
    STATUS status;
    UINT32 k;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cmd == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&spifi->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
#if (CFG_SPIFIIRQ)
    SIGNAL_Clear(&spifi->signals, CFG_DRIVERSIGNAL);
    
    spifi->REG->STAT.BITS.INTRQ = 1;
    spifi->REG->CTRL.BITS.INTEN = 1;
#endif
    
    spifi->REG->ADDR = addr;
    spifi->REG->CMD = (cmd->opcode << 24) |
                      (cmd->frame << 21) |
                      (cmd->field << 19) |
                      (cmd->intlen << 16) |
                      (1 << 15) |
                      nbytes;
    
    if (nbytes % 4) {
        for (k = 0; k < nbytes; k++) {
            spifi->REG->DATA8 = ((UINT8*)data)[k]; 
        }
    } else {
        for (k = 0; k < (nbytes >> 2); k++) {
           spifi->REG->DATA32 = ((UINT32*)data)[k];
        }
    }
    
    status = SPIFI_WaitCmd(spifi, timeout);
    
    MUTEX_Release(&spifi->mutex);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Waits for a previous command to complete.

    @param[in]  spifi       A pointer to the SPIFI executing a command.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the coommand to complete. Must not be zero
                            and must be large enough to allow the command to complete. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The requested data was written.
     ERR_NULLREFERENCE      | The argument 'spifi', 'cmd' or 'data' was found to be NULL.
     ERR_TIMEOUT            | The specified amount of time has elapsed before the command was complete.

    @module     internal

*******************************************************************************************************************************************/
static STATUS SPIFI_WaitCmd(SPIFI* spifi, UINT32 timeout)
{
#if (CFG_SPIFIIRQ)
    
    STATUS status;
    
    
    status = SIGNAL_WaitOne(&spifi->signals, SIGNAL_0, timeout);
    
    spifi->REG->CTRL.BITS.INTEN = 0;
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
    
#else
    
    UINT32 ticks;
    
    
    ticks = KERNEL_Ticks();
    
    while (spifi->REG->STAT.BITS.CMD == 1) {
        if (KERNEL_Ticks() - ticks > timeout) {
            return ERR_TIMEOUT;
        }
    }
    
    return SUCCESS;
#endif /* CFG_SPIFIIRQ */
}

/***************************************************************************************************************************************//**

    Waits for status bits to match.

    @param[in]  spifi       A pointer to the SPIFI to execute the command.
    @param[in]  cmd         A pointer to the command to be executed.
    @param[out] devstat     A pointer to caller allocated variable to receive the final status value from the device.
    @param[in]  mask        The bits to be checked within the receive status byte (only bits 2:0 are supported).
    @param[in]  bitval      The bit value that must be matched to return.
    @param[in]  timeout     The maximum amount of time, in kernel ticks, to block and wait for the coommand to complete. Must not be zero
                            and must be large enough to allow the command to complete. Use INFINITE to wait indefinitely.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The status bits matched the specified value.
     ERR_NULLREFERENCE      | The argument 'spifi' or 'cmd' was found to be NULL.
     ERR_TIMEOUT            | The specified amount of time has elapsed before the command was complete.

    @module     spifi-lpc18xx

*******************************************************************************************************************************************/
STATUS SPIFI_WaitStatus(SPIFI* spifi, const SPIFICMD* cmd, BYTE* devstat, BYTE mask, BYTE bitval, UINT32 timeout)
{
    STATUS status;
    BYTE stat;
    UINT32 ticks;
    
    
#if (CFG_NULLCHECKING)
    if (spifi == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (cmd == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MUTEX_Acquire(&spifi->mutex, timeout);
    if (status != SUCCESS) {
        return status;
    }
    

    ticks = KERNEL_Ticks();
    
    do {
        
#if (CFG_SPIFIIRQ)
        SIGNAL_Clear(&spifi->signals, CFG_DRIVERSIGNAL);
    
        spifi->REG->STAT.BITS.INTRQ = 1;
        spifi->REG->CTRL.BITS.INTEN = 1;
#endif
        
        spifi->REG->IDATA = 0xFF;
        spifi->REG->ADDR = 0;
        spifi->REG->CMD = (cmd->opcode << 24) |
                          (cmd->frame << 21) |
                          (cmd->field << 19) |
                          (cmd->intlen << 16) |
                          1;
        
        stat = spifi->REG->DATA8;
        
        status = SPIFI_WaitCmd(spifi, timeout);
        if (status != SUCCESS) {
            MUTEX_Release(&spifi->mutex);
            return status;
        }
        
        if (KERNEL_Ticks() - ticks > timeout) {
            return ERR_TIMEOUT;
        }
    } while ((stat & mask) != bitval);
    
    if (devstat) {
        *devstat = stat;
    }
    
    MUTEX_Release(&spifi->mutex);
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Handler for a SPIFI interrupt.

    @param[in]  irq         The interrupt request to be handled.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void SPIFI_IRQ(IRQ irq)
{
    SPIFI* spifi;
    
    
    spifi = mcu_spifi[0];
    
#if (CFG_SPIFIIRQ)
    SIGNAL_Set(&spifi->signals, SIGNAL_0);                      /* Release any blocked thread */
#endif
    
    spifi->REG->CTRL.BITS.INTEN = 0;
    spifi->REG->STAT.BITS.INTRQ = 1;
}
