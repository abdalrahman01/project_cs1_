#include "../calendar.h"
#include "GUI_constants.h"
#include "../lcd_commands.h"
#include "GUI.h"
#include "stdio.h"

void print_date(struct date d, unsigned short dispaly, unsigned char x, unsigned char y);
void print_time(struct time t, unsigned short dispaly, unsigned char x, unsigned char y);


struct time time_now ;
struct date date_now ;



void date_current_day()
{
  

    if ((TICK & 1) == 1)
    {
        time_now = get_time();
        printf("%d:%d:%d\n", time_now.hours,time_now.minutes,time_now.seconds);
        print_time(time_now, PAGE_1_ADDRESS, 6, 1);
    }
    if ((TICK & (1 << 2)) == (1 << 2))
    {
        date_now = get_date();
        print_date(date_now, PAGE_1_ADDRESS, 13, 0);
    }
}

void print_date(struct date d, unsigned short dispaly, unsigned char x, unsigned char y)
{
    // prints the time t from position x. where x and x+1: dd. x+3 and x+4 : mm. x+6 . x+10: yyyy
    set_address_pointer(dispaly, x, y);
    unsigned char word[10];

    word[0] = d.day / 10 + '0';
    word[1] = d.day % 10 + '0';
    word[2] = '/';
    word[3] = d.month / 10 + '0';
    word[4] = d.month % 10 + '0';
    word[5] = '/';
    word[6] = d.year / 1000 + '0';
    d.year /= 1000;
    word[7] = d.year / 100 + '0';
    d.year /= 100;
    word[8] = d.year / 10 + '0';
    word[9] = d.year % 10 + '0';
    print_word(word, 10);
}

void print_time(struct time t, unsigned short dispaly, unsigned char x, unsigned char y)
{
    set_address_pointer(dispaly, x, y);
    unsigned char word[8];

    word[0] = t.hours / 10 + '0';
    word[1] = t.hours % 10 + '0';
    word[2] = ':';
    word[3] = t.minutes / 10 + '0';
    word[4] = t.minutes % 10 + '0';
    word[5] = ':';
    word[6] = t.seconds / 10 + '0';
    word[7] = t.seconds % 10 + '0';

    print_word(word, 8);
}