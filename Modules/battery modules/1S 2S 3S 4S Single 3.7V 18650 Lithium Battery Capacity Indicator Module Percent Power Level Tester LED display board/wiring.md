# Wiring — Capacity Indicator (1S–4S)

Short diagram and typical pin names (verify on your board):

Battery connections (examples):

- 1S: BAT+ -> module B+, BAT- -> module B-
- 2S/3S/4S: module will have multiple cell inputs (B1, B2, B3, B4 or balance pads). Connect cells in series to corresponding pads.

Example 1S minimal wiring:

Battery (+) ----- [BAT+] module
Battery (-) ----- [BAT-] module

If module has an output header (e.g., LED pins):
- LED pins / DATA: to indicator LED array (on-board usually)

Notes:
- Always verify silkscreen labels and polarity with a multimeter before powering.
- If you have the module photos with silkscreen, add them to the folder so this file can be expanded with specific pin labels.