/* includes*******************************************/
#include "stm32f10x.h"
#include "./HCSR/hcsr.h"
#include "./Usart/usart.h"
#include "./systick/systick.h"
#include "./ultrasound/ultrasound.h"
#include "./timer/time.h"

/* defines *******************************************/

extern u32  ultrasound_Distance;
/* defines main func**********************************/
/**
 * @brief   main function definition
 * @param   none
 * @retval  none
 * @author  vicky
 */
int main(void)
{	
	SysTick_Init();
	USART_Config();
//	TIM2_Config();//for ultrasound
//	TIM3_Init();//for ultrasound
//	Ultrasound_GPIO_Init();
//	EXTI_HCSR_GPIO_Config();
//	printf("\r\n hello here are the echo string\r\n ");
//	printf("done in 2019-1-9 13:42\r\n\r\n");
    while(1)
    {
		
    }

}


//		  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
//		  {
//			  HC_SR501_ScanDelay();

//			  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
//			  {
//				   printf("\n\r you \r\n");
//			  }
//			 
//		  }
//		  else
//		  {
//			  printf("\n\r wu \r\n");
//		  }

//		Delay_ms(1000);
//		printf("The Distance is:  %d\r\n",ultrasound_Distance);
/*********************************************END OF FILE**********************/
