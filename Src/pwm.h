//
// Created by 张亮亮 on 2022/2/6.
//

#ifndef HAL_06_LCD_PWM_H
#define HAL_06_LCD_PWM_H

#include "main.h"

void MX_TIM2_PWM2_Init(void);
void Set_TIM2_PWM2_Duty(uint32_t duty);
void Set_TIM2_PWM2_Period(uint32_t period);

#endif //HAL_06_LCD_PWM_H
