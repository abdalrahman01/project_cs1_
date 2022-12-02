#include "GUI_constants.h"
#include "GUI.h"
#include "../keypad.h"



void exit_back(int key);

void controll_home_page()
{

    if (MODE != MODE_HOME_PAGE_MENU_VIEW)
        return;

    // short local_address = HOME_PAGE_ADDRESS;
    int key = button_released();

    switch (key)
    {
    case 1:
        set_text_home_address(PAGE_1_ADDRESS);
        MODE = MODE_PAGE_1_GREENHOUSE_VIEW;
        break;
    case 2:
        set_text_home_address(PAGE_2_ADDRESS);
        MODE = MODE_PAGE_2_DATATABLE_VIEW;
        break;
    case 3:
        set_text_home_address(PAGE_3_ADDRESS);
        MODE = MODE_PAGE_3_OPTIONS_VIEW;
        break;

    default:
        MODE = MODE_HOME_PAGE_MENU_VIEW;
        break;
    }
}

void controll_page_1_current_day()
{

    if (MODE != MODE_PAGE_1_GREENHOUSE_VIEW)
        return;
    int key = button_released();
    switch (key)
    {
    case 10:
        set_text_home_address(HOME_PAGE_ADDRESS);
        MODE = MODE_HOME_PAGE_MENU_VIEW;

        break;
    case 12:
        set_text_home_address(PAGE_3_ADDRESS);
        MODE = MODE_PAGE_3_OPTIONS_VIEW;

        break;

    default:
        break;
    }
}
void controll_page_2_datatable()
{
    if (MODE != MODE_PAGE_2_DATATABLE_VIEW)
        return;
    int key = button_released();
    switch (key)
    {
    case 10:
        set_text_home_address(HOME_PAGE_ADDRESS);
        MODE = MODE_HOME_PAGE_MENU_VIEW;
        break;
    case 12:
        set_text_home_address(PAGE_1_ADDRESS);
        MODE = MODE_PAGE_1_GREENHOUSE_VIEW;
        break;
    default:
        break;
    }
}
void controll_page_3_options()
{
    if (MODE != MODE_PAGE_3_OPTIONS_VIEW)
        return;
    int key = button_released();
    switch (key)
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
        break;
    case 12:
        set_text_home_address(PAGE_1_ADDRESS);
        MODE = MODE_PAGE_1_GREENHOUSE_VIEW;
        break;

    default:
        break;
    }
}

void temp_low_edit()
{

    if (MODE != MODE_TEMP_LOW_EDIT)
        return;
    short local_address = PAGE_3_ADDRESS;

    int key = clicked_released();
    exit_back(key);
    short temprature = 0;

    set_cursor_pointer(14, 5);
    set_address_pointer(local_address, 14, 5);

    print_char(key + '0'); // 1 + '0' = '1'
    temprature += key; 

    key = clicked_released();
    exit_back(key);

    set_cursor_pointer(13, 5);
    set_address_pointer(local_address, 13, 5);

    print_char(key + '0'); // 1 + '0' = '1'
    temprature += key * 10; 

    MODE = MODE_PAGE_3_OPTIONS_VIEW;
}
void temp_high_edit(){
	
	if ( MODE != MODE_TEMP_HIGH_EDIT)
		return;
    short local_address = PAGE_3_ADDRESS;

	int key = clicked_released(); 
    	exit_back(key);

	short temprature = 0; 

	set_cursor_pointer(14,6); 
	set_address_pointer(local_address,14, 6); 
	
	print_char(key + '0');  // 1 + '0' = '1'
 	temprature += key;  

	key = clicked_released();
	exit_back(key);

	set_cursor_pointer(13,6); 
	set_address_pointer(local_address,13, 6); 

	print_char(key + '0');  // 1 + '0' = '1'
 	temprature += key * 10 ; 

	MODE = MODE_PAGE_3_OPTIONS_VIEW;

}
void edit_date()
{
    if (MODE != MODE_DATE_EDIT)
        return;
    int key = 0;
    char date[8] = "00/00/00";

    for (char i = 0; i < 8; i++)
    {
        if (i == 2 || i == 5) // jumb over "/"
            continue;

        set_curser_pointer(PAGE_2_ADDRESS, i, 4);
        key = button_released();

        if (key == HOME_BUTTON)
            go_home();
        if (key == RETURN_BUTTON)
            return;

        set_address_pointer(PAGE_2_ADDRESS, i, 4);
        date[i] = key + '0';
        print_char(key + '0');
    }
}

void edit_clock()
{
    if (MODE != MODE_CLOCK_EDIT)
        return;
    int key = 0;
    char time[8] = "00:00:00";

    for (char i = 0; i < 8; i++)
    {
        if (i == 2 || i == 5) // jumb over ":"
            continue;

        set_curser_pointer(PAGE_2_ADDRESS, i + 8, 4);
        key = button_released();

        if (key == HOME_BUTTON)
            go_home();
        if (key == RETURN_BUTTON)
            return;

        set_address_pointer(PAGE_2_ADDRESS, i + 8, 4);
        time[i] = key + '0';
        print_char(key + '0');
    }
}
void go_home()
{
    set_text_home_address(HOME_PAGE_ADDRESS);
    MODE = MODE_HOME_PAGE_MENU_VIEW;
}

void exit_back(int key)
{
    if (key == 10)
    {
        go_home();
    }
    else if (key == 11)
    {
        MODE == MODE_PAGE_3_OPTIONS_VIEW;
    }
}