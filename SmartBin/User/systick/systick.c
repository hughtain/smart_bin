 #include "./systick/systick.h"
#include "core_cm3.h"
#include "misc.h"

static __IO u32 TimingDelay;
 
/**
  * @brief  ENABLES SysTick
  * @param  NONE
  * @retval NONE
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    interrupt every 1ms
	 * SystemFrequency / 100000	 interrupt every 10us
	 * SystemFrequency / 1000000 interrupt every 1us
	 */
//	if (SysTick_Config(SystemFrequency / 100000))	// ST3.0.0 version
	if (SysTick_Config(SystemCoreClock / 100000))	// ST3.5.0 version
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   delay  10 us units
  * @param  
  *	@arg nTime: Delay_us( 1 )   equales delaying  1 * 10us = 10us
  * @retval  none
  */
void Delay_us(__IO u32 nTime)
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

#if 0
// if this function in core_cm3.h
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
  // reload register into 24 bit
	if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);
  
  // reload register 's startup value
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;
	
	// set interrupt priority as 1<<4-1 = 15 the lowest
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 
	
	// set counter value
  SysTick->VAL   = 0;
	
	// set systick clock as 72m
	// enable interrupt
	// enable systick
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    
  return (0); 
}
#endif

// timeof(counter -1) = 1/ systick_clk
// COUNTER decreases from reload to 0 makes it a loop,if interrupt is enabled, run IRQ
// CTRL-countflag set 1 at the same time
// time of 1 loop: reload * (1/systick_clk) 

void SysTick_Delay_Us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SystemCoreClock/1000000);
	
	for(i=0;i<us;i++)
	{
		// COUNTER decreases from reload to 0 makes it a loop,if interrupt is enabled, run IRQ
        // CTRL-countflag(bit 16) set 1 at the same time
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// close systick 
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Ms( __IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SystemCoreClock/1000);
	
	for(i=0;i<ms;i++)
	{
		// COUNTER decreases from reload to 0 makes it a loop,if interrupt is enabled, run IRQ
		// CTRL-countflag(bit 16) set 1 at the same time
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// close systick
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}


/*********************************************END OF FILE**********************/

