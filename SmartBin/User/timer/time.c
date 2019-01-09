/* includes*******************************************/
#include "./timer/time.h"
#include "./ultrasound.h"

/* defines func***************************************/

/**
 * @brief   TIM2 NVIC CONFIGURATION  
 * @param   none
 * @retval  none
 * @author  vicky
 */
static void GENERAL_TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}   

/**
 * @brief  timer2 configuration  
 * @param   none
 * @retval  none
 * @author  vicky
 */
void TIM_2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);
    TIM_DeInit(GENERAL_TIM);

    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);   
    TIM_ITConfig(GENERAL_TIM, TIM_IT_Update, ENABLE);
    TIM_Cmd(GENERAL_TIM, ENABLE);
}

/**
 * @brief  TIM2 CONFIGARATION UNION
 * @param   none
 * @retval  none
 * @author  vicky
 */
void TIM2_Config(void)
{
    TIM_2_Init();
    GENERAL_TIM_NVIC_Config();
}

/**
 * @brief   TIM4 channel 1 gpio configurasion
 * @param   none
 * @retval  none
 * @more	used for sg90 running
 * @author  vicky
 */
void TIM_4_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //TIM4 CH1 GPIO CONFIGURATION
    RCC_APB2PeriphClockCmd(GENERAL_TIM_4_CH1_GPIO_CLK , ENABLE);
    GPIO_InitStructure.GPIO_Pin = GENERAL_TIM_4_CH1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GENERAL_TIM_4_CH1_PORT, &GPIO_InitStructure);
	
//	GPIO_ResetBits(GENERAL_TIM_4_CH1_PORT, GENERAL_TIM_4_CH1_PIN);
}

/**
 * @brief   TIM4 channel 1 pwm configuration
 * @param   none
 * @retval  none
 * @author  vicky
 * @more	used for sg90 running
 */
void TIM_4_Mode_Config(u16 period,u16 prescaler)
{
//	uint16_t CCR1_Val = 0;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    //TIM4 CH1 MODE CONFIGURATION
    GENERAL_TIM_APBxClock_FUN_4(GENERAL_TIM_CLK_4, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = period;
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(GENERAL_TIM_4, &TIM_TimeBaseStructure);

    //PWM OUTPUT CONFIGURATION
    
    //ENABLE PWM OUTPUT
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	//PWM OUTPUT LOADING
//    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OC1Init(GENERAL_TIM_4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(GENERAL_TIM_4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(GENERAL_TIM_4, ENABLE); 
    //ENABLE COUNTER
    TIM_Cmd(GENERAL_TIM_4, ENABLE);

}


/*********************************************END OF FILE**********************/

