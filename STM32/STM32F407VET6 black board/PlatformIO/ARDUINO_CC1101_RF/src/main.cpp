/*
    Arduino CC1101_RF library demo. Build 2(or more!) modules and upload the same sketch
 
 
   PIN connections.

   CC1101     ProMini(3.3@8MHz)     Blue/        ESP8266
              bare atmega328        BlackPill    NodeMCU etc.

    CSN            10               PA4(SS1)     D8(CS)
    CSK            13               PA5(SCK1)    D5
    MISO           12               PA6(MISO1)   D6(MISO)+D2(for digitalReead)
    MOSI           11               PA7(MOSI1)   D7(MOSI)
    GND            GND              GND          GND
    VCC          3.3V/Vcc           3.3V         3.3V

    * GDO0        is not used (See the pingLowPower example for this)
    * ESP8266 CC1101-MISO + D6 + D2 are connected as esp8266 cannot read MISO if SPI is active
    * The source code Pin definitions assume atmega328 target, change them for other targets
    
    Also connect a LED to an unused PIN
*/

#include <Arduino.h>
#include <SPI.h>
#include <CC1101_RF.h>

byte LEDPIN = PA7;
// or if the platdorm has one and want to use it
// byte LEDPIN = LED_BUILTIN;

// We can send packets without using the serial terminal
byte BUTTONPIN = PE4;

// Your specific connections:
#define CC1101_CS   PB7  // Chip Select
#define CC1101_GDO0 PB6  // GDO0 (interrupt, optional)

// Use SPI1 (on PB3/PB4/PB5)
CC1101 radio(CC1101_CS, CC1101_GDO0, SPI);
// or
// CC1101 radio(A0); // Uses Arduino Pin A0 for CSN
//
// or if using 2 second SPI bus on a bluepill
// SPIClass spi2(2); // the second SPI bus
// CC1101 pins  CSN, MISO, SPIbus
// CC1101 radio( PB12, PB14, spi2 );
//
// ESP8266 (see notes above)
// CC1101 radio(D8,  D2);

// Works with a mechanical button and INPUT_PULUP pin 
bool debounceButton() {
    static byte buttonState; // debounced state LOW or HIGH (for 50ms)
    static byte previousReading;  // the previous reading
    static uint32_t lastChangeTime; // we need to have at least 50ms the same state to be reliable
    // current reading
    byte reading = digitalRead(BUTTONPIN);
    // If the switch changed, due to noise or pressing:
    if (reading != previousReading) {
        previousReading = reading;
        // reset the debouncing timer, =millis() means NOW
        lastChangeTime = millis();
    }
    if (millis()-lastChangeTime>50) {
        // the reading is same for the last 50 ms
        //
        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;
            // We return true to the caller
            // only when we transition frm HIGH to LOW
            // and the caller is signalled to take action
            if (buttonState == LOW) {
                return true;
            }
        }
    }
    // All other cases return false
    return false;
}

void showhelp() {
    Serial.println("Press some alphanumeric keys to send 1-byte RF packets");
    Serial.println("Special commands are \"=\" and \".\"");
}

void cc1101Reset() {
  digitalWrite(CC1101_CS, HIGH);
  delayMicroseconds(30);
  digitalWrite(CC1101_CS, LOW);
  delayMicroseconds(30);
  digitalWrite(CC1101_CS, HIGH);
  delayMicroseconds(45);
  digitalWrite(CC1101_CS, LOW);

  // Send SRES strobe
  SPI.transfer(0x30);  // SRES command
  digitalWrite(CC1101_CS, HIGH);
  delay(1);
}

uint8_t cc1101ReadRegister(uint8_t addr) {
  digitalWrite(CC1101_CS, LOW);
  SPI.transfer(addr | 0x80);  // READ single
  uint8_t val = SPI.transfer(0x00);
  digitalWrite(CC1101_CS, HIGH);
  return val;
}
uint8_t readStatusReg(uint8_t addr) {
    digitalWrite(CC1101_CS, LOW);
  //  while (digitalRead(_misoPin)); // wait for MISO to go low

    // Send address with status read bits (0xC0 OR address)
    SPI.transfer(addr | 0xC0);
    uint8_t val = SPI.transfer(0x00);

    digitalWrite(CC1101_CS, HIGH);
    return val;
}

