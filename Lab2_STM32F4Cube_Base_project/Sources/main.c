////////////////////////////////////////////////////////////////////////////////
//	File Name					: main.c
//	Description				: program entry
//	Author						: Group 14
//	Date							: Oct 1st, 2016
////////////////////////////////////////////////////////////////////////////////
	
//		Includes		//
#include <stm32f4xx_hal.h>
#include <supporting_functions.h>
#include <sysclk_config.h>
#include <gpio_example.h>
#include <gpio.h>
#include <adc.h>

//		Global variables		//
volatile int systick_flag; // flag to tell if a systick interrup has occured
ADC_HandleTypeDef ADC1_Handle;

/**Brief: Displays the temperature on the 7 segment display.
 *        First it sets up the system clock. With the clock, everytime interval of time, there is an interupt and the systick_flag is set to 1.
 *		  Each time this happens, at different intervals of time, the ADC will poll another value, the display value will update, and the display will refresh_display
 *		  An alarm will go off (in the form of the on board LEDs flashing in a circular motion) if the temperatue is greater than 60 degrees C
 * Params: None
 * Return: None
 */
int main(void){
	int adc_counter = 0;
	int update_value_counter = 0;
	int display_rate_counter = 0;
	int alarm_counter = 0;
	int delay_counter = 0;
	int tick = 0;

	float ADC_val, temperature;
	float temperature_sample = 0.0;
	
	//		MCU Configuration		//
	//	Reset of all peripherals, Initializes the Flash interface and the Systick	//
	HAL_Init();
	
	//	Configure the system clock	//
	SystemClock_Config();

	gpio_init();
	adc_init();

	while(1) {
		// run every 1 second. This can also be achieved with HAL_Delay(100) for the current settengs
		if(systick_flag == 1) { // Please look in stm32f4xx_it.c to understand how this variable is set and used
			systick_flag = 0;

			//how often poll the adc temperature sensor
			if(adc_counter++ == 100) { // increments every 10 ms, used to count when 1 second has passed
				adc_counter = 0;
				
				ADC_val = adc();
				temperature = adc_to_temperature(ADC_val);
				printf("ADC voltage = %f Volts,  temperature = %f\n", ADC_val, temperature);	
			}
			
			//how often to update the display value
			if (update_value_counter++ == 10000){
				update_value_counter = 0;

				temperature_sample = temperature;
			}

			//display rate of 7 segment display (so how often to change which digit is displaying)
			if(display_rate_counter++ == 10) { 
				display_rate_counter = 0;
				refresh_display(tick, temperature_sample);
			}

			//For the alarm
			if (alarm_counter++ == 10000 && temperature>60){
					display_LED(tick);
			}
			if (tick++ > 32766)
				tick = 0;
		}	
	}
}