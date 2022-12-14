#include "../calendar.h"
#include "GUI_constants.h"
#include "../lcd_commands.h"
#include "GUI.h"

void print_date(struct date d, unsigned short dispaly, unsigned char x, unsigned char y);
void print_time(struct time t, unsigned short dispaly, unsigned char x, unsigned char y);

void date_current_day()
{
    struct time time_now;
    struct date date_now;

    if ((TICK & 1) == 1)
    {
        time_now = get_time();
        print_time(time_now, PAGE_1_ADDRESS, 6, 1);
    }
    if ((TICK & (1 << 2)) == (1 << 2))
    {
        date_now = get_date();
        print_date(date_now, PAGE_1_ADDRESS, 13, 0);
    }
}
void update_date(char date[10])
{
    // date = "dd/mm/yyyy"
    // set_date(dd, mm, yyyy)
    // dd = date[0] * 10 + date[1]
    // mm = date[3] * 10 + date[4]
    // yyyy = date[6] * 1000 + date[7] * 100 + date[8] * 10 + date[9]
    // to convert from '1' to 1: char - 0x30 => int.

    set_date(((date[0] - 0x30) * 10) + ((date[1] - 0x30)),
             ((date[3] - 0x30) * 10) + ((date[4] - 0x30)),
             ((date[6] - 0x30) * 1000) + ((date[7] - 0x30) * 100) + ((date[8] - 0x30) * 10) + ((date[9] - 0x30)));

    // update the current date.
    delay(1000);
    print_date(get_date(), PAGE_1_ADDRESS, 13, 0);
}

void update_time(char time[8])
{
    // time = "hh:mm:ss"
    // set_time(ss,mm, hh)
    // hh = time[0] * 10 + time[1]
    // mm = time[3] * 10 + time[4]
    // ss = time[6] * 10 + time[7]
    // to convert from '1' to 1: char - 0x30 => int.

    set_time(((time[0] - 0x30) * 10) + (time[1] - 0x30),
             ((time[3] - 0x30) * 10) + (time[4] - 0x30),
             ((time[6] - 0x30) * 10) + (time[7] - 0x30));
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

    word[9] = d.year % 10 + '0';
    d.year /= 10;
    word[8] = d.year % 10 + '0';
    d.year /= 10;
    word[7] = d.year % 10 + '0';
    d.year /= 10;
    word[6] = d.year % 10 + '0';


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