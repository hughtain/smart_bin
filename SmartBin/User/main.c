/* includes*******************************************/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
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
//	u16 led0pwmval;
	SysTick_Init();
	USART_Config();
//	TIM2_Config();//for ultrasound
//	TIM3_Init();//for ultrasound
//	Ultrasound_GPIO_Init();//for ultrasonic
//	EXTI_HCSR_GPIO_Config();//for human sensor

//for sg90 begin	
//	Delay_ms(30);
//	TIM_4_Init();
//	TIM_4_Mode_Config(2000,719);
//	for(led0pwmval=50;led0pwmval<150;led0pwmval++) 									 
//	{	    
//		TIM_SetCompare1(TIM4,led0pwmval);
//	    Delay_ms(15);					 //延时多久很重要，自己一点点试。
//	}
//	TIM_SetCompare1(GENERAL_TIM_4,3000);
// for sg90 end

	printf("all done in 2019-1-9 21:05\r\n\r\n");
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
