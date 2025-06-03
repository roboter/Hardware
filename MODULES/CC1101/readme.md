## Libraries HAL
* https://github.com/dsoldevila/CC1101 - not finished



## PlatformIO working CC1101 library with stm32F407


```ini
[env:black_f407ve]
platform = ststm32
board = black_f407ve
framework = arduino
upload_protocol = stlink
debug_tool = stlink
lib_deps =
    https://github.com/pkarsy/CC1101_RF.git
```