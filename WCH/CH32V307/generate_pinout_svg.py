#!/usr/bin/env python3
"""Generate a clean vector SVG pinout overview for CH32V307 EVT (by SCCZ / Elecrow, external WCH-Link)."""

from pathlib import Path

OUT = Path(__file__).parent / "CH32V307V-EVT-R1-pinout.svg"

# Canvas dimensions (main board only, 29-row outer headers + 2x5 SWD/UART header)
W, H = 1000, 1140

# Colors (clean technical diagram style)
BG = "#ffffff"
PCB_MAIN = "#f2f3f5"
PCB_STROKE = "#222222"
HDR_FILL = "#9ea4ad"
HDR_STROKE = "#222222"
PIN_GOLD = "#ffd200"
PIN_STROKE = "#333333"
CHIP_BODY = "#e2dcc8"
METAL_SILVER = "#d9dce0"
TEXT_DARK = "#1a1a1a"
TEXT_MUTED = "#555555"
TEXT_POWER = "#b91c1c"
TEXT_HIGHLIGHT = "#b91c1c"
LED_RED = "#ef4444"
LED_BLUE = "#60a5fa"

parts = []


def add(s: str):
    parts.append(s)


def rect(x, y, w, h, fill="none", stroke=PCB_STROKE, sw=1.2, rx=0, extra=""):
    rx_attr = f' rx="{rx}" ry="{rx}"' if rx else ""
    add(f'<rect x="{x}" y="{y}" width="{w}" height="{h}" fill="{fill}" stroke="{stroke}" stroke-width="{sw}"{rx_attr} {extra}/>')


def circle(cx, cy, r, fill="none", stroke=PCB_STROKE, sw=1.2):
    add(f'<circle cx="{cx}" cy="{cy}" r="{r}" fill="{fill}" stroke="{stroke}" stroke-width="{sw}"/>')


def line(x1, y1, x2, y2, stroke=PCB_STROKE, sw=1.2, dash=""):
    d = f' stroke-dasharray="{dash}"' if dash else ""
    add(f'<line x1="{x1}" y1="{y1}" x2="{x2}" y2="{y2}" stroke="{stroke}" stroke-width="{sw}"{d}/>')


def text(x, y, s, size=11, anchor="start", fill=TEXT_DARK, weight="normal", family="ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace"):
    esc = s.replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
    add(f'<text x="{x}" y="{y}" font-family="{family}" font-size="{size}" font-weight="{weight}" text-anchor="{anchor}" fill="{fill}">{esc}</text>')


def pin_square(cx, cy, size=5):
    half = size / 2
    rect(cx - half, cy - half, size, size, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.8)


def tactile_switch(cx, cy, label):
    rect(cx - 26, cy - 26, 52, 52, fill="#d4d7dc", stroke=PCB_STROKE, sw=1.4, rx=4)
    for dx in (-22, 22):
        for dy in (-22, 22):
            circle(cx + dx, cy + dy, 3.5, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.9)
    circle(cx, cy, 13, fill="#2c2f36", stroke=PCB_STROKE, sw=1.2)
    text(cx, cy + 44, label, size=15, anchor="middle", weight="600")


def usbc_port(cx, y_bottom, label):
    w, h = 76, 44
    x = cx - w / 2
    y = y_bottom - h
    for i in range(12):
        px = x + 12 + i * 4.6
        rect(px, y - 9, 2.8, 9, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.6)
    rect(x, y, w, h, fill=METAL_SILVER, stroke=PCB_STROKE, sw=1.4, rx=3)
    rect(x - 5, y + 8, 5, 14, fill="#b8bec6", stroke=PCB_STROKE, sw=0.9)
    rect(x + w, y + 8, 5, 14, fill="#b8bec6", stroke=PCB_STROKE, sw=0.9)
    text(cx, y + 27, label, size=15, anchor="middle", weight="600")


def led_horiz(cx, cy, label, color, label_side="left"):
    rect(cx - 12, cy - 6, 24, 12, fill="#ffffff", stroke=PCB_STROKE, sw=1)
    circle(cx, cy, 4.5, fill=color, stroke=PCB_STROKE, sw=0.9)
    if label_side == "left":
        text(cx - 18, cy + 4, label, size=13, anchor="end", weight="500")
    else:
        text(cx + 18, cy + 4, label, size=13, anchor="start", weight="500")