void CC1101_DumpRegisters(char *buf, size_t bufsize) {
  uint8_t regVal;
  size_t idx = 0;

  for (uint8_t addr = 0x00; addr <= 0x2F; addr++) {
    regVal = radio.readRegister(addr);  // Replace with your CC1101 read function
    idx += snprintf(buf + idx, bufsize - idx, "[0x%02X]=0x%02X,", addr, regVal);
    if (idx >= bufsize - 1) break; // Prevent buffer overflow
  }

  // Append PARTNUM
  regVal = readStatusReg(CC1101_PARTNUM);
  idx += snprintf(buf + idx, bufsize - idx, "\nPARTNUM = 0x%02X\n", regVal);
  if (idx >= bufsize - 1) return;

  // Append VERSION
  regVal = readStatusReg(CC1101_VERSION);
  idx += snprintf(buf + idx, bufsize - idx, "VERSION = 0x%02X\n", regVal);
}


void setup() {
 volatile int sysClockFreq = HAL_RCC_GetSysClockFreq();
  volatile int HCLKFreq = HAL_RCC_GetHCLKFreq();
  volatile int PCLK1Freq = HAL_RCC_GetPCLK1Freq();
  volatile int PCLK2Freq = HAL_RCC_GetPCLK2Freq();
  Serial.begin(115200);
  pinMode(PB7, OUTPUT);  // CS
  digitalWrite(PB7, HIGH);

  SPI.begin(); // - this is needed // SPI1 on PB3/PB4/PB5


  volatile uint32_t prescaler = (SPI1->CR1 & SPI_CR1_BR_Msk) >> SPI_CR1_BR_Pos;

 volatile uint16_t spi_div[] = {2,4,8,16,32,64,128,256}; // lookup table
volatile  uint32_t spi_clk = PCLK2Freq / spi_div[prescaler];
//SPI.begin(); // MOSI, MISO, SCK
// SPI.setDataMode(SPI_MODE0);
// SPI.setClockDivider(SPI_CLOCK_DIV32); // Or slower
// SPI.setBitOrder(MSBFIRST);

  delay(100);

   // 433.2 MHz . The function is getting uint32_t (433200000) , not float
    bool ok = radio.begin(433.2e6);

    uint8_t mdmcfg2 = radio.readRegister(CC1101_MDMCFG2);
uint8_t modulation = mdmcfg2 & 0x03; // Extract bits 1:0

Serial.println("Current Modulation: ");
switch(modulation) {
    case 0x00: Serial.println("2-FSK\n"); break;
    case 0x01: Serial.println("GFSK\n"); break;
    case 0x02: Serial.println("ASK/OOK\n"); break;
    case 0x03: Serial.println("4-FSK\n"); break;
}

char buf[900] = {};
CC1101_DumpRegisters(buf, 900);
Serial.println(buf);
    // Configure CC1101 parameters
    // radio.setTxPower(10);       // 10 dBm output power
    // radio.setDataRate(38.4);    // 38.4 kbps data rate
    // radio.setChannel(0);        // Channel 0
    // radio.setSyncWord(0xD3, 0x91); // Default sync word
    if (!ok) {
        Serial.println("CC1101 is not found, check the connections");
        while(1);
    }

    // Start listening. Should be the last radio related command inside setup()
    // This of course is subject to the communication schema used
    radio.setRXstate();

    showhelp();

    // LED setup. It is importand as we can use the module without serial terminal
    pinMode(LEDPIN, OUTPUT);
    // or use an external more visible LED for outdoor tests
    // pinMode(PB9, OUTPUT); // A LED connected to PB9 - GND

    // BUTTON setup, do we can send packets without a serial terminal
    pinMode(BUTTONPIN, INPUT_PULLUP);
}

