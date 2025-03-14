 
#ifndef XC_HEADER_TEMPLATE_H_REGISTERS
#define	XC_HEADER_TEMPLATE_H_REGISTERS

#include <xc.h> // include processor files - each processor file is guarded.  

//Note size of bits!


/*******************************************************************************
********************************** Pins ****************************************
*******************************************************************************/
//Better LAT for switch, PORT for read. Add this, please
//M12 (GSM module power supply) transistor
#define BIT_PIN_1_IO                         TRISGbits.TRISG15    //write
#define BIT_PIN_1_SWITCH                     PORTGbits.RG15
//Relay 11
#define BIT_PIN_3_IO                         TRISEbits.TRISE5     //write
#define BIT_PIN_3_SWITCH                     PORTEbits.RE5  
//Relay 1
#define BIT_PIN_4_IO                         TRISEbits.TRISE6     //write
#define BIT_PIN_4_SWITCH                     PORTEbits.RE6
//GSM module turn ON button 
#define BIT_PIN_14_IO                        TRISGbits.TRISG9     //write
#define BIT_PIN_14_SWITCH                    PORTGbits.RG9
//M13 (GPS module power supply) transistor
#define BIT_PIN_53_IO                        TRISFbits.TRISF8     //write
#define BIT_PIN_53_SWITCH                    PORTFbits.RF8
//RX from GPS UART
#define BIT_PIN_55_IO                        TRISFbits.TRISF6     //write
#define BIT_PIN_55_SWITCH                    PORTFbits.RF6
//M1 (main power supply) transistor 
#define BIT_PIN_87_IO                        TRISFbits.TRISF0     //write
#define BIT_PIN_87_SWITCH                    PORTFbits.RF0
//Software TX UART2
#define BIT_PIN_79_IO                        TRISDbits.TRISD12     //write
#define BIT_PIN_79_SWITCH                    PORTDbits.RD12        //read
//Software RX UART2
#define BIT_PIN_80_IO                        TRISDbits.TRISD13     //write
#define BIT_PIN_80_SWITCH                    PORTDbits.RD13        //read


/*******************************************************************************
******************************** System  Bits **********************************
*******************************************************************************/
#define BITS_SYSTEM_PLLPRE           CLKDIVbits.PLLPRE   //<4:0>  // write       
#define BITS_SYSTEM_PLLDIV           PLLFBDbits.PLLDIV   //<8:0>  // write       
#define BITS_SYSTEM_PLLPOST          CLKDIVbits.PLLPOST  //<1:0>  // write
#define BIT_SYSTEM_WATCHDOG          RCONbits.SWDTEN              // write
#define BIT_SYSTEM_PLL_READY         OSCCONbits.LOCK              // read



/*******************************************************************************
********************* Special Function Registers and Bits **********************
*******************************************************************************/
#define BITS_SPECIAL_UART1_RX                U1RXREG              // read                  
#define BITS_SPECIAL_UART2_RX                U2RXREG              // read
#define BIT_SPECIAL_UART1_RX_AVAILABLE       U1STAbits.URXDA      // read
#define BIT_SPECIAL_UART2_RX_AVAILABLE       U2STAbits.URXDA      // read
#define BIT_SPECIAL_UART1_FRAMING_ERROR      U1STAbits.FERR       // read
#define BIT_SPECIAL_UART2_FRAMING_ERROR      U2STAbits.FERR       // read
#define BIT_SPECIAL_UART1_FULL_BUFFER        U1STAbits.OERR       // read/clear
#define BIT_SPECIAL_UART2_FULL_BUFFER        U2STAbits.OERR       // read/clear
#define BIT_SPECIAL_UART1_TX_AVAILABLE       U1STAbits.TRMT       // read
#define BIT_SPECIAL_UART2_TX_AVAILABLE       U2STAbits.TRMT       // read


/*******************************************************************************
*********************************** Timers *************************************
*******************************************************************************/
#define BIT_TIMER1_SWITCH                    T1CONbits.TON
#define BIT_TIMER1_EXTERNAL_CLOCK            T1CONbits.TCS
#define BIT_TIMER1_GATEMODE                  T1CONbits.TGATE
#define BITS_TIMER1_COUNTER                  TMR1
#define BITS_TIMER1_PRESCALER                T1CONbits.TCKPS
#define BITS_TIMER1_PERIOD                   PR1
#define BITS_TIMER1_PRIORITY                 IPC0bits.T1IP
#define BIT_TIMER1_INTERRUPT_FLAG            IFS0bits.T1IF

/*******************************************************************************
******************************* Interrups **************************************
*******************************************************************************/
#define BITS_INTERRUPT_CPU_PRIORITY          SRbits.IPL            //write
#define BIT_INTERRUPT_NESTING_DISABLE        INTCON1bits.NSTDIS    //write 
#define BIT_INTERRUPT_PIN55_ENABLE           IEC0bits.INT0IE       //write 
#define BITS_INTERRUPT_PIN55_PRIORITY        IPC0bits.INT0IP       //write
#define BIT_INTERRUPT_PIN55_STATUS           IFS0bits.INT0IF       //write



#endif	/* XC_HEADER_TEMPLATE_H_REGISTERS */

