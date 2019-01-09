#ifndef __SYSTICK_H
#define __SYSTICK_H

/* includes*******************************************/
#include "stm32f10x.h"

/* defines func***************************************/


void SysTick_Init(void);

void Delay_ms( __IO u32 nTime );
void TimingDelay_Decrement( void );



#endif /* __SYSTICK_H */

/*********************************************END OF FILE**********************/

