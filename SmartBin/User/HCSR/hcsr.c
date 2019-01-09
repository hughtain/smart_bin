/* includes*******************************************/
#include "./HCSR/hcsr.h"
#include "./Usart/usart.h"

/* defines func***************************************/

/**
 * @brief   HCSR NVIC CONFIGURATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
static void HCSR_NVIC_Configuration(void)
{
    NVIC_InitTypeDef    NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = HCSR_INT_EXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void HC_SR501_ScanDelay(void)
{  
  uint32_t i,j;
  for(i=0;i<100;++i)
    for(j=0;j<1000;++j){ }                
}


/**
 * @brief   HCSR GPIO PORT & EXTI CONFIGURATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
void EXTI_HCSR_GPIO_Config(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;
    EXTI_InitTypeDef    EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(HCSR_GPIO_CLK, ENABLE);
    HCSR_NVIC_Configuration();

    GPIO_InitStructure.GPIO_Pin = HCSR_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(HCSR_GOIO_PORT, &GPIO_InitStructure);

    GPIO_EXTILineConfig(HCSR_INT_EXTI_PORTSOURCE, HCSR_INT_EXTI_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = HCSR_INT_EXTI_LINE;

    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;

    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  This function handles HCSR Handler.
  * @param  None
  * @retval None
  * @author vicky
  */
void HCSR_IRQHandler(void)
{
  //make sure if EXTI Line has happened
  if(EXTI_GetITStatus(HCSR_INT_EXTI_LINE) != RESET)
  {
    //func that does whenever HCSR EXTI has happened
		if(HCSR_State)
		{
			HC_SR501_ScanDelay();
			if(HCSR_State);
			printf("\n\r有人\r\n");
		}
		else
		{
			printf("\n\r没人\r\n");
		}
		EXTI_ClearITPendingBit(HCSR_INT_EXTI_LINE);
  }
}

/*********************************************END OF FILE**********************/
