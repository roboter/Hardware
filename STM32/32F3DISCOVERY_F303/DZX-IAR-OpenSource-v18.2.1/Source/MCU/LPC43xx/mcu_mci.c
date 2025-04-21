/*******************************************************************************************************************************************

    DZX | LPC43xx | MULTIMEDIA CARD INTERFACE                                                                             VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the MCU peripheral drivers and provides support for the MMC/SD card interface (MCI).

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
#include "mcu_mci.h"
#include "mcu_irq.h"
#include "mcu_cgu.h"
#include "mcu_cfg.h"
#include "mcu_kernel.h"
#include "Kernel/kernel_core.h"

/*******************************************************************************************************************************************
    PRIVATE DEFINITIONS
*******************************************************************************************************************************************/
#define MCI_FIFOSIZE        32
#define MCI_IRQCMD          ((1 << 1) | (1 << 2) | (1 << 8))
#define MCI_IRQDATA         ((1 << 1) | (1 << 3) | (1 << 8))

/*******************************************************************************************************************************************
    PRIVATE VARIABLES
*******************************************************************************************************************************************/
static MCI* mcu_mci[1];

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void MCI_CmdCIU(MCI* port, UINT32 cmd, UINT32 arg);
static void MCI_IRQ(IRQ irq);

/***************************************************************************************************************************************//**

    Opens and initializes a multimedia card interface.

    @param[in]  port        A caller allocated card interface port to be initialized.
    @param[in]  number      The number of the port to be opened. Only one interface (number 0) is supported.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port interface was successfully configured and is ready for communications.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).
     ERR_NOTSUPPORTED       | The specified port number is not supported.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_Open(MCI* port, UINT32 number)
{
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    switch (number) {
        case 0:
            port->REG = REG_MCI0;
            REGBITS_CGUBASESDIOCLK.AUTOBLOCK = 1;
            REGBITS_CGUBASESDIOCLK.CLKSEL = 9;
            REGBITS_CGUBASESDIOCLK.PD = 0;
            IRQ_RegisterHandler(IRQ_SDIO, MCI_IRQ);
            IRQ_Enable(IRQ_SDIO);
            break;
            
        default:
            return ERR_NOTSUPPORTED;
    }
       
    port->number = number;
    mcu_mci[number] = port;
    
    SIGNAL_Init(&port->signals);
    
    port->REG->BMOD.BITS.SWR = 1;
    
    port->REG->CTRL.VALUE = 0x7;
    while (port->REG->CTRL.VALUE & 0x7);
        
    port->REG->CTRL.BITS.USEINTERNALDMAC = 1;
    
    port->REG->RINTSTS.VALUE = 0xFFFFFFFF;                      /* Clear any pending interrupts */
    
    port->REG->FIFOTH.BITS.RXWMARK = (MCI_FIFOSIZE / 2) - 1;
    port->REG->FIFOTH.BITS.TXWMARK = (MCI_FIFOSIZE / 2);
    port->REG->FIFOTH.BITS.DMAMTS = 1;
    
    port->REG->CLKSRC = 0;
    port->REG->CLKENA.BITS.CCLKLOWPOWER = 0;
    port->REG->CLKENA.BITS.CCLKENABLE = 0;
    
    port->REG->CTYPE.BITS.CARDWIDTH0 = 0;                       /* Begin in 1-bit mode */
    
    port->REG->BMOD.BITS.DSL = 4;
    port->REG->BMOD.BITS.PBL = 1;
    port->REG->BMOD.BITS.FB = 0;
    port->REG->BMOD.BITS.DE = 1;
    
    port->REG->CTRL.BITS.INTENABLE = 1;
   
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Closes a multimedia card interface.

    @param[in]  port        A pointer to the card interface port to be closed.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The port interface was closed.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_INVALIDCONTEXT     | This operation is not supported from the context of an interrupt service routine (ISR).

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_Close(MCI* port)
{
#if (CFG_CONTEXTCHECKING)
    if (KERNEL_IsISR()) {
        return ERR_INVALIDCONTEXT;
    }
#endif
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    if (port != mcu_mci[port->number]) {
        return SUCCESS;
    }

    switch (port->number) {
        case 0:
            port->REG->CLKENA.BITS.CCLKENABLE = 0;              /* Turn off clock to card */
            IRQ_Disable(IRQ_SDIO);                              /* Disable any further interrupts */
            break;
        default:
            return ERR_NOTSUPPORTED;
    }
    
    mcu_mci[port->number] = NULL;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns the configured block size for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.

    @return     The configured block size, in bytes, for the specified interface port.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
UINT32 MCI_BlockSize(MCI* port)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return 0;
    }
