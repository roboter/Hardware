/*
  This code is not clean and also is not perfect, this is only
  a reference to extract ideas and adapte to your solution.
*/
void send_char(unsigned int a);
#define LCD_in 7  // This is the pin number 7 on Arduino UNO
#define LCD_wr 8 // This is the pin number 8 on Arduino UNO
#define LCD_cs 9 // This is the pin number 9 on Arduino UNO
/*
  #define BIN(x) \
  ( ((0x##x##L & 0x00000001L) ? 0x01 : 0) \
  | ((0x##x##L & 0x00000010L) ? 0x02 : 0) \
  | ((0x##x##L & 0x00000100L) ? 0x04 : 0) \
  | ((0x##x##L & 0x00001000L) ? 0x08 : 0) \
  | ((0x##x##L & 0x00010000L) ? 0x10 : 0) \
  | ((0x##x##L & 0x00100000L) ? 0x20 : 0) \
  | ((0x##x##L & 0x01000000L) ? 0x40 : 0) \
  | ((0x##x##L & 0x10000000L) ? 0x80 : 0))
*/
//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.

//*************************************************//
void setup() {
  pinMode(LCD_wr, OUTPUT);
  pinMode(LCD_in, OUTPUT);
  pinMode(LCD_cs, OUTPUT);

  pinMode(13, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LCD_cs, LOW);
  delayMicroseconds(5);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);

  initLCD();
  // delay(100);
  // testLCD();
  // delay(1000);
}
void send_char(unsigned int a)
{
  //
  unsigned int data = 0;
  unsigned int mask = 1; //our bitmask
  data = a;
  digitalWrite(LCD_cs, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(2);
  // I define the size of mask to send only 12 bits
  for (mask = 000000000001; mask < 4096; mask <<= 1) { //iterate through bit mask
    // Serial.println(mask, BIN);
    digitalWrite(LCD_wr, LOW); // need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(LCD_in, HIGH);
      // Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(LCD_in, LOW);
      // Serial.print(0);
    }
    digitalWrite(LCD_wr, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
  }
  digitalWrite(LCD_cs, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(2);
}
void send_cmd(unsigned int a)
// Attention: The "cmd" use 13 bits, the send_char use only 12
{
  //
  unsigned int data = 0;
  unsigned int mask = 1; //our bitmask
  data = a;
  digitalWrite(LCD_cs, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(2);
  // I define the size of mask to send only 12 bits
  for (mask = 0000000000001; mask < 8192; mask <<= 1) { //iterate through bit mask
    //Serial.println(mask, BIN);
    digitalWrite(LCD_wr, LOW); // need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
    if (data & mask) { // if bitwise AND resolves to true
      digitalWrite(LCD_in, HIGH);
      //Serial.print(1);
    }
    else { //if bitwise and resolves to false
      digitalWrite(LCD_in, LOW);
      //Serial.print(0);
    }
    digitalWrite(LCD_wr, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
  }
  digitalWrite(LCD_cs, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
  delayMicroseconds(2);
}
//READ 110 A5A4A3A2A1A0D0D1D2D3 D Read data from the RAM
//WRITE 101 A5A4A3A2A1A0D0D1D2D3 D Write data to the RAM
//READMODIFYWRITE 101 A5A4A3A2A1A0D0D1D2D3 D READ and WRITE to the RAM
//SYS DIS 100 0000-0000-X C Turn off both system oscillator and LCD bias generator Yes
//SYS EN 100 0000-0001-X C Turn on system oscillator LCD, OFF 100 0000-0010-X C
//Turn off LCD bias generator Yes LCD ON 100 0000-0011-X C Turn on LCD bias generator
void initLCD() {
  //*****************************************************************//
  //  LCD OFF 10000000010X Turn off LCD outputs
  //  LCD ON  10000000011X Turn on LCD outputs
  //
  //  BIAS & COM 1000010abXcX
  //  c=0: 1/2 bias option
  //  c=1: 1/3 bias option
  //  ab=00: 2 commons option
  //  ab=01: 3 commons option
  //  ab=10: 4 commons option
  //****************************************************************//
  //            X0Xba0100001
  //send_char(0b000111111001); //100 0010-abX0-X BIAS 1/2 LCD 1/2 bias option ab=00: 2 commons option ab=01: 3 commons option ab=10: 4 commons option
  //send_char(0b010100100001); //100 0010-abX0-X BIAS 1/2 LCD 1/2 bias option ab=00: 2 commons option ab=01: 3 commons option ab=10: 4 commons option
  // The LCD I'm use, have 4 common pins. I let the position of "a" with "1" to select this option!
  //send_char(0b000010100001); //100 0010-abX1-X BIAS 1/3 LCD 1/3 bias option ab=00: 2 commons option ab=01: 3 commons option ab=10: 4 commons option
  //send_char(0b001100000001);// TIMER EN 100 0000-0110-X  Enable time base output
  //send_char(0b000000000001); //SYS DIS Turn off both system oscillator and LCD bias generator, stay off
  //delay(2000);
  //send_char(0B100000000010); // SYS EN
  //send_char(0B010000000001); // SYS EN
  //send_char(0B100000000110); // LCD ON
  //send_char(0B011000000001); // LCD ON
  //send_char(0B001000000001); // LCD OFF
  //send_char(0B011000000001); // LCD ON

  send_char(0B010000000001);
  send_char(0B011000000001);// LCD ON
  send_char(0B000011000001);
  send_char(0B010010100001);
  //  send_cmd (0B0000000000101);
  //  send_cmd (0B0000100000101);
  //  send_cmd (0B0000010000101);
  //  send_cmd (0B0000110000101);
  //  send_cmd (0B0000001000101);

}
void testLCD(void) {
  send_char(0b000000111001); //Mode Test
  delay(2000);
  send_char(0b011000111001); //Normal Mode Test
  delay(2000);
  segmentClear();
}
void fourBitsZero(void) {
  // tudos 4 bits a 0000;
  send_cmd(0B0000000000101);
  send_cmd(0B0000100000101);
  send_cmd(0B0000010000101);
  send_cmd(0B0000110000101);
  send_cmd(0B0000001000101);
  send_cmd(0B0000101000101);
  send_cmd(0B0000011000101);
  send_cmd(0B0000111000101);
  send_cmd(0B0000000100101);
  send_cmd(0B0000100100101);
  send_cmd(0B0000010100101);
  send_cmd(0B0000110100101);
  send_cmd(0B0000001100101);
  send_cmd(0B0000101100101);
  send_cmd(0B0000011100101);
  send_cmd(0B0000111100101);
  //a0-a15 ... d0-d15
  send_cmd(0B0000000010101);
  send_cmd(0B0000100010101);
  send_cmd(0B0000010010101);
  send_cmd(0B0000110010101);
  send_cmd(0B0000001010101);
  send_cmd(0B0000101010101);
  send_cmd(0B0000011010101);
  send_cmd(0B0000111010101);
  send_cmd(0B0000000110101);
  send_cmd(0B0000100110101);
  send_cmd(0B0000010110101);
  send_cmd(0B0000110110101);
  send_cmd(0B0000001110101);
  send_cmd(0B0000101110101);
  send_cmd(0B0000011110101);
  send_cmd(0B0001111110101);
}
void letters(void) {
  // 1/0-1/15 ... 4/0-4/15
  send_cmd(0B1101000000101);
  send_cmd(0B0000100000101);
  send_cmd(0B1010010000101);
  send_cmd(0B0001110000101);
  send_cmd(0B1101001000101);
  send_cmd(0B1001101000101);
  send_cmd(0B0010011000101);
  send_cmd(0B0000111000101);
  //
  send_cmd(0B1001000100101);
  send_cmd(0B1000100100101);
  send_cmd(0B0000010100101);
  send_cmd(0B0000110100101);
  send_cmd(0B1001001100101);
  send_cmd(0B1000101100101);
  send_cmd(0B0000011100101);
  send_cmd(0B0000111100101);
  //a0-a15 ... d0-d15
  send_cmd(0B1001000010101);
  send_cmd(0B1001100010101);
  send_cmd(0B1000010010101);
  send_cmd(0B0001110010101);
  send_cmd(0B0000001010101);
  send_cmd(0B0000101010101);
  send_cmd(0B0000011010101);
  send_cmd(0B0000111010101);
  //
  send_cmd(0B0000000110101);
  send_cmd(0B0000100110101);
  send_cmd(0B0000010110101);
  send_cmd(0B0000110110101);
  send_cmd(0B0000001110101);
  send_cmd(0B0000101110101);
  send_cmd(0B0000011110101);
  send_cmd(0B0000111110101);
}
void simbols1(void) {
  send_cmd(0B0000000110101);
  send_cmd(0B0000100110101);
  send_cmd(0B0000010110101);
  send_cmd(0B0000110110101);
  send_cmd(0B0000001110101);
  send_cmd(0B0000101110101);
  send_cmd(0B0001011110101);
  send_cmd(0B0001111110101);
}
void simbols2(void) {
  send_cmd(0B0000000110101);
  send_cmd(0B0000100110101);
  send_cmd(0B0000010110101);
  send_cmd(0B0000110110101);
  send_cmd(0B0000001110101);
  send_cmd(0B0000101110101);
  send_cmd(0B0011011110101);
  send_cmd(0B0011111110101);
}
void simbols3(void) {
  send_cmd(0B0000000110101);
  send_cmd(0B0000100110101);
  send_cmd(0B0000010110101);
  send_cmd(0B0000110110101);
  send_cmd(0B0000001110101);
  send_cmd(0B0000101110101);
  send_cmd(0B0111011110101);
  send_cmd(0B0111111110101);
}
void simbols4(void) {
  send_cmd(0B0000000110101);
  send_cmd(0B0000100110101);
  send_cmd(0B0000010110101);
  send_cmd(0B0000110110101);
  send_cmd(0B0000001110101);
  send_cmd(0B0000101110101);
  send_cmd(0B1111011110101);
  send_cmd(0B1111111110101);
}
void segmentClear(void) {
  unsigned int common = 0;
  unsigned int address = 0;
  unsigned int cmd = 0b101;
  unsigned int mem = 0;
  unsigned int aux = 0;
  unsigned int var = 0;
  unsigned int data = 0;
  unsigned int temp = 0;
  //
  for (common = 0; common < 16; common++) {
    temp = 0;
    var = (common << 9);
    for (mem = 0; mem < 64; mem++) {
      data = 0;
      data = (data | cmd);
      //Serial.print("Data 1: "); Serial.println(data, BIN); // Only for Debug
      aux = mem << 3;
      //Serial.print("aux: "); Serial.print(aux, BIN); Serial.print("; mem="); Serial.println(mem, DEC); // Only for Debug
      data = (data | aux);
      //Serial.print("Data 2: "); Serial.println(data, BIN); // Only for Debug
      temp = (data | var);
      send_cmd(temp);
      //Serial.println(temp, BIN);
      delayMicroseconds(2);
    }
  }
}
void segmentTest(void) {
  unsigned int common = 0;
  unsigned int address = 0;
  unsigned int cmd = 0b101;
  unsigned int mem = 0;
  unsigned int aux = 0;
  unsigned int var = 0;
  unsigned int data = 0;
  unsigned int temp = 0;
  //
  for (common = 0; common < 16; common++) {
    temp = 0;
    var = (common << 9);
    //Serial.print("var: "); Serial.print(var, BIN); Serial.print("; var=");Serial.println(var, DEC);// Only for Debug
    //
    for (mem = 0; mem < 64; mem++) {
      data = 0;
      data = (data | cmd);
      //Serial.print("Data 1: "); Serial.println(data, BIN); // Only for Debug
      aux = mem << 3;
      //Serial.print("aux: "); Serial.print(aux, BIN); Serial.print("; mem="); Serial.println(mem, DEC); // Only for Debug
      data = (data | aux);
      //Serial.print("Data 2: "); Serial.println(data, BIN); // Only for Debug
      temp = (data | var);
      send_cmd(temp);
      //Serial.println(temp, BIN); // Only for Debug
      delay(30);
    }
  }
}
void loop() {
  segmentClear();
  delay(50);
  int i = 0x589;
  send_char(i);
  //i = 0x498;
  //delay(9000);
  //send_char(i);
  i = 0;
  while (1) {
    //send_cmd(0B0000000000001);//clear?
   // send_cmd(0B0000000000101);
    //letters();
   // delay(5);
   // simbols1();
 //   delay(50);
    //simbols2();

    //delay(50);
    //simbols3();
    //delay(50);
    //simbols4();
    //delay(50);

    i++;
    int b = ((i) <<4) + 0B0101;
    send_cmd(b);
    //send_char(b);
    Serial.println(b, BIN); // Only for Debug
   // delay(90);
  //  
  }
}

 uint8_t reverseX(uint8_t x){
    x = (((x&0xaa)>>1) + ((x&0x55)<<1));
    x = (((x&0xcc)>>2) + ((x& 0x33)<<2));
    return((x>>4) + (x<<4));
  }
