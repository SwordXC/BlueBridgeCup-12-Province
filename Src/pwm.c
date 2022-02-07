//
// Created by 张亮亮 on 2022/2/6.
//

#include "pwm.h"

TIM_HandleTypeDef htim2;
TIM_OC_InitTypeDef tim2_ch2_OC_Handle;

void MX_TIM2_PWM2_Init(void)//PA1 TIM2_CH2 ,PA7 TIM17_CH1
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_TIM17_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	htim2.Instance = TIM17;
	htim2.Init.Prescaler = 80; //预分频系数80M/80=1MHz
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP; //向上计数
	htim2.Init.Period = 500; //PWM计数周期
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //时钟源1分频
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	htim2.Init.RepetitionCounter  = 0;
	HAL_TIM_Base_Init(&htim2);
	
	//引脚初始化，PA1用作TIM2 CH2
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; //复用推挽输出
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM17; //复用功能
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// 定时器输出PWM初始化
	tim2_ch2_OC_Handle.OCMode = TIM_OCMODE_PWM1; // 模式选择PWM1
	tim2_ch2_OC_Handle.OCPolarity = TIM_OCPOLARITY_HIGH; // 输出比较极性为低
	tim2_ch2_OC_Handle.OCNPolarity = TIM_OCPOLARITY_HIGH;
	tim2_ch2_OC_Handle.OCFastMode = TIM_OCFAST_DISABLE;
	tim2_ch2_OC_Handle.Pulse = 100; //PWM定占空比
	HAL_TIM_PWM_ConfigChannel(&htim2, &tim2_ch2_OC_Handle, TIM_CHANNEL_1); // 配置PWM输出
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // 开始PWM输出
}

//设置TIM2 CH2 PWM的占空比
void Set_TIM2_PWM2_Duty(uint32_t duty) //0-500
{
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	tim2_ch2_OC_Handle.Pulse = duty;
	HAL_TIM_PWM_ConfigChannel(&htim2, &tim2_ch2_OC_Handle, TIM_CHANNEL_1); // 配置PWM输出
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // 开始PWM输出
}

//设置TIM2 CH2 PWM的周期
void Set_TIM2_PWM2_Period(uint32_t period)
{	
	htim2.Init.Period = period; 
	HAL_TIM_Base_Init(&htim2);
}
//同学们根据上文中的引脚复用表，自行思考如何使用其他定时器的其他引脚输出PWM
