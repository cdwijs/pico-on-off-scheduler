#ifndef PICO_ON_OFF_SCHEDULER_H
#define PICO_ON_OFF_SCHEDULER_H

/** \page main
    Cable Tester \n
    \dot
digraph
{
    node [shape=record, color=red];
    edge [arrowhead=open,color=green];

    rankdir="TD"
    ST_MAIN_INIT -> ST_MAIN_ON [ label = "" ];
    ST_MAIN_OFF -> ST_MAIN_ON [ label = "button" ];
    ST_MAIN_ON -> ST_MAIN_OFF  [ label = "5 minutes no change" ];
}
    \enddot
*/


typedef enum
{
    ST_MAIN_INIT = 0,
    ST_MAIN_ON,
    ST_MAIN_OFF,
}TMAINSTATE;

int picomain(void);
void mainLoop(void);

typedef struct
{
    TMAINSTATE           state;
}TMAIN;


#endif

