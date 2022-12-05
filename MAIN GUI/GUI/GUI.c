#include "../calendar.h"
#include "../lcd_commands.h"
#include "../commands_data_lcd.h"
#include "../keypad.h"
#include "GUI_constants.h"
#include "GUI_controls.h"
#include "GUI_views.h"
#include "GUI_data.h"


extern char MODE = 0;

void init_gui(){
   home_view();
  page1_view();
  page2_view();
  page3_view();
//   struct date date_now = ;

  print_date(get_date(), PAGE_1_ADDRESS, 13,0);
}

void run_gui(){
    date_current_day();
}

void set_address_pointer(unsigned short address, char col, char row)
{
    // address: choose which diplay to use (HOME_PAGE_ADDRESS, PAGE_1_ADDRESS, etc ...)

    // if (col, row) is outside the col.
    if (col > 30 || row > 16)
        return;

    address += (row * 30) + col;

    run_command_op2(SET_ADDRESS_POINTER, address & 0xff, (address & 0xff00) >> 8);
}
void set_curser_pointer(char col, char row)
{

    // if (col, row) is outside the col.
    if (col > 30 || row > 16)
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

    switch (MODE)
    {
    case MODE_HOME_PAGE_MENU_VIEW:
        controll_home_page();
        break;

    case MODE_PAGE_1_GREENHOUSE_VIEW:
        controll_page_1_current_day();
        break;

    case MODE_PAGE_2_DATATABLE_VIEW:
        controll_page_2_datatable();
        break;

    case MODE_PAGE_3_OPTIONS_VIEW:
        controll_page_3_options();
        break;

    case MODE_TEMP_LOW_EDIT:
        edit_temprature_lower();
        break;

    case MODE_TEMP_HIGH_EDIT:
        edit_temprature_higher();
        break;

    case MODE_DATE_EDIT:
        edit_date();
        break;

    case MODE_CLOCK_EDIT:
        edit_clock();
        break;

    
    default:
        break;
    }
 
    
}