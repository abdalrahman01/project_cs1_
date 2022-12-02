#include "lcd_commands.h"
#include "commands_data_lcd.h"
#include "keypad.h"

#define HOME_PAGE_ADDRESS 0x0000
#define PAGE_1_ADDRESS 0x001E // screen size is cols x rows (16 x 30 = 480 [0x1e])
#define PAGE_2_ADDRESS 0x003C
#define PAGE_3_ADDRESS 0x05A0

#define MODE_HOME_PAGE_MENU_VIEW 0
#define MODE_PAGE_1_DATATABLE_VIEW 1
#define MODE_PAGE_2_OPTIONS_VIEW 2
#define MODE_PAGE_2_OPTIONS_EDIT 3
#define MODE_PAGE_3_GREENHOUSE_VIEW 4

#define MODE_TEMP_LOW_EDIT 5
#define MODE_TEMP_HIGH_EDIT 6
#define MODE_DATE_EDIT 7
#define MODE_CLOCK_EDIT 8

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

extern char MODE = 0;

void init_home_page()
{
    short local_address = HOME_PAGE_ADDRESS;

    set_address_pointer(local_address, 0, 0);
    print_word("(1): Page 1", 12);
    set_address_pointer(local_address, 0, 1);
    print_word("(2): Page 2       (3): Page 3", 30);
}

void init_page_1()
{
    short local_address = PAGE_1_ADDRESS;

    set_address_pointer(local_address, 0, 0);
    // min max avg
    for (char i = 0; i < 7; i++)
    {

        print_word("dd/mm/yy  xxx   xxx   xxx    ", 30);
        print_word("min: hh:mm:ss   max: hh:mm:ss", 30);
    }

    set_address_pointer(local_address, 0, 15);
    print_word("(#) (*): Home Page.", 16);
}
void init_page_2()
{

    short local_address = PAGE_2_ADDRESS;
    set_address_pointer(local_address, 0, 0);

    print_word("SHOW/EDIT OPTIONS:", 19);

    set_address_pointer(local_address, 0, 1);
    print_word("TEMP:", 6);

    set_address_pointer(local_address, 0, 2);
    print_word("MIN: xx MAX: xx", 17);

    set_address_pointer(local_address, 0, 3);
    print_word("DATE AND TIME:", 15);
    set_address_pointer(local_address, 0, 4);
    print_word("dd/mm/yy hh:mm:ss", 18);

    set_address_pointer(local_address, 0, 5);
    print_word("Edit:", 6);
    set_address_pointer(local_address, 0, 6);
    print_word("(1) temp low (2) temp high", 27);
    set_address_pointer(local_address, 0, 8);
    print_word("(3) date (4) clock", 19);

    set_address_pointer(local_address, 0, 15);
    print_word("(#): Home Page.", 16);
}
void init_page_3()
{
    short local_address = PAGE_3_ADDRESS;
    set_address_pointer(local_address, 0, 0);

    print_word("Today: dd/mm/yy", 16);
    set_address_pointer(local_address, 0, 1);
    print_word("Time Now: hh:mm:ss", 19);

    set_address_pointer(local_address, 0, 2);
    print_word("Temprature Now: xx (Celsius) ", 30);
    print_word("Sun position in degrees: xxxx", 30);
    print_word("hours in dark xx in Light xxx", 30);

    set_address_pointer(local_address, 0, 11);
    print_word("(1) RESET ALARM", 16);

    set_address_pointer(local_address, 0, 12);
    print_word("(2) CHANGE UPPER/LOWER LIMITS FOR TMEPRATURE", 45);

    set_address_pointer(local_address, 0, 15);
    print_word("(#): Home Page.", 16);
}

void command_window(short address)
{
    set_address_pointer(address, 0, 15);
    print_word("(#): Home Page. (*):Back", 25);
}

