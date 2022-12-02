
void make_databus_as_input();

unsigned char data_bus();

void initialize_pins_LCD();

void delay(int value);

unsigned char read_status_display(void);
void write_command_2_display(unsigned char command);

void make_databus_as_output();
void write_data_2_display(unsigned char data);

void init_display(void);
void print_hello();

void make_databus_as_input();
unsigned char data_bus();
void clear_databus();

void set_command_to_databus(unsigned char command);
void set_data_to_databus(unsigned char data);
void run_display();
void from_keypad_to_display();