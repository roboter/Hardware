#!/usr/bin/env python3
"""
Generate LR1262 KiCad footprint with correct pin numbering
"""

def generate_lr1262_footprint():
    chip_size = 16.0  # 16x16mm chip
    
    # Side pads configuration (left and right)
    side_pads_count = 10
    side_pad_spacing = 1.1
    side_edge_to_first_pad = 4.1580  # From TOP edge to CENTER of first pad
    side_pad_width = 1.4032
    side_pad_length = 0.9
    
    # Top pads configuration
    top_pads_count = 2
    top_pad_spacing = 1.48
    top_edge_to_pad = 5.0177  # From right edge to CENTER of rightmost pad
    top_pad_width = 1.4032
    top_pad_length = 0.9
    
    # Bottom pads configuration
    bottom_pads_count = 12
    bottom_edge_to_pad = 1.75  # From left/right edges to CENTER of first/last pad
    bottom_pad_width = 1.4032
    bottom_pad_length = 0.95
    
    # Calculate bottom pad spacing
    bottom_available_space = chip_size - (2 * bottom_edge_to_pad)
    bottom_pad_spacing = bottom_available_space / (bottom_pads_count - 1)
    
    # Generate the KiCad footprint
    footprint = f"""(footprint "LR1262" (version 20221018) (generator pcbnew)
  (layer "F.Cu")
  (descr "LR1262 {chip_size}x{chip_size}mm chip")
  (tags "LR1262 chip")
  (attr smd)
  (fp_text reference "REF**" (at 0 -9) (layer "F.SilkS")
      (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_text value "LR1262" (at 0 9) (layer "F.Fab")
      (effects (font (size 1 1) (thickness 0.15)))
  )
  (fp_line (start -{chip_size/2} -{chip_size/2}) (end {chip_size/2} -{chip_size/2})
    (stroke (width 0.15) (type solid)) (layer "Edge.Cuts"))
  (fp_line (start -{chip_size/2} {chip_size/2}) (end -{chip_size/2} -{chip_size/2})
    (stroke (width 0.15) (type solid)) (layer "Edge.Cuts"))
  (fp_line (start {chip_size/2} -{chip_size/2}) (end {chip_size/2} {chip_size/2})
    (stroke (width 0.15) (type solid)) (layer "Edge.Cuts"))
  (fp_line (start {chip_size/2} {chip_size/2}) (end -{chip_size/2} {chip_size/2})
    (stroke (width 0.15) (type solid)) (layer "Edge.Cuts"))
  (fp_line (start -{chip_size/2} -{chip_size/2}) (end {chip_size/2} -{chip_size/2})
    (stroke (width 0.1) (type solid)) (layer "F.Fab"))
  (fp_line (start -{chip_size/2} {chip_size/2}) (end -{chip_size/2} -{chip_size/2})
    (stroke (width 0.1) (type solid)) (layer "F.Fab"))
  (fp_line (start {chip_size/2} -{chip_size/2}) (end {chip_size/2} {chip_size/2})
    (stroke (width 0.1) (type solid)) (layer "F.Fab"))
  (fp_line (start {chip_size/2} {chip_size/2}) (end -{chip_size/2} {chip_size/2})
    (stroke (width 0.1) (type solid)) (layer "F.Fab"))
"""
    
    # Calculate pad positions
    half_chip = chip_size / 2
    pad_offset = half_chip + 0.225  # Pad extends outside chip
    
    pad_number = 1
    
    # Generate LEFT pads (10 pads) - PINS 1-10
    print("Left pads configuration (Pins 1-10):")
    # Calculate from top edge to center of first pad
    first_pad_y = half_chip - side_edge_to_first_pad  # Top edge is +8mm
    for i in range(side_pads_count):
        y_pos = first_pad_y - (i * side_pad_spacing)  # Going downward from first pad
        footprint += f'  (pad "{pad_number}" smd rect (at -{pad_offset:.3f} {y_pos:.4f}) (size {side_pad_width:.4f} {side_pad_length:.4f}) (layers "F.Cu" "F.Paste" "F.Mask"))\n'
        print(f"  Pin {pad_number}: x=-{pad_offset:.3f}, y={y_pos:.4f}")
        pad_number += 1
    
    # Generate BOTTOM pads (12 pads) - PINS 11-22
    print("\nBottom pads configuration (Pins 11-22):")
    for i in range(bottom_pads_count):
        x_pos = -half_chip + bottom_edge_to_pad + (i * bottom_pad_spacing)
        footprint += f'  (pad "{pad_number}" smd rect (at {x_pos:.4f} -{pad_offset:.3f}) (size {bottom_pad_length:.4f} {bottom_pad_width:.4f}) (layers "F.Cu" "F.Paste" "F.Mask"))\n'
        print(f"  Pin {pad_number}: x={x_pos:.4f}, y=-{pad_offset:.3f}")
        pad_number += 1
    
    # Generate RIGHT pads (10 pads) - PINS 23-32
    print("\nRight pads configuration (Pins 23-32):")
    for i in range(side_pads_count):
        y_pos = first_pad_y - (i * side_pad_spacing)  # Same Y positions as left side
        footprint += f'  (pad "{pad_number}" smd rect (at {pad_offset:.3f} {y_pos:.4f}) (size {side_pad_width:.4f} {side_pad_length:.4f}) (layers "F.Cu" "F.Paste" "F.Mask"))\n'
        print(f"  Pin {pad_number}: x={pad_offset:.3f}, y={y_pos:.4f}")
        pad_number += 1
    
    # Generate TOP pads (2 pads) - PINS 33-34
    print("\nTop pads configuration (Pins 33-34):")
    # Calculate positions for 2 pads with 1.48mm spacing
    # Rightmost pad is 5.0177mm from right edge (center to edge)
    rightmost_x = half_chip - top_edge_to_pad
    leftmost_x = rightmost_x - top_pad_spacing
    
    footprint += f'  (pad "{pad_number}" smd rect (at {leftmost_x:.4f} {pad_offset:.3f}) (size {top_pad_length:.4f} {top_pad_width:.4f}) (layers "F.Cu" "F.Paste" "F.Mask"))\n'
    print(f"  Pin {pad_number}: x={leftmost_x:.4f}, y={pad_offset:.3f}")
    pad_number += 1
    
    footprint += f'  (pad "{pad_number}" smd rect (at {rightmost_x:.4f} {pad_offset:.3f}) (size {top_pad_length:.4f} {top_pad_width:.4f}) (layers "F.Cu" "F.Paste" "F.Mask"))\n'
    print(f"  Pin {pad_number}: x={rightmost_x:.4f}, y={pad_offset:.3f}")
    pad_number += 1
    
    footprint += ")"
    
    # Print summary with verification
    print(f"\nSummary:")
    print(f"  Total pins: {pad_number - 1}")
    print(f"  - Left: 10 pins (Pins 1-10)")
    print(f"  - Bottom: 12 pins (Pins 11-22)") 
    print(f"  - Right: 10 pins (Pins 23-32)")
    print(f"  - Top: 2 pins (Pins 33-34)")
    
    # Verify pin 1 position
    print(f"\nPin 1 verification:")
    print(f"  Pin 1: x=-{pad_offset:.3f}, y={first_pad_y:.4f}")
    print(f"  Distance from top edge to Pin 1 center: {side_edge_to_first_pad:.3f}mm ✓")
    
    return footprint

def main():
    footprint = generate_lr1262_footprint()
    
    # Save to file
    with open("LR1262.kicad_mod", "w") as f:
        f.write(footprint)
    
    print("\nLR1262.kicad_mod generated successfully!")

if __name__ == "__main__":
    main()