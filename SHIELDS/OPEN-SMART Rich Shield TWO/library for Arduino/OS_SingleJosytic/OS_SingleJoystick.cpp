#include "OS_SingleJoystick.h"

SingleJoystick::SingleJoystick(uint8_t x,uint8_t y)
{
	xPin = x;
	yPin = y;
}
void SingleJoystick::init()
{
  nowX = getX();
  nowY = getY();
  preX = nowX; 
  preY = nowY;
}

int SingleJoystick::getX()
{
  return analogRead(xPin);
}

int SingleJoystick::getY()
{
  return analogRead(yPin);
}

uint8_t SingleJoystick::isChange()
{
  uint8_t flag_change = 0;

  nowX = getX();
  if((nowX < (preX-50)) || nowX > (preX+50))
  {
    preX = nowX;
	flag_change = 1;
  }
  nowY = getY();
  if((nowY < (preY-50)) || nowY > (preY+50))
  {
    preY = nowY;
	flag_change = 1;
  }
  
  return flag_change;
}

uint8_t SingleJoystick::multipleRead() {
	if (isUp()) {
		return MOVE_UP;
	} else if (isDown()) {
		return MOVE_DOWN;
	} else if (isRight()) {
		return MOVE_RIGHT;
	} else if (isLeft()) {
		return MOVE_LEFT;
	}
	return MOVE_NOT;
}

boolean SingleJoystick::isUp() {
	return isHigh(getY());
}

boolean SingleJoystick::isDown() {
	return isLow(getY());
}

boolean SingleJoystick::isRight() {
	return isHigh(getX());
}

boolean SingleJoystick::isLeft() {
	return isLow(getX());
}


inline boolean SingleJoystick::isLow(const int value) {
	return (value <= min);
}

inline boolean SingleJoystick::isHigh(const int value) {
	return (value >= max);
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/