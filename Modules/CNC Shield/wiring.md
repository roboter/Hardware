# Wiring — Arduino CNC Shield

Typical connections:
- Stepper driver sockets: insert A4988/DRV8825 modules (observe orientation)
- Motor outputs: A+/A- and B+/B- for each axis
- Endstops: connect to limit switch inputs (X/Y/Z)
- Spindle and coolant: connect to corresponding headers if implemented

Notes:
- Set microstep jumpers according to desired microstepping and motor current.
- Verify motor driver current limits and cooling before running motors.