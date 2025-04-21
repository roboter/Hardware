/*******************************************************************************************************************************************

    DZX | LPC1857-MCB | EXTERNAL MEMORY CONTROLLER                                                                        VERSION 18.2.1
    ------------------------------------------------------------------------------------------------------------------------------------

    This is part of the board support drivers and provides setup of the external memory controller.

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
#include "board_emc.h"
#include "mcu_emc.h"
#include "mcu_ccu.h"
#include "mcu_creg.h"
#include "mcu_pin.h"

/*******************************************************************************************************************************************
    PRIVATE FUNCTIONS
*******************************************************************************************************************************************/
static void EMC_InitPin(PIN pin, BYTE function);
static UINT32 EMC_NanosecondsToCycles(UINT32 emcClk, UINT32 nanoseconds);

/***************************************************************************************************************************************//**

    Initializes and configures the external memory controller (EMC) for the board.

    @return

     Status Code            | Description
    ----------------------- | ------------------------------------------------------------------------------------------------------
     SUCCESS                | The memory controller has been initialized.

    @module     BOARD-EMC-LPC1857-MCB

*******************************************************************************************************************************************/
STATUS EMC_Initialize(void)
{
    UINT32 emcClk = 90000000;
    volatile UINT32 delay;
    UINT32 temp;
    
    
    EMC_InitPin(P1_00, 2);                                  /* EMC_A5 */
    EMC_InitPin(P1_01, 2);                                  /* EMC_A6 */
    EMC_InitPin(P1_02, 2);                                  /* EMC_A7 */
    EMC_InitPin(P1_03, 3);                                  /* EMC_OE */
    EMC_InitPin(P1_05, 3);                                  /* EMC_CS0 */
    EMC_InitPin(P1_06, 3);                                  /* EMC_WE */
    EMC_InitPin(P1_07, 3);                                  /* EMC_D0 */
    EMC_InitPin(P1_08, 3);                                  /* EMC_D1 */
    EMC_InitPin(P1_09, 3);                                  /* EMC_D2 */
    EMC_InitPin(P1_10, 3);                                  /* EMC_D3 */
    EMC_InitPin(P1_11, 3);                                  /* EMC_D4 */
    EMC_InitPin(P1_12, 3);                                  /* EMC_D5 */
    EMC_InitPin(P1_13, 3);                                  /* EMC_D6 */
    EMC_InitPin(P1_14, 3);                                  /* EMC_D7 */
    EMC_InitPin(P2_00, 2);                                  /* EMC_A13 */
    EMC_InitPin(P2_01, 2);                                  /* EMC_A12 */
    EMC_InitPin(P2_02, 2);                                  /* EMC_A11 */
    EMC_InitPin(P2_06, 2);                                  /* EMC_A10 */
    EMC_InitPin(P2_07, 3);                                  /* EMC_A9 */
    EMC_InitPin(P2_08, 3);                                  /* EMC_A8 */
    EMC_InitPin(P2_09, 3);                                  /* EMC_A0 */
    EMC_InitPin(P2_10, 3);                                  /* EMC_A1 */
    EMC_InitPin(P2_11, 3);                                  /* EMC_A2 */
    EMC_InitPin(P2_12, 3);                                  /* EMC_A3 */
    EMC_InitPin(P2_13, 3);                                  /* EMC_A4 */
    EMC_InitPin(P5_00, 2);                                  /* EMC_D12 */
    EMC_InitPin(P5_01, 2);                                  /* EMC_D13 */
    EMC_InitPin(P5_02, 2);                                  /* EMC_D14 */
    EMC_InitPin(P5_03, 2);                                  /* EMC_D15 */
    EMC_InitPin(P5_04, 2);                                  /* EMC_D8 */
    EMC_InitPin(P5_05, 2);                                  /* EMC_D9 */
    EMC_InitPin(P5_06, 2);                                  /* EMC_D10 */
    EMC_InitPin(P5_07, 2);                                  /* EMC_D11 */
    EMC_InitPin(P6_04, 3);                                  /* EMC_CAS */
    EMC_InitPin(P6_05, 3);                                  /* EMC_RAS */
    EMC_InitPin(P6_07, 1);                                  /* EMC_A15 */
    EMC_InitPin(P6_08, 1);                                  /* EMC_A14 */
    EMC_InitPin(P6_09, 3);                                  /* EMC_DYCS0 */
    EMC_InitPin(P6_10, 3);                                  /* EMC_DQMOUT1 */
    EMC_InitPin(P6_11, 3);                                  /* EMC_CKEOUT */
    EMC_InitPin(P6_12, 3);                                  /* EMC_DQMOUT0 */
    EMC_InitPin(PA_04, 3);                                  /* EMC_A23 */
    EMC_InitPin(PD_00, 2);                                  /* EMC_DQMOUT2 */
    EMC_InitPin(PD_02, 2);                                  /* EMC_D16 */
    EMC_InitPin(PD_03, 2);                                  /* EMC_D17 */
    EMC_InitPin(PD_04, 2);                                  /* EMC_D18 */
    EMC_InitPin(PD_05, 2);                                  /* EMC_D19 */
    EMC_InitPin(PD_06, 2);                                  /* EMC_D20 */
    EMC_InitPin(PD_07, 2);                                  /* EMC_D21 */
    EMC_InitPin(PD_08, 2);                                  /* EMC_D22 */
    EMC_InitPin(PD_09, 2);                                  /* EMC_D23 */
    EMC_InitPin(PD_15, 2);                                  /* EMC_A17 */
    EMC_InitPin(PD_16, 2);                                  /* EMC_A16 */
    EMC_InitPin(PE_00, 3);                                  /* EMC_A18 */
    EMC_InitPin(PE_01, 3);                                  /* EMC_A19 */
    EMC_InitPin(PE_02, 3);                                  /* EMC_A20 */
    EMC_InitPin(PE_03, 3);                                  /* EMC_A21 */
    EMC_InitPin(PE_04, 3);                                  /* EMC_A22 */
    EMC_InitPin(PE_05, 3);                                  /* EMC_D24 */
    EMC_InitPin(PE_06, 3);                                  /* EMC_D25 */
    EMC_InitPin(PE_07, 3);                                  /* EMC_D26 */
    EMC_InitPin(PE_08, 3);                                  /* EMC_D27 */
    EMC_InitPin(PE_09, 3);                                  /* EMC_D28 */
    EMC_InitPin(PE_10, 3);                                  /* EMC_D29 */
    EMC_InitPin(PE_11, 3);                                  /* EMC_D30 */
    EMC_InitPin(PE_12, 3);                                  /* EMC_D31 */
    EMC_InitPin(PE_13, 3);                                  /* EMC_DQMOUT3 */
    
    REG_EMCCLKDELAY = 0x7777;                               /* SDRAM clock output delay (~3.5ns) */
    
    REGBITS_CCU1CLKM3EMCDIVCFG.AUTO = 1;
    REGBITS_CCU1CLKM3EMCDIVCFG.WAKEUP = 1;
    REGBITS_CCU1CLKM3EMCDIVCFG.RUN = 1;
    REGBITS_CCU1CLKM3EMCDIVCFG.DIV = 1;
    
    REGBITS_CCU1CLKM3EMCCFG.AUTO = 1;
    REGBITS_CCU1CLKM3EMCCFG.WAKEUP = 1;
    REGBITS_CCU1CLKM3EMCCFG.RUN = 1;
    
    REGBITS_CREG6.EMCCLKSEL = 1;
    
    REG_EMCCONFIG = 0;
    REG_EMCCONTROL = 1;
    
    REGBITS_EMCDYNAMICCONFIG0.MD = 0;
    REGBITS_EMCDYNAMICCONFIG0.AML = 0x2A;
    REGBITS_EMCDYNAMICCONFIG0.AMH = 0x1;
    REGBITS_EMCDYNAMICCONFIG0.B = 0;
    REGBITS_EMCDYNAMICCONFIG0.P = 0;
    
    REGBITS_EMCDYNAMICREADCONFIG.RD = 1;                                    /* Read data strategy */
    REGBITS_EMCDYNAMICTRP.TRP = EMC_NanosecondsToCycles(emcClk, 18) - 1;
    REGBITS_EMCDYNAMICTRAS.TRAS = EMC_NanosecondsToCycles(emcClk, 42) - 1;
    REGBITS_EMCDYNAMICTSREX.TSREX = EMC_NanosecondsToCycles(emcClk, 70) - 1;
    REGBITS_EMCDYNAMICTAPR.TAPR = 1;
    REGBITS_EMCDYNAMICTDAL.TDAL = 5;
    REGBITS_EMCDYNAMICTWR.TWR = EMC_NanosecondsToCycles(emcClk, 12) - 1;
    REGBITS_EMCDYNAMICTRC.TRC = EMC_NanosecondsToCycles(emcClk, 60) - 1;
    REGBITS_EMCDYNAMICTRFC.TRFC = EMC_NanosecondsToCycles(emcClk, 60) - 1;
    REGBITS_EMCDYNAMICTXSR.TXSR = EMC_NanosecondsToCycles(emcClk, 70) - 1;
    REGBITS_EMCDYNAMICTRRD.TRRD = EMC_NanosecondsToCycles(emcClk, 12) - 1;
    REGBITS_EMCDYNAMICTMRD.TMRD = 2;
    
    for (delay = 0; delay < 1000; delay++);
    REG_EMCDYNAMICCONTROL = 0x183;
    
    for (delay = 0; delay < 1000; delay++);
    REG_EMCDYNAMICCONTROL = 0x103;
    
    REG_EMCDYNAMICREFRESH = 2;
    for (delay = 0; delay < 80; delay++);
    
    REG_EMCDYNAMICREFRESH = 0x58;
    REG_EMCDYNAMICCONTROL = 0x83;       /* MODE Command */
    
    
    temp = *((volatile UINT32*)(0x28000000 | (50 << 0xA)));
    temp = temp;
    
    
    REG_EMCDYNAMICCONTROL = 0;          /* NORMAL command */
    
    REGBITS_EMCDYNAMICCONFIG0.B = 1;
    REGBITS_EMCDYNAMICCONFIG1.B = 1;
    REGBITS_EMCDYNAMICCONFIG2.B = 1;
    REGBITS_EMCDYNAMICCONFIG3.B = 1;
    
    return SUCCESS;
}

