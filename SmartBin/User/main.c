/* includes*******************************************/
#include "stm32f10x.h"
#include "./HCSR/hcsr.h"
#include "./Usart/usart.h"
#include "./timer/time.h"
#include "./systick/systick.h"
#include "./ultrasound/ultrasound.h"

/* defines *******************************************/
uint32_t time = 0;
/* defines main func**********************************/
/**
 * @brief   main function definition
 * @param   none
 * @retval  none
 * @author  vicky
 */
int main(void)
{	
	USART_Config();
	TIM_2_Init();
//	SysTick_Init();
//	EXTI_HCSR_GPIO_Config();
	Ultrasound_GPIO_Init();
	printf("\r\n hello here are the echo string\r\n ");
    while(1)
    {
		
		if( time == 20000 )
		{
			time = 0;
			Ultrasound_Start();
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
		  
    }

}
/*********************************************END OF FILE**********************/