#endif    
    
    return port->REG->BLKSIZ;
}

/***************************************************************************************************************************************//**

    Sets the block size for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.
    @param[in]  size        The new block size, in bytes.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The interface block size was set.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_SetBlockSize(MCI* port, UINT32 size)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    
    
    port->REG->BLKSIZ = size;
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Executes a command over a multimedia card interface.

    @param[in]  port        A pointer to the card interface port to execute the command.
    @param[in]  cmd         The command to be executed.
    @param[in]  arg         The argument to be executed.
    @param[in]  irqmask     The interrupt mask used to pend for complete.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
static STATUS MCI_Execute(MCI* port, UINT32 cmd, UINT32 arg, UINT32 irqmask, UINT32 timeout)
{
    STATUS status;
    

    
    if (port->thread) {                                         /* Is there already a command pending? */
        return ERR_ACCESSDENIED;                                /* Cannot allow multiple access */
    }
    
    port->thread = kernel.thread;                               /* Keep a reference the calling thread to signal when complete */
    
    SIGNAL_Clear(&port->signals, SIGNAL_0);
    
    port->REG->INTMASK.VALUE = irqmask;                         /* Assign the interrupts to be waited upon */
    port->REG->RINTSTS.VALUE = 0xFFFFFFFF;                      /* Clear any existing pending interrupts */
    
    port->REG->CMDARG = arg;
    port->REG->CMD = 0x80000000 | cmd;

    status = SIGNAL_WaitOne(&port->signals, SIGNAL_0, timeout); /* Wait for an interrupt */
    
    port->thread = NULL;                                        /* Release the reference to the calling thread */
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Executes a command over a multimedia card interface.

    @param[in]  port        A pointer to the card interface port to execute the command.
    @param[in]  rca         The relative card address for the target card.
    @param[in]  cmd         The command to be executed.
    @param[in]  arg         The argument for the command to be executed.
    @param[out] resp        A pointer to a caller allocated response to receive the response values. Can be NULL.
    @param[in]  type        The type of response expected.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_Command(MCI* port, UINT32 rca, UINT32 cmd, UINT32 arg, MCIRESPONSE* resp, MCIRESPONSETYPE type, UINT32 timeout)
{
    STATUS status;
    UINT32 cmd_value;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    cmd_value = cmd & 0x3F;
    
    if (type != MCIRESPONSE_NONE) {                             /* Response expected? */
        cmd_value |= (1 << 6);
    }
    
    if (type == MCIRESPONSE_LONG) {                             /* A long response expected? */
        cmd_value |= (1 << 7);
    }
    
    if (cmd & MCI_CMDINITFLAG) {                                /* Send initialization clocks? */
        cmd_value |= (1 << 15);
    }
    
    if (cmd & MCI_CMDAPPFLAG) {                                 /* An app command? */
        status = MCI_Execute(port,                              /* Yes, execute a 55 command first */
                             0x80000077, 
                             rca,
                             MCI_IRQCMD,
                             timeout);
        
        if (status != SUCCESS) {
            return status;
        }   
    }
    
    status = MCI_Execute(port,                                  /* Execute the requested command */
                         cmd_value, 
                         arg,
                         MCI_IRQCMD,
                         timeout);
    
    if (status != SUCCESS) {
        return status;
    }   
    
    if (port->sts.RTO) {                                        /* A response timeout? */
        return ERR_NORESPONSE;
    }
    
    if (resp) {
        resp->value[0] = port->REG->RESP0;                      /* Read the received response */
        resp->value[1] = port->REG->RESP1;
        resp->value[2] = port->REG->RESP2;
        resp->value[3] = port->REG->RESP3;
    }
    
    return SUCCESS;
}
            