def mounting_hole(cx, cy):
    circle(cx, cy, 20, fill="#ffffff", stroke=PCB_STROKE, sw=1.3)
    circle(cx, cy, 13, fill="#ffffff", stroke=PCB_STROKE, sw=1.1)


# SVG Header
add(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}" width="{W}" height="{H}">')
rect(0, 0, W, H, fill=BG, stroke="none", sw=0)

# ==============================================================================
# MAIN BOARD (Elecrow / SCCZ CH32V307 EVT, external WCH-Link)
# ==============================================================================
MAIN_Y = 25
MAIN_H = 1080
rect(20, MAIN_Y, W - 40, MAIN_H, fill=PCB_MAIN, stroke=PCB_STROKE, sw=1.8, rx=4)

text(500, MAIN_Y + 295, "CH32V307V-EVT-R1", size=24, anchor="middle", weight="700")
text(500, MAIN_Y + 320, "External WCH-Link Revision (by SCCZ)", size=14, anchor="middle", fill=TEXT_MUTED)

# Mounting holes
mounting_hole(310, MAIN_Y + 62)
mounting_hole(685, MAIN_Y + 62)
mounting_hole(118, MAIN_Y + 1025)
mounting_hole(882, MAIN_Y + 1025)

# 2x5 Debug / SWD + UART IDC Header at top center (2x size)
dbg_w, dbg_h = 224, 84
dbg_x = 500 - dbg_w / 2
dbg_y = MAIN_Y + 4
rect(dbg_x, dbg_y, dbg_w, dbg_h, fill="#2d3139", stroke=PCB_STROKE, sw=1.8, rx=3)
rect(500 - 18, dbg_y - 2, 36, 10, fill=PCB_MAIN, stroke=PCB_STROKE, sw=1.2)
dbg_top_labels = ["+5V", "3V3", "GND", "PA10", "PA9"]
dbg_bot_labels = ["+5V", "3V3", "GND", "DIO", "CLK"]
text(dbg_x - 10, dbg_y + 108, "Top:", size=15, anchor="end", fill=TEXT_MUTED, weight="700")
text(dbg_x - 10, dbg_y + 128, "Bot:", size=15, anchor="end", fill=TEXT_DARK, weight="700")
for i in range(5):
    px = dbg_x + 28 + i * 42
    pin_square(px, dbg_y + 26, size=10)
    pin_square(px, dbg_y + 58, size=10)
    text(px, dbg_y + 108, dbg_top_labels[i], size=15, anchor="middle", fill=TEXT_MUTED, weight="600")
    text(px, dbg_y + 128, dbg_bot_labels[i], size=15, anchor="middle", weight="700")
text(500, dbg_y + 148, "SWD / UART (2x5)", size=13, anchor="middle", fill=TEXT_MUTED, weight="600")

# USER & RESET buttons
tactile_switch(395, MAIN_Y + 195, "USER")
tactile_switch(605, MAIN_Y + 195, "RESET")

# LED1, LED2
led_horiz(500, MAIN_Y + 205, "LED1", LED_BLUE, "left")
led_horiz(500, MAIN_Y + 230, "LED2", LED_BLUE, "left")

# ==============================================================================
# CENTRAL MCU: CH32V307VCT6 (LQFP100)
# ==============================================================================
MCU_S = 186
MCU_X = 500 - MCU_S / 2
MCU_Y = MAIN_Y + 355
rect(MCU_X, MCU_Y, MCU_S, MCU_S, fill=CHIP_BODY, stroke=PCB_STROKE, sw=1.6)
circle(MCU_X + 14, MCU_Y + MCU_S - 14, 4, fill=PCB_STROKE, stroke="none")
lead_pitch = (MCU_S - 16) / 24
for i in range(25):
    offset = 8 + i * lead_pitch
    rect(MCU_X + offset - 1.5, MCU_Y - 12, 3, 12, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.5)
    rect(MCU_X + offset - 1.5, MCU_Y + MCU_S, 3, 12, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.5)
    rect(MCU_X - 12, MCU_Y + offset - 1.5, 12, 3, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.5)
    rect(MCU_X + MCU_S, MCU_Y + offset - 1.5, 12, 3, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.5)

