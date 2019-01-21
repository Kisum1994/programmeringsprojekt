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
    uart_init( 96000 ); //initialize USB serial emulation at 9600 baud

    // ryder op på skærmen
    clrscr();
    gotoxy(0,0);

    //init ur
    initTimer();
    TIM15->CR1 = 0x0001; //  <-- start timer 2
    TIM1_BRK_TIM15_IRQHandler();

    // init structs, deres værdier bliver skrevet i initObjects(); - denne findes i objects.c

    struct box gameBox;
    struct velocityvector shot;
    struct velocityvector ship;
    struct velocityvector seagull0;
    struct velocityvector seagull1;
    struct velocityvector seagull2;
    struct velocityvector seagull3;
    struct velocityvector asteroidS;
    struct velocityvector asteroidL;
    initObjects(&ship,&shot,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);


    printf("\e[?25l"); // gør cursor usynlig


    printf("Pre-alpha stage: Everything you see is subject to change.\n");
    //splashScreen();


    drawBox(&gameBox);
    moveAsteroid(&asteroidS);
    moveAsteroid(&asteroidL);

    drawShip(&ship);

    uart_clear();

    //

while (1) {
    char str[4]={""};  // denne SKAL deklares i main
   if(keyboardInput(str)>0) {

    shipControls(str, &ship, &shot, &gameBox);// styring af skib


    bossKey(str,&ship,&shot,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
   }

    if (moveShot(&shot,&gameBox,3)==1) {
        // herinde er ting der skal ske samtidig med skudets bevægelse.
        detectAsteroid(&shot, &asteroidL);
    }
    if (shot.alive>0) {

        //Gravity(&shot,&asteroidL);
    }


    //detectCollsionShip(&shot,&ship);
    detectCollisionSeagull(&shot,&seagull0);




    detectCollsionShip(&asteroidL,&ship);
    //detectCollsionShip(&seagull0,&ship);

    if(updateSeagull1(1)==15){
        moveSeagull(&shot,&seagull0 ,&gameBox);
    }
    detectAsteroid(&seagull0, &asteroidL);
    detectAsteroid(&seagull0,&asteroidS);



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
