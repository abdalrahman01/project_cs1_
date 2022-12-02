#include "GPIO_config.h"
#include "startup_files/at91sam3x8.h"
#include "lcd_commands.h"
#include "keypad.h"
#include "commands_data_lcd.h"
#include "lcd_keypad_buss.h"

#define   DELAY 50

void make_databus_as_input();
void delay(int value);

unsigned char data_bus();
void make_databus_as_output();
void clear_databus();
void set_command_to_databus(unsigned char command);
void init_reset_button();
void set_data_to_databus(unsigned char data);

void initialize_pins_LCD()
{   

    flag_pins_LCD();
    rest_pins_not_enabled_with_keypad(6);

    init_reset_button();
}

void init_reset_button()
{
    PIOD_PER(0);
    PIOD_PUDR(0);
    PIOD_OER(0);
}

void delay(int value)
{
    for (int i = 0; i < value; i++)
        asm("nop");
}

unsigned char is_display_ok(unsigned char status_word)
{
    // dataseet p.13
    if ((status_word & (1)) != 1) // check sta0: command execution capability
        return 0;
    if ((status_word & (1 << 1)) != (1<<1)) // check sta1: data read/write  capability
        return 0;

    return 1;
}

unsigned char read_status_display(void)
{

    unsigned char temp;

    make_databus_as_input(); // Abd does not think it right

    PIOC_SODR(DIR); // set dir as input

    PIOC_CODR(ACTIVATE_CHIP74_LCD); // clear/enable output

    PIOC_SODR(CD); // Set C/D

    PIOC_CODR(CE); // clear chip select display

    PIOC_CODR(RD); // clear read display

    delay(DELAY);

    temp = data_bus(); // read databuss

    PIOC_SODR(CE); // SET chip select display
    PIOC_SODR(RD); // SET read display

    PIOC_SODR(ACTIVATE_CHIP74_LCD); // disable output

    PIOC_CODR(DIR); // clear dir

    return temp;
}

void write_command_2_display(unsigned char command)
{

    while (is_display_ok(read_status_display()) == 0)
    {
    }

   
    make_databus_as_output(); // set databus as output
   
    clear_databus();
    set_command_to_databus(command);

    PIOC_CODR(DIR); // set_dir_as_output();

    PIOC_CODR(ACTIVATE_CHIP74_LCD); // enable_output();


    PIOC_SODR(CD); // command mode S

    PIOC_CODR(CE); // clear_chip_select_display();

    PIOC_CODR(WR); // clear_write_display();

    delay(DELAY);

    PIOC_SODR(CE); // set_chip_enable_display(); ?????

    PIOC_SODR(WR); // set_write_display();

    PIOC_SODR(ACTIVATE_CHIP74_LCD); // disable_output_74chip();

    make_databus_as_input();
}

void write_data_2_display(unsigned char data)
{

    while (is_display_ok(read_status_display()) == 0)
    {
    }

    clear_databus();
    set_data_to_databus(data);

    PIOC_CODR(DIR); // information flows from arduino to lcd

    PIOC_CODR(ACTIVATE_CHIP74_LCD); // clearing is enabling, the pin is inverted
    make_databus_as_output();       // passes data from arduino to lcd

    PIOC_CODR(CD); // choose data mode 

    PIOC_CODR(CE); // clear_chip_select

    PIOC_CODR(WR); // clear_write_display()

    delay(DELAY);

    PIOC_SODR(CE); // chip enable display

    PIOC_SODR(CD); // choose command mode 


    PIOC_SODR(WR); // set write enable display

    PIOC_SODR(ACTIVATE_CHIP74_LCD); // disable 74chip();

    make_databus_as_input();
}

void init_display(void)
{

    PIOD_CODR(RESET); // clear reset display
    delay(DELAY);
    PIOD_SODR(RESET); // set reset display

    
    run_command_op2(SET_TEXT_HOME_ADDRESS, 0x00, 0x00);

    run_command_op2(SET_GRAPHIC_HOME_ADDRESS, 0x00, 0x40);


    run_command_op2(SET_TEXT_AREA, 0x1e, 0x00); 


    run_command_op2(SET_GRAPHIC_AREA, 0x1e, 0x00);

    write_command_2_display(TEXT_MODE); // text mode

    write_command_2_display(TEXT_ON_GRAPHIC_OFF | 0x93); // text on graphic off |curson on blink on


    run_command_op2(0x21, 0,2);
    // write_command_2_display(0x21); // set cursor pointer
//    run_command_op2(0x60, 1,1); // cursor auto moving Enabled
    write_command_2_display(0xa0);

    
    run_command_op2(SET_ADDRESS_POINTER, 0x00, 0x00); // Set Address pointer
    clear_screen();
    run_command_op2(SET_ADDRESS_POINTER, 0x00, 0x00);


}


void make_databus_as_input()
{
    *AT91C_PIOC_ODR = DATABUS;
}
void make_databus_as_output()
{
    *AT91C_PIOC_OER = DATABUS;
}

unsigned char data_bus()
{
    return ((*AT91C_PIOC_PDSR & DATABUS) >> 2); // *AT91C_PIOC_PDSR & DATABUS = 00xx xxxx xx00;
}

void clear_databus()
{

    *AT91C_PIOC_CODR = (DATABUS);
}

void set_command_to_databus(unsigned char command)
{

    *AT91C_PIOC_SODR = (command << 2);
}
void set_data_to_databus(unsigned char data)
{

    *AT91C_PIOC_SODR = (data << 2);
}

void from_keypad_to_display()
{
    int key = pressed_key();
    if (key==0)
        return; 
    print_from_keypad(key);
}