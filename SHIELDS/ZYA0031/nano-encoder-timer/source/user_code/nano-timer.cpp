
#include <Arduino.h>
// include the library code:
//#include <LiquidCrystal.h>
#include <Wire.h>
#include <menu.h>
#include <menuIO/liquidCrystalOut.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

using namespace Menu;

#define LEDPIN LED_BUILTIN
#define MAX_DEPTH 1

#include <Arduino.h>

/********************
Sept. 2014 Rui Azevedo - ruihfazevedo(@rrob@)gmail.com

menu output to standard arduino LCD (LiquidCrystal)
output: LCD
input: encoder and Serial
www.r-site.net
***/

#include <Wire.h>
#include <menu.h>
#include <menuIO/liquidCrystalOut.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>
#include <menuIO/encoderIn.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>

using namespace Menu;

// LCD /////////////////////////////////////////
#define RS 8
#define RW 3
#define EN 9
LiquidCrystal lcd(RS, RW, EN, 4, 5, 6, 7);

// Encoder /////////////////////////////////////
#define encA A2
#define encB A1
//this encoder has a button here
#define encBtn A3

encoderIn<encA,encB> encoder;//simple quad encoder driver
encoderInStream<encA,encB> encStream(encoder,4);// simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{-encBtn,defaultNavCodes[enterCmd].ch}};//negative pin numbers use internal pull-up, this is on when low
keyIn<1> encButton(encBtn_map);//1 is the number of keys

//input from the encoder + encoder button + serial
serialIn serial(Serial);
menuIn* inputsList[]={&encStream,&encButton,&serial};
chainStream<3> in(inputsList);//3 is the number of inputs

#define LEDPIN 13

result doAlert(eventMask e, prompt &item);

result showEvent(eventMask e,navNode& nav,prompt& item) {
  Serial.print("event: ");
  Serial.println(e);
  return proceed;
}

int test=55;

result action1(eventMask e,navNode& nav, prompt &item) {
  Serial.print("action1 event: ");
  Serial.print(e);
  Serial.println(", proceed menu");
  Serial.flush();
  return proceed;
}

result action2(eventMask e,navNode& nav, prompt &item) {
  Serial.print("action2 event: ");
  Serial.print(e);
  Serial.print(", quiting menu.");
  Serial.flush();
  return quit;
}

int ledCtrl=LOW;

result myLedOn() {
  ledCtrl=HIGH;
  return proceed;
}
result myLedOff() {
  ledCtrl=LOW;
  return proceed;
}

TOGGLE(ledCtrl,setLed,"Led: ",doNothing,noEvent,noStyle//,doExit,enterEvent,noStyle
  ,VALUE("On",HIGH,doNothing,noEvent)
  ,VALUE("Off",LOW,doNothing,noEvent)
);

int selTest=0;
SELECT(selTest,selMenu,"Select",doNothing,noEvent,noStyle
  ,VALUE("Zero",0,doNothing,noEvent)
  ,VALUE("One",1,doNothing,noEvent)
  ,VALUE("Two",2,doNothing,noEvent)
);

int chooseTest=-1;
CHOOSE(chooseTest,chooseMenu,"Choose",doNothing,noEvent,noStyle
  ,VALUE("First",1,doNothing,noEvent)
  ,VALUE("Second",2,doNothing,noEvent)
  ,VALUE("Third",3,doNothing,noEvent)
  ,VALUE("Last",-1,doNothing,noEvent)
);

//customizing a prompt look!
//by extending the prompt class
class altPrompt:public prompt {
public:
  altPrompt(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    return out.printRaw(F("special prompt!"),len);;
  }
};

MENU(subMenu,"Sub-Menu",showEvent,anyEvent,noStyle
  ,OP("Sub1",showEvent,anyEvent)
  ,OP("Sub2",showEvent,anyEvent)
  ,OP("Sub3",showEvent,anyEvent)
  ,altOP(altPrompt,"",showEvent,anyEvent)
  ,EXIT("<Back")
);

/*extern menu mainMenu;
TOGGLE((mainMenu[1].enabled),togOp,"Op 2:",doNothing,noEvent,noStyle
  ,VALUE("Enabled",enabledStatus,doNothing,noEvent)
  ,VALUE("disabled",disabledStatus,doNothing,noEvent)
);*/

// char* constMEM hexDigit MEMMODE="0123456789ABCDEF";
// char* constMEM hexNr[] MEMMODE={"0","x",hexDigit,hexDigit};
// char buf1[]="0x11";

