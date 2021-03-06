/**
  EUSART2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart2.c

  @Summary
    This is the generated driver implementation file for the EUSART2 driver using CCL

  @Description
    This source file provides APIs for EUSART2.
    Generation Information :
        Product Revision  :  CCL - 1.8.2
        Device            :  PIC18F47Q43
        Driver Version    :  2.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.2
        MPLAB 	          :  Standalone
*/

/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

/**
  Section: Included Files
*/
#include "../eusart2.h"

const struct UART_INTERFACE EUSART2_Interface = {
  .Initialize = EUSART2_Initialize,
  .Write = EUSART2_Write,
  .Read = EUSART2_Read,
  .RxCompleteCallbackRegister = EUSART2_SetRxInterruptHandler,
  .TxCompleteCallbackRegister = EUSART2_SetTxInterruptHandler,
  .ErrorCallbackRegister = EUSART2_SetErrorHandler,
  .FramingErrorCallbackRegister = EUSART2_SetFramingErrorHandler,
  .OverrunErrorCallbackRegister = EUSART2_SetOverrunErrorHandler,
  .ParityErrorCallbackRegister = NULL,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = EUSART2_IsRxReady,
  .IsTxReady = EUSART2_IsTxReady,
  .IsTxDone = EUSART2_IsTxDone
  };

/**
  Section: Macro Declarations
*/

#define EUSART2_TX_BUFFER_SIZE 8
#define EUSART2_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
*/
volatile uint8_t eusart2TxHead = 0;
volatile uint8_t eusart2TxTail = 0;
volatile uint8_t eusart2TxBuffer[EUSART2_TX_BUFFER_SIZE];
volatile uint8_t eusart2TxBufferRemaining;

volatile uint8_t eusart2RxHead = 0;
volatile uint8_t eusart2RxTail = 0;
volatile uint8_t eusart2RxBuffer[EUSART2_RX_BUFFER_SIZE];
volatile eusart2_status_t eusart2RxStatusBuffer[EUSART2_RX_BUFFER_SIZE];
volatile uint8_t eusart2RxCount;
volatile eusart2_status_t eusart2RxLastError;

/**
  Section: EUSART2 APIs
*/
void (*EUSART2_TxDefaultInterruptHandler)(void);
void (*EUSART2_RxDefaultInterruptHandler)(void);

void (*EUSART2_FramingErrorHandler)(void);
void (*EUSART2_OverrunErrorHandler)(void);
void (*EUSART2_ErrorHandler)(void);

void EUSART2_DefaultFramingErrorHandler(void);
void EUSART2_DefaultOverrunErrorHandler(void);
void EUSART2_DefaultErrorHandler(void);

void EUSART2_Initialize(void)
{
    // disable interrupts before changing states
    PIE3bits.RC2IE = 0;
    EUSART2_SetRxInterruptHandler(EUSART2_Receive_ISR);
    PIE3bits.TX2IE = 0;
    EUSART2_SetTxInterruptHandler(EUSART2_Transmit_ISR);
    // Set the EUSART2 module to the options selected in the user interface.

    // ABDEN disabled; WUE disabled; BRG16 16bit_generator; SCKP Non-Inverted; ABDOVF no_overflow; 
    BAUD2CON = 0x48;

    // ADDEN disabled; CREN disabled; SREN disabled; RX9 8-bit; SPEN enabled; 
    RC2STA = 0x80;

    // TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; TXEN enabled; TX9 8-bit; CSRC client; 
    TX2STA = 0x26;

    // SPBRGL 25; 
    SP2BRGL = 0x19;

    // SPBRGH 0; 
    SP2BRGH = 0x0;


    EUSART2_SetFramingErrorHandler(EUSART2_DefaultFramingErrorHandler);
    EUSART2_SetOverrunErrorHandler(EUSART2_DefaultOverrunErrorHandler);
    EUSART2_SetErrorHandler(EUSART2_DefaultErrorHandler);

    eusart2RxLastError.status = 0;

    // initializing the driver state
    eusart2TxHead = 0;
    eusart2TxTail = 0;
    eusart2TxBufferRemaining = sizeof(eusart2TxBuffer);

    eusart2RxHead = 0;
    eusart2RxTail = 0;
    eusart2RxCount = 0;

    // enable receive interrupt
    PIE3bits.RC2IE = 1;
}

bool EUSART2_IsTxReady(void)
{
    return (eusart2TxBufferRemaining ? true : false);
}

bool EUSART2_is_tx_ready(void)
{
    return EUSART2_IsTxReady();
}

