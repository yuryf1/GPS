#ifndef CONFIGURATION_H
#define	CONFIGURATION_H

#define FINPUT            10000000ULL      // 10 MHz oscillator
#define FOSC              48000000ULL      // for minimaze timers error; x8 and x6 PLL devides work good
#define FCY               FOSC/2           // device instruction clock for delay_ms() and others

#define GPS_BAUDRATE      4800
#define GSM_BAUDRATE      115200

//ADVANCED
//00 = 1:1 //00 = 1:1 //10 = 1:64 //11 = 1:256
#define TIMER_PRESCALERS {1, 0b00},  \
                         {8, 0b01},  \
                         {64, 0b10}, \
                         {256, 0b11}  
                



#endif	/* PROPERTIES_H */

