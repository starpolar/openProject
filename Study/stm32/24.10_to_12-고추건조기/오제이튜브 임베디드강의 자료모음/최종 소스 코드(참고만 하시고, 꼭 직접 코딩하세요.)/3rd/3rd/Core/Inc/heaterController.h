/*
 * heaterController.h
 *
 *  Created on: May 18, 2022
 *      Author: JiWanOh
 */

#ifndef INC_HEATERCONTROLLER_H_
#define INC_HEATERCONTROLLER_H_

#include "main.h"
#include "controlType.h"
#include "defines.h"
uint8_t getHeaterState();
void heaterOnOff(uint8_t onOff);

void setDesiredTemper(void);

int getDesiredTemper(void);

void heaterControl(float temper);
void temper_up(void);
void temper_down(void);

void setFixedTemper(void);
int getFixedTemper(void);


#endif /* INC_HEATERCONTROLLER_H_ */
