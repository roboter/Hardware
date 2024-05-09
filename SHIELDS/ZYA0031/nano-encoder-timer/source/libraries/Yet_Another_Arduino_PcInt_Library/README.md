Yet Another Arduino PcInt Library
=================================

As you may have guessed, this is an Arduino library to handle Pin Change Interrupts.

Examples
-------

``` c++
#define PCINT_PIN A15

#include <YetAnotherPcInt.h>

void pinChanged(const char* message, bool pinstate) {
  Serial.print(message);
  Serial.println(pinstate ? "HIGH" : "LOW");
}

void setup() {
  Serial.begin(115200);
  pinMode(PCINT_PIN, INPUT_PULLUP);
  PcInt::attachInterrupt(PCINT_PIN, pinChanged, "Pin has changed to ", CHANGE);
}

void loop() {}
```

Features
--------
- Easy to install and use
- Callbacks provide useful arguments:

  - _A User-provided pointer_: This can be an object with some context, a string to print, or to whatever else you want.

    This is specially useful when developing components that can be instantiated many times ([See example](examples/PinListenerComponent/PinListenerComponent.ino))
    
  - _The pin's state_: That's the very first thing you were going to do inside the callbacks, wasn't it?
    
    Providing it as an argument prevents concurrency issues.
    
- It should support `RISING`/`FALLING`/`CHANGE` modes

- Code is very efficient (It's an ISR, after all)

- Code is very small (~250 lines) and readable

API
---

### attachInterrupt

Attaches a callback function to Pin Change Interruptions on the specified pin.

```
void PcInt.attachInterrupt(
    uint8_t pin, 
    callback func, 
    T *userdata, 
    uint8_t mode=CHANGE, 
    bool trigger_now=false);
```

Arguments:

* `pin`: The pin number you are listening.
* `callback`: The funcion called whenever the interrupt was triggered. 
  
  Your funcion must look like one of these:
  
  * `void myfunction() { ... }`
  * `void myfunction(bool newstate) { ... }`
  * `void myfunction(T* userdata) { ... }`
  * `void myfunction(T* userdata, bool newstate) { ... }`
* `userdata`: User-provided argument for `callback`. Skip this If your callback doesn't have a `userdata` argument.
  
  User-provided arguments are useful when reusing the same callback funcion to handle changes on multiple pins.

* `mode`: The transition Which triggers the callbacks: `CHANGE`, `RISING` or `FALLING`.

* `trigger_now`: If set, the callback is called immediately. This is useful for initialization.

### detachInterrupt
```
void PcInt.detachInterrupt(
    uint8_t pin);
```

Removes the callback function from Pin Change Interruptions on the specified pin.

Arguments:

* `pin`: The pin number you are no longer listening to.

About Pin Change Interruptions
------------------------------

AVR microcontrollers only have a few external Interruption pins.
But I want to monitor more pins... Looots more!

The alternative is using pin change interrupts, which is supported on lots of pins simultaneously.

The interrupt can be enabled for each supported pin individually, but there are only a few interrupt vectors, so up to 8 pins share the same service routine.

It's up to the software to figure out which pins changed state and act accordingly. This library does it for you :)


Comparisson with other libraries
--------------------------------

As the name suggests, there are many other libraries out there for handling Pin Change Interruptions.

In particular, this project started as a fork of [Sodaq_PcInt](https://github.com/SodaqMoja/Sodaq_PcInt) and 
uses [PinChangeInterruptBoards.h](src/PinChangeInterruptBoards.h) from [NicoHood's PinChangeInterrupt Library](https://github.com/NicoHood/PinChangeInterrupt)

I've looked at many of them before I decided to create this library, and this is how they compare.

- [PcInt example code](http://playground.arduino.cc/Main/PcInt) from [arduino.cc](http://www.arduino.cc/)
  - [ ] Not available on Arduino's library manager (It's not really a library, after all)
  - [ ] Doesn't support user data on callbacks
  - [ ] Doesn't provide trigger type (`RISING`/`FALLING`)
  - [X] Supports `RISING`/`FALLING`/`CHANGE` modes
  - [ ] Not very optimized
  - [X] Code quality is Okay
  - [ ] I think it might need some tweaks depending on the microcontroller used

- [Sodaq_PcInt](https://github.com/SodaqMoja/Sodaq_PcInt) by [SODAQ](https://github.com/SodaqMoja)
  - [X] Available on Arduino's library manager
  - [ ] Doesn't support user data on callbacks
  - [ ] Doesn't provide trigger type (`RISING`/`FALLING`)
  - [ ] Doesn't supports `RISING`/`FALLING`/`CHANGE` modes (Unless you are using [GabrielNotman's fork](https://github.com/GabrielNotman/Sodaq_PcInt))
  - [X] Very optimized
  - [X] Excelent code
  - [X] Should support all/most AVR Arduinos

- [PinChangeInterrupt Library](https://github.com/NicoHood/PinChangeInterrupt) by [NicoHood](https://github.com/NicoHood)
  - [X] Available on Arduino's library manager
  - [ ] Doesn't support user data on callbacks
  - [X] Provides trigger type (`RISING`/`FALLING`) via `getPinChangeInterruptTrigger()`
  - [X] Supports `RISING`/`FALLING`/`CHANGE` modes
  - [X] It's super-optimized and configurable, but...
  - [ ] The code is a bit messy (IMHO, anyway)
  - [X] Should on all/most AVR Arduinos

- [EnableInterrupt](https://github.com/GreyGnome/EnableInterrupt) by [Mike "GreyGnome" Schwager](https://github.com/GreyGnome)
  - [X] Available on Arduino's library manager
  - [ ] Doesn't support user data on callbacks (but does provide the pin number via the `EI_ARDUINO_INTERRUPTED_PIN` macro)
  - [ ] Doesn't provide trigger type (`RISING`/`FALLING`)
  - [X] Supports `RISING`/`FALLING`/`CHANGE` modes
  - [X] It's super-optimized and configurable, but...
  - [ ] Big monolithic messy code
  - [X] Should support all/most AVR Arduinos (It also supports External Interrupts!)

- [PciManager](https://github.com/prampec/arduino-pcimanager) by [Balazs Kelemen](https://github.com/prampec)
  - [X] Available on Arduino's library manager
  - [ ] Doesn't support user data on callbacks
  - [X] Provides trigger type (`RISING`/`FALLING`) via `getPinChangeInterruptTrigger()`
  - [ ] Doesn't supports `RISING`/`FALLING`/`CHANGE` modes
  - [ ] Not very optimized
  - [X] Good code quality
  - [X] Should support all/most AVR Arduinos
