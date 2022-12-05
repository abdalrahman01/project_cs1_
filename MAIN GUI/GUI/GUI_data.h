#pragma once
void date_current_day();

void print_time(struct time t, unsigned short dispaly, unsigned char x, unsigned char y);
void print_date(struct date d, unsigned short dispaly, unsigned char x, unsigned char y);
void update_time(char time[8]);
void update_date(char date[10]);