/***************************************************************************************************************************************//**

    Reads and returns the current state for a multimedia card.

    @param[in]  port        A pointer to the interface port used for communications.
    @param[in]  rca         The relative card address for the target card.
    @param[out] state       A pointer to a caller allocated variable to receive the state.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' or 'state' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_State(MCI* port, UINT32 rca, MCICARDSTATE* state, UINT32 timeout)
{
    STATUS status;
    MCIRESPONSE resp;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (state == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MCI_Command(port,                                  /* Execute a command to retrieve the state */
                         rca,
                         MCI_CMD13 | (1 << 13), 
                         rca, 
                         &resp,
                         MCIRESPONSE_SHORT,
                         timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    *state = (MCICARDSTATE)(resp.value[0] >> 9);                /* Provide the received state value */
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Selects a card for data transfers.

    @param[in]  port        A pointer to the card interface port used to execute the command.
    @param[in]  rca         The relative card address for the target card.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_Select(MCI* port, UINT32 rca, UINT32 timeout)
{
    STATUS status;
    MCIRESPONSE resp;
    MCICARDSTATE state;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MCI_State(port, rca, &state, timeout);             /* Retrieve the current state */
    if (status != SUCCESS) {
        return status;
    }
    
    if (state == MCICARD_TRANS) {                               /* Exit now if the card is already in the transfer state */
        return SUCCESS; 
    }
    
    status = MCI_Command(port,                                  /* Command the card to the transfer state */
                         rca,
                         MCI_CMD7 | (1 << 13),
                         rca,
                         &resp,
                         MCIRESPONSE_SHORT,
                         timeout);
    
    if (status != SUCCESS) {
        return status;
    }
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Returns an indication of whether the card is detected.

    @param[in]  port        A pointer to the target card interface port.

    @return     TRUE if the card is detected; otherwise FALSE.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
BOOLEAN MCI_CardDetect(MCI* port)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return FALSE;
    }
#endif
    
    if (port->REG->CDETECT) {
        return FALSE;
    }
    
    return TRUE;
}

