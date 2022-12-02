#include "startup_files/at91sam3x8.h"
#include "startup_files/system_sam3x.h"

#define PIN62 17 // port B
int calc_new_position(int pos);
int previus_position = 0 ;
void delay(int d);
void init_serv()
{
    *AT91C_PMC_PCER1 = (1 << 4); // PWM
    *AT91C_PMC_PCER = (1 << 12);

    *AT91C_PIOB_PDR = (1 << PIN62);   // peripheral enabling
                                      //    *AT91C_PIOB_OER = (1 << PIN62); //
    *AT91C_PIOB_ABMR |= (1 << PIN62); // B peripheral  (r/w register) // it is not working
    *AT91C_PWMC_ENA = (1 << 1);       // ChID1
    *AT91C_PWMC_CH1_CMR |= (5 << 0);  // selecting prescaler MCK/32
    *AT91C_PWMC_CH1_CPRDR = 30000;    // p.991
    *AT91C_PWMC_CH1_CDTYR = 1500;
}

void update_position_servo(char key, int *counter)
{
    if (*counter < 100) 
        return;

    
    if (key == previus_position) 
        return;

    if (key == 0) // if keypad not pressed
        return; 


    if(key == 11)
        *AT91C_PWMC_CH1_CDTYUPDR = calc_new_position(0);
    else if (key>0 || key < 10){
        *AT91C_PWMC_CH1_CDTYUPDR = calc_new_position(key);
    }

    *counter = 0; 
}

int calc_new_position(int pos)
{
    // the time is in ms
    return (700/3) * (pos)  + 1300;
}

