#include "LCD.h"

#include "commands_data_lcd.h"



void run_command_op2(unsigned char command, unsigned char op_low, unsigned op_hi);
void print_char(unsigned char c);


/// <summary>
/// Plots a charecter to the display in (x, y) position, this function only works for the display 0 with origo (0,0)
/// </summary>
/// <param name="x">the col</param>
/// <param name="y">the row</param>
/// <param name="c">the char to printed</param>
void plot(int x, int y, char c){
    // x*8: every char = 8 bit.
    unsigned short position = x + 30 * y;
    run_command_op2(SET_ADDRESS_POINTER, position & 0xff, (position & 0xff00) >> 8); // Set Address pointer
    print_char(c);
    
}


/// <summary>
/// run command to the lcd display with 2 bytes of data
/// </summary>
/// <param name="command">the command is 1 byte (from the datasheet for the display)</param>
/// <param name="op_low">the lower 1 byte of the data</param>
/// <param name="op_hi">the upper 1 byte of the data</param>
void run_command_op2(unsigned char command, unsigned char op_low, unsigned op_hi)
{
    write_data_2_display(op_low);
    write_data_2_display(op_hi);
    write_command_2_display(command);
};

/// <summary>
/// run command to the lcd display with 1 byte of data
/// </summary>
/// <param name="command">the command is 1 byte (from the datasheet for the display)</param>
/// <param name="op_low">the 1 byte of the data</param>
void run_command_op1(unsigned char command, unsigned char op_low)
{
    write_data_2_display(op_low);
    write_command_2_display(command);
};

/// <summary>
/// prints a char on display then increment the address pointer. You need to set the address pointer in specific position before. 
/// </summary>
/// <param name="c">the char to be printed</param>
void print_char_increment_ADP(unsigned char c)
{
    // in the ascci table:  characters starts from 0x20 end in 0x7e
    // but the table for the LCD start from 0x00, 
    // thats why c - 0x20 
    run_command_op1(DATA_WRITE_AND_INCREMENT_ADP, c - 0x20);
}

/// <summary>
/// prints a char on display without incrementing the address pointer. You need to set the address pointer in specific position before. 
/// </summary>
/// <param name="c"> the char to be printed</param>
void print_char(unsigned char c)
{
    // in the ascci table:  characters starts from 0x20 end in 0x7e
    // but table for the LCD start from 0x00, 
    // thats why c - 0x20   
    run_command_op1(DATA_WRITE_AND_NON_VARIABLE_ADP, c - 0x20);
}


/// <summary>
///    Prints an array of characters (string), the user must give the length of that array. You need to set the address pointer before using the function.
/// </summary>
/// <param name="word">an array of characters</param>
/// <param name="length">the length of the array</param>
void print_word(unsigned char * word, int length)
{
    for (int i = 0; i < length; i++)
        print_char_increment_ADP(word[i]);
}

/// <summary>
/// Changes the shape of the cursor pointer, 1 for small cursor, 7 for big cursor 
/// </summary>
/// <param name="line"></param>
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


/// <summary>
/// Do not use bad!! 
/// </summary>
/// <param name="key"></param>
void print_from_keypad(int key)
{
  
    if (key < 1 || key > 12)
        return;
    plot(60,0,key+'0');
}


/// <summary>
/// removes all charachters from the whole display
/// </summary>
void clear_screen(){
    for (int i = 0; i<16*30*4; i++){
        print_char_increment_ADP(' ');
    }
}