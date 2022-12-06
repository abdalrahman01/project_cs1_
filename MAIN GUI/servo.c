#include "startup_files/at91sam3x8.h"
#include "startup_files/system_sam3x.h"

#define PIN62 17 // port B
int calc_new_position(int pos);
int previus_position = 0;
void delay(int d);

/// <summary>
/// iniat the servo motor
/// </summary>
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

/// <summary>
/// change the position of the servo motor in degrees. 
/// the counter is to make a 100 ms delay
/// </summary>
/// <param name="key"> the values (0,1,2,3,4,5..,9) corresponds to (0, 10, 20, 30, .., 90) degree rotation</param>
/// <param name="counter"> a counter in ms, to make a delay</param>
void update_position_servo(char key, int *counter)
{
    if (*counter < 100)
        return;

    if (key == previus_position)
        return;

    if (key == 0) // if keypad not pressed
        return;

    if (key == 11)
        *AT91C_PWMC_CH1_CDTYUPDR = calc_new_position(0);
    else if (key > 0 || key < 10)
    {
        *AT91C_PWMC_CH1_CDTYUPDR = calc_new_position(key);
    }

    *counter = 0;
}

/// <summary>
/// calculates the value to be stored in duty update register (Channel Duty Cycle Update Register). 
/// </summary>
/// <param name="pos"> values from 0 to 18</param>
/// <returns>the waveform lenght (CDTYUPD) </returns>
int calc_new_position(int pos)
{
    // the time is in ms
    return (700 / 3) * (pos) + 1300;
}
