# Wiring — L9110 Motor Driver

Typical wiring:
- VCC -> motor supply (e.g., 6–12 V depending on motor)
- GND -> ground (share with MCU)
- IN1/IN2 -> control pins for Motor A (PWM or digital outputs)
- IN3/IN4 -> control pins for Motor B
- Motor A -> A+ / A-
- Motor B -> B+ / B-

Notes:
- Use PWM on control pins for speed control.
- Ensure driver rating matches motor stall current; add heat sinking if needed.