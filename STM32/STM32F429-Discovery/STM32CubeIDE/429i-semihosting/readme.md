Testing printf with SWO
from main loop as well from timer

OpenOCD Debugger and Semi-hosting
======================================
Set the linker arguments 
-specs=rdimon.specs -lc -lrdimon

Add semi-hosting run command
monitor arm semihosting enable 

Add the below function call to main.c 
extern void initialise_monitor_handles(void);
initialise_monitor_handles();
