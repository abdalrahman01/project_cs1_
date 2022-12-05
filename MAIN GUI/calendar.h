#ifndef _CALENDAR_
void init_calander(); 

extern unsigned int MILLIESECONDS_COUNTER;

extern char TICK; // a flag is set each second

struct time get_time();
struct date get_date();

void update_counters();
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
};  
#endif