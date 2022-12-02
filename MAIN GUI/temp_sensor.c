#include "startup_files/at91sam3x8.h"
#include "startup_files/system_sam3x.h"
#include "LCD.h"
#include "commands_data_lcd.h"
#include "lcd_commands.h"


void delay(int value);
void enable_NVIC_TC();
void delay();
void reset_puls();
int read_TC_SR();
int calc_temp(int a, int b);
void start_puls(int d);
void delay(int);
char * int_to_char_array(int number);
void print_to_display(int temp);
// pin2 : B 25
#define PIN2 25

extern int Global_Rising_Edge_Temp = 0;
extern int Global_Temp = 0;

void init_temp_sensor()
{
    // enable PMC

    *AT91C_PMC_PCER = (1 << 27); // TC0
    *AT91C_PMC_PCER = (1 << 12); // PortB

    // Select Timer_Clock1 as TCCLK
    *AT91C_TC0_CMR &= ~(3 << 0);

    // enable clock and reset
    *AT91C_TC0_CCR |= 0b101; // 5 = 0b101

    // load counter to A (falling):
    *AT91C_TC0_CMR |= (2 << 16);

    // load counter to B (rising):
    *AT91C_TC0_CMR |= (1 << 18);

    *AT91C_PIOB_PER = (1 << PIN2);   // pin2
    *AT91C_PIOB_PPUDR = (1 << PIN2); // pin2

    reset_puls();
    enable_NVIC_TC();


    // run_command_op2(SET_ADDRESS_POINTER, 0,0); 
    // print_word("Celsius: ", 9);
   
    
    

}

void start_mesurement()
{
    start_puls(25);
    *AT91C_TC0_CCR |= (1 << 2); // sw reset

    read_TC_SR(); // reading status reg to clear old interrupt

    *AT91C_TC0_IER |= (1 << 6); // enable interrupt for LDRBS
}

void TC0_Handler()
{

    if ((*AT91C_TC0_SR & (1 << 6)) != (1 << 6))
        return;

    // disable interrupt LDRBS
    *AT91C_TC0_IDR |= (1 << 6);
    Global_Rising_Edge_Temp = 1;
}

void run_temp_sensor(int *c)
{

    if (*c < 500)
    {

        if (Global_Rising_Edge_Temp)
        {
            Global_Temp = calc_temp(*AT91C_TC0_RA, *AT91C_TC0_RB);
            print_to_display(Global_Temp);
            Global_Rising_Edge_Temp = 0;
//            start_mesurement();
            
        }
    } else {
        *c = 0;
        reset_puls();
        start_mesurement();

    }

}

int calc_temp(int a, int b)
{

    int temp = ((b - a) / (42*5))   - 273.15;
    return temp;
}
void reset_puls()
{

    *AT91C_PIOB_OER = (1 << PIN2);
    *AT91C_PIOB_SODR = (1 << PIN2);
    *AT91C_PIOB_CODR = (1 << PIN2);
    delay(SystemCoreClock * (3 / 200)); // to achive 15 ms
    *AT91C_PIOB_SODR = (1 << PIN2);
    *AT91C_PIOB_ODR = (1 << PIN2);
}
void start_puls(int d)
{

    *AT91C_PIOB_OER = (1 << PIN2);
    *AT91C_PIOB_SODR = (1 << PIN2);
    *AT91C_PIOB_CODR = (1 << PIN2);
    delay(d);
    *AT91C_PIOB_ODR = (1 << PIN2);
}

void enable_NVIC_TC()
{
    NVIC_ClearPendingIRQ(TC0_IRQn);
    NVIC_SetPriority(TC0_IRQn, 1);
    NVIC_EnableIRQ(TC0_IRQn);
}


int read_TC_SR()
{
    return *AT91C_TC0_SR;
}


void print_to_display(int temp){
    
    // plot(11, 0, temp%10 + 0x30);
    // plot(10, 0, temp/10 + 0x30);

}

