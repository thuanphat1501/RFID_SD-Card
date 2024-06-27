#ifndef SERVO_H
#define SERVO_H

#include "stm32f10x.h"

void TIM2_Config(void);
void TIM2_PWM_Config(uint16_t pulse);
void MoveServoTo90Degrees(void);
void MoveServoBackTo0Degrees(void);
void MoveServoTo180Degrees(void);
void Delay(uint32_t milliseconds);
#endif
