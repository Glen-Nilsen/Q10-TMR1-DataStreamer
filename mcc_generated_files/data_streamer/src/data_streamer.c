// Generate variable frames for sending data to the MPLAB Data Visualizer, 
// e.g. to be display on a graph.
#include <stdint.h>
#include "../../uart/eusart2.h"

#define DATA_STREAMER_START_BYTE 3  //trivial Data Streamer Protocol start of frame token
#define DATA_STREAMER_END_BYTE (255 - DATA_STREAMER_START_BYTE)  
// Data Streamer Protocol end byte is the One's compliment (~) of startByte, 
// e.g. startByte: 0b0000 0011, endByte: 0b1111 1100

static void variableWrite_sendValue(uint8_t* byte_ptr, uint8_t num_bytes)
 {
      for(uint8_t i = 0; i < num_bytes; i++)
      {
         EUSART2_Write(byte_ptr[i]);
      }
}

void variableWrite_sendFrame(uint8_t count_8bit, uint16_t count_16bit, uint32_t count_32bit)
{
   EUSART2_Write(DATA_STREAMER_START_BYTE);  

   EUSART2_Write(count_8bit);                // uint8_t

   EUSART2_Write((count_16bit >> 0)  & 0xFF); // Low  byte of uint16_t 
   EUSART2_Write((count_16bit >> 8)  & 0xFF); // High byte

   variableWrite_sendValue((uint8_t *) &count_32bit, 4);

   EUSART2_Write(DATA_STREAMER_END_BYTE);  

   while(!EUSART2_IsTxDone());
}
