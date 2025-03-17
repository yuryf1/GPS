#ifndef TIMER_METHODS_H
#define	TIMER_METHODS_H

#include "registers.h"
#include <stddef.h>



void Timer1_Enable(void);
void Timer1_Disable(void);

void Timer1_ExternalClock_Enable(void);
void Timer1_ExternalClock_Disable(void);

void Timer1_MeasureMode_Enable(void);
void Timer1_MeasureMode_Disable(void);
size_t Timer1_MeasureMode_Counter_Get(void);
void Timer1_MeasureMode_Counter_Set(size_t counter);

size_t Timer1_Period_Get(void);
void Timer1_Period_Set(size_t pr);

void Timer1_PriorityFrom0to7_Set(unsigned short priority);
unsigned short Timer1_PriorityFrom0to7_Get(void);

void Timer1_InterruptFlag_Clear(void);
void Timer1_InterruptFlag_Fill(void);

void Timer1_Interrupt_Enable(void);
void Timer1_Interrupt_Disable(void);



void Timer2_Enable(void);
void Timer2_Disable(void);

void Timer2_ExternalClock_Enable(void);
void Timer2_ExternalClock_Disable(void);

void Timer2_MeasureMode_Enable(void);
void Timer2_MeasureMode_Disable(void);
size_t Timer2_MeasureMode_Counter_Get(void);
void Timer2_MeasureMode_Counter_Set(size_t counter);

size_t Timer2_Period_Get(void);
void Timer2_Period_Set(size_t pr);

void Timer2_PriorityFrom0to7_Set(unsigned short priority);
unsigned short Timer2_PriorityFrom0to7_Get(void);

void Timer2_InterruptFlag_Clear(void);
void Timer2_InterruptFlag_Fill(void);

void Timer2_Interrupt_Enable(void);
void Timer2_Interrupt_Disable(void);



#endif	/* TIMER_METHODS_H */