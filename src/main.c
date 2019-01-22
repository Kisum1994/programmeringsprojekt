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
//#include "interface.c"

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
    initObjects(&ship,&shot0,&shot1,&shot2,&shot3,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL,&powerUp0,&powerUp1,&powerUp2);


    printf("\e[?25l"); // gør cursor usynlig


    printf("Pre-alpha stage: Everything you see is subject to change.\n");
    //splashScreen();
    int rgb[3];
    rgb[0]=1;
    rgb[1]=0;
    rgb[2]=0;
    initLED();
    setLED(rgb);

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

    shipControls(str, &ship, &shot0, &shot1, &gameBox, &powerUp0);// styring af skib


     bossKey(str,&ship,&shot0,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
   }

      if(updateShot0(3)==1){
        if (moveShot(&shot0,&gameBox,3)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.
            detectAsteroid(&shot0, &asteroidL);
        }}
      if(updateShot1(3)==1)
            if (moveShot(&shot1,&gameBox,3)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.
            detectAsteroid(&shot1, &asteroidL);
        }

    if (shot0.alive>0) {

        //Gravity(&shot0,&asteroidL);
    }
    if (shot1.alive>0) {

        //Gravity(&shot1,&asteroidL);
    }


    //detectCollsionShip(&shot,&ship);
    detectCollisionSeagull(&shot0,&seagull0);
    detectCollisionSeagull(&shot1,&seagull0);





    detectCollsionShip(&asteroidL,&ship);
    //detectCollsionShip(&seagull0,&ship);

    if(updateSeagull1(1)==15){
        moveSeagull(&shot0,&seagull0 ,&gameBox);
    }
    detectAsteroid(&seagull0, &asteroidL);
    detectAsteroid(&seagull0,&asteroidS);

    enablePowerUp(&ship,&powerUp0,rgb);

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
