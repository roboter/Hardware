------------MSP430G2553-LaunchPad Audio CapacitanceTouch BoosterPack (ACTBP) Host Application-------------
Ver.: 1.1 Release
April 2012
SDK
Texas Instruments, Inc.
www.ti.com/audioboosterpack 
-------------------------------------------------------------------------------------------------------------------------------


CONTENTS
         
I. PROJECT & FILE CONFIGURATION
II. PROJECT IMPORT IN CCS
III. HISTORY
IV. KNOWN ISSUES
V. BUG FIXES

I. PROJECT & FILE CONFIGURATION
-----------------------------------

PROJECT ROOT  - ACTBP_Host_App 
|   ACTBP_Host_App.c     <Main application code>
|   ACTBP_HostVars.h     <H file: Variables definition for host application>
|   C55_APRF_UIF.h        <H file: Environment variables for Audio Player Recorder Framework (APRF)>
|   ACTBP_capinput.c      <C file: CapacitanceTouch sensing and Gesture and Event detection>
|   ACTBP_capinput.h      <H file: CapacitanceTouch sensing and Gesture and Event detection>
|   ACTBP_uart.c            <C file: HW UART ISRs and UART APIs to communicate with DSP>
|   ACTBP_uart.h            <H file: HW UART ISRs and UART APIs to communicate with DSP>
|   ACTBP_timer.c          <C file: Timer ISRs and UART communication error timeout reset mechanism>
|   ACTBP_timer.h          <C file: Timer ISRs and UART communication error timeout reset mechanism>
|   ACTBP_filesys.c         <C file: Functions to send file system navigation commands to APRF>
|   ACTBP_filesys.h         <H file: Functions to send file system navigation commands to APRF>
|   ACTBP_display.c        <C file: Functions to send OLED display commands to APRF>
|   ACTBP_display.h        <H file: Functions to send OLED display commands to APRF>
|   ACTBP_test.c             <C file: Initial test code>
|   README                    <This file>
|   
+---[CapTouchLibrary]       <Capacitive Touch Library Code>
|       Cap_Touch_HAL.c         
|       Cap_Touch_HAL.h
|       Cap_Touch_Layer.c
|       Cap_Touch_Layer.h
|       structure.c           <Created using template_structure.*>
|       structure.h           <Configured/calibrated specifically for this HW>
|       
+---[CCS]                   <CCS Project Configuration Files>  
|   |                         <All listed files are required>
|   |                         <The non-listed can be safely removed>
|   |   .ccsproject           
|   |   .cdtbuild             
|   |   .cdtproject
|   |   .project             <Contains links to portable project folders/files>
|   |   lnk_msp430g2553.cmd
|   |   macros.ini           <Enables portable project>
|   |   MSP430G2553.ccxml
|   |   

           
II. PROJECT IMPORT IN CCS & IAR
-----------------------------------  
  1. Project Import in CCS  
       a. Open CCS.
       b. Select a new project workspace outside of the project folder*           
       c. Select Project-->Import Existing Project 
       d. Browse to the [PROJECT_ROOT]\CCS folder
       e. Select Finish 
       
       *Ideally, workspace should be in completely independent folder, not
       containing or contained by the project/package folder.
       
       !Note: For CCS, while project root is in the outer directory, the CCS 
       project files are located inside CCS. To enable the portability of
       the project, the file macros.ini is created to define the root. 
       Additionally, all project code files (*.c, *.h) are added as linked 
       resources with their relative path to the project root.
      
 
III. HISTORY 
-----------------------------------
Ver. 1.1 Candidate April 2012
- Bug fix to allow proper fast forward or rewind operation when playback is paused.
- Corrected LED (Diode) placement documentation in ACTBP_Host_App.c and updated #defines accordingly 
- Set CCS v4 build properties to use MSP430G2553 device instead of MSP430G2533

Ver. 1.0 February 2012
- Initial release for MSP430G2553 MCU on LaunchPad for the Audio Capacitive Touch 
Booster Pack.


IV. KNOWN ISSUES
------------------------------------
  1. Users browsing directories after having completed a recording could the sequence of
      directories displayed on the OLED screen skip once.
  2. Host application ignores ACK for UIF_CMD_SLEEP command.
  
V. BUG FIXES
------------------------------------
  1. Trying to fast forward or rewind when playback is paused causes the host application to lose sync
      with the DSP application as these operations are not allowed when APRF is in PAUSE state. 
      Stopping playback restores sync.
  2. Documentation and #defines for LED (Diode) placement on BoosterPack is reversed. 
  3. CCS v4 project is setup for MSP430G2533 device instead of MSP430G2553
