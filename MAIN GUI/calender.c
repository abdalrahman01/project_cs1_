#include "startup_files/at91sam3x8.h"
#include "startup_files/system_sam3x.h"

extern unsigned int MILLIESECONDS_COUNTER = 0;
unsigned int SECONDS_COUNTER = 0;
unsigned int MINUTES_COUNTER = 0;
unsigned int HOURS_COUNTER = 0;
unsigned int DAYS_COUNTER = 0;
unsigned int MONTHS_COUNTER = 0;
unsigned int YEARS_COUNTER = 0;

struct date {
    unsigned char day; // 5 bits 
    unsigned char  month; // 4 bits
    unsigned char year; // 7 bits
}; // total 4 bytes

struct time
{
    unsigned char seconds; // 6 bits
    unsigned char minutes; // 6 bits
    unsigned char hours; // 5 bits
}; // total 4 bytes



// void init_calander()
// {
//     SysTick_Config(SystemCoreClock / 1000);
// }

void datetime_now(struct time *tnow, struct date *dnow){
    tnow->hours = HOURS_COUNTER;
    tnow->minutes = MINUTES_COUNTER;
    tnow->seconds = SECONDS_COUNTER;

    dnow->day = DAYS_COUNTER;
    dnow->month = MONTHS_COUNTER;
    dnow->year = YEARS_COUNTER;
}
struct time * get_time(){
    struct time  ti = {SECONDS_COUNTER, MINUTES_COUNTER, HOURS_COUNTER};
    return &ti; 
}
struct date * get_date(){
    struct date  da = {DAYS_COUNTER,MONTHS_COUNTER, YEARS_COUNTER};
    return &da; 
}

void set_date(char day, char month, char year){
    DAYS_COUNTER = day;
    MONTHS_COUNTER = month;
    YEARS_COUNTER = year;
}
void set_time(char secs, char month, char yr){
    SECONDS_COUNTER  =secs; 
    MONTHS_COUNTER = month;
    YEARS_COUNTER = yr;
}


void update_counters()
{
    if (MILLIESECONDS_COUNTER >= 1000)
    {
        SECONDS_COUNTER++;
        MILLIESECONDS_COUNTER = 0;
    }
    if (SECONDS_COUNTER >= 60)
    {
        MINUTES_COUNTER++;
        SECONDS_COUNTER = 0;
    }
    if (MINUTES_COUNTER >= 60)
    {
        HOURS_COUNTER++;
        MINUTES_COUNTER = 0;
    }
    if (HOURS_COUNTER >= 24)
    {
        DAYS_COUNTER++;
        HOURS_COUNTER = 0;
    }
    if (DAYS_COUNTER >= 30)
    {
        MONTHS_COUNTER++;
        DAYS_COUNTER = 0;
    }
    if (MONTHS_COUNTER >= 12)
    {
        YEARS_COUNTER++;
        MONTHS_COUNTER = 0;
    }
    if (YEARS_COUNTER >= 2099)
    {
        YEARS_COUNTER = 0;
    }
}