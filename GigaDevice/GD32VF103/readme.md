## GigaDevice page
https://www.gd32mcu.com/en/download/7?kw=GD32VF1
check mark to get all documentation

search does not work

## Links

https://www.hackster.io/news/gigadevice-unveils-new-risc-v-based-gd32v-microcontroller-c0a2b147568b
https://doc.nucleisys.com/nuclei_sdk/design/soc/gd32vf103.html
https://lupyuen.github.io/articles/porting-apache-mynewt-os-to-gigadevice-gd32-vf103-on-risc-v - differences
https://robbert-groen.medium.com/getting-started-with-the-gd32vf103-risc-v-microcontroller-22cb34718b0d - install under linux


## Description 

Power: 3.3v
Full chip Name: GD32VF103RBT6
Flash: 128Kb
FMax: 108MHz

After 103 is package
GD32VF103Vx LQFP100
GD32VF103Rx LQFP64 <--
GD32VF103Cx LQFP48
GD32VF103Tx QFN36

OTG why USB-mini?

## OpenOCD Config

-f "interface/cmsis-dap.cfg" -f "target/gd32vf103_jtag.cfg"

