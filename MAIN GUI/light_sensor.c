#include "startup_files/at91sam3x8.h"
#include "startup_files/system_sam3x.h"
#include "LCD.h"
#include "commands_data_lcd.h"
#include "lcd_commands.h"

int is_EOC1_ready = 0;
int is_EOC2_ready = 0;
extern double EOC1;
extern double EOC2;

void read_values_light_sensors();
void enable_NVIC_light_sensor();
double C12bits_to16bits_conversion(unsigned int ui_offset);

void delay(int);
void print_to_display_light_sensor(double n, char l);
void init_light_sensors()
{

    // enable PMC

    *AT91C_PMC_PCER = (1 << 11); // port A;
    *AT91C_PMC_PCER1 = (1 << 5); // PID37;

    *AT91C_PIOA_PER = (0b11 << 3);
    *AT91C_PIOA_PPUDR = (0b11 << 3);
    *AT91C_PIOA_ODR = (0b11 << 3);

    // set prescaler to 2 in ADC_MR:
    *AT91C_ADCC_MR |= (2 << 8); //

    // select channels for AD1 AD2
    *AT91C_ADCC_CHER = (0b11 << 1);

    // start ADC
    *AT91C_ADCC_CR = (1 << 1);

    // read status register to clear old interrupts

    enable_NVIC_light_sensor();
    run_command_op2(SET_ADDRESS_POINTER, 30, 0);
   
    // print_word("Light Sensors: ", 15);
}

void start_masurment()
{
    *AT91C_ADCC_CR = (1 << 1);

    *AT91C_ADCC_SR;

    *AT91C_ADCC_IER = (0b11 << 1);
}

void enable_NVIC_light_sensor()
{

    NVIC_ClearPendingIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 1);
    NVIC_EnableIRQ(ADC_IRQn);
}

void read_values_light_sensors(unsigned int *c)
{
 
    if (*c > 500)
    {
        start_masurment();
        if (is_EOC1_ready)
        {
            EOC1 = C12bits_to16bits_conversion(*AT91C_ADCC_CDR1);
            // print_to_display_light_sensor(EOC1, 30);

            is_EOC1_ready = 0;
        }

        if (is_EOC2_ready)
        {
            EOC2 = C12bits_to16bits_conversion(*AT91C_ADCC_CDR2);
            // print_to_display_light_sensor(EOC2, 60);

            is_EOC2_ready = 0;
        }
    
        *c =0;
    }
}

void ADC_Handler()
{

    int sr = *AT91C_ADCC_SR;

    if ((sr & (1 << 1)) == (1 << 1))
    {
        is_EOC1_ready = 1;
        *AT91C_ADCC_IDR = (1 << 1);
    }
    if ((sr & (1 << 2)) == (1 << 2))
    {
        is_EOC2_ready = 1;
        *AT91C_ADCC_IDR = (1 << 2);
    }
}

void print_to_display_light_sensor(double n, char l)
{
    int m = n; 
    char num[6]; 
    
    num[0] = m % 10 + '0'; 

    num[1] = '.';
    n*=10;
    m = n;
    num[2] = m %10 + '0'; 
    n*=10;
    m = n;
    num[3] = m %10 + '0'; 
    n*=10;
    m = n;
    num[4] = m %10 + '0'; 
    n*=10;
    m = n;
    num[5] = m %10 + '0'; 
     
    run_command_op2(SET_ADDRESS_POINTER, 30 + 9 + 1 + l, 0);
    print_word(num, 6);
}

double C12bits_to16bits_conversion(unsigned int ui_offset)
{
    return ((ui_offset  * 3.3 / 0xfff));
}
