#include "../lcd_commands.h"
#include "../commands_data_lcd.h"
#include "../keypad.h"
#include "GUI_constants.h"
#include "GUI_controls.h"

extern char MODE = 0;

void daley(int);
void set_address_pointer(unsigned short address, char col, char row)
{
    // address: choose which diplay to use (HOME_PAGE_ADDRESS, PAGE_1_ADDRESS, etc ...)

    // if (col, row) is outside the col.
    if (col > 30 || col < 0 || row < 0 || row > 16)
        return;

    address += (row * 30) + col;

    run_command_op2(SET_ADDRESS_POINTER, address & 0xff, (address & 0xff00) >> 8);
}
void set_curser_pointer(unsigned short address, char col, char row)
{
    // address: choose which diplay to use (HOME_PAGE_ADDRESS, PAGE_1_ADDRESS, etc ...)

    // if (col, row) is outside the col.
    if (col > 30 || col < 0 || row < 0 || row > 16)
        return;

    address += (row * 30) + col;

    run_command_op2(SET_CURSER_POINTER, address & 0xff, (address & 0xff00) >> 8);
}
void set_text_home_address(unsigned short address)
{
    // address: choose which diplay to use (HOME_PAGE_ADDRESS, PAGE_1_ADDRESS, etc ...)

    run_command_op2(SET_TEXT_HOME_ADDRESS, address & 0xff, (address & 0xff00) >> 8);
    delay(100); // wait 100ms
}



void key_listner(int key)
{
    if (key == 0)
        return;
    controll_home_page();
    controll_page_1_current_day();
    controll_page_2_datatable();
    controll_page_3_options();
    
}
