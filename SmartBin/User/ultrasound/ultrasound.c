/* includes*******************************************/
#include "./ultrasound/ultrasound.h"
#include "./Usart/usart.h"
#include "systick.h"
/* defines *******************************************/
u8 ultrasound_Level = 0;
u16 ultrasound_Highcnt = 0;
float ultrasound_Distance = 0;

/* defines func***************************************/

/**
 * @brief   Ultrasound ECHO AND TRIG PIN CONFIGURATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
void Ultrasound_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(ULTRASOUND_ECHO_CLK | ULTRASOUND_TRIG_CLK, ENABLE);
    //ECHO 
    GPIO_InitStructure.GPIO_Pin = ULTRASOUND_ECHO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(ULTRASOUND_ECHO_PORT, &GPIO_InitStructure);

    //TRIG
    GPIO_InitStructure.GPIO_Pin = ULTRASOUND_TRIG_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(ULTRASOUND_TRIG_PORT, &GPIO_InitStructure);
}

/**
 * @brief   send a start signal to ULTRASOUND
 * @param   none
 * @retval  none
 * @author  vicky
 */
void Ultrasound_Start(void)
{
    ULTRASOUND_TRIG_HIGH;
    SysTick_Delay_Us(10);
    ULTRASOUND_TRIG_LOW;
}

/**
 * @brief   distance measurement
 * @param   none
 * @retval  none
 * @author  vicky
 */
void Ultrasound_Measure(void)
{
    u8 echo = 0;
    echo = READ_ULTRASOUND_ECHO;

    if(echo == 1 && ultrasound_Level == 0)
    {
        ultrasound_Highcnt ++;
    }

    if(echo == 0 && ultrasound_Level == 1)
    {
        ultrasound_Level = 0;
        ultrasound_Distance = 17 * (float)ultrasound_Highcnt;
        ultrasound_Highcnt = 0;
        printf("distance :");
        printf("%8f", ultrasound_Distance);
        printf("mm");
        printf("\r\n");
    }
}
/*********************************************END OF FILE**********************/
