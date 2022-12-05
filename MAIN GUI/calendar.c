#include "startup_files/at91sam3x8.h"
#include "startup_files/system_sam3x.h"

extern unsigned int MILLIESECONDS_COUNTER = 0;
unsigned int SECONDS_COUNTER;
unsigned int MINUTES_COUNTER;
unsigned int HOURS_COUNTER;
unsigned int DAYS_COUNTER;
unsigned int MONTHS_COUNTER;
unsigned int YEARS_COUNTER;

extern char TICK = 0; //  [bit 0: seconds, bit2: days ] if bit set, the counter has been updated recently 

struct date
{
    unsigned char day;
    unsigned char month;
    unsigned short year;
}; // total 4 bytes

struct time
{
    char seconds; // 6 bits
    char minutes; // 6 bits
    unsigned char hours;   // 5 bits
};                         // total 4 bytes

void init_calander()
{
    MILLIESECONDS_COUNTER = 0;
    SECONDS_COUNTER = 0;
    MINUTES_COUNTER = 23;
    HOURS_COUNTER = 4;
    DAYS_COUNTER = 5;
    MONTHS_COUNTER = 3;
    YEARS_COUNTER = 2020;
    TICK = 0; 
;
}

void datetime_now(struct time *tnow, struct date *dnow)
{
    tnow->hours = HOURS_COUNTER;
    tnow->minutes = MINUTES_COUNTER;
    tnow->seconds = SECONDS_COUNTER;

    dnow->day = DAYS_COUNTER;
    dnow->month = MONTHS_COUNTER;
    dnow->year = YEARS_COUNTER;
}
struct time get_time()
{
    struct time ti = {SECONDS_COUNTER, MINUTES_COUNTER, HOURS_COUNTER};
    
    return ti;
}
struct date get_date()
{
    struct date da = {DAYS_COUNTER, MONTHS_COUNTER, YEARS_COUNTER};
    return da;
}

void set_date(unsigned char day, unsigned char month, unsigned short year)
{
    DAYS_COUNTER = day;
    MONTHS_COUNTER = month;
    YEARS_COUNTER = year;
}
void set_time(unsigned char hours, unsigned char minutes, unsigned char secs)
{
    SECONDS_COUNTER = secs;
    MINUTES_COUNTER = minutes;
    HOURS_COUNTER = hours;
}

void update_counters()
{
    if (MILLIESECONDS_COUNTER >= 1000)
    {
        SECONDS_COUNTER++;
        MILLIESECONDS_COUNTER = 0;
        TICK |= 1; // set the minutes flag

    }  else {
        TICK &= (0 << 0); // clear the minutes flag
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
        TICK |= (1<< 2); // set the dayss' flag
    } else {
        TICK &= ~(1 << 2); // clear the days' flag
    }
    if (DAYS_COUNTER >= 30)
    {
        MONTHS_COUNTER++;
        DAYS_COUNTER = 0;
        TICK |= (1<<2) ;
    } else {
        TICK &= ~(1<<2) ;


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