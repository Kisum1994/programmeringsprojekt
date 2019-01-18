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

/*  // burg af globale variable: indsæt getTime(); istedet for for time variable i main,
     getTime();
     getTime_();
     getS();
     getS_();
     getM();
     getH();

    */


int main(void) {
    uart_init( 9600 ); //initialize USB serial emulation at 9600 baud

    // ryder op på skærmen
    clrscr();
    gotoxy(0,0);

    //init ur
    initTimer();
    TIM2->CR1 = 0x0001; //  <-- start timer 2
    TIM2_IRQHandler();

    // init structs, deres værdier bliver skrevet i initObjects(); - denne findes i objects.c

    struct box gameBox;
    struct velocityvector shot;
    struct velocityvector ship;
    struct velocityvector seagull;
    struct velocityvector asteroidS;
    struct velocityvector asteroidL;
    initObjects(&ship,&shot,&gameBox,&seagull,&asteroidS,&asteroidL);

    printf("\e[?25l"); // gør cursor usynlig


    printf("Pre-alpha stage: Everything you see is subject to change.\n");
    //splashScreen();


    drawBox(&gameBox);

    drawShip(&ship);

    uart_clear();

    //

while (1) {
      // styring af skib
    char str[4]={""}; // denne SKAL deklares i main
    shipControls(str, &ship, &shot,&gameBox);

     // shotHandler(); -> ??

    if (shot.alive>0) {
        moveBall(&shot);
        // indførelse af bounce limit
        if (detectBarrier(&gameBox,&shot)==1) {
                shot.alive--;
                if (shot.alive==0){
                        death(&shot);
                }
        }
        detectCollsionShip(&shot,&ship);
        detectCollisionSeagull(&shot,&seagull);
    }
    detectCollsionShip(&seagull,&ship);
   if (getTime()==50) {
    moveSeagull(&shot,&seagull,&gameBox);
    }








    // skibets hastighed sættes til nul igen skal gøres efter detectCollisions, ellers er der ingen pointe med collisions.
    ship.vx = 0;
    ship.vy = 0;
    if (ship.alive==0){
        break;
    }

 } // enden af programmets whileloop


gotoxy(25,25);
printf("U DEAD HA HA HA!");



  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
