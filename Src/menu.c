#include "menu.h"
#include "LED.h"
#include "pwm.h"
u8   CNBR_Num;
u8   VNBR_Num;
u8   IDLE_Num;
u8   ALL_Num;
u8   LED2_flag;
float    CNBR_Fee;
float    VNBR_Fee;
uint8_t show_flag=0;

void menu_init()
{
    CNBR_Num=0;
    VNBR_Num=0;
    IDLE_Num=8;
    ALL_Num=8;
    CNBR_Fee=3.50;
    VNBR_Fee=2.00;
    LED2_flag=0;
    key_init();

}

void menu_First()
{
    key key_v = no_key;
    show_data();
    show_data_s();
    while(1)
    {
        LED1();
        LED2();
        show_flag=1;
        key_v = key_scan();
        if(key_v==key1_on)
        {
            show_para();
            show_para_s();
            while (1)
            {
                LED1();
                LED2();
                show_flag=2;
                key_v = key_scan();
                if(key_v==key1_on)
                {
                    show_data();
                    show_data_s();
                    break;
                }
                else if(key_v==key2_on)
                {
                    CNBR_Fee+=0.5f;
                    VNBR_Fee+=0.5f;
                    show_para_s();
                }
                else if(key_v==key3_on)
                {
                    if(VNBR_Fee<0.5f)
                    {
                        continue;
                    }
                    CNBR_Fee-=0.5f;
                    VNBR_Fee-=0.5f;
                    show_para_s();
                }
                else if(key_v==key4_on)
                {
                    Pwm_Judge();
                }
            }
        }

        else if(key_v==key4_on)
        {
            Pwm_Judge();
        }
    }

}

void Pwm_Judge()
{
    if(LED2_flag==0)
    {
        Set_TIM2_PWM2_Duty(100);
        LED2_flag=1;
        return;
    }
    else if(LED2_flag==1)
    {
        Set_TIM2_PWM2_Duty(0);
        LED2_flag=0;
        return;
    }
}

key key_scan()
{
    key key_value = no_key;

    if ((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET) ||
        (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET) || (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET))
    {
        HAL_Delay(20);
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            key_value = key1_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
        {
            key_value = key2_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
        {
            key_value = key3_on;
            while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
        {
            key_value = key4_on;
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
                ;
            return key_value;
        }
    }
    return no_key;
}

void show_data()
{
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine(Line1,Column7,"Data");
    LCD_DisplayStringLine(Line3,Column3,"CNBR:");
    LCD_DisplayStringLine(Line5,Column3,"VNBR:");
    LCD_DisplayStringLine(Line7,Column3,"IDLE:");
}
void show_data_s()
{
    IDLE_Num=ALL_Num-CNBR_Num-VNBR_Num;
    LCD_DispDecAt(Line3,Column8,CNBR_Num,1);
    LCD_DispDecAt(Line5,Column8,VNBR_Num,1);
    LCD_DispDecAt(Line7,Column8,IDLE_Num,1);

}
void show_para()
{
    LCD_Clear(Black);
    LCD_SetBackColor(Black);
    LCD_SetTextColor(White);
    LCD_DisplayStringLine(Line1,Column7,"Para");
    LCD_DisplayStringLine(Line3,Column3,"CNBR:");
    LCD_DisplayStringLine(Line5,Column3,"VNBR:");

}
void show_para_s()
{
    LCD_DispFolatAt(Line3,Column8,CNBR_Fee,2);
    LCD_DispFolatAt(Line5,Column8,VNBR_Fee,2);
}
