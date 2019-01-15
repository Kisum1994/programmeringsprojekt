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

  /*  int time;
    int time_;
    int s;
    int s_;
    int m;
    int h;
    //skibs position og angle
    int centerx=15;
    int centery=25;
    int ang=0;
    /*
 /*
//Struct der håndterer alle typer opbjekter der skal bevæges
struct velocityvector{
    int32_t x;
    int32_t y;
    int32_t vx;
    int32_t vy;
    };
// regner ny hastighed og gemmer i struct
void updateVelocityVector(struct  velocityvector * velovector){
velovector->x=velovector->x+velovector->vx;
velovector->y=velovector->y+velovector->vy;
};
//skriver punkt til promt
void makeball(int32_t x, int32_t y){
gotoxy(x,y);
printf("o");
}
//skriver punkt i ny position og sletter gammelt punkt
void moveBall(struct velocityvector * velovector){
   int32_t xo;
   int32_t yo;
updateVelocityVector(velovector);
makeball(velovector->x,velovector->y);
xo=velovector->x-velovector->vx;
yo=velovector->y-velovector->vy;
gotoxy(xo,yo);
printf("%c",' ');
};
//checkker om der skabes en collision i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
int detectBarrier( int x1, int y1, int x2, int y2, struct velocityvector * velovector){
    if(velovector->x+velovector->vx<=x1 ){
           velovector->vx=velovector->vx*(-1);
            return 1;
    }
    if (velovector->x+velovector->vx>=x1+x2 ){
            velovector->vx=velovector->vx*(-1);
            return 1;
    }


    if (velovector->y+velovector->vy<=y1 ){
            velovector->vy=velovector->vy*(-1);
            return 1;
    }
    if (velovector->y+velovector->vy>=y1+y2 ){
            velovector->vy=velovector->vy*(-1);
            return 1;
    }
    else return 0;
}



void shoot(struct velocityvector * shot,struct velocityvector * ship) {



    if(ang==0){
                shot->x=ship->x-2;
                shot->y=ship->y;
                shot->vx=-1;
                shot->vy=0;
    }
    else if(ang==1){
                shot->x=ship->x-2;
                shot->y=ship->y-2;
                shot->vx=-1;
                shot->vy=-1;
    }
    else if(ang==2){
                shot->x=ship->x;
                shot->y=ship->y-2;
                shot->vx=0;
                shot->vy=-1;
    }
    else if(ang==3){
                shot->x=ship->x+2;
                shot->y=ship->y-2;
                shot->vx=1;
                shot->vy=-1;
    }
    else if(ang==4){
                shot->x=ship->x-2;
                shot->y=ship->y;
                shot->vx=-1;
                shot->vy=0;
    }
    else if(ang==5){
                shot->x=ship->x+2;
                shot->y=ship->y+2;
                shot->vx=1;
                shot->vy=1;
    }
    else if(ang==6){
                shot->x=ship->x+2;
                shot->y=ship->y;
                shot->vx=0;
                shot->vy=1;
    }
    else if(ang==7){
            shot->x=ship->x-2;
            shot->y=ship->y+2;
            shot->vx=-1;
            shot->vy=1;

    }
}

int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2){
    if(obj1->x+obj1->vx==obj2->x+obj2->vx && obj1->y+obj1->vy==obj2->y+obj2->vy){
        return 1;

    } else {
    return 0;
    }
}

int detectCollsionShip( struct velocityvector * obj1,struct velocityvector * ship) {

        if (detectCollision(obj1,ship)==1) {
                obj1->vx=0;
                obj1->vy=0;
                return 1;
        }
        else {
                return 0;
        }
}

void drawShip(int x, int y,int rot) {
         // lav muligvis enkelte funktioner for hver rotation af skibet
        int xc=x-1;
        int yc=y-1;
        gotoxy(xc,yc);
    if (rot==0) {
        printf("%c%c%c",' ',94,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",47,79,92);
        gotoxy(xc+2,yc);
        printf("%c%c%c",88,88,88);
    }
    if (rot==1) {
        printf("%c%c%c",218,196,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",179,79,43);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',43,43);
    }
    if (rot==2) {
        printf("%c%c%c",' ',47,88);
        gotoxy(xc+1,yc);
        printf("%c%c%c",60,79,88);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',92,88);
    }
    if (rot==3) {
        printf("%c%c%c",' ',43,43);
        gotoxy(xc+1,yc);
        printf("%c%c%c",179,79,43);
        gotoxy(xc+2,yc);
        printf("%c%c%c",192,196,' ');
    }
    if (rot==4) {
        printf("%c%c%c",88,88,88);
        gotoxy(xc+1,yc);
        printf("%c%c%c",92,79,47);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',118,' ');
    }
    if (rot==5) {
        printf("%c%c%c",43,43,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",43,79,179);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',196,217);
    }
    if (rot==6) {
        printf("%c%c%c",88,92,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",88,79,62);
        gotoxy(xc+2,yc);
        printf("%c%c%c",88,47,' ');
    }
    if (rot==7) {
        printf("%c%c%c",' ',196,191);
        gotoxy(xc+1,yc);
        printf("%c%c%c",43,79,179);
        gotoxy(xc+2,yc);
        printf("%c%c%c",43,43,' ');
    }
}

 */


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




    initJoystick();
    clrscr();
    gotoxy(1,0);
    initTimer();
    TIM2->CR1 = 0x0001; //  <-- start timer 2
    TIM2_IRQHandler();

    // Design rotation
    struct box gameBox;
    struct velocityvector shot;
    struct velocityvector ship;
    initObjects(&ship,&shot,&gameBox);


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

    window(&gameBox);

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

}






  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
