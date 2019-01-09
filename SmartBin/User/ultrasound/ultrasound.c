/* includes*******************************************/
#include "./ultrasound/ultrasound.h"
#include "./Usart/usart.h"
#include "systick.h"
/* defines *******************************************/

u8 Done;
u32 ultrasound_Distance = 0;
u32 __IO time_1ms = 0;

/* defines func***************************************/
//times counter(¼ÆÊýÆ÷)
void TIM3_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 	//NVIC_InitTypeDef 		   NVIC_InitStructure;
  	/* TIM3 clock enable */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  	/* Time base configuration */
  	TIM_TimeBaseStructure.TIM_Period = 0xFFFF; 
	TIM_TimeBaseStructure.TIM_Prescaler = 142;         
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  	TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);	
	TIM_Cmd(TIM3, DISABLE);
}


/**
 * @brief   Ultrasound ECHO AND TRIG PIN CONFIGURATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
void Ultrasound_GPIO_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
   	
	//TRIG
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = ULTRASOUND_TRIG_PIN;
    GPIO_Init(ULTRASOUND_TRIG_PORT, &GPIO_InitStructure);
    //ECHO 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = ULTRASOUND_ECHO_PIN;
    GPIO_Init(ULTRASOUND_ECHO_PORT, &GPIO_InitStructure);
	
	GPIO_ResetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN);

	
    //EXTI CONFIGURATIONS
	EXTI_ClearITPendingBit(ULTRASOUND_ECHO_INT_EXTI_LINE);
    GPIO_EXTILineConfig(ULTRASOUND_ECHO_INT_EXTI_PORTSOURCE, ULTRASOUND_ECHO_INT_EXTI_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = ULTRASOUND_ECHO_INT_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = ULTRASOUND_ECHO_INT_EXTI_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0;        
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;   
	NVIC_Init(&NVIC_InitStructure);

    ultrasound_Distance = 0;
    Done = 1;
}

/**
 * @brief   DO THE BIT SET TO TRIG PIN
 * @param   none
 * @retval  none
 * @author  vicky
 */
void Ultrasound_Trig_SET(void)
{
    u16 i = 0;
    if((Done == 1) && (time_1ms > 100))
	{
        time_1ms = 0;
        GPIO_SetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN);
        for(i = 0; i < 0xf0; i ++);
		GPIO_ResetBits(ULTRASOUND_TRIG_PORT, ULTRASOUND_TRIG_PIN);
        Done = 0;
    }

}


//WARNING YOU'VE DONE WRONG HERE three times
void EXTI9_5_IRQHandler(void)
{
	static u8 flag_Sta = 0;
	if(EXTI_GetITStatus(ULTRASOUND_ECHO_INT_EXTI_LINE) != RESET)		
	{
		EXTI_ClearITPendingBit(ULTRASOUND_ECHO_INT_EXTI_LINE);  
		if(READ_ULTRASOUND_ECHO)
		{
			 TIM_SetCounter(TIM3,0);	
			 flag_Sta=1;
			 TIM_Cmd(TIM3, ENABLE);     
		}
		else
		{
			TIM_Cmd(TIM3, DISABLE); 					
			if(flag_Sta)
			{		
				ultrasound_Distance = TIM_GetCounter(TIM3);
				ultrasound_Distance = ultrasound_Distance /29;
				if(ultrasound_Distance > 300)
					ultrasound_Distance = 300;
				Done = 1;
			}
			flag_Sta=0;
		}
	}
}
/*********************************************END OF FILE**********************/
