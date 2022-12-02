//#include "startup_files/at91sam3x8.h"
//#include "startup_files/system_sam3x.h"

unsigned int MILLIESECONDS_COUNTER = 0;
unsigned int SECONDS_COUNTER = 0;
unsigned int MINUTES_COUNTER = 0;
unsigned int HOURS_COUNTER = 0;
unsigned int DAYS_COUNTER = 0;
unsigned int MONTHS_COUNTER = 0;
unsigned int YEARS_COUNTER = 0;

struct date {
    unsigned char day[5]; // 5 bits 
    unsigned char  month[4]; // 4 bits
    short year; // 7 bits
}; // total 4 bytes

struct time
{
    unsigned char seconds[6]; // 6 bits
    unsigned char minutes[6]; // 6 bits
    short hours; // 5 bits
}; // total 4 bytes


//void init_calander()
//{
//    SysTick_Config(SystemCoreClock / 1000);
//}

void SysTick_Handler()
{
    MILLIESECONDS_COUNTER++;
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