void controll_home_page(int *key)
{
    short local_address = HOME_PAGE_ADDRESS;
    switch (*key)
    {
    case 1:
        set_text_home_address(PAGE_1_ADDRESS);
        MODE = MODE_PAGE_1_DATATABLE_VIEW;
        break;
    case 2:
        set_text_home_address(PAGE_2_ADDRESS);
        MODE = MODE_PAGE_2_OPTIONS_EDIT;
        break;
    case 3:
        set_text_home_address(PAGE_3_ADDRESS);
        MODE = MODE_PAGE_3_GREENHOUSE_VIEW;
        break;

    default:
        MODE = MODE_HOME_PAGE_MENU_VIEW;
        break;
    }
}

void controll_page_1_table(int *key)
{
    if (*key == 10 || *key == 12)
    {
        set_text_home_address(HOME_PAGE_ADDRESS);
        MODE = MODE_HOME_PAGE_MENU_VIEW;
    }
}
void controll_page_2_view(int *key)
{
    switch (*key)
    {
    case 1:
        MODE = MODE_TEMP_LOW_EDIT;
        break;
    case 2:
        MODE = MODE_TEMP_HIGH_EDIT;
        break;
    case 3:
        MODE = MODE_DATE_EDIT;
        break;
    case 4:
        MODE = MODE_CLOCK_EDIT;
        break;
    case 10:
        set_text_home_address(HOME_PAGE_ADDRESS);
        MODE = MODE_HOME_PAGE_MENU_VIEW;

    default:
        break;
    }
}
void controll_page_3_view(int *key)
{
    switch (*key)
    {
    case 1:
        reset_alram_temp_sensor();
        break;
    case 2:
        set_text_home_address(PAGE_2_ADDRESS);
        MODE = MODE_PAGE_2_OPTIONS_VIEW;
        break;

    default:
        break;
    }
}

void edit_temprature(char limit)
{
    // if limit is set: edit the upper limit
    // else: edit the lower limit.
    int col_position = 0;
    if (limit == 1)
        col_position = 14;
    else
        col_position = 6;

    set_curser_pointer(PAGE_2_ADDRESS, col_position, 2);

    short new_temp = 0;
    int key = 0;

    // set_address_pointer(PAGE_2_ADDRESS, col_position, 2);
    // print_char(new_temp % 10 + '0');
    // set_curser_pointer(PAGE_2_ADDRESS, col_position - 1, 2);

   
    // read to digits from keypad
}

void edit_date()
{
    int key = 0;
    char date[6] = "000000";
    for (char i = 0; i < 6; i++)
    {
    }
}
void go_home()
{
    set_text_home_address(HOME_PAGE_ADDRESS);
    MODE = MODE_HOME_PAGE_MENU_VIEW;
}
void key_listner(int *key)
{
    if (*key == 0)
        return;
    switch (MODE)
    {
    case MODE_HOME_PAGE_MENU_VIEW:
        set_text_home_address(HOME_PAGE_ADDRESS);
        break;
    case MODE_PAGE_1_DATATABLE_VIEW:
        set_text_home_address(PAGE_1_ADDRESS);
        break;
    case MODE_PAGE_2_OPTIONS_VIEW:
        set_text_home_address(PAGE_2_ADDRESS);
        break;
    case MODE_PAGE_3_GREENHOUSE_VIEW:
        set_text_home_address(PAGE_3_ADDRESS);
        break;
    case MODE_TEMP_HIGH_EDIT:
        set_text_home_address(PAGE_2_ADDRESS);
        edit_temprature(1);
    case MODE_TEMP_LOW_EDIT:
        set_text_home_address(PAGE_2_ADDRESS);
        edit_temprature(0);
        break;
    case MODE_DATE_EDIT:
        set_text_home_address(PAGE_2_ADDRESS);
        edit_date();
    case MODE_CLOCK_EDIT:
        set_text_home_address(PAGE_2_ADDRESS);
        edit_clock();
        break;

    default:
        break;
    }
}
