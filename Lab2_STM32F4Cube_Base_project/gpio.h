////////////////////////////////////////////////////////////////////////////////
//	File Name					: gpio_example.h
//	Description				: header file for gpio_example.c
//	Author						: Harsh Aurora
//	Date							: Oct 1st, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _GPIO_EXAMPLE
#define _GPIO_EXAMPLE 

#include <stm32f4xx_hal.h>
#include <supporting_functions.h>

#define PORT_D GPIOD
#define PORT_E GPIOE

//These are the connected to the on board LEDs and are in PORT_D
#define PIN_GREEN GPIO_PIN_12 // Green LED
#define PIN_ORANGE GPIO_PIN_13 // Orange LED
#define PIN_RED GPIO_PIN_14 // Red LED
#define PIN_BLUE GPIO_PIN_15 // Blue LED

//These are the digits and will be in PORT_E
#define PIN_1 GPIO_PIN_0
#define PIN_2 GPIO_PIN_1
#define PIN_3 GPIO_PIN_2 
#define PIN_4 GPIO_PIN_3 
#define PIN_MIDDLE GPIO_PIN_4

//These are the segments and will be in PORT_D
#define PIN_A GPIO_PIN_0 
#define PIN_B GPIO_PIN_1
#define PIN_C GPIO_PIN_2
#define PIN_D GPIO_PIN_3
#define PIN_E GPIO_PIN_4
#define PIN_F GPIO_PIN_5
#define PIN_G GPIO_PIN_6
#define PIN_DOT GPIO_PIN_7

#define PIN_PIEZO GPIO_PIN_10 

#define DELAY 10

//GPIO_InitTypeDef GPIO_InitDef;

#define PORT_D_CLK_EN __HAL_RCC_GPIOD_CLK_ENABLE();
#define PORT_E_CLK_EN __HAL_RCC_GPIOE_CLK_ENABLE();

void gpio_init(void);
void gpio_display_number(int num, int place, int decimal);
void update_display(int count);
void display_LED(int count);
#endif
