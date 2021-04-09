/**
  Generated Pins header File

  Company:
    Microchip Technology Inc.

  File Name:
    pins.h

  Summary:
    This is generated driver header for pins. 

  Description:
    This header file provides APIs for all pins selected in the GUI.

  Generation Information:
    Driver Version:  3.0.0

*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA4 aliases
#define IO_RA4_TRIS                 TRISAbits.TRISA4
#define IO_RA4_LAT                  LATAbits.LATA4
#define IO_RA4_PORT                 PORTAbits.RA4
#define IO_RA4_WPU                  WPUAbits.WPUA4
#define IO_RA4_OD                   ODCONAbits.ODCA4
#define IO_RA4_ANS                  ANSELAbits.ANSELA4
#define IO_RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_RA4_GetValue()           PORTAbits.RA4
#define IO_RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_RA4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_RA4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_RA4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_RA4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_RA4_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define IO_RA4_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RE0 aliases
#define LED_RE0_TRIS                 TRISEbits.TRISE0
#define LED_RE0_LAT                  LATEbits.LATE0
#define LED_RE0_PORT                 PORTEbits.RE0
#define LED_RE0_WPU                  WPUEbits.WPUE0
#define LED_RE0_OD                   ODCONEbits.ODCE0
#define LED_RE0_ANS                  ANSELEbits.ANSELE0
#define LED_RE0_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_RE0_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_RE0_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_RE0_GetValue()           PORTEbits.RE0
#define LED_RE0_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_RE0_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_RE0_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_RE0_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_RE0_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_RE0_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_RE0_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LED_RE0_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set RE2 aliases
#define SW0_RE2_TRIS                 TRISEbits.TRISE2
#define SW0_RE2_LAT                  LATEbits.LATE2
#define SW0_RE2_PORT                 PORTEbits.RE2
#define SW0_RE2_WPU                  WPUEbits.WPUE2
#define SW0_RE2_OD                   ODCONEbits.ODCE2
#define SW0_RE2_ANS                  ANSELEbits.ANSELE2
#define SW0_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define SW0_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define SW0_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define SW0_RE2_GetValue()           PORTEbits.RE2
#define SW0_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define SW0_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define SW0_RE2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define SW0_RE2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define SW0_RE2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define SW0_RE2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define SW0_RE2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define SW0_RE2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PINS_H
/**
 End of File
*/