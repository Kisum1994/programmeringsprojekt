
#include "stm32f30x_conf.h" // STM32 config

#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"

#define ESC 0x1B

    int time;
    int time_;
    int s;
    int s_;
    int m;
    int h;

 // OBJEKTER:
int getTime() {return time;}
int getTime_() {return time_;}
int getS() {return s;}
int getS_() {return s_;}
int getM() {return m;}
int getH() {return h;}


void initObjects(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox) {  // kan man dette med funktion?
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=15;
        ship->y=25;
        ship->ang=0;

    // SHOT
        shot->x=0;
        shot->vx=0;
        shot->y=0;
        shot->vy=0;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=30;
        gameBox->y1=5;
        gameBox->y2=80;
        gameBox->title[6]="title"; // omkriv længde inden i [], til "længde af titel"+1
        gameBox->style=1;

    // MÅGER skal indsættes!



}


    //ANIMATION AF OBJEKTER:


void updateVelocityVector(struct  velocityvector * velovector){
velovector->x = velovector->x+velovector->vx;
velovector->y = velovector->y+velovector->vy;
};

void makeball(int32_t x, int32_t y){
gotoxy(x,y);
printf("o");
}

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


    //INTERAKTION MELLEM OBJEKTER:


//checkker om der skabes en collision i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
int detectBarrier( struct box * gameBox, struct velocityvector * velovector){ //OMSKRIV SÅ DEN TAGER gameBox STRUCT!
    if(velovector->x+velovector->vx<=gameBox->x1 ){
           velovector->vx=velovector->vx*(-1);
            return 1;
    }
    if (velovector->x+velovector->vx>=gameBox->x1+gameBox->x2 ){
            velovector->vx=velovector->vx*(-1);
            return 1;
    }


    if (velovector->y+velovector->vy<=gameBox->y1 ){
            velovector->vy=velovector->vy*(-1);
            return 1;
    }
    if (velovector->y+velovector->vy>=gameBox->y1+gameBox->y2 ){
            velovector->vy=velovector->vy*(-1);
            return 1;
    }
    else return 0;
}

void shoot(struct velocityvector * shot,struct velocityvector * ship) {

    if(ship->ang==0){
                shot->x=ship->x-2;
                shot->y=ship->y;
                shot->vx=-1;
                shot->vy=0;
    }
    else if(ship->ang==1){
                shot->x=ship->x-2;
                shot->y=ship->y-2;
                shot->vx=-1;
                shot->vy=-1;
    }
    else if(ship->ang==2){
                shot->x=ship->x;
                shot->y=ship->y-2;
                shot->vx=0;
                shot->vy=-1;
    }
    else if(ship->ang==3){
                shot->x=ship->x+2;
                shot->y=ship->y-2;
                shot->vx=1;
                shot->vy=-1;
    }
    else if(ship->ang==4){
                shot->x=ship->x-2;
                shot->y=ship->y;
                shot->vx=-1;
                shot->vy=0;
    }
    else if(ship->ang==5){
                shot->x=ship->x+2;
                shot->y=ship->y+2;
                shot->vx=1;
                shot->vy=1;
    }
    else if(ship->ang==6){
                shot->x=ship->x+2;
                shot->y=ship->y;
                shot->vx=0;
                shot->vy=1;
    }
    else if(ship->ang==7){
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



    //GRAFIK AF OBJEKTER:


void drawShip(struct velocityvector * ship) {
         // lav muligvis enkelte funktioner for hver rotation af skibet
        int xc=ship->x-1;
        int yc=ship->y-1;
        gotoxy(xc,yc);
    if (ship->ang==0) {
        printf("%c%c%c",' ',94,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",47,79,92);
        gotoxy(xc+2,yc);
        printf("%c%c%c",88,88,88);
    }
    if (ship->ang==1) {
        printf("%c%c%c",218,196,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",179,79,43);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',43,43);
    }
    if (ship->ang==2) {
        printf("%c%c%c",' ',47,88);
        gotoxy(xc+1,yc);
        printf("%c%c%c",60,79,88);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',92,88);
    }
    if (ship->ang==3) {
        printf("%c%c%c",' ',43,43);
        gotoxy(xc+1,yc);
        printf("%c%c%c",179,79,43);
        gotoxy(xc+2,yc);
        printf("%c%c%c",192,196,' ');
    }
    if (ship->ang==4) {
        printf("%c%c%c",88,88,88);
        gotoxy(xc+1,yc);
        printf("%c%c%c",92,79,47);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',118,' ');
    }
    if (ship->ang==5) {
        printf("%c%c%c",43,43,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",43,79,179);
        gotoxy(xc+2,yc);
        printf("%c%c%c",' ',196,217);
    }
    if (ship->ang==6) {
        printf("%c%c%c",88,92,' ');
        gotoxy(xc+1,yc);
        printf("%c%c%c",88,79,62);
        gotoxy(xc+2,yc);
        printf("%c%c%c",88,47,' ');
    }
    if (ship->ang==7) {
        printf("%c%c%c",' ',196,191);
        gotoxy(xc+1,yc);
        printf("%c%c%c",43,79,179);
        gotoxy(xc+2,yc);
        printf("%c%c%c",43,43,' ');
    }
}
