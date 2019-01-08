/* includes*******************************************/
#include "./timer/time.h"
#include "./ultrasound.h"

/* defines func***************************************/

/**
 * @brief  timer2 configuration  
 * @param   none
 * @retval  none
 * @author  vicky
 */
void TIM_2_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK, ENABLE);
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);

    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

    TIM_ITConfig(GENERAL_TIM, TIM_IT_Update, ENABLE);
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
    TIM_Cmd(GENERAL_TIM, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  timer2 IRQ function definition  
 * @param   none
 * @retval  none
 * @author  vicky
 */
void TIM2_IRQHandler(void)
{
    TIM_ClearFlag(GENERAL_TIM, TIM_FLAG_Update);
    Ultrasound_Measure();
}
/*********************************************END OF FILE**********************/

