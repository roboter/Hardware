#ifndef _OPENSMART_SINGLE_JOYSTICK_H__
#define _OPENSMART_SINGLE_JOYSTICK_H__

#include <Arduino.h>

#define MOVE_NOT	1
#define MOVE_UP		2
#define MOVE_DOWN	3
#define MOVE_RIGHT	4
#define MOVE_LEFT	5
class SingleJoystick{

private:
	static const int AXIS_DEVIATION = 100;
		// Min value of Arduino ADC.
	static const int ADC_MIN = 0;
		// Max value of Arduino ADC.
	static const int ADC_MAX = 1023;
	int min = ADC_MIN + AXIS_DEVIATION;
	int max = ADC_MAX - AXIS_DEVIATION;	
    uint8_t xPin, yPin;
	int preX, preY;
public:
    SingleJoystick(uint8_t x=A0,uint8_t y=A1);
	void init();                        
    int getX();
	int getY();
    uint8_t isChange();
	int nowX, nowY;
	uint8_t SingleJoystick::multipleRead();
	boolean SingleJoystick::isUp();
	boolean SingleJoystick::isDown();
	boolean SingleJoystick::isRight();
	boolean SingleJoystick::isLeft();
	inline boolean isLow(int value);
    inline boolean isHigh(int value);
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/