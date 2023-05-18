/*
 * TM1637_2.h
 *
 *  Created on: Jun 13, 2022
 *      Author: roboter
 */

#ifndef SRC_TM1637_2_H_
#define SRC_TM1637_2_H_


#pragma once

void tm1637Init(void);
void tm1637DisplayDecimal(int v, int displaySeparator);
void tm1637SetBrightness(char brightness);


#endif /* SRC_TM1637_2_H_ */