void setup1() {
    // atmega328@8mhz can do 57600
    // bluepill, nodemcu can communicate with higher speeds(not needed)
    // depending of course of the Serial port used
    Serial.begin(57600);
    Serial.println("CC1101_RF library example");
    // The library does not start SPI automatically. If your program stucks at radio.begin()
    // it is probably because you forgot this.
  //  SPI.begin();
    // 433.2 MHz . The function is getting uint32_t (433200000) , not float
    bool ok = radio.begin(433.2e6);

   // radio.setXtalFrequency(26000000);  // 26 MHz

    // Configure CC1101 parameters
    // radio.setTxPower(10);       // 10 dBm output power
    // radio.setDataRate(38.4);    // 38.4 kbps data rate
    // radio.setChannel(0);        // Channel 0
    // radio.setSyncWord(0xD3, 0x91); // Default sync word
    if (!ok) {
        Serial.println("CC1101 is not found, check the connections");
        while(1);
    }

    // The following commands should be used after radio.begin()
    // and before radio.setRXstate()

    // The default is 4800, lower baudrate but longer distance and obstacle penetration
    // radio.setBaudrate4800bps(); // no need to set, is the default
    // or
    // radio.setBaudrate38000bps(); // higher baudrate but shorter distance.

    // this is the default, no need to set explicity
    // radio.setPower10dbm();
    // They can be used to reduce interference to nearby projects and is good for
    // tests at very short distances
    // radio.setPower5dbm();
    // radio.setPower0dbm();
    
    // 99.9% Do not use it
    // Do not use sync word for packet filtering. The default syncword has the best reception capability
    // Use differnet frequences to isolate different projects and addresses for fine tuning.
    // 
    // radio.setSyncWord(0x91, 0xD3); // this is the default and best, no need to set
    // or setSyncWord10(sync1 ,sync0)
    // radio.setSyncWord10(0xD3 ,0x91);
    
    // If enabled the cc1101 chip
    // rejects packets with different addresses(the first byte of the packet)
    // In this demo you can enable it at runtime with '=' keypress
    // the default is radio.disableAddressCheck()
    // it is the responsibility of the developer to construct a packet with the correct
    // the first byte, and also to strip the first byte from incoming packets.
    //
    // the radio will reject all packets with packet[0]!=3
    // radio.enableAddressCheck(3);
    //
    // The same but we can actually print the packet and see the address (for tests)
    // radio.enableAddressCheck('W');
    //
    // Similar but also accepts packets beginning with 0x00 (broadcast address)
    // radio.enableAddressCheckBcast('#');
    //
    // the default(no need to set) is 
    // radio.disableAddressCheck();

    // whitening is a feature of the CC1101 chip where the payload is converted
    // to a pseudorandom sequence for better transmission characteristcs. For example a
    // sequence of zeros is challenging for the receiving part but whitening is converting it
    // to sequence of 0 and 1 much easier for the receiver.
    // Disable it only for interoperability with other modules that do not use
    // this feature. The default (no need to set it explicity) is radio.enableWhitening()
    // radio.disableWhitening();

    // Start listening. Should be the last radio related command inside setup()
    // This of course is subject to the communication schema used
    radio.setRXstate();

    showhelp();

    // LED setup. It is importand as we can use the module without serial terminal
    pinMode(LEDPIN, OUTPUT);
    // or use an external more visible LED for outdoor tests
    // pinMode(PB9, OUTPUT); // A LED connected to PB9 - GND

    // BUTTON setup, do we can send packets without a serial terminal
    pinMode(BUTTONPIN, INPUT_PULLUP);

}


// used for tests enabling/disabling address check
bool addrCheck = false;
// used for periodic pings see below
uint32_t pingTimer;
// enable/disable the pings
bool pingEnable = false;
// We use it to calculate how much time the led is ON
uint32_t ledTimer;

const uint32_t PING_PERIOD = 5000;

