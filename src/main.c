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
    struct velocityvector shot0;
    struct velocityvector shot1;
    struct velocityvector shot2;
    struct velocityvector shot3;
    struct velocityvector ship;
    struct velocityvector seagull0;
    struct velocityvector seagull1;
    struct velocityvector seagull2;
    struct velocityvector seagull3;
    struct velocityvector asteroidS;
    struct velocityvector asteroidL;
    struct velocityvector powerUp0;
    struct velocityvector powerUp1;
    struct velocityvector powerUp2;
    initObjects(&ship,
                &shot0,&shot1,&shot2,&shot3,
                &gameBox,
                &seagull0,&seagull1,&seagull2,&seagull3,
                &asteroidS,&asteroidL,
                &powerUp0,&powerUp1,&powerUp2);


    int rgb[3];
    rgb[0]=1;
    rgb[1]=0;
    rgb[2]=0;

    initLED(rgb);

    printf("\e[?25l"); // gør cursor usynlig


    printf("BETA stage: Everything you see is subject to change.\n");
    //splashScreen();


    drawBox(&gameBox);
    moveAsteroid(&asteroidS);
    moveAsteroid(&asteroidL);

    drawShip(&ship);

    drawPowerUp(&powerUp0);

    uart_clear();

    //

while (1) {
    char str[4]={""};  // denne SKAL deklares i main
    if(keyboardInput(str)>0) {
        shipControls(str, &ship, &shot0, &shot1, &shot2,&gameBox,&powerUp0,&powerUp1,powerUp2,&asteroidL);// styring af skib
        bossKey(str,&ship,&shot0,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
    }


    if(updateShot0(3)==1){
        if (moveShot(&shot0,&gameBox)==1) { // move tjekker om skud er i live!
            // herinde er ting der skal ske samtidig med skudets bevægelse.

            Gravity(&shot0,&asteroidL);
            Gravity(&shot0,&asteroidS);
        }
    }
    if(updateShot1(3)==1){
        if (moveShot(&shot1,&gameBox)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.

            Gravity(&shot1,&asteroidL);
            Gravity(&shot1,&asteroidS);
        }
    }
    if(updateShot2(3)==1){
        if (moveShot(&shot2,&gameBox)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.

            Gravity(&shot2,&asteroidL);
            Gravity(&shot2,&asteroidS);
        }
    }


    //håndtere bounce på asteroide
    detectAsteroid(&shot0, &asteroidL);
    detectAsteroid(&shot0, &asteroidS);

    detectAsteroid(&shot1, &asteroidL);
    detectAsteroid(&shot1, &asteroidS);

    detectAsteroid(&shot2, &asteroidL);
    detectAsteroid(&shot2, &asteroidS);


    //man kan skyde sig selv #selvmord
    detectCollsionShip(&shot0,&ship);
    detectCollsionShip(&shot1,&ship);
    detectCollsionShip(&shot2,&ship);

    //man kan skyde måger
    detectCollisionSeagull(&shot0,&seagull0);
    detectCollisionSeagull(&shot0,&seagull1);
    detectCollisionSeagull(&shot0,&seagull2);
    detectCollisionSeagull(&shot0,&seagull3);

    detectCollisionSeagull(&shot1,&seagull0);
    detectCollisionSeagull(&shot1,&seagull1);
    detectCollisionSeagull(&shot1,&seagull2);
    detectCollisionSeagull(&shot1,&seagull3);

    detectCollisionSeagull(&shot1,&seagull0);
    detectCollisionSeagull(&shot1,&seagull1);
    detectCollisionSeagull(&shot1,&seagull2);
    detectCollisionSeagull(&shot1,&seagull3);



    //man kan flyve ind i asteroider! avs!
    detectCollsionShip(&asteroidS,&ship);
    detectCollsionShip(&asteroidL,&ship);


    //måger kan æde en
    detectCollsionShip(&seagull0,&ship);
    detectCollsionShip(&seagull1,&ship);
    detectCollsionShip(&seagull2,&ship);
    detectCollsionShip(&seagull3,&ship);

    //måger kan bevæge sig
    if(updateSeagull1(1)==1){
       moveSeagull(&shot0,&seagull0 ,&gameBox);
    }
    // MANGLER FLERE MÅGER



    //måger kan bounce på asteroider
    detectAsteroid(&seagull0, &asteroidL);
    detectAsteroid(&seagull0, &asteroidS);



    // skibets hastighed sættes til nul igen skal gøres efter detectCollisions, ellers er der ingen pointe med collisions.
    ship.vx = 0;
    ship.vy = 0;
    if (ship.alive==0){
        break;
    }

 } // enden af programmets whileloop


gotoxy(ship.x-5,ship.y);
printf("U DEAD HA HA HA!");



  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
