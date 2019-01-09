#ifndef __ULTRASOUND_H
#define __ULTRASOUND_H

/* includes*******************************************/
#include "stm32f10x.h"

/* defines pin****************************************/


#define ULTRASOUND_TRIG_PIN                     GPIO_Pin_4
#define ULTRASOUND_TRIG_PORT                    GPIOA
#define ULTRASOUND_TRIG_CLK                     RCC_APB2Periph_GPIOA

#define ULTRASOUND_ECHO_PIN                     GPIO_Pin_5
#define ULTRASOUND_ECHO_PORT                    GPIOA
#define ULTRASOUND_ECHO_CLK                     RCC_APB2Periph_AFIO

//ECHO EXTI DEFINES
#define ULTRASOUND_ECHO_INT_EXTI_PORTSOURCE     GPIO_PortSourceGPIOA
#define ULTRASOUND_ECHO_INT_EXTI_PINSOURCE      GPIO_PinSource5
#define ULTRASOUND_ECHO_INT_EXTI_LINE           EXTI_Line5
#define ULTRASOUND_ECHO_INT_EXTI_IRQ            EXTI9_5_IRQn

/* defines states*************************************/
#define READ_ULTRASOUND_ECHO             GPIO_ReadInputDataBit(ULTRASOUND_ECHO_PORT, ULTRASOUND_ECHO_PIN)
//#define ULTRASOUND_TRIG_HIGH             GPIO_SetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN)
//#define ULTRASOUND_TRIG_LOW              GPIO_ResetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN)

/* defines func****************************************/
void Ultrasound_GPIO_Init(void);
void Ultrasound_Trig_SET(void);
void TIM3_Init(void);
#endif /*__ULTRASOUND_H*/

/*********************************************END OF FILE**********************/
