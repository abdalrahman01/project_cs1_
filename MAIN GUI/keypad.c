

#include "startup_files/at91sam3x8.h"
#include "GPIO_config.h"
#include "lcd_keypad_buss.h"

int cols[3] = {7, 8, 9};
int rows[4] = {2, 3, 4, 5};

extern int Global_Key_Pressed = 0;

void initialize_pins()
{

    // PID 13 for port c
    // PID 14 for port d

    // enable clocks for PID 13 and 14
    PMC_enable(PIDPIOC);
    PMC_enable(PIDPIOD);

    keypad_cols_config();
    keypad_rows_config();
    PIOD_button_config(BUTTON);
    PIOD_led_config(LED);
    chip74_activate();
}

int pressed_key()
{
    int value = 0;

    PIOD_CODR(ACTIVATE_CHIP74_keypad);

    cols_as_output(cols);

    set_cols(cols);
    int a = 1;
    for (int i = 0; i < 3; i++)
    {

        PIOC_CODR(cols[i]);

        for (int j = 0; j < 4; j++)
        {
            a = read_row(rows[j]);

            if (a == 0)
            {
                value = j * 3 + i + 1;
                PIOC_SODR(cols[i]);
                cols_as_input(cols);
                return value;
            }
        }

        PIOC_SODR(cols[i]);
    }
    cols_as_input(cols);

    return value;
}

void update_key()
{
    Global_Key_Pressed = pressed_key();
    ;
}

int button_released()
{

    int value = pressed_key();

    while (value == 0)
    {
        value = pressed_key();
    }


    while (pressed_key() != 0)
    {
    }

    return value;
}
