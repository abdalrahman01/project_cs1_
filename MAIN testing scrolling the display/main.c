
#include "startup_files/system_sam3x.h"
#include "startup_files/at91sam3x8.h"
#include "GPIO_config.h"

#include "keypad.h"
#include "LCD.h"

#include "commands_data_lcd.h"
#include "temp_sensor.h"
#include "light_sensor.h"

#include "servo.h"
#include "lcd_commands.h"
void initializing_peripherals();
void run_peripherals();
void print_to_screen_line_numbers_to_count_screen_nums();
void scroll_screen(); 
unsigned int systick_counter = 0;
unsigned int systick_counter_temp = 0;
unsigned int systick_counter_light = 0;
unsigned int systick_counter_servo = 0;

int main()
{
  SystemInit();
  initializing_peripherals();

  SysTick_Config(SystemCoreClock / 1000);
   print_to_screen_line_numbers_to_count_screen_nums();
  scroll_screen();
  while (1)
  {
    run_peripherals();
  }
  return 0;
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

void run_peripherals()
{
  from_keypad_to_display();
  run_temp_sensor(&systick_counter_temp);
  read_values_light_sensors(&systick_counter_light);
  update_position_servo(pressed_key(), &systick_counter_servo);
}

void SysTick_Handler()
{
  systick_counter++;
  systick_counter_temp++;
  systick_counter_light++;
  systick_counter_servo++;
}

void print_to_screen_line_numbers_to_count_screen_nums()
{
  int address = 16 * 4 * 30 ; 
  char low = address & (0xff);
  char hi = (address & (0xff00) >> 8);
    for (int i = 0; i < 16 * 4 -1; i++)
  {
    
    run_command_op2(SET_ADDRESS_POINTER,low,hi );
    print_char(i);
    address -= 30; 
    low = address & (0xff);
    hi = ((address & (0xff00)) >> 8);
  }

}
void scroll_screen(){
   short address = 16 * 4 * 30 ; 
   char low = address & (0xff);
   char hi = (address & (0xff00) >> 8);
   
   for (int i = 0; i < 16 * 4 -1; i++)
    {
    
    run_command_op2(0x40,low,hi );
    
    address -= 30; 
    low = address & (0xff);
    hi = ((address & (0xff00)) >> 8);
  }
}