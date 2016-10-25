#include "keypad.h"
#include "gpio.h"
// Pin maps for keypad columns and rows

const uint16_t rowMap[] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11};
const uint16_t colMap[] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14};
uint8_t mode_flag;

const uint8_t keypadMapped[4][3] = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
	{10, 0, 11}
};

GPIO_InitTypeDef GPIORow, GPIOCol;

void keypadInit(void) {
	GPIORow.Pin = rowMap[0] | rowMap[1] | rowMap[2] | rowMap[3];
	GPIOCol.Pin = colMap[0] | colMap[1] | colMap[2];
	setAsInput(&GPIOCol);
	setAsOutput(&GPIORow);
}

/**
   * @brief Set the relevant GPIO pins to be input
   * @param Keypad_Input	the GPIO init struct that stores the pins used
   * @retval None
   */
void setAsInput(GPIO_InitTypeDef *Keypad_Input){
	Keypad_Input->Speed = GPIO_SPEED_FREQ_LOW;
	Keypad_Input->Mode = GPIO_MODE_INPUT;
	Keypad_Input->Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(PORT_E, Keypad_Input);
}

/**
   * @brief Set the relevant GPIO pins to be output
   * @param Keypad_Output	the GPIO init struct that stores the pins used
   * @retval None
   */
void setAsOutput(GPIO_InitTypeDef* Keypad_Output){
	Keypad_Output->Speed = GPIO_SPEED_FREQ_LOW;
	Keypad_Output->Mode = GPIO_MODE_OUTPUT_PP;
	Keypad_Output->Pull = GPIO_NOPULL;
	HAL_GPIO_Init(PORT_E, Keypad_Output);
}



// Returns row of pressed key
uint8_t getRow(void) {
	uint8_t row1 = HAL_GPIO_ReadPin(PORT_E, rowMap[0]);
	uint8_t row2 = HAL_GPIO_ReadPin(PORT_E, rowMap[1]);
	uint8_t row3 = HAL_GPIO_ReadPin(PORT_E, rowMap[2]);
	uint8_t row4 = HAL_GPIO_ReadPin(PORT_E, rowMap[3]);
	
	if (row1) {
		return 1;
	}
	if (row2) {
		return 2;
	}
	if (row3) {
		return 3;
	}
	if (row4) {
		return 4;
	}	
	// Return -1 if noise
	return -1;
}

// Returns column of pressed key
uint8_t getColumn(void) {
	uint8_t col1 = HAL_GPIO_ReadPin(PORT_E, colMap[0]);
	uint8_t col2 = HAL_GPIO_ReadPin(PORT_E, colMap[1]);
	uint8_t col3 = HAL_GPIO_ReadPin(PORT_E, colMap[2]);
	
	if(col1) {
		return 1;
	} 
	if(col2) {
		return 2;
	} 
	if(col3) {
		return 3;
	}
	
	return -1;
}


uint8_t readKeypadValue(void) {
	uint8_t key;
	
	setAsInput(&GPIOCol);
	setAsOutput(&GPIORow);
	
	HAL_GPIO_WritePin(PORT_E,rowMap[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_E,rowMap[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_E,rowMap[2], GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_E,rowMap[3], GPIO_PIN_SET);
	
	uint8_t colNumber = getColumn();
	
	setAsInput(&GPIORow);
	setAsOutput(&GPIOCol);
	
	HAL_GPIO_WritePin(PORT_E,colMap[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_E,colMap[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_E,colMap[2], GPIO_PIN_SET);
	
	uint8_t rowNumber = getRow();
	
	if (rowNumber >= 1 && rowNumber <= 4 && colNumber >= 1 && colNumber <= 3) {
		key = keypadMapped[rowNumber - 1][colNumber - 1];
		printf("key: %d\n", key);		
		return key;
	}	
	
	return -1;
}

void selectMode(void) {
	while(1) {
		uint8_t mode = readKeypadValue();
		// Acceleration mode
		if (mode == 1) {
			mode_flag = 1;
			break;
		}
		// Piezo mode
		if (mode == 2) {
			mode_flag = 2;
			break;
		}
		mode_flag = -1;
	}
}

void handleKeyOnPress(void) {
	
}