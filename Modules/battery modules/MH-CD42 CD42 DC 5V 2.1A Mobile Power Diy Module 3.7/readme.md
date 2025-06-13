MH-CD42

### Product Parameters
Charging voltage: DC4.5V-5.5V (recommended DC5V)
Charging current: 0-2.1A
Charging quiescent current: 100uA
Full voltage: 4.2V ± 1%
Discharge current: 0-3.5A
Discharge quiescent current: 50uA
Discharge efficiency: up to 96%
Output voltage: 5V
Output current: 0-2.1A
Ambient temperature: -20~+85°C
The module comes with a lithium battery protection function (for lithium batteries without protection, with protection board)
Overcurrent protection (OCP)
Overvoltage protection (OVP)
Short circuit protection (SCP)
Over temperature protection (OTP)
Charge and discharge power level 4 interval indication
Pin Description
VIN: The correct input of the charging port + (DC4.5V-5.5V (recommended DC 5V)
GND: negative input of the charging port -
GND: Lithium battery -
BAT: Lithium battery +
GND: Output negative output -
VOUT: Output positive output +
KEY: Output enable trigger port (low pulse trigger)
Note
In the discharge mode (the charging mode KEY function is invalid), the KEY port is triggered once, and the output is turned on; the KEY port is continuously triggered twice, and the output is turned off.
When the load is first connected, the output will be automatically turned on. If the small fish 50MA is loaded, the output will be turned off after 30 seconds; if the load is greater than 50MA, the output will be continuously turned on.
 Allow one side to discharge while charging (Note: this is the output voltage >4.7/<5V)
Wiring Instructions
When the module is plugged in, the output will switch to external power supply (it will be powered off for 0.3s). When charging, the output voltage will be less than >4.7/<5V, depending on the charger load capacity!
Trigger mode: low level trigger (ground)
Connect to the single-chip microcomputer, if the connection is less than the load KEY, you can connect the single-chip microcomputer for about 20s to give a low level to keep the module working continuously.
Indicator Light
Applications
Car charging retrofit
Driving recorder power supply
Mobile power / charging treasure
Portable devices such as mobile phones and tablets