/***************************************************************************************************************************************//**

    Initializes a pin to be used by the external memory controller (EMC).

    @return     None.
    @module     BOARD-EMC-LPC1857-MCB

*******************************************************************************************************************************************/
static void EMC_InitPin(PIN pin, BYTE function)
{
    PIN_SetFunction(pin, function);
    PIN_SetFastSlewRate(pin, TRUE);
    PIN_SetInputBuffer(pin, TRUE);
    PIN_SetGlitchFilter(pin, FALSE);
}

/***************************************************************************************************************************************//**

    Converts nanoseconds into clock cycles.

    @param[in]  emcClk      The EMC clock rate, in hertz.
    @param[in]  nanoseconds The number of nanoseconds.

    @return     None.
    @module     BOARD-EMC-LPC1857-MCB

*******************************************************************************************************************************************/
static UINT32 EMC_NanosecondsToCycles(UINT32 emcClk, UINT32 nanoseconds)
{
    UINT32 nanoperclk;
    UINT32 cycles;
    
    
    nanoperclk = (UINT32)1000000000 / (UINT32)emcClk;           /* Calc nanoseconds per clock cycle */
    cycles = nanoseconds / nanoperclk;                          /* Convert nanoseconds into clock cycles */
    
    if (nanoseconds % nanoperclk) {
        cycles++;
    }
    
    return cycles;
}

