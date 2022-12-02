#ifndef _GUI_
void set_text_home_address(unsigned short address);
void set_curser_pointer(char col, char row);
void set_address_pointer(unsigned short address, char col, char row);
extern char MODE;
void key_listner(int key);
void init_gui();

#endif