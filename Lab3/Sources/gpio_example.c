//////////////////////////////////////////////////////////////////////////////////
////	File Name					: gpio_example.c
////	Description				: Sample code to help use the GPIO driver
////	Author						: Harsh Aurora
////	Date							: Oct 1st, 2016
//////////////////////////////////////////////////////////////////////////////////
//	
////		Includes		//


#include <gpio_example.h>

///*Brief: Sets up the desired(refer to header) GPIO pin to output mode
//**			 and initializes its value to 0
//**Params: None
//**Return: None
//*/
//void gpio_example_init(void) {
//	// LED + Segments
//	GPIO_InitTypeDef GPIO_InitDef;
//			
//	EXAMPLE_PORT_CLK_EN; 									
//	
//	// Initializing LED lights
//	GPIO_InitDef.Pin = PIN_1 | PIN_2 | PIN_3 | PIN_4 | PIN_A | PIN_B 
//		| PIN_C | PIN_C | PIN_D | PIN_E | PIN_F | PIN_G | PIN_DOT | PIN_MIDDLE;
//	GPIO_InitDef.Mode = GPIO_MODE_OUTPUT_PP;   			
//	GPIO_InitDef.Pull = GPIO_NOPULL;
//	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;
//	
//	// Initializing Segments
//	
//	HAL_GPIO_Init(EXAMPLE_PORT, &GPIO_InitDef);
//}

//// Testing purposes
//void gpio_all_segments_on(void){
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_SET);	
//}


//void read_piezo() {
//	GPIO_InitTypeDef GPIO_InitDef_Piezo;
//	GPIO_InitDef_Piezo.Pin = PIN_PIEZO;
//	GPIO_InitDef_Piezo.Pull = GPIO_NOPULL;
//	GPIO_InitDef_Piezo.Speed = GPIO_SPEED_FREQ_MEDIUM;
//	
//	HAL_GPIO_ReadPin(EXAMPLE_PORT, PIN_PIEZO);
//}

//// decimal 0 means no decimal. otherwise, decimal
//void gpio_display_number(int num, int place, int decimal) {	
//	switch(num){
//		case 0:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 1:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 2:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 3:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);	
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 4:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 5:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 6:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 7:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 8:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		case 9:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		// Case 10 is to not show anything
//		case 10:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;
//		// Case 11 is to show the dot
//		case 11:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_SET);
//			break;
//		// Degree sign
//		case 12:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_A, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_B, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_C, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_D, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_E, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_F, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_G, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_RESET);
//			break;		
//	}
//	
//	switch(place){
//		case 0:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_RESET);
//		  break;
//		case 1:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_RESET);
//				
//			if (decimal) {
//				HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_DOT, GPIO_PIN_SET);				
//			}
//		
//		  break;
//		case 2:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_RESET);
//		  break;
//		case 3:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_RESET);
//			break;
//		
//		case 4:
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_SET);
//			break;
//	}
//}

//void gpio_example(void) {	
//	// LED CYCLING
//	HAL_Delay(DELAY);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_SET);
//	
//	HAL_Delay(DELAY);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_2, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_SET);

//	HAL_Delay(DELAY);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_3, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_SET);
//	

//	HAL_Delay(DELAY);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_MIDDLE, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_SET);
//	
//	HAL_Delay(DELAY);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_4, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(EXAMPLE_PORT, PIN_1, GPIO_PIN_SET);

//}