// NOTICE: The code should not have long delay() otherwise the receiving code
// may not be able to receive a packet in time
void loop() {
    // Turn on the LED for 200ms. The ledTimer is resetting when receiving a packet
    // as you can see we do this without using delay()
    digitalWrite(LEDPIN, millis()-ledTimer < 200);
    // if the LED is active LOW replace "<" with ">"
    // digitalWrite(LEDPIN, millis()-ledTimer > 200);

    // WARNING for old users: With the old settings it was possible to read the GDO0
    // pin to check if a packed was received. However this method was proved unreliable
    // So for the "normal" mode of operation, which means active CC1101 and MCU do not use
    // the GDO0 pin at all. For low power projects(they need the GDO0 pin) see the
    // dedicated example.
    
    // Receive part. The receive buffer must be 64 bytes
    byte packet[64];
    volatile byte pkt_size = radio.getPacket(packet);
    // no need to set RX state, getPacket is doing this automatically.
    
    if (pkt_size>0 && radio.crcok()) { // We have a valid packet with some data
        Serial.print("Got packet \"");
        Serial.write(packet, pkt_size);
        Serial.print("\" len=");
        Serial.print(pkt_size);
        Serial.print(" Signal="); // for field tests to check the signal strength
        Serial.print(radio.getRSSIdbm());
        Serial.print(" LQI="); // for field tests to check the signal quality

        Serial.println(radio.getLQI());
        ledTimer=millis(); // The LED will be on
    }

    // Serial terminal input
    if (Serial.available()>0) {
        byte c = Serial.read();
        while (Serial.read()!=-1); // discard excessive keypresses
        switch (c) {
            case '=':
                addrCheck = !addrCheck;
                if (addrCheck) {
                    // better use a printable character for this test
                    const char ADDR = '#'; // or '1' '*' etc
                    Serial.print("Address check enabled addr=\'");
                    Serial.write(ADDR);
                    Serial.print("\'.\r\nNow only packets with first byte \'");
                    Serial.write(ADDR);
                    Serial.println("\' will be accepted");
                    radio.enableAddressCheck(ADDR); // sets the state to IDLE.
                    // or using addrss 0x00 as broadcast
                    // radio.enableAddressCheckBcast('a');
                    radio.setRXstate();
                } else {
                    Serial.println("Address check disabled.");
                    radio.disableAddressCheck(); // sets the state to IDLE
                    radio.setRXstate();
                }
            break;

            case '.':
                pingEnable = not pingEnable;
                if (pingEnable) {
                    Serial.println("Sending pings enabled.");
                    pingTimer=millis(); // The next ping will be after PING_PERIOD ms
                } else {
                    Serial.println("Sending pings disabled.");
                }
            break;

            default:
                if (c<=32 || c>126) {
                    showhelp();
                    break;
                }
                byte packet[1]={c};
                // using sendPacket with a byte array and a size
                bool ok = radio.sendPacket(packet,1);
                if (ok) {
                    Serial.print("Sending \"");
                    Serial.print((char)c);
                    Serial.println("\"");
                } else {
                    Serial.print("Could not send packet, High RSSI or receiving a packet.");
                }
                // we postpone the ping
                pingTimer = millis();
            break; 
        }
    }

    if (pingEnable && (millis()-pingTimer>PING_PERIOD)) { // ping every PING_PERIOD ms
        // we reset the ping timer
        pingTimer += PING_PERIOD;
        bool ok = radio.sendPacket("ping");
        if (ok) {
            Serial.println("Ping sent, press \".\" to disable.");
        } else {
            Serial.println("Ping failed due to high RSSI and/or incoming packet.");
        }
        //
        // If we want to transmit binary data we can use this syntax
        // bool ok = radio.sendPacket(buffer,4);
        // where buffer is byte*
        // Another option is to use radio.printf(fmt,...)
        // radio.printf uses the normal printf formatting. Of course is adding to the
        // firmware size a few Kb due to internal use of sprintf
        // bool ok = radio.printf("time=%lu",millis()/1000);
        // It is extremely useful if the other side is meant to be read by a human
    }

    if (debounceButton()) {
        bool ok = radio.sendPacket("Button");
        Serial.print(F("Button pressed ... "));
        if (ok) {
            Serial.println(F("packet sent."));
        } else {
            Serial.println(F("sending failed due to high RSSI and/or incoming packet."));
        }
    }
}

