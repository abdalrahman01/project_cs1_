#pragma once
#ifndef _LCD_COMMANDS

void print_char_increment_ADP(unsigned char c);
void print_char(unsigned char c);
void print_word(unsigned char word[], int length);
void select_line(int line);

void print_from_keypad(int key);

void run_command_op2(unsigned char command, unsigned char op_low, unsigned op_hi);
void run_command_op1(unsigned char command, unsigned char op_low);

void clear_screen();
void plot(int x, int y, char c);
#endif