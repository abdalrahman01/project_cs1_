


void PMC_enable(int PID);


void PIOC_PER(int pin);
void PIOD_PER(int pin);
void PIOC_PUER(int pin);

void PIOC_PUDR(int pin);

void PIOD_PUDR(int pin);
void PIOD_ODR(int pin);
void PIOD_OER(int pin);
void PIOC_ODR(int pin);
void PIOC_OER(int pin);


void PIOD_CODR(int pin);
void PIOC_CODR(int pin);
void PIOD_SODR(int pin);
void PIOC_SODR(int pin);

void keypad_rows_config();
void keypad_cols_config();
void button_config();
void led_config();
void chip74_activate();

int read_row(int row);
void set_cols();
void cols_as_output();
void cols_as_input();
void PIOD_button_config(int pin);
void PIOD_led_config(int pin);

void flag_pins_LCD();
void rest_pins_not_enabled_with_keypad(int pin);

void PIOB_PER(int pin);
void PIOB_PDR(int pin);
void PIOB_ODR(int pin);
void PIOB_PUDR(int pin);
void PIOB_PUER(int pin);



#define BUTTON 1
#define LED 3

#define SERVO_PIN 17

#define PIDPWM 4 // register PMC_PCER1
#define PIDADC 5 // register PMC_PCER1


#define PIDTC0 27

#define PIDPIOA 11
#define PIDPIOB 12
#define PIDPIOC 13
#define PIDPIOD 14