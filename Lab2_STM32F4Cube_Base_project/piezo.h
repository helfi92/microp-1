////////////////////////////////////////////////////////////////////////////////
//	File Name					: piezo.h
//	Description				: header file for adc.h
//	Author						: Group 14
//	Date							: 
////////////////////////////////////////////////////////////////////////////////

#ifndef _ADC_PIEZO
#define _ADC_PIEZO

#define POLL_TIMEOUT 10000

#define PIEZO_ADC ADC1
#define PIEZO_ADC_CHANNEL ADC_CHANNEL_2
#define PIEZO_ADC_CLK_EN 	__HAL_RCC_ADC2_CLK_ENABLE()

#define PIEZO_ADC_GPIO_PORT GPIOA //Port C
#define PIEZO_ADC_GPIO_PIN GPIO_PIN_2 // Pin C4 is connected to the ADC2 Channel 15 input
#define PIEZO_ADC_GPIO_PORT_CLK_EN __HAL_RCC_GPIOA_CLK_ENABLE();

void piezo_adc_init(void);
float piezo_adc(void);
float piezo_adc_to_temperature(float piezo_val);
#endif
