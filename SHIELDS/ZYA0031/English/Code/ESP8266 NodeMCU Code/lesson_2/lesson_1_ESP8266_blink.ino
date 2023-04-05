/*********
 ESP8266 控制LED 闪烁
 2021-8-11
*********/
int pin = 2; //接控制板D4引脚
void setup() {
  // 初始化GPIO 2作为输出。
  pinMode(pin, OUTPUT);}// 循环函数一遍又一遍地运行
void loop() {
  digitalWrite(pin, HIGH);     // 打开LED
  delay(1000);                 // 延时一秒
  digitalWrite(pin, LOW);    // 通过降低电压来关闭LED
  delay(1000);               // 延时一秒
  }
 
