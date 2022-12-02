
#include "startup_files/system_sam3x.h"
#include "startup_files/at91sam3x8.h"
#include "GPIO_config.h"

#include "keypad.h"
#include "LCD.h"

#include "commands_data_lcd.h"
#include "temp_sensor.h"
#include "light_sensor.h"

#include "servo.h"


#include "GUI/GUI.h"    

#include "calendar.h"

void initializing_peripherals();
void run_peripherals();

unsigned int systick_counter = 0;
unsigned int systick_counter_temp = 0;
unsigned int systick_counter_light = 0;
unsigned int systick_counter_servo = 0;

int main()
{
  SystemInit();
  initializing_peripherals();

  SysTick_Config(SystemCoreClock / 1000);
  
  init_gui();
  
  while (1)
  {
    
    key_listner(pressed_key());
    // run_peripherals();
  }

}

void initializing_peripherals()
{
  initialize_pins();
  initialize_pins_LCD();
  init_display();
  init_temp_sensor();
  init_light_sensors();
  init_serv();
}

//void run_peripherals()
//{
//  from_keypad_to_display();
//  run_temp_sensor(&systick_counter_temp);
//  read_values_light_sensors(&systick_counter_light);
//  update_position_servo(pressed_key(), &systick_counter_servo);
//}

void SysTick_Handler()
{
  systick_counter++;
  systick_counter_temp++;
  systick_counter_light++;
  systick_counter_servo++;
  MILLIESECONDS_COUNTER++;

}