/***************************************************************************************************************************************//**

    Returns the transfer mode for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.

    @return

     Mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MCI_1BIT               | The interface is using the 1-bit transfer mode.
     MCI_4BIT               | The interface is using the 4-bit transfer mode.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
MCITRANSFERMODE MCI_TransferMode(MCI* port)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return MCI_1BIT;
    }
#endif  
    
    if (port->REG->CTYPE.BITS.CARDWIDTH0 == 0) {
        return MCI_1BIT;
    }
    
    return MCI_4BIT;
}

/***************************************************************************************************************************************//**

    Assigns a transfer mode for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.
    @param[in]  mode        The new tranfer mode for the interface.

     mode                   | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     MCI_1BIT               | Use the 1-bit transfer mode.
     MCI_4BIT               | Use the 4-bit transfer mode.
     MCI_8BIT               | Not supported by this driver.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The command was executed successfully.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.
     ERR_NOTSUPPORTED       | The specified mode is not supported.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_SetTransferMode(MCI* port, MCITRANSFERMODE mode)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif

    switch (mode) {
        case MCI_1BIT:
            port->REG->CTYPE.BITS.CARDWIDTH0 = 0;
            return SUCCESS;
            
        case MCI_4BIT:
            port->REG->CTYPE.BITS.CARDWIDTH0 = 1;
            return SUCCESS;
            
        case MCI_8BIT:
        default:
            return ERR_NOTSUPPORTED;
    }
}

/***************************************************************************************************************************************//**

    Configures a DMA data transfer for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface port.
    @param[in]  addr        The address for the data transfer.
    @param[in]  nblks       The number of blocks to be transferred.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The transfer has been configured.

    @module     internal

*******************************************************************************************************************************************/
static STATUS MCI_ConfigureDMA(MCI* port, UINT32 addr, UINT32 nblks)
{
    UINT32 total = 0;
    UINT32 num;
    UINT32 nbytes;
    UINT32 k = 0;
    
    
    port->REG->CTRL.BITS.FIFORESET = 1;
    while (port->REG->CTRL.BITS.FIFORESET);
    
    port->REG->CTRL.BITS.DMARESET = 1;
    while (port->REG->CTRL.BITS.DMARESET);
    
    
    nbytes = nblks * port->REG->BLKSIZ;
    port->REG->BYTCNT = nbytes;
    
    while (total < nbytes) {
        num = nbytes - total;
        if (num > 4096) {
            num = 4096;
        }
        
        port->dma[k].DESC0 = 0x80000010;                        /* Init as chained with DMA as owner */
        port->dma[k].DESC1 = num;                               /* Number of bytes to be transferred */
        port->dma[k].DESC2 = (addr + total);                    /* Address of the buffer for the transfer */
        port->dma[k].DESC3 = (UINT32)&port->dma[k + 1];         /* Chain to the next descriptor */
        
        total += num;
        
        if (total == nbytes) {
            port->dma[k].DESC0 |= (1 << 2);                     /* Indicate that this is the last descriptor */
        }
        
        ++k;
    }

    port->dma[0].DESC0 |= (1 << 3);                             /* Indicate the first descriptor */
    port->REG->DBADDR = (UINT32)&port->dma[0];
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Reads and returns data from a multimedia card.

    @param[in]  port        A pointer to the interface port for communications with the card.
    @param[in]  rca         The relative card address for the target card.
    @param[out] buf         A pointer to a caller allocated buffer to receive the data.
    @param[in]  nblks       The total number of blocks to be received and returned.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been received and returned.
     ERR_NULLREFERENCE      | The argument 'port' or 'buf' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_Read(MCI* port, UINT32 rca, UINT32 addr, void* buf, UINT32 nblks, UINT32 timeout)
{
    STATUS status;
    UINT32 cmd;
    MCICARDSTATE state;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (buf == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MCI_Select(port, rca, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    MCI_ConfigureDMA(port, (UINT32)buf, nblks);
    
    cmd = (nblks == 1) ? 17 : (18 | (1 << 12));
    
    status = MCI_Execute(port,
                         cmd | (1 << 6) | (1 << 9) | (1 << 13),
                         addr,
                         MCI_IRQDATA,
                         timeout);

    if (status != SUCCESS) {
        return status;
    }
    
    
    do {
        status = MCI_State(port, rca, &state, timeout);
        if (status != SUCCESS) {
            return status;
        }
        
    } while (state != MCICARD_TRANS);
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Writes data to a multimedia card.

    @param[in]  port        A pointer to the interface port for communications with the card.
    @param[in]  rca         The relative card address for the target card.
    @param[in]  data        A pointer to the data to be written to the card.
    @param[in]  nblks       The total number of blocks to be written.
    @param[in]  timeout     The maximum amount of time to wait for the command to complete. Must be larger than zero.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The data has been written to the card.
     ERR_NULLREFERENCE      | The argument 'port' or 'data' was found to be NULL.
     ERR_TIMEOUT            | The specified timeout interval elapsed before the command completed.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_Write(MCI* port, UINT32 rca, UINT32 addr, const void* data, UINT32 nblks, UINT32 timeout)
{
    STATUS status;
    UINT32 cmd;
    MCICARDSTATE state;
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
    
    if (data == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif
    
    status = MCI_Select(port, rca, timeout);
    if (status != SUCCESS) {
        return status;
    }
    
    MCI_ConfigureDMA(port, (UINT32)data, nblks);
    
    cmd = (nblks == 1) ? 24 : (25 | (1 << 12));
    
    status = MCI_Execute(port,
                         cmd | (1 << 6) | (1 << 9) | (1 << 10) | (1 << 13),
                         addr,
                         MCI_IRQDATA,
                         timeout);

    if (status != SUCCESS) {
        return status;
    }
    
    do {
        status = MCI_State(port, rca, &state, timeout);
        if (status != SUCCESS) {
            return status;
        }
        
    } while (state != MCICARD_TRANS);
    
    return SUCCESS;
}
        
/***************************************************************************************************************************************//**

    Commands the CIU and waits for the command to be accepted.

    @param[in]  port        A pointer to the target card interface.
    @param[in]  cmd         The command to be accepted.
    @param[in]  arg         The argument to the command to be accepted.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void MCI_CmdCIU(MCI* port, UINT32 cmd, UINT32 arg)
{
    port->REG->CMDARG = arg;
    port->REG->CMD = 0x80000000 | cmd;
    
    while (port->REG->CMD & 0x80000000);
}

/***************************************************************************************************************************************//**

    Returns the current clock speed for a multimedia card interface.

    @param[in]  port        A pointer to the target card interface.

    @return     The clock speed, in hertz, for the specified card interface.
    @remark     The value returned is the actual clock rate and may not be exactly what was set using MCI_SetClock() since every possible
                rate is not attainable by the hardware.
    @module     mci-lpc43xx

*******************************************************************************************************************************************/
UINT32 MCI_Clock(MCI* port)
{
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return 0;
    }
#endif    
    
    if (port->REG->CLKENA.BITS.CCLKENABLE == 0) {               /* Is the clock disabled? */
        return 0;
    }
   
    if (port->REG->CLKDIV.BITS.DIVIDER0 == 0) {                 /* Ensure no divide by zero */
        return 0;
    }
    
    return (MCU_ClockHz() / ((UINT32)port->REG->CLKDIV.BITS.DIVIDER0 << 1));
}

/***************************************************************************************************************************************//**

    Sets a new clock speed for a multimedia card interface.

    @param[in]  port        A pointer to the interface port to receive the new clock speed.
    @param[in]  freqHz      The new clock speed, in hertz, for the interface. Use '0' to disable the clock to the card.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The clock speed has been set.
     ERR_NULLREFERENCE      | The argument 'port' was found to be NULL.

    @module     mci-lpc43xx

*******************************************************************************************************************************************/
STATUS MCI_SetClock(MCI* port, UINT32 freqHz)
{
    UINT32 divider;
    
    
    
#if (CFG_NULLCHECKING)
    if (port == NULL) {
        return ERR_NULLREFERENCE;
    }
#endif    
    
    port->REG->CLKENA.BITS.CCLKENABLE = 0;                      /* Disable card clock */
    MCI_CmdCIU(port, 1 << 21, 0);                               /* Update clock command */
    
    if (freqHz == 0) {                                          /* Requesting disable? */
        return SUCCESS;
    }
    
    divider = ((MCU_ClockHz() / freqHz) + 1) >> 1;              /* Divider is hw mult by 2 (+1 for round up for odd numbers) */
    
    port->REG->CLKDIV.BITS.DIVIDER0 = divider;
    MCI_CmdCIU(port, 1 << 21, 0);                               /* Update clock divider */
    
    port->REG->CLKENA.BITS.CCLKENABLE = 1;                      /* Re-enable the clock */
    MCI_CmdCIU(port, 1 << 21, 0);                               /* Update clock command */
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    An interrupt handler for a multimedia card interface.

    @param[in]  irq         The interrupt request to be handled.

    @return     None.
    @module     internal

*******************************************************************************************************************************************/
static void MCI_IRQ(IRQ irq)
{
    MCI* port = mcu_mci[0];
    
    
    port->sts = port->REG->RINTSTS.BITS;                        /* Capture the status bits */
    SIGNAL_Set(&port->signals, SIGNAL_0);                       /* Signal the waiting thread */

    port->REG->RINTSTS.VALUE = port->REG->RINTSTS.VALUE;        /* Clear the interrupt */
}
