////////////////////////////////////////////////////////////////////////////////
//	File Name					: gpio.c
//	Description				: Code to use the GPIO driver
//	Author						: Group 14
//	Date							: Oct 6th, 2016
////////////////////////////////////////////////////////////////////////////////
	
//		Includes		//
//#include <gpio_example.h>
#include "gpio.h"

/**Brief: Sets up the desired(refer to header) GPIO pin to output mode
 *			 and initializes its value to 0
 * Params: None
 * Return: None
*/
void gpio_init(void) {
	// LED + Segments
	GPIO_InitTypeDef GPIO_InitDef;
	
	// Digits
	GPIO_InitTypeDef GPIO_InitDef_digits;
			
	PORT_D_CLK_EN;
	PORT_E_CLK_EN;	
	
	// Initializing LED + Segments
	GPIO_InitDef.Pin = PIN_A | PIN_B | PIN_C | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G | PIN_DOT
						| PIN_GREEN | PIN_BLUE | PIN_RED | PIN_ORANGE;
	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef.Pull = GPIO_NOPULL;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
	// Initializing Digits
	GPIO_InitDef_digits.Pin = PIN_1 | PIN_2 | PIN_3 | PIN_4 | PIN_MIDDLE;
	GPIO_InitDef_digits.Mode = GPIO_MODE_OUTPUT_PP;   			
	GPIO_InitDef_digits.Pull = GPIO_NOPULL;
	GPIO_InitDef_digits.Speed = GPIO_SPEED_FREQ_MEDIUM;
	
	//Initializing Ports
	HAL_GPIO_Init(PORT_D, &GPIO_InitDef);
	HAL_GPIO_Init(PORT_E, &GPIO_InitDef_digits);
}

/**Brief: Displays segments to show a number of your choice between [0-9]
 * Params: num: an 'int' representing a digit to display
 *				place: an 'int' representing the indexed segment between 0 to 4 inclusively
 *				decimal: an 'int' set to 1 if you want the decimal in index 1 to be displayed
 * Return: None
*/
void gpio_display_number(int num, int place, int decimal) {	
	// Controlling the digit to display
	switch(num){
		case 0:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 4:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 5:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 6:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 7:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 8:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		// Case 10 is to not show anything
		case 10:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;
		// Case 11 is to show the dot
		case 11:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_SET);
			break;
		// Degree sign
		case 12:
			HAL_GPIO_WritePin(PORT_D, PIN_A, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_B, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_C, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_D, PIN_D, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_E, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_F, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_G, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_RESET);
			break;		
	}
	// Controls the index (place) to display on the board
	switch(place){
		case 0:
			HAL_GPIO_WritePin(PORT_E, PIN_1, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_E, PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_MIDDLE, GPIO_PIN_RESET);
		  break;
		case 1:
			HAL_GPIO_WritePin(PORT_E, PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_2, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_E, PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_MIDDLE, GPIO_PIN_RESET);
				
			if (decimal) {
				HAL_GPIO_WritePin(PORT_D, PIN_DOT, GPIO_PIN_SET);				
			}
		
		  break;
		case 2:
			HAL_GPIO_WritePin(PORT_E, PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_3, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_E, PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_MIDDLE, GPIO_PIN_RESET);
		  break;
		case 3:
			HAL_GPIO_WritePin(PORT_E, PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_4, GPIO_PIN_SET);
			HAL_GPIO_WritePin(PORT_E, PIN_MIDDLE, GPIO_PIN_RESET);
			break;
		
		case 4:
			HAL_GPIO_WritePin(PORT_E, PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_4, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(PORT_E, PIN_MIDDLE, GPIO_PIN_SET);
			break;
	}
}

/**Brief: This displays one of the 4 onscreen LEDS
 * Params: index: an "int" that determines which colour light to display.
 *					0: green
 *					1: orange
 *					2: red
 *					3: blue		
 * Return: None
*/
void display_LED(int index){
	if (index == 4){
		HAL_GPIO_WritePin(PORT_D, PIN_GREEN, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PORT_D, PIN_ORANGE, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PORT_D, PIN_RED, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(PORT_D, PIN_BLUE, GPIO_PIN_RESET);
	}	
	else {	
		switch(index%4){
			case 0:
				HAL_GPIO_WritePin(PORT_D, PIN_GREEN, GPIO_PIN_SET);
				HAL_GPIO_WritePin(PORT_D, PIN_ORANGE, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_BLUE, GPIO_PIN_RESET);
				break;
			case 1:
				HAL_GPIO_WritePin(PORT_D, PIN_GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_ORANGE, GPIO_PIN_SET);
				HAL_GPIO_WritePin(PORT_D, PIN_RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_BLUE, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(PORT_D, PIN_GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_ORANGE, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_RED, GPIO_PIN_SET);
				HAL_GPIO_WritePin(PORT_D, PIN_BLUE, GPIO_PIN_RESET);
				break;
			case 3:
				HAL_GPIO_WritePin(PORT_D, PIN_GREEN, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_ORANGE, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_RED, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(PORT_D, PIN_BLUE, GPIO_PIN_SET);
				break;
			}
	}
}

