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
 * @brief  TIM2 CONFIGARATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
void TIM2_Config(void)
{
    TIM_2_Init();
    GENERAL_TIM_NVIC_Config();
}
/*********************************************END OF FILE**********************/

