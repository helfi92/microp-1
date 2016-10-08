////////////////////////////////////////////////////////////////////////////////
//	File Name					: main.c
//	Description				: program entry
//	Author						: Harsh Aurora
//	Date							: Oct 1st, 2016
////////////////////////////////////////////////////////////////////////////////
	
//		Includes		//
#include <stm32f4xx_hal.h>
#include <supporting_functions.h>
#include <sysclk_config.h>
#include <gpio_example.h>
#include <gpio.h>
#include <adc.h>
void refresh_display(int tick, float number);

//		Global variables		//
volatile int systick_flag; // flag to tell if a systick interrup has occured
ADC_HandleTypeDef ADC1_Handle;

/*Brief: Sets up the system clock and then calls update_display
**Params: None
**Return: None
*/
int main(void)
{
	int time_counter = 0;
	float ADC_val;
	int delay_counter = 0;
	
  //		MCU Configuration		//
  //	Reset of all peripherals, Initializes the Flash interface and the Systick	//
  HAL_Init();
	
  //	Configure the system clock	//
  SystemClock_Config();

  //	Example code initialization	//
	gpio_init();
	adc_init();
	//gpio_all_segments_on();
	
	
	//	run sample code forever	//
//	while(1) {
//			
//		// run every 1 second. This can also be achieved with HAL_Delay(100) for the current settengs
//		if(systick_flag == 1) { // Please look in stm32f4xx_it.c to understand how this variable is set and used
//			
//			// Conditon to reset delay counter
//			if (delay_counter >= DELAY) {
//				delay_counter = 0;
//			}
//			
//			delay_counter++;
//			//update_display(delay_counter % DELAY);
//			
//			systick_flag = 0;
//			if(time_counter++ == 100) { // increments every 10 ms, used to count when 1 second has passed
//				time_counter = 0;
//				ADC_val = adc();
//				float temperature = adc_to_temperature(ADC_val);
//				printf("%f\n",temperature);
//				//numberToDisplay((factor), delay_counter);
//				refresh_display(delay_counter % DELAY, temperature);
//				//printf("ADC voltage = %f Volts\n", ADC_val);	
//			}
//		}		
//	}
		int count = 0; 
		float temperature;
		float  temperature_sample = 0.0;
		while(1) {
			
		// run every 1 second. This can also be achieved with HAL_Delay(100) for the current settengs
		if(systick_flag == 1) { // Please look in stm32f4xx_it.c to understand how this variable is set and used
			systick_flag = 0;
			if(time_counter++ == 100) { // increments every 10 ms, used to count when 1 second has passed
				time_counter = 0;
				
				
				//gpio_example();
				ADC_val = adc();
				temperature = adc_to_temperature(ADC_val);
				printf("ADC voltage = %f Volts\n", ADC_val);	
				
				//how often to update the display
				if (count%100  == 0){
					 temperature_sample = temperature;
				}
				refresh_display(count, temperature_sample);
				//For the alarm
				//if (temperature>60){
					if (count%101 == 0){
							display_LED(count);
					}
				//}
				count++;
			}
			
		}		
	
	}
}

int refresh_counter = 0;
/*Brief: Takes a number to display to the 7 segment display board
**Params: num: a 'float' that represents the number to display | delay_counter: an 'int' that represent the counter from [0 to DELAY[
**Return: None
*/
//void refresh_display(int tick, float number) {
//	refresh_counter++;
////	printf("raw number is: %f\n", number);
//	int parsedInt = (int) (number * 10);
//	int decimal, ones, tens;
//	decimal = parsedInt % 10;
//	ones = (parsedInt / 10) % 10;
//	tens = (parsedInt / 100) % 10;
//	
////	printf("tens are: %d\n", tens);
////	printf("ones are: %d\n", tens);
////	printf("decimals are: %d\n", tens);
//	
//	if (refresh_counter == 1) {
//      gpio_display_number(tens,0, 0);
//  }
//  else if (refresh_counter == 2) {
//      gpio_display_number(ones,1, 1);
//  }
//  else if (refresh_counter == 3) {
//      gpio_display_number(decimal,2, 0);
//  }
//  else if (refresh_counter == 4) {
//      gpio_display_number(12,4, 0);			
//			refresh_counter = 0;
//  }
//}

/*Brief: Takes a number to display to the 7 segment display board
**Params: num: a 'float' that represents the number to display | delay_counter: an 'int' that represent the counter from [0 to DELAY[
**Return: None
*/
void refresh_display(int tick, float number) {
	int parsedInt = (int) (number * 10);
	int decimal, ones, tens;
	decimal = parsedInt % 10;
	ones = (parsedInt / 10) % 10;
	tens = (parsedInt / 100) % 10;
	
//	printf("tens are: %d\n", tens);
//	printf("ones are: %d\n", tens);
//	printf("decimals are: %d\n", tens);

	switch(tick%4){
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
