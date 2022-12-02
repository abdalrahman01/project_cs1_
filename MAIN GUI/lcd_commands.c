#include "LCD.h"

#include "commands_data_lcd.h"



void run_command_op2(unsigned char command, unsigned char op_low, unsigned op_hi);
void print_char(unsigned char c);

void plot(int x, int y, char c){
    // x*8: every char = 8 bit.
    run_command_op2(SET_ADDRESS_POINTER, x, y); // Set Address pointer
    print_char(c);
    
}



void run_command_op2(unsigned char command, unsigned char op_low, unsigned op_hi)
{
    write_data_2_display(op_low);
    write_data_2_display(op_hi);
    write_command_2_display(command);
};
void run_command_op1(unsigned char command, unsigned char op_low)
{
    write_data_2_display(op_low);
    write_command_2_display(command);
};


void print_char_increment_ADP(unsigned char c)
{
    // in the ascci table:  characters starts from 0x20 end in 0x7e
    // but table for the LCD start from 0x00, 
    // thats why c - 0x20 
    run_command_op1(DATA_WRITE_AND_INCREMENT_ADP, c - 0x20);
}
void print_char(unsigned char c)
{
    // in the ascci table:  characters starts from 0x20 end in 0x7e
    // but table for the LCD start from 0x00, 
    // thats why c - 0x20   
    run_command_op1(DATA_WRITE_AND_NON_VARIABLE_ADP, c - 0x20);
}

void print_word(unsigned char * word, int length)
{
    for (int i = 0; i < length; i++)
        print_char_increment_ADP(word[i]);
}


void select_line(int line)
{

    if (line < 0 || line > 7)
        return;

    unsigned char lines[] = {
        0xA0,
        0xA1,
        0xA2,
        0xA3,
        0xA4,
        0xA5,
        0xA6,
        0xA7};

    write_command_2_display(lines[line]);
}

void print_from_keypad(int key)
{
  
    if (key < 1 || key > 12)
        return;
    plot(60,0,key+'0');
}

void clear_screen(){
    for (int i = 0; i<16*30*4; i++){
        print_char_increment_ADP(' ');
    }
}