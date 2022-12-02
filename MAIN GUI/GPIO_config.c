
#include "startup_files/system_sam3x.h"
#include "startup_files/at91sam3x8.h"


void PMC_enable(int PID)
{
    *AT91C_PMC_PCER = (1 << PID);
}

void PIOC_PER(int pin)
{
    *AT91C_PIOC_PER = (1 << pin);
}
void PIOD_PER(int pin)
{
    *AT91C_PIOD_PER = (1 << pin);
}
void PIOC_PUDR(int pin)
{
    *AT91C_PIOC_PPUDR = (1 << pin);
}

void PIOD_PUDR(int pin)
{
    *AT91C_PIOD_PPUDR = (1 << pin);
}
void PIOD_ODR(int pin){
     *AT91C_PIOD_ODR = (1 << pin);
}
void PIOD_OER(int pin){
     *AT91C_PIOD_OER = (1 << pin);
}
void PIOC_PUER(int pin){
    *AT91C_PIOC_PPUER = (1 << pin);
}
void PIOD_PUER(int pin){
    *AT91C_PIOD_PPUER = (1 << pin);
}

void PIOC_ODR(int pin){
     *AT91C_PIOC_ODR = (1 << pin);
}

void PIOC_OER(int pin){
    *AT91C_PIOC_OER = (1 << pin);
}

void PIOD_CODR(int pin){
    *AT91C_PIOD_CODR = (1 << pin);
}

void PIOC_CODR(int pin){
    *AT91C_PIOC_CODR = (1 << pin);
}
void PIOD_SODR(int pin){
    *AT91C_PIOD_SODR = (1 << pin);
}

void PIOC_SODR(int pin){
    *AT91C_PIOC_SODR = (1 << pin);
}
void PIOB_PER(int pin)
{
    *AT91C_PIOB_PER = (1 << pin);
}
void PIOB_PDR(int pin)
{
    *AT91C_PIOB_PDR = (1 << pin);
}

void PIOB_ODR(int pin)
{
    *AT91C_PIOB_ODR = (1 << pin);
}
void PIOB_PUDR(int pin)
{
    *AT91C_PIOB_PPUDR = (1 << pin);
}
void PIOB_PUER(int pin)
{
    *AT91C_PIOB_PPUER = (1 << pin);
}






void keypad_rows_config(){


    *AT91C_PIOC_PER = (0xf << 2);
    *AT91C_PIOC_PPUDR = (0xf << 2);
    *AT91C_PIOC_ODR = (0xf << 2);

}

void keypad_cols_config(){
  
 
    *AT91C_PIOC_PER = (0x3 << 7);
    *AT91C_PIOC_PPUDR = (0x3 << 7);
    *AT91C_PIOC_OER = (0x3 << 7);

}

void PIOD_button_config(int pin){
    PIOD_PER(pin);
    PIOD_PUDR(pin);
    PIOD_ODR(pin); 
}

void PIOD_led_config(int pin){
    PIOD_PER(pin);
    PIOD_PUDR(pin);
    PIOD_OER(pin); 
}

void chip74_activate(){
    int pin = 2; // pin 27 on Arduino
    PIOD_PER(pin);
    PIOD_PUER(pin);
    PIOD_OER(pin); 
}

void cols_as_input(int cols[]){
    
    for(int i  = 0; i < 3; i++){
        PIOC_ODR(cols[i]);
    } 
}
void cols_as_output(int cols[]){
    
    for(int i  = 0; i < 3; i++){
        PIOC_OER(cols[i]);
    } 
}

void set_cols(int cols[]){
    for(int i  = 0; i < 3; i++){
        PIOC_SODR(cols[i]);
    } 
}

int read_row(int row){
    return (*AT91C_PIOC_PDSR & (1 << row)) == (1 << row);
}

void flag_pins_LCD(){
    *AT91C_PIOC_PER = (0xff << 12);
    *AT91C_PIOC_PPUDR = (0xff << 12);
    *AT91C_PIOC_OER = (0xff << 12);
}
void rest_pins_not_enabled_with_keypad(int pin){
    PIOC_PER(pin);
    PIOC_PUDR(pin);
    PIOC_OER(pin);
}