MENU(mainMenu,"Main menu",doNothing,noEvent,wrapStyle
  ,OP("Op1",action1,anyEvent)
  ,OP("Op2",action2,enterEvent)
  //,SUBMENU(togOp)
  ,FIELD(test,"Test","%",0,100,10,1,doNothing,noEvent,wrapStyle)
  ,SUBMENU(subMenu)
  ,SUBMENU(setLed)
  ,OP("LED On",myLedOn,enterEvent)
  ,OP("LED Off",myLedOff,enterEvent)
  ,SUBMENU(selMenu)
  ,SUBMENU(chooseMenu)
  ,OP("Alert test",doAlert,enterEvent)
  // ,EDIT("Hex",buf1,hexNr,doNothing,noEvent,noStyle)
  ,EXIT("<Back")
);

//const panel panels[] MEMMODE={{0,0,16,2}};
//navNode* nodes[sizeof(panels)/sizeof(panel)];
//panelsList pList(panels,nodes,1);

#define MAX_DEPTH 2
/*idx_t tops[MAX_DEPTH];
liquidCrystalOut outLCD(lcd,tops,pList);//output device for LCD
menuOut* constMEM outputs[] MEMMODE={&outLCD};//list of output devices
outputsList out(outputs,1);//outputs list with 2 outputs*/

MENU_OUTPUTS(out, MAX_DEPTH
  ,LIQUIDCRYSTAL_OUT(lcd,{0,0,16,2})
  ,NONE
);
NAVROOT(nav,mainMenu,MAX_DEPTH,in,out);//the navigation root object

result alert(menuOut& o,idleEvent e) {
  if (e==idling) {
    o.setCursor(0,0);
    o.print("alert test");
    o.setCursor(0,1);
    o.print("[select] to continue...");
  }
  return proceed;
}

result doAlert(eventMask e, prompt &item) {
  nav.idleOn(alert);
  return proceed;
}

result idle(menuOut& o,idleEvent e) {
  switch(e) {
    case idleStart:o.print("suspending menu!");break;
    case idling:o.print("suspended...");break;
    case idleEnd:o.print("resuming menu.");break;
  }
  return proceed;
}





#define CLK 2
#define DT 9
#define SW 8

const int interrupt0 = 0;
int count = 0;//Define the count
int  lastCLK = 0;//CLK initial value

void setup();

void loop();

//void ClockChanged()
//{
//	if(digitalRead(SW))
//	{
//		int clkValue = digitalRead(CLK);
//		int dtValue = digitalRead(DT);
//		if (lastCLK != clkValue)
//		{
//			lastCLK = clkValue;
//			count += (clkValue != dtValue ? 1 : -1);
//			lcd.print(count);
//		}
//	}
//}

//The interrupt handlers
void ClockChanged()
{
  int clkValue = digitalRead(CLK);//Read the CLK pin level
  int dtValue = digitalRead(DT);//Read  the DT pin level
  if (lastCLK != clkValue)
  {
    lastCLK = clkValue;
    count += (clkValue != dtValue ? 1 : -1);//CLK and inconsistent DT + 1, otherwise  - 1

    Serial.print("count:");
    Serial.println(count);
   // LedOutput(count);
  }
}

void setup() {
  pinMode(encBtn,INPUT_PULLUP);
  pinMode(LEDPIN,OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Arduino Menu Library");Serial.flush();
  encoder.begin();
  lcd.begin(16,2);
  nav.idleTask=idle;//point a function to be used when menu is suspended
  mainMenu[1].enabled=disabledStatus;
  nav.showTitle=false;
  lcd.setCursor(0, 0);
  lcd.print("Menu 4.x LCD");
  lcd.setCursor(0, 1);
  lcd.print("r-site.net");
  delay(2000);
}
void setup2() {
	// initialize digital pin LED_BUILTIN as an output.
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(CLK, INPUT_PULLUP);
	pinMode(DT, INPUT_PULLUP);
	pinMode(SW, INPUT_PULLUP);
	
	attachInterrupt(interrupt0, ClockChanged, CHANGE);
	
	lcd.begin(16,2);
	lcd.clear();
	Serial.begin(115200);
}

bool blink(int timeOn,int timeOff) {
  return millis()%(unsigned long)(timeOn+timeOff)<(unsigned long)timeOn;
}
// the loop function runs over and over again forever
void loop2() {
	 nav.poll();
	digitalWrite(LED_BUILTIN, blink(timeOn,timeOff));
//	if (!digitalRead(SW) && count != 0) //Read the button  press and the count value to 0 when the counter reset
//  {
//    count = 0;
//    Serial.print("count:");
//    Serial.println(count);
//  }
//	lcd.clear();
//	lcd.print(count);
//	int BTN = digitalRead(SW);
//	if(BTN == HIGH){
//		digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//	}
//  //delay(1000);                       // wait for a second
//	else{
//		digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//	}
//]


//  delay(100);                       // wait for a second
}

void loop() {
  nav.poll();
  digitalWrite(LEDPIN, ledCtrl);
  delay(100);//simulate a delay as if other tasks are running
}
