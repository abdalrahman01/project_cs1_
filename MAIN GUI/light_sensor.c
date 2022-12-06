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
double convert_adc_data_to_voltage(unsigned int ui_offset);

void delay(int);
void print_to_display_light_sensor(double n, char l);

/// <summary>
/// Initializes 2 light sensors.
/// </summary>
void init_light_sensors()
{

    // enable PMC

    *AT91C_PMC_PCER = (1 << 11); // port A;
    *AT91C_PMC_PCER1 = (1 << 5); // PID37;

    // enable digital pins as input
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

}

/// <summary>
///  set the sesnors to start measuring.
/// </summary>
void start_masurment()
{
    // sets the start bit in the control register for the ADC
    *AT91C_ADCC_CR = (1 << 1);

    // read the status register to clear pending interrupts 
    *AT91C_ADCC_SR;

    // enabling the interrupt for EOC 1 & 2.
    *AT91C_ADCC_IER = (0b11 << 1);
}


/// <summary>
/// set the NVIC options.
/// </summary>
void enable_NVIC_light_sensor()
{

    NVIC_ClearPendingIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 1);
    NVIC_EnableIRQ(ADC_IRQn);
}


/// <summary>
/// to read the the sensor data periodically, shuold be used in a loop. The param c is a counter in ms. every 500 ms; read values.
/// </summary>
/// <param name="c"></param>
void read_values_light_sensors(unsigned int *c)
{
 
    if (*c > 500)
    {
        start_masurment();
        if (is_EOC1_ready)
        {
            EOC1 = convert_adc_data_to_voltage(*AT91C_ADCC_CDR1);
            // print_to_display_light_sensor(EOC1, 30);

            is_EOC1_ready = 0;
        }

        if (is_EOC2_ready)
        {
            EOC2 = convert_adc_data_to_voltage(*AT91C_ADCC_CDR2);
            // print_to_display_light_sensor(EOC2, 60);

            is_EOC2_ready = 0;
        }
    
        *c =0;
    }
}

/// <summary>
/// The handler is called by the interrupt when a conversion is ready
/// </summary>
void ADC_Handler()
{


    // we have 2 channles to read.
    int sr = *AT91C_ADCC_SR;

    // this one for EOC1
    if ((sr & (1 << 1)) == (1 << 1))
    {
        is_EOC1_ready = 1;
        *AT91C_ADCC_IDR = (1 << 1);
    }

    // this one for EOC2
    if ((sr & (1 << 2)) == (1 << 2))
    {
        is_EOC2_ready = 1;
        *AT91C_ADCC_IDR = (1 << 2);
    }
}


/// <summary>
/// print a double value to screen. Notice: it only prints the least digit of (heltal), param l specifies how many total digits to be printed plus the ','. 
/// </summary>
/// <param name="n">the double value to be printed</param>
/// <param name="l">total digits to be printed plus the ','</param>
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


/// <summary>
/// Converts 12 bit value to represent the voltage source
/// </summary>
/// <param name="ui_offset">the 12 bit value</param>
/// <returns>a double ranging from 0-3.3</returns>
double convert_adc_data_to_voltage(unsigned int ui_offset)
{
    return ((ui_offset  * 3.3 / 0xfff));
}