text(500, MCU_Y + 68, "CH32V307", size=22, anchor="middle", weight="700")
text(500, MCU_Y + 102, "VCT6", size=22, anchor="middle", weight="700")
text(MCU_X + MCU_S - 28, MCU_Y + MCU_S - 18, "WCH", size=18, anchor="middle", weight="600")

# ==============================================================================
# BOTTOM CONNECTORS: P7 (USB-C), P2 (RJ45), P6 (USB-C), LDO, PWR LED
# ==============================================================================
rect(295, MAIN_Y + 897, 54, 34, fill="#222222", stroke=PCB_STROKE, sw=1)
rect(310, MAIN_Y + 883, 24, 14, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.8)
for lx in (302, 319, 336):
    rect(lx, MAIN_Y + 931, 6, 16, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.7)

rect(210, MAIN_Y + 950, 14, 24, fill="#ffffff", stroke=PCB_STROKE, sw=1)
circle(217, MAIN_Y + 962, 4.5, fill=LED_RED, stroke=PCB_STROKE, sw=0.8)
text(217, MAIN_Y + 991, "PWR", size=14, anchor="middle", weight="600")

usbc_port(270, MAIN_Y + MAIN_H + 14, "P7")

p2_w, p2_h = 116, 152
p2_x = 500 - p2_w / 2
p2_y = MAIN_Y + MAIN_H - 134
rect(p2_x, p2_y, p2_w, p2_h, fill=METAL_SILVER, stroke=PCB_STROKE, sw=1.5)
rect(p2_x - 8, p2_y + 52, 8, 24, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.8)
rect(p2_x + p2_w, p2_y + 52, 8, 24, fill=PIN_GOLD, stroke=PIN_STROKE, sw=0.8)
text(500, p2_y + 82, "P2 (RJ45)", size=16, anchor="middle", weight="600")

usbc_port(730, MAIN_Y + MAIN_H + 14, "P6")

# ==============================================================================
# LEFT HEADERS: J3 (2x29), J5 (1x8), J6 (1x6)
# ==============================================================================
HDR_PITCH = 28.5
J3_X = 95
J3_Y = MAIN_Y + 52
J3_W = 46
J3_H = 29 * HDR_PITCH + 14

rect(J3_X, J3_Y, J3_W, J3_H, fill=HDR_FILL, stroke=HDR_STROKE, sw=1.3)
text(J3_X + J3_W / 2, J3_Y - 10, "J3", size=17, anchor="middle", weight="700")

j3_left_labels = [
    ("GND", TEXT_POWER),
    ("+5V", TEXT_POWER),
    ("3V3", TEXT_DARK),
    ("BOOT1", TEXT_HIGHLIGHT),
    ("GND", TEXT_POWER),
    ("3V3", TEXT_DARK),
    ("GND", TEXT_DARK),
    ("ELED1", TEXT_DARK),
    ("ELED2", TEXT_DARK),
    ("VCC", TEXT_DARK),
    ("+5V", TEXT_DARK),
    ("LED1", TEXT_DARK),
    ("LED2", TEXT_DARK),
    ("KEY", TEXT_HIGHLIGHT),
    ("GND", TEXT_DARK),
    ("PA14", TEXT_DARK),
    ("PA13", TEXT_DARK),
    ("PC0", TEXT_DARK),
    ("PC1", TEXT_DARK),
    ("PC2", TEXT_DARK),
    ("PC3", TEXT_DARK),
    ("PC4", TEXT_DARK),
    ("PB2", TEXT_DARK),
    ("PE8", TEXT_DARK),
    ("PE10", TEXT_DARK),
    ("PE12", TEXT_DARK),
    ("PE14", TEXT_DARK),
    ("PD8", TEXT_DARK),
    ("PD10", TEXT_DARK),
]

