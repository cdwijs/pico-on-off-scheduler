/**
 * Copyright (c) 2024 Cdwijs
 *
 * SPDX-License-Identifier: GPL2+/LGPL2+
 */
#include "pico-on-off-scheduler.h"
#include <stdio.h> //for serial communication via USB
#include <pico/stdlib.h>
#include "utils.h"

TMAIN myMainData;
TMAIN* const myMain = &myMainData;

#ifdef RUNNING_SIMULATED_ON_PC
int picomain(void) //qt also defines a main() function
#else
int main()
#endif
{
    stdio_init_all(); //for serial communication via USB
    printf("Hello Timer!\n");
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) 
    {
        mainLoop();
        gpio_put(LED_PIN, 0);
        printf("Hello, world!\n");
        sleep_ms(400);
    }
}

void mainLoop(void) //to be able to test one cycle of the main program
{
    switch (myMain->state)
    {
        case ST_MAIN_INIT:
        {
            myMain->state = ST_MAIN_ON;
            break;
        }
        case ST_MAIN_ON:
        {
            //if (samplerCableChanged())
            if (TRUE)
            {
                //timerSet(TMR_ONOFF,TIME_5_MINUTE);
            }
            //if (timerElapsed(TMR_ONOFF))
            if (FALSE)
            {
                myMain->state = ST_MAIN_OFF;
            }
            //if (buttonIsPressed())
            if (TRUE)
            {

            }
            break;
        }
        case ST_MAIN_OFF:
        {
            //if (buttonIsPressed())
            if (TRUE)
            {
                myMain->state = ST_MAIN_ON;
            }
            break;
        }
    }
    //.samplerExecute();
}
