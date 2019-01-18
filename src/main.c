

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
#include "interface.h"
#include "fpsqrt.h"


int main(void) {
     uart_init( 9600 ); //initialize USB serial emulation at 9600 baud

    /*  // burg af globale variable: indsæt getTime(); istedet for for time variable i main,
     getTime();
     getTime_();
     getS();
     getS_();
     getM();
     getH();
    */
    // startUP();
    printf("\e[?25l");
    lcd_init();
    int flag=0;
    clrscr();
    initTimer();
    TIM2->CR1 = 0x0001; //  <-- start timer 2
    TIM2_IRQHandler();

//--------------------------------------------------------------------------
    // Design rotation
    struct box gameBox;
    struct velocityvector shot;
    struct velocityvector ship;
    struct velocityvector seagull;
    struct velocityvector asteroidS;
    struct velocityvector asteroidL;
    initObjects(&ship,&shot,&gameBox,&seagull,&asteroidS,&asteroidL);


 /* while (1) {
    if (time%10==0) { //  når uret "tikker": så ...
            drawShip(x,y,ang);
            ang++;
            if (ang >=8) {
            ang=0;
            }
    }
} */



    printf("test");

    drawBox(&gameBox);

    drawShip(&ship);
    uart_clear();

while (1) {
        char str[4]={""};

        if (keyboardInput(str)>0) {

            if (arrowInput(str)==4) {
                ship.ang++;
                if (ship.ang >=8) {
                    ship.ang=0;
                }
                drawShip(&ship);
            }
            else if (arrowInput(str)==8){
                ship.ang--;

                if (ship.ang<0) {
                    ship.ang=7;
                }
                drawShip(&ship);
            }




             else if (arrowInput(str)==16){      // denne kan tændes hvis skibet skal kunne bevæge sig fremad i dens retning.

                if (ship.ang==7 || ship.ang==0 || ship.ang==1) {
                    ship.x--;
                    ship.vx=-1;
                }
                if (ship.ang==1 || ship.ang==2 || ship.ang==3) {
                    ship.y--;
                    ship.vy=-1;
                }
                if (ship.ang==3 || ship.ang==4 || ship.ang==5) {
                    ship.x++;
                    ship.vx=1;
                }
                if (ship.ang==5 || ship.ang==6 || ship.ang==7) {
                    ship.y++;
                    ship.vy=1;
                }
                drawShip(&ship);
            }


            if(arrowInput(str)==0x01){
                shoot(&shot,&ship);
            }
        }
    if (shot.x>0) {
        moveBall(&shot);
        detectBarrier(&gameBox,&shot);

        if (detectCollsionShip(&shot,&ship)==1) {

            gotoxy(ship.x-1,ship.y-1);
            printf("%*c",3,' ');
            gotoxy(ship.x,ship.y-1);
            printf("%*c",3,' ');
            gotoxy(ship.x+1,ship.y-1);
            printf("%*c",3,' ');

        }
    }
    ship.vx = 0;
    ship.vy = 0;

    moveAsteroid(&asteroidL);
    cleanAsteroid(&asteroidL);
    detectBarrier(&gameBox,&asteroidL);
    Gravity(&shot,&asteroidL);

    //if (getS()%1==0){
        //tegn flyvende rumhavmåge
        /*if (seagull.alive==1 && getTime()==100){
            moveSeagull(&shot, &seagull);
                if (seagull.ani==0){
                    seagull.ani=1;
                }
                else if (seagull.ani==1){
                    seagull.ani=0;
                }
        detectBarrier(&gameBox,&seagull);
        }*/
    //}

    //if(getTime()%120==1){
           // moveAsteroid(&asteroidS);
            //detectBarrier(&gameBox,&asteroidS);
    //}
    //if(getTime()%100==0){
            //moveAsteroid(&asteroidL);
            //detectBarrier(&gameBox,&asteroidL);
    //}
}

 //-------------------------------------------------------------------------------------------------------------------------------------------------------


    //  Her starter kode til 6.2
    char str[]="Ida er leakker";


    int8_t buffer[512];
    memset(buffer,0x00,512);

    lcd_write_string(buffer,str,0);

    lcd_push_buffer(buffer);

        //char str[21];
    //str[2]="2";
    //PCtimer();
    clrscr();
/* Tegn måge kode */
/*
    // første koordinat nedad og 2 koordinat til siden
    int k=0;
    int g=0;
    int position=4;
    // tegn rumhavmåger
    while (1){

        if (time%10==0){
        //tegn stor asteroide
            drawAsteroide(5,position+5,0);
            CleanAsteroide(5, 0, position+5, 1, 0);
        // tegn lille asteroide
            drawAsteroide(10,position+7,1);
            CleanAsteroide(10, 0, position+7, 1, 1);
        // tegn flyvende rumhavmåge
            if (g<2){
                drawSeagull(position,position,k);
                CleanSeagull(position,1,position,1,k);
                if (k==0){
                    k=1;
                    position++;
                }
                else if (k==1){
                    k=0;
                }
            }
        }
        if (time%60==0){
            g++;
                if (g==2){
                    deleteSeagull(position,1,position,1);
                }
        }
    }
*/
    // skriv den tomme ldc_update fil

    // først skal der laves en funktion lcd_write_string()
     while (1) {
        if (flag=1) {
            lcd_update(buffer,str);
            lcd_push_buffer(buffer);
            flag=0;
        }
    }

  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
