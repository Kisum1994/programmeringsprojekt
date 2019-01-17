/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/


#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"
#include <string.h>







int main(void) {
    uart_init( 9600 );
    clrscr();
    gotoxy(0,0);
    initTimer();
    TIM2->CR1 = 0x0001; //  <-- start timer 2
    TIM2_IRQHandler();
    uart_clear();

    struct box gameBox;
    struct velocityvector shot;
    struct velocityvector ship;
    struct velocityvector seagull;
    struct velocityvector asteroidS;
    struct velocityvector asteroidL;
    initObjects(&ship,&shot,&gameBox,&seagull,&asteroidS,&asteroidL);

    drawBox(&gameBox);
    drawShip(&ship);
    drawSeagull(&seagull);





while (1) {
        char str[4]={""};
        shipControls(str,&ship,&shot);



    if (shot.alive>0) {
        moveBall(&shot);

        detectBarrier(&gameBox,&shot);
        detectCollsionShip(&shot,&ship);

    }
    if (seagull.alive==1) {
        moveSeagull(&shot, &seagull,&gameBox);
                if (seagull.ani==0){
                    seagull.ani=1;
                }
                else if (seagull.ani==1){
                    seagull.ani=0;
                }
    }






        }



  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
