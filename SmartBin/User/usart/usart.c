/* includes*******************************************/
#include "./Usart/usart.h"
#include "stm32f10x_usart.h"

/* defines func***************************************/

/**
 * @brief   USART NVIC CONFIGURATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
//static void NVIC_Configuration(void)
//{
//    NVIC_InitTypeDef NVIC_InitStucture;
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//    NVIC_InitStucture.NVIC_IRQChannel = DEBUG_USART_IRQ;
//    NVIC_InitStucture.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStucture.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStucture.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStucture);
//}

/**
 * @brief   USART CONFIGURATION
 * @param   none
 * @retval  none
 * @author  vicky
 */
void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

    //USART TX (PA.9) GPIO CONFIGURATION white
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    //USART RX (PA.10) GPIO CONFIGURATION green
    GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    //USART WORKING PARAMETER
    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = 
    USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(DEBUG_USARTx, &USART_InitStructure);

    //ENABLE USART RX INTERRUPTIONG
//    USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);
    //ENABLE USART
    USART_Cmd(DEBUG_USARTx, ENABLE);
}

/**
 * @brief   USART sends one byte
 * @param   USART_TypeDef * pUSARTx , uint8_t ch
 * @retval  none
 * @author  vicky
 */
//void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
//{
//    //sends one byte to USART
//    USART_SendData(pUSARTx, ch);
//    //waits until Transmit data register is empty
//    while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
//}

/**
 * @brief   USART sends 8 bits array
 * @param   USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num
 * @retval  none
 * @author  vicky
 */
//void Usart_SendArray(USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
//{
//    uint8_t i;

//    for(i = 0; i < num; i ++)
//    {
//        //sends one byte to USART
//        Usart_SendByte(pUSARTx, array[i]);
//    }
//    //waits until sending accomplished
//    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
//}

/**
 * @brief   USART sends string
 * @param   USART_TypeDef *pUSARTx, char *str
 * @retval  none
 * @author  vicky
 */
//void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
//{
//    unsigned int k = 0;
//    do
//    {
//        Usart_SendByte( pUSARTx, *(str + k) );
//        k ++;
//    }while(*(str + k ) != '\0');
//    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET)
//    {}
//}

/**
 * @brief   USART sends halfword(usually 2 bytes)
 * @param   USART_TypeDef *pUSARTx, uint16_t ch
 * @retval  none
 * @author  vicky
 */
//void USART_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
//{
//    uint8_t temp_h, temp_l;
//    //high 8 bits
//    temp_h = (ch&0xFF00)>>8;
//    //low 8 bits
//    temp_l = ch&0x00FF;

//    //sends high 8 bits
//    USART_SendData(pUSARTx, temp_h);
//    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
//    //sends low 8 bits
//    USART_SendData(pUSARTx, temp_l);
//    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
//}



int fputc(int ch, FILE *f)
{
    //sends the first byte data to USART
    USART_SendData(DEBUG_USARTx, (uint8_t) ch);
    //waits until sending accomplished
    while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);
    return(ch);
}

int fgetc(FILE *f)
{
    //waits iusart
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(DEBUG_USARTx);
}
/*********************************************END OF FILE**********************/
