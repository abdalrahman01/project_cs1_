#include "GUI_constants.h"
#include "GUI.h"
#include "../lcd_commands.h"

void command_window(short local_address);


void home_view(){
    short local_address = HOME_PAGE_ADDRESS;
    // set_text_home_address(local_address);

    set_address_pointer(local_address, 13, 0);
    print_word("HELLO" ,5); 

    set_address_pointer(local_address, 7, 2);
    print_word("CHOOSE OPTIONS" ,15); 
    
    set_address_pointer(local_address, 0, 4);
    print_word("(1)CURRENT DAY (2)TABLE DATA", 29);
    set_address_pointer(local_address, 0, 6);
    print_word("(3)EDIT OPTIONS (4)LOG IN", 26);

    set_address_pointer(local_address, 0, 12);
    print_word("Abdulfattah Morad", 18);
    set_address_pointer(local_address, 0, 14);
    print_word("Abd Alrahman Atieh", 19);
    
}

void page1_view(){
    short local_address = PAGE_1_ADDRESS;
    // set_text_home_address(local_address);

    set_address_pointer(local_address, 0,0);
    print_word("Current Day: dd/mm/yyyy",24);
    set_address_pointer(local_address, 0,1);
    print_word("Time: hh:mm:ss",15);

    set_address_pointer(local_address, 0,2);
    print_word("Sun Position: aa" ,16);

    set_address_pointer(local_address, 0,4);
    print_word("Hours In Sunlight: aa" ,21);

    set_address_pointer(local_address, 0,6);
    print_word("Hours In Darkness: aa" ,21);

    set_address_pointer(local_address, 0,8);
    print_word("Hours Of Lighting System: aa" ,29);

    set_address_pointer(local_address, 0,15);
    print_word("*:Go Home # :Edit time" ,22);

    }
    
void page2_view(){
    short local_address = PAGE_2_ADDRESS;
    // set_text_home_address(local_address);
    
    
    
    set_address_pointer(local_address, 0, 0);
    print_word("Tempr:    min     max     avg" ,30);
    for (int i = 1; i < 7; i++)
    {
        set_address_pointer(local_address, 0, i*2);
        print_word("dd/mm/yy aaa      mmm     aaa",30);
        set_address_pointer(local_address, 9, i*2 +1);
        print_word("hh:mm:ss hh:mm:ss", 18);
    }
    set_address_pointer(local_address, 0,15);
    print_word("*:Go Home #:Go Current Day" ,27);

     
}

void page3_view(){
    short local_address = PAGE_3_ADDRESS;
    // set_text_home_address(local_address);


    set_address_pointer(local_address, 0,0);
    print_word("Options/Edit",13);

    set_address_pointer(local_address, 0,1);
    print_word("(1) Temp Low",13);

    set_address_pointer(local_address, 0,2);
    print_word("(2) Temp Upper",15);

    set_address_pointer(local_address, 0,3);
    print_word("(3) date",9);

    set_address_pointer(local_address, 0,4);
    print_word("(4) Time",9);
    set_address_pointer(local_address, 0,5);
    print_word("-----------------------------",30);
    set_address_pointer(local_address, 0,7);
    print_word("Lower limit = xx",17);
    set_address_pointer(local_address, 0,8);
    print_word("Upper limit = xx",17);
    set_address_pointer(local_address, 0,9);
    print_word("Date: dd/mm/yyyy",15);
    set_address_pointer(local_address, 0,10);
    print_word("Time: ss:mm:hh",15);
    
    set_address_pointer(local_address, 0,11);
    print_word("----------------",17);



    set_address_pointer(local_address, 0,15);
    print_word("*:Go Home #:Go CurrentDay" ,26);
 }

void command_window(short local_address){
        set_address_pointer(local_address, 0,15);
        print_word("1:Go Home 2:Go CurrentDay" ,26);

}