j3_right_labels = {
    0: ("GND", TEXT_POWER),
    1: ("+5V", TEXT_POWER),
    2: ("3V3", TEXT_DARK),
    3: ("BOOT0", TEXT_HIGHLIGHT),
    4: ("GND", TEXT_POWER),
    5: ("3V3", TEXT_DARK),
    21: ("PC5", TEXT_DARK),
    22: ("PE7", TEXT_DARK),
    23: ("PE9", TEXT_DARK),
    24: ("PE11", TEXT_DARK),
    25: ("PE13", TEXT_DARK),
    26: ("PE15", TEXT_DARK),
    27: ("PD9", TEXT_DARK),
    28: ("PD11", TEXT_DARK),
}

for r in range(29):
    py = J3_Y + 20 + r * HDR_PITCH
    px_l = J3_X + 12
    px_r = J3_X + 34
    pin_square(px_l, py)
    pin_square(px_r, py)

    lbl, col = j3_left_labels[r]
    text(J3_X - 8, py + 4.5, lbl, size=13.5, anchor="end", fill=col, weight="600" if col != TEXT_DARK else "normal")

    if r in j3_right_labels:
        rlbl, rcol = j3_right_labels[r]
        text(J3_X + J3_W + 8, py + 4.5, rlbl, size=13.5, anchor="start", fill=rcol, weight="600" if rcol != TEXT_DARK else "normal")

# J5 (8-pin, aligned with J3 rows 6..13)
J5_X = 186
J5_Y = J3_Y + 6 * HDR_PITCH + 2
J5_W = 24
J5_H = 8 * HDR_PITCH + 10
rect(J5_X, J5_Y, J5_W, J5_H, fill=HDR_FILL, stroke=HDR_STROKE, sw=1.3)
text(J5_X + J5_W / 2, J5_Y - 10, "J5", size=16, anchor="middle", weight="700")

j5_labels = [("NC", TEXT_MUTED), ("VCC", TEXT_DARK), ("NRST", TEXT_DARK), ("VCC", TEXT_DARK), ("+5V", TEXT_DARK), ("GND", TEXT_DARK), ("GND", TEXT_DARK), ("+5V", TEXT_DARK)]
for i, (lbl, col) in enumerate(j5_labels):
    py = J5_Y + 18 + i * HDR_PITCH
    px = J5_X + J5_W / 2
    pin_square(px, py)
    line(J3_X + 37, py, px - 3, py, stroke="#555555", sw=0.9)
    text(J5_X + J5_W + 8, py + 4.5, lbl, size=13.5, anchor="start", fill=col)

# J6 (6-pin, aligned with J3 rows 15..20)
J6_X = 186
J6_Y = J3_Y + 15 * HDR_PITCH + 2
J6_W = 24
J6_H = 6 * HDR_PITCH + 10
rect(J6_X, J6_Y, J6_W, J6_H, fill=HDR_FILL, stroke=HDR_STROKE, sw=1.3)
text(J6_X + J6_W / 2, J6_Y - 10, "J6", size=16, anchor="middle", weight="700")

j6_labels = ["PA0", "PA1", "PA2", "PA3", "PA4", "PA5"]
for i, lbl in enumerate(j6_labels):
    py = J6_Y + 18 + i * HDR_PITCH
    px = J6_X + J6_W / 2
    pin_square(px, py)
    line(J3_X + 37, py, px - 3, py, stroke="#555555", sw=0.9)
    text(J6_X + J6_W + 8, py + 4.5, lbl, size=13.5, anchor="start")

# ==============================================================================
# RIGHT HEADERS: J4 (2x29), J7 (1x10), J8 (1x8)
# ==============================================================================
J4_X = W - 95 - 46
J4_Y = MAIN_Y + 52
J4_W = 46
J4_H = 29 * HDR_PITCH + 14

rect(J4_X, J4_Y, J4_W, J4_H, fill=HDR_FILL, stroke=HDR_STROKE, sw=1.3)
text(J4_X + J4_W / 2, J4_Y - 10, "J4", size=17, anchor="middle", weight="700")

