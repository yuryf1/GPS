#ifndef TIMER_METHODS_H
#define	TIMER_METHODS_H

#include "registers.h"


#endif	/* TIMER_METHODS_H */

void Timer1_Enable(void);
void Timer1_Disable(void);

void Timer1_ExternalClock_Enable(void);
void Timer1_ExternalClock_Disable(void);

void Timer1_MeasureMode_Enable(void);
void Timer1_MeasureMode_Disable(void);
size_t Timer1_MeasureMode_Counter_Get(void);
void Timer1_MeasureMode_Counter_Set(size_t counter);