#ifndef __HCSR_
#define __HCSR_

/* includes*******************************************/
#include "stm32f10x.h"

/* defines pin****************************************/
#define     HCSR_GPIO_CLK              RCC_APB2Periph_GPIOA
#define     HCSR_GOIO_PORT             GPIOA
#define     HCSR_GPIO_PIN              GPIO_Pin_2
#define     HCSR_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define     HCSR_INT_EXTI_PINSOURCE    GPIO_PinSource2
#define     HCSR_INT_EXTI_LINE         EXTI_Line2
#define     HCSR_INT_EXTI_IRQ          EXTI0_IRQn

#define     HCSR_IRQHandler            EXTI0_IRQHandler

/* defines states*************************************/
#define     HCSR_State  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)


/* defines func****************************************/

void EXTI_HCSR_GPIO_Config(void);
void HC_SR501_ScanDelay(void);

#endif /*_HCSR_H*/

/*********************************************END OF FILE**********************/