j4_right_labels = [
    ("+5V", TEXT_POWER),
    ("3V3", TEXT_DARK),
    ("PC13", TEXT_DARK),
    ("VBAT", TEXT_DARK),
    ("PE6", TEXT_DARK),
    ("PE5", TEXT_DARK),
    ("PE4", TEXT_DARK),
    ("PE3", TEXT_DARK),
    ("PE2", TEXT_DARK),
    ("PE1", TEXT_DARK),
    ("PE0", TEXT_DARK),
    ("PB7", TEXT_DARK),
    ("PB6", TEXT_DARK),
    ("PB4", TEXT_DARK),
    ("PB3", TEXT_DARK),
    ("PD7", TEXT_DARK),
    ("PD5", TEXT_DARK),
    ("PD4", TEXT_DARK),
    ("PD3", TEXT_DARK),
    ("PD2", TEXT_DARK),
    ("PD1", TEXT_DARK),
    ("PC12", TEXT_DARK),
    ("PC10", TEXT_DARK),
    ("NC", TEXT_MUTED),
    ("PA11", TEXT_DARK),
    ("PC8", TEXT_DARK),
    ("PC6", TEXT_DARK),
    ("PD14", TEXT_DARK),
    ("PD12", TEXT_DARK),
]

j4_left_labels = {
    0: ("GND", TEXT_POWER),
    1: ("GND", TEXT_POWER),
    12: ("PD6", TEXT_DARK),
    21: ("PD0", TEXT_DARK),
    22: ("PC11", TEXT_DARK),
    23: ("PA15", TEXT_DARK),
    24: ("PA12", TEXT_DARK),
    25: ("PC9", TEXT_DARK),
    26: ("PC7", TEXT_DARK),
    27: ("PD15", TEXT_DARK),
    28: ("PD13", TEXT_DARK),
}

for r in range(29):
    py = J4_Y + 20 + r * HDR_PITCH
    px_l = J4_X + 12
    px_r = J4_X + 34
    pin_square(px_l, py)
    pin_square(px_r, py)

    rlbl, rcol = j4_right_labels[r]
    text(J4_X + J4_W + 8, py + 4.5, rlbl, size=13.5, anchor="start", fill=rcol, weight="600" if rcol != TEXT_DARK else "normal")
    if r in j4_left_labels:
        llbl, lcol = j4_left_labels[r]
        text(J4_X - 8, py + 4.5, llbl, size=13.5, anchor="end", fill=lcol, weight="600" if lcol != TEXT_DARK else "normal")

# J7 (10-pin, aligned with J4 rows 2..11)
J7_X = J4_X - 45 - 24
J7_Y = J4_Y + 2 * HDR_PITCH + 2
J7_W = 24
J7_H = 10 * HDR_PITCH + 10
rect(J7_X, J7_Y, J7_W, J7_H, fill=HDR_FILL, stroke=HDR_STROKE, sw=1.3)
text(J7_X + J7_W / 2, J7_Y - 10, "J7", size=16, anchor="middle", weight="700")

j7_labels = ["PB10", "PB11", "VDDA", "GND", "PB13", "PB14", "PB15", "PB12", "PB0", "PB1"]
for i, lbl in enumerate(j7_labels):
    py = J7_Y + 18 + i * HDR_PITCH
    px = J7_X + J7_W / 2
    pin_square(px, py)
    line(px + 3, py, J4_X + 9, py, stroke="#555555", sw=0.9)
    text(J7_X - 8, py + 4.5, lbl, size=13.5, anchor="end")

# J8 (8-pin, aligned with J4 rows 13..20)
J8_X = J4_X - 45 - 24
J8_Y = J4_Y + 13 * HDR_PITCH + 2
J8_W = 24
J8_H = 8 * HDR_PITCH + 10
rect(J8_X, J8_Y, J8_W, J8_H, fill=HDR_FILL, stroke=HDR_STROKE, sw=1.3)
text(J8_X + J8_W / 2, J8_Y - 10, "J8", size=16, anchor="middle", weight="700")

j8_labels = ["PB9", "PB8", "PB5", "PA6", "PA7", "PA8", "PA9", "PA10"]
for i, lbl in enumerate(j8_labels):
    py = J8_Y + 18 + i * HDR_PITCH
    px = J8_X + J8_W / 2
    pin_square(px, py)
    line(px + 3, py, J4_X + 9, py, stroke="#555555", sw=0.9)
    text(J8_X - 8, py + 4.5, lbl, size=13.5, anchor="end")

add("</svg>")

OUT.write_text("\n".join(parts), encoding="utf-8")
print(f"Wrote {OUT} ({OUT.stat().st_size} bytes)")
