#ifndef __ULTRASOUND_H
#define __ULTRASOUND_H

/* includes*******************************************/
#include "stm32f10x.h"

/* defines pin****************************************/

//echo->PC6
//trig->PC7
#define ULTRASOUND_TRIG_PIN              GPIO_Pin_6
#define ULTRASOUND_TRIG_PORT             GPIOC
#define ULTRASOUND_TRIG_CLK              RCC_APB2Periph_GPIOC

#define ULTRASOUND_ECHO_PIN              GPIO_Pin_7
#define ULTRASOUND_ECHO_PORT             GPIOC
#define ULTRASOUND_ECHO_CLK              RCC_APB2Periph_GPIOC

/* defines states*************************************/
#define READ_ULTRASOUND_ECHO             GPIO_ReadInputDataBit(ULTRASOUND_ECHO_PORT, ULTRASOUND_ECHO_CLK)
#define ULTRASOUND_TRIG_HIGH             GPIO_SetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN)
#define ULTRASOUND_TRIG_LOW              GPIO_ResetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN)

/* defines func****************************************/
void Ultrasound_GPIO_Init(void);
void Ultrasound_Start(void);
void Ultrasound_Measure(void);
#endif /*__ULTRASOUND_H*/

/*********************************************END OF FILE**********************/
