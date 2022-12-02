#include "../lcd_commands.h"
#include "../commands_data_lcd.h"
#include "../keypad.h"
#include "GUI_constants.h"
#include "GUI_controls.h"
#include "GUI_views.h"


extern char MODE = 0;

void init_gui(){
   home_view();
  page1_view();
  page2_view();
  page3_view();
}

void set_address_pointer(unsigned short address, char col, char row)
{
    // address: choose which diplay to use (HOME_PAGE_ADDRESS, PAGE_1_ADDRESS, etc ...)

    // if (col, row) is outside the col.
    if (col > 30 || col < 0 || row < 0 || row > 16)
        return;

    address += (row * 30) + col;

    run_command_op2(SET_ADDRESS_POINTER, address & 0xff, (address & 0xff00) >> 8);
}
void set_curser_pointer(char col, char row)
{

    // if (col, row) is outside the col.
    if (col > 30 || col < 0 || row < 0 || row > 16)
        return;


    run_command_op2(SET_CURSER_POINTER, col, row);
}
void set_text_home_address(unsigned short address)
{
    // address: choose which diplay to use (HOME_PAGE_ADDRESS, PAGE_1_ADDRESS, etc ...)

    run_command_op2(SET_TEXT_HOME_ADDRESS, address & 0xff, (address & 0xff00) >> 8);
 
}



void key_listner(int key)
{
    if (key == 0)
        return;
    controll_home_page();
    controll_page_1_current_day();
    controll_page_2_datatable();
    controll_page_3_options();
    edit_clock();
    edit_date();
    edit_temprature_higher();
    edit_temprature_lower();
    
}
