////////////////////////////////////////////////////////////////////////////////
//	File Name					: adc.h
//	Description				: header file for adc.h
//	Author						: Group 14
//	Date							: Oct 6th, 2016
////////////////////////////////////////////////////////////////////////////////

#ifndef _ADC_EXAMPLE
#define _ADC_EXAMPLE

#define POLL_TIMEOUT 10000

#define EXAMPLE_ADC ADC1
#define EXAMPLE_ADC_CHANNEL ADC_CHANNEL_16
#define EXAMPLE_ADC_CLK_EN 	__HAL_RCC_ADC1_CLK_ENABLE()

#define EXAMPLE_ADC_GPIO_PORT GPIOA
#define EXAMPLE_ADC_GPIO_PIN GPIO_PIN_5 // Pin A5 is connected to the ADC1 Channel 5 input
#define EXAMPLE_ADC_GPIO_PORT_CLK_EN __HAL_RCC_GPIOA_CLK_ENABLE();

void adc_init(void);
float adc_to_temperature(float adc);
float adc(void);
#endif
