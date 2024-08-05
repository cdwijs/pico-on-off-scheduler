/**
 * Copyright (c) 2024 Cdwijs
 *
 * SPDX-License-Identifier: GPL2+/LGPL2+
 */
#include "pico-on-off-scheduler.h"
#include <stdio.h> //for serial communication via USB
#include <pico/stdlib.h>
#include "utils.h"

const int hz = 1;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;

const uint RELAYS_PIN = 4;

TMAIN myMainData;
TMAIN* const myMain = &myMainData;


bool myLedOn = FALSE;
bool myLedState = FALSE;
bool myRelaysState = TRUE; 

int myRelaysOnTime = 0;
int myRelaysOffTime = 0;

repeating_timer_t timer;
bool timer_callback(repeating_timer_t *rt);

#ifdef RUNNING_SIMULATED_ON_PC
int picomain(void) //qt also defines a main() function
#else
int main()
#endif
{
     
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(RELAYS_PIN);
    gpio_set_dir(RELAYS_PIN, GPIO_OUT);
    stdio_init_all(); //for serial communication via USB
    
    printf("Hello Timer!\n");

    if (!add_repeating_timer_us(-1000000 / hz, timer_callback, NULL, &timer)) 
    {
        printf("Failed to add timer\n");
    }

    while (true) 
    {
        char c = getchar();
        printf("%c", c);
        switch (c) 
        {
            case 'c':
            {
                c = getchar();
                printf("%c\n", c);
                if (c < '0' || c > '7') 
                {
                    myLedOn = FALSE;
                    printf("Unknown input channel\n");
                } 
                else 
                {
                    myLedOn = TRUE;
                    printf("Switched to channel %c\n", c);
                }
                break;
            }
        }
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
}


bool timer_callback(repeating_timer_t *rt)
{
    printf("Callback\n");
    gpio_put(RELAYS_PIN, myRelaysState);
    if (myRelaysState)
    {
        printf("On, switching off in %d seconds\n",myRelaysOnTime);
        if (myRelaysOnTime)
        {
            myRelaysOnTime--;
        }
        else
        {
            myRelaysOffTime = 10; //todo: make configurable
            myRelaysState = FALSE;
        }
    }
    else
    {
        printf("Off, switching on in %d seconds\n",myRelaysOffTime);
        if (myRelaysOffTime)
        {
            myRelaysOffTime--;
        }
        else
        {
            myRelaysOnTime = (30*60 - 10); //todo: make configurable
            myRelaysState = TRUE;
        }
    }

    if (myLedOn)
    {
        gpio_put(LED_PIN, myLedState);
    }
    else
    {
        gpio_put(LED_PIN, 0);
    }
    myLedState = !myLedState;
}