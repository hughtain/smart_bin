#ifndef __TIME_H
#define __TIME_H
/* includes*******************************************/
#include "stm32f10x.h"

/* defines ******************************************/

//set 1 to enable whichever timer you need
// #define GENERAL_TIM2    1
// #define GENERAL_TIM3    0
// #define GENERAL_TIM4    1
// #define GENERAL_TIM5    0

// #if  GENERAL_TIM2
#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_Period            (2000-1)
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM2_IRQn
#define            GENERAL_TIM_IRQHandler        TIM2_IRQHandler

// #elif  GENERAL_TIM3
// #define            GENERAL_TIM_3                  TIM3
// #define            GENERAL_TIM_APBxClock_FUN_3    RCC_APB1PeriphClockCmd
// #define            GENERAL_TIM_CLK_3              RCC_APB1Periph_TIM3
// #define            GENERAL_TIM_Period_3           (1000-1)
// #define            GENERAL_TIM_Prescaler_3        71
// #define            GENERAL_TIM_IRQ_3              TIM3_IRQn
// #define            GENERAL_TIM_IRQHandler_3       TIM3_IRQHandler

// #elif   GENERAL_TIM4
#define            GENERAL_TIM_4                  TIM4
#define            GENERAL_TIM_APBxClock_FUN_4    RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK_4              RCC_APB1Periph_TIM4
//#define            GENERAL_TIM_Period_4           (1000-1)
//#define            GENERAL_TIM_Prescaler_4        71
#define            GENERAL_TIM_IRQ_4              TIM4_IRQn
#define            GENERAL_TIM_IRQHandler_4       TIM4_IRQHandler

#define            GENERAL_TIM_4_CH1_PORT         GPIOB
#define            GENERAL_TIM_4_CH1_PIN          GPIO_Pin_6
#define            GENERAL_TIM_4_CH1_GPIO_CLK     RCC_APB2Periph_GPIOB


// #endif
/* defines func***************************************/
void TIM_2_Init(void);
void TIM2_Config(void);


void TIM_4_Init(void);
void TIM_4_Mode_Config(u16 period,u16 prescaler);

#endif
/*********************************************END OF FILE**********************/
