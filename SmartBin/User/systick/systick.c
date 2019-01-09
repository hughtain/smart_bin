 #include "./systick/systick.h"


static __IO u32 TimingDelay = 0;
 
/**
  * @brief  ENABLES SysTick
  * @param  NONE
  * @retval NONE
  */
void SysTick_Init(void)
{
	
	if (SysTick_Config(SystemCoreClock / 1000))	
	{ 
		/* Capture error */ 
		while (1);
	}
	SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief   delay in ms units
  * @param  
  *	@arg nTime: Delay_ms( 1 )   equales delaying  1 * 10us = 10us
  * @retval  none
  */
void Delay_ms(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	// enable systick
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;

	while(TimingDelay != 0);
}

/**
  * @brief  captures tick
  * @param  none 
  * @retval none
  * @attention  using in systick interrupt function SysTick_Handler()
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}




/*********************************************END OF FILE**********************/

