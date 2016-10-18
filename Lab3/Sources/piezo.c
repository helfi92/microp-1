////////////////////////////////////////////////////////////////////////////////
//	File Name					: piezo.c
//	Description				: 
//	Author						: 
//	Date							: 
////////////////////////////////////////////////////////////////////////////////
	
//		Includes		//
#include <stm32f4xx_hal.h>
#include <supporting_functions.h>
#include "piezo.h"

//		Global variables		//
extern ADC_HandleTypeDef ADC_Piezo_Handle;

/*Brief: Sets up the desired(refer to header) ADC and corresponding GPIO for input
**Params: None
**Return: None
*/
void piezo_adc_init(void) {
	ADC_InitTypeDef PIEZO_ADC_Init; 																	// definition of ADC1 initialiation struct
	ADC_ChannelConfTypeDef PIEZO_ADC_Channel;												// definition of ADC1 channel struct
	HAL_LockTypeDef PIEZO_ADC_Lock; 																	// define ADC1 locking object
	ADC_MultiModeTypeDef PIEZO_ADC_Mode; 														// define ADC1 mode struct
	
	/*  initialize ADC init struct */
	PIEZO_ADC_Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;					// ADC Clock frequency 42MHz (168/4)
	PIEZO_ADC_Init.Resolution = ADC_RESOLUTION_12B;										// 12 bit resolution, better but slower
	PIEZO_ADC_Init.DataAlign = ADC_DATAALIGN_RIGHT;										// align the 12 bits data at the right of the 32 bits words
	PIEZO_ADC_Init.ScanConvMode = DISABLE;														// single channel mode
	PIEZO_ADC_Init.EOCSelection = ADC_EOC_SEQ_CONV;										// perform ADC conversions without having to read all conversion data
	PIEZO_ADC_Init.ContinuousConvMode = DISABLE;											// single mode convertion
	PIEZO_ADC_Init.DMAContinuousRequests = DISABLE;										// single mode DMA request
	PIEZO_ADC_Init.NbrOfConversion = 1;																// one conversion
	PIEZO_ADC_Init.DiscontinuousConvMode = ENABLE;										// enable discountinuous mode
	PIEZO_ADC_Init.NbrOfDiscConversion = 1;														// one conversion
	PIEZO_ADC_Init.ExternalTrigConv = ADC_SOFTWARE_START;							// no external trigger
	PIEZO_ADC_Init.ExternalTrigConvEdge = ADC_SOFTWARE_START;					// no external trigger
	
	/* initialize ADC handle struct */
	ADC_Piezo_Handle.Instance = PIEZO_ADC;
	ADC_Piezo_Handle.Init = PIEZO_ADC_Init;
	ADC_Piezo_Handle.NbrOfCurrentConversionRank = 1;
	ADC_Piezo_Handle.Lock = PIEZO_ADC_Lock;
	ADC_Piezo_Handle.State = 0;
	ADC_Piezo_Handle.ErrorCode = HAL_ADC_ERROR_NONE;
	
	/* initialize ADC channel struct */
	PIEZO_ADC_Channel.Channel = PIEZO_ADC_CHANNEL;
	PIEZO_ADC_Channel.Rank = 1;																			// use to determine the rank in which this channel is sampled
	PIEZO_ADC_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;				// time for the internal capacitor to charge. longer means more accurate
	PIEZO_ADC_Channel.Offset = 0;
	
	/* initialize ADC mode struct */
	PIEZO_ADC_Mode.Mode = ADC_MODE_INDEPENDENT;														
	PIEZO_ADC_Mode.DMAAccessMode = ADC_DMAACCESSMODE_DISABLED;
	PIEZO_ADC_Mode.TwoSamplingDelay = ADC_TWOSAMPLINGDELAY_5CYCLES;
	
	PIEZO_ADC_CLK_EN;
	HAL_ADC_ConfigChannel(&ADC_Piezo_Handle, &PIEZO_ADC_Channel);
	HAL_ADCEx_MultiModeConfigChannel(&ADC_Piezo_Handle, &PIEZO_ADC_Mode);	/* configure mode */

	GPIO_InitTypeDef GPIO_InitDef; 								
	PIEZO_ADC_GPIO_PORT_CLK_EN; 									
	
	GPIO_InitDef.Pin = PIEZO_ADC_GPIO_PIN; 	
	GPIO_InitDef.Mode = GPIO_MODE_ANALOG;   			
	GPIO_InitDef.Pull = GPIO_PULLDOWN;
	GPIO_InitDef.Speed = GPIO_SPEED_FREQ_MEDIUM;		
	
	HAL_GPIO_Init(PIEZO_ADC_GPIO_PORT, &GPIO_InitDef);
}

/*Brief: Performs the steps to poll the ADC, and converts the obtained value to a voltage
**Params: None
**Return: None
*/
float piezo_adc(void) {
	float val = 0;
	HAL_ADC_Start(&ADC_Piezo_Handle);
	if(HAL_ADC_PollForConversion(&ADC_Piezo_Handle, POLL_TIMEOUT) == HAL_OK) {
		val = HAL_ADC_GetValue(&ADC_Piezo_Handle);
	}
		
	HAL_ADC_Stop(&ADC_Piezo_Handle);
	return (val*3.0)/4096.0;
}

float piezo_adc_to_temperature(float piezo_val) {
	return (piezo_val - 0.76) / 0.0025 + 25;
}


