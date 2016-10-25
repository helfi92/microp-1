#ifndef _KEYPAD
#define _KEYPAD

#include <stm32f4xx_hal.h>
#include <supporting_functions.h>

void setAsInput(GPIO_InitTypeDef *Keypad_Input);
void setAsOutput(GPIO_InitTypeDef* Keypad_Output);
void keypadInit(void);
uint8_t getRow(void);
uint8_t getColumn(void);
void handleKeyOnPress(void);
uint8_t readKeypadValue(void);
void selectMode(void);


extern uint8_t mode_flag;

typedef struct keypad_state{
	uint8_t key; 
} keypad_state;

#endif