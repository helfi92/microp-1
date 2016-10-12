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
#include "kalmanfilter.h"
#include "piezo.h"

void refresh_display(float number, int index); //TODO Figure out why this stops working when moved to gpio.c
void display_LED(int count);

//		Global variables		//
volatile int systick_flag; // flag to tell if a systick interrup has occured
ADC_HandleTypeDef ADC1_Handle;
ADC_HandleTypeDef ADC_Piezo_Handle;

	



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
	float ADC_val, temperature, piezo_val;
	float temperature_sample = 0.0;
	float kalmanOutput[1];
	
	
	// Kalman_state initializations
	struct kalman_state ks;
	ks.q = Q_INIT;
	ks.r = R_INIT;
	ks.x = X_INIT;
	ks.p = P_INIT;
	ks.k = K_INIT;
	ks.f = F_INIT;
	ks.h = H_INIT;
	
	//		MCU Configuration	
	//	Reset of all peripherals, Initializes the Flash interface and the Systick	//
	HAL_Init();
	
	//	Configure the system clock	//
	SystemClock_Config();

	gpio_init();
	adc_init();
	//piezo_adc_init();

	while(1) {

		// run every 1 ms. This can also be achieved with HAL_Delay(100) for the current settengs
		if(systick_flag == 1) { // Please look in stm32f4xx_it.c to understand how this variable is set and used
			systick_flag = 0;
			
			//how often poll the adc temperature sensor
			if(adc_counter++ == 100) { // increments every 100 ms, used to count when 100 ms has passed
				adc_counter = 0;
				
				ADC_val = adc();
				temperature = adc_to_temperature(ADC_val);
				Kalmanfilter_C(&temperature, kalmanOutput, &ks, LEN);		
				// printf("ADC voltage = %f Volts,  temperature = %f\n", ADC_val, temperature);	
				
				//Piezo sensor
				//piezo_val = piezo_adc();
				//printf("Piezo val = %f, Piezo temperature = %f\n", piezo_val, piezo_adc_to_temperature(piezo_val));		
				
			}
			
			//how often to update the display value
			if (update_value_counter++ == 500){ // 
				// printf("counter: %d\n", update_value_counter);
				update_value_counter = 0;

				temperature_sample = kalmanOutput[0];
			}

			//display rate of 7 segment display (so how often to change which digit is displaying)
			if(display_rate_counter++ == 2) { 
				display_rate_counter = 0;
				refresh_display(temperature_sample, tick);
			}

			if (alarm_counter++ >= 100){
				if(temperature_sample > 34.0) {
					alarm_counter = 0;
					display_LED(tick);
				} else {
					// Shut off alarm i.e., all LED's
					display_LED(4);
				}
			}
			if (tick++ > 32766)
				tick = 0;
		}	
	}
}
/**Brief: Takes a number to display to the 7 segment display.
 *Params: num: a 'float' that represents the number to display 
 *		  index: an 'int' that corresponds to  which digit index to dislay (from 0 to 2 inclusively)
 *Return: None
*/
void refresh_display(float number, int index) {
	int parsedInt = (int) (number * 10);
	int decimal, ones, tens;
	decimal = parsedInt % 10;
	ones = (parsedInt / 10) % 10;
	tens = (parsedInt / 100) % 10;
	switch(index%4){
		case 0:
			gpio_display_number(tens,0, 0);
			break;
		case 1:
			gpio_display_number(ones,1, 1);
			break;
		case 2:
			gpio_display_number(decimal,2, 0);
			break;
		case 3:
			gpio_display_number(12,4, 0);
			break;
	}
}