bool EUSART2_IsRxReady(void)
{
    return (eusart2RxCount ? true : false);
}

bool EUSART2_is_rx_ready(void)
{    
    return EUSART2_IsRxReady();
}

bool EUSART2_IsTxDone(void)
{
    return TX2STAbits.TRMT;
}

bool EUSART2_is_tx_done(void)
{
    return EUSART2_IsTxDone();
}

eusart2_status_t EUSART2_GetLastStatus(void){
    return eusart2RxLastError;
}

eusart2_status_t EUSART2_get_last_status(void){
    return EUSART2_GetLastStatus();
}

uint8_t EUSART2_Read(void)
{
    uint8_t readValue  = 0;
    
    while(0 == eusart2RxCount)
    {
    }

    eusart2RxLastError = eusart2RxStatusBuffer[eusart2RxTail];

    readValue = eusart2RxBuffer[eusart2RxTail++];
    if(sizeof(eusart2RxBuffer) <= eusart2RxTail)
    {
        eusart2RxTail = 0;
    }
    PIE3bits.RC2IE = 0;
    eusart2RxCount--;
    PIE3bits.RC2IE = 1;

    return readValue;
}

void EUSART2_Write(uint8_t txData)
{
    while(0 == eusart2TxBufferRemaining)
    {
    }

    if(0 == PIE3bits.TX2IE)
    {
        TX2REG = txData;
    }
    else
    {
        PIE3bits.TX2IE = 0;
        eusart2TxBuffer[eusart2TxHead++] = txData;
        if(sizeof(eusart2TxBuffer) <= eusart2TxHead)
        {
            eusart2TxHead = 0;
        }
        eusart2TxBufferRemaining--;
    }
    PIE3bits.TX2IE = 1;
}


void EUSART2_Transmit_ISR(void)
{

    // add your EUSART2 interrupt custom code
    if(sizeof(eusart2TxBuffer) > eusart2TxBufferRemaining)
    {
        TX2REG = eusart2TxBuffer[eusart2TxTail++];
        if(sizeof(eusart2TxBuffer) <= eusart2TxTail)
        {
            eusart2TxTail = 0;
        }
        eusart2TxBufferRemaining++;
    }
    else
    {
        PIE3bits.TX2IE = 0;
    }
}

void EUSART2_Receive_ISR(void)
{
    
    eusart2RxStatusBuffer[eusart2RxHead].status = 0;

    if(RC2STAbits.FERR){
        eusart2RxStatusBuffer[eusart2RxHead].ferr = 1;
        EUSART2_FramingErrorHandler();
    }

    if(RC2STAbits.OERR){
        eusart2RxStatusBuffer[eusart2RxHead].oerr = 1;
        EUSART2_OverrunErrorHandler();
    }
    
    if(eusart2RxStatusBuffer[eusart2RxHead].status){
        EUSART2_ErrorHandler();
    } else {
        EUSART2_RxDataHandler();
    }
    
    // or set custom function using EUSART2_SetRxInterruptHandler()
}

void EUSART2_RxDataHandler(void){
    // use this default receive interrupt handler code
    eusart2RxBuffer[eusart2RxHead++] = RC2REG;
    if(sizeof(eusart2RxBuffer) <= eusart2RxHead)
    {
        eusart2RxHead = 0;
    }
    eusart2RxCount++;
}

void EUSART2_DefaultFramingErrorHandler(void){}

void EUSART2_DefaultOverrunErrorHandler(void){
    // EUSART2 error - restart

    RC2STAbits.CREN = 0;
    RC2STAbits.CREN = 1;

}

void EUSART2_DefaultErrorHandler(void){
    EUSART2_RxDataHandler();
}

void EUSART2_SetFramingErrorHandler(void (* interruptHandler)(void)){
    EUSART2_FramingErrorHandler = interruptHandler;
}

void EUSART2_SetOverrunErrorHandler(void (* interruptHandler)(void)){
    EUSART2_OverrunErrorHandler = interruptHandler;
}

void EUSART2_SetErrorHandler(void (* interruptHandler)(void)){
    EUSART2_ErrorHandler = interruptHandler;
}

void EUSART2_SetTxInterruptHandler(void (* interruptHandler)(void)){
    EUSART2_TxDefaultInterruptHandler = interruptHandler;
}

void EUSART2_SetRxInterruptHandler(void (* interruptHandler)(void)){
    EUSART2_RxDefaultInterruptHandler = interruptHandler;
}
/**
  End of File
*/
