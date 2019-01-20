
#include "stm32f30x_conf.h" // STM32 config

#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include <string.h>
#include "objects.h"



#define ESC 0x1B




void death(struct velocityvector * deadObject){

        int xc;
        int yc;
       // printer "blank" på dens position
        if (deadObject->width==3){ // hvis skib
            xc=deadObject->x-1;
            yc=deadObject->y-1;
            gotoxy(xc,yc);
            printf("%*c",3,' ');
            gotoxy(xc+1,yc);
            printf("%*c",3,' ');
            gotoxy(xc+2,yc);
            printf("%*c",3,' ');
            deadObject->vy=1;
        }

        if (deadObject->width==9) { // hvis måge
            xc=deadObject->x-1;
            yc=deadObject->y-4;
            gotoxy(xc,yc);
            printf("%*c",9,' ');
            gotoxy(xc+1,yc);
            printf("%*c",9,' ');
            gotoxy(xc+2,yc);
            printf("%*c",9,' ');
            deadObject->vy=30;
        }
        // reseter objectet til nul
        deadObject->vx=0;

        deadObject->x=0;
        deadObject->y=0;
        deadObject->ang=0;
        deadObject->alive=0;
}


void initObjects(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox, struct velocityvector *  seagull,struct velocityvector * asteroidS, struct velocityvector * asteroidL) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=15;
        ship->y=15;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=1;

    // SHOT
        shot->x=0;
        shot->vx=0;
        shot->y=0;
        shot->vy=0;
        shot->alive=0;
        shot->height=1;
        shot->width=1;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=40;
        gameBox->y1=5;
        gameBox->y2=50;
        strcpy(gameBox->title,"fghjkl"); // omkriv længde inden i [], til "længde af titel"+1
        gameBox->style=1;

    // MÅGER

        seagull->x=15;
        seagull->y=25;
        seagull->vy=1;
        seagull->vx=1;
        seagull->alive=1;
        seagull->width=9;
        seagull->height=3;
        seagull->ang=0; // ikke nødvendig !!!jo den er så!!!
        seagull->ani=0;

	// ASTEROIDR
    // Asteroid Stor

        asteroidS->vx=1;
        asteroidS->vy=1;
        asteroidS->x=3;
        asteroidS->y=3;
        asteroidS->width=5;
        asteroidS->height=3;
        asteroidS->alive=1;

    // Asteroid lille

        asteroidL->vx=1;
        asteroidL->vy=1;
        asteroidL->x=7;
        asteroidL->y=7;
        asteroidL->height=1;
        asteroidL->width=3;
        asteroidL->alive=1;

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
makeball(velovector->x,velovector->y);
updateVelocityVector(velovector);
xo=velovector->x-velovector->vx;
yo=velovector->y-velovector->vy;
gotoxy(xo,yo);
printf("%c",' ');
};

void shipControls(char * str,struct velocityvector * ship,struct velocityvector * shot) {

    int tegn=0; // ship.alive
     if (keyboardInput(str)>0) {

            if (arrowInput(str)==4) { // venstre rotation af skib
                ship->ang++;
                if (ship->ang >=8) {
                    ship->ang=0;
                }
                tegn=1;
            }
            else if (arrowInput(str)==8){ //højre rotation af skib
                ship->ang--;

                if (ship->ang<0) {
                    ship->ang=7;
                }
                tegn=1;
            }
             if(arrowInput(str)==0x01){
                shoot(shot,ship);
            }
            if (tegn==1) {
                drawShip(ship);
                tegn=0;
            }

            /*  // denne kan tændes hvis skibet skal kunne bevæge sig fremad i dens retning

             else if (arrowInput(str)==16){      .
                t=1;
                if (ship->ang==7 || ship->ang==0 || ship->ang==1) {
                    ship->x--;
                    ship->vx=-1;
                }
                if (ship->ang==1 || ship->ang==2 || ship->ang==3) {
                    ship->y--;
                    ship->vy=-1;
                }
                if (ship->ang==3 || ship->ang==4 || ship->ang==5) {
                    ship->x++;
                    ship->vx=1;
                }
                if (ship->ang==5 || ship->ang==6 || ship->ang==7) {
                    ship->y++;
                    ship->vy=1;
                }
            } */

        }


}

    //INTERAKTION MELLEM OBJEKTER:


//checkker om der skabes en collision i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
int detectBarrier( struct box * gameBox, struct velocityvector * velovector){ //OMSKRIV SÅ DEN TAGER gameBox STRUCT!
    if(velovector->x+velovector->vx-((velovector->height-1)/2)<=gameBox->x1 ){
           velovector->vx=velovector->vx*(-1);
            return 1;
    }
    else if (velovector->x+velovector->vx+((velovector->height-1)/2)>=gameBox->x2 ){
            velovector->vx=velovector->vx*(-1);
            return 1;
    }


    else if (velovector->y+velovector->vy-((velovector->width)/2)<=gameBox->y1 ){
            velovector->vy=velovector->vy*(-1);
            return 1;
    }
    else if (velovector->y+velovector->vy+((velovector->width)/2)>=gameBox->y2 ){
            velovector->vy=velovector->vy*(-1);
            return 1;
    }
    else return 0;
}

void shoot(struct velocityvector * shot,struct velocityvector * ship) {
    shot->alive=1;
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
                shot->x=ship->x+2;
                shot->y=ship->y;
                shot->vx=1;
                shot->vy=0;
    }
    else if(ship->ang==5){
                shot->x=ship->x+2;
                shot->y=ship->y+2;
                shot->vx=1;
                shot->vy=1;
    }
    else if(ship->ang==6){
                shot->x=ship->x;
                shot->y=ship->y+2;
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
    int i1=(obj1->x+obj1->vx-((obj1->height-1)/2));
    int j1=(obj1->y+obj1->vy-((obj1->width-1)/2));

    int i2=(obj1->x+obj1->vx+((obj1->height-1)/2));
    int j2=(obj1->y+obj1->vy+((obj1->width-1)/2));

    int k1=(obj2->x+obj2->vx-((obj2->height-1)/2));
    int l1=(obj2->y+obj2->vy-((obj2->width-1)/2));

    int k2=(obj2->x+obj2->vx+((obj2->height-1)/2));
    int l2=(obj2->y+obj2->vy+((obj2->width-1)/2));

    for(i1;i1<=i2;i1++){
            for(j1;j1<=j2;j1++){
                    if(k1 <= i1 && i1 <= k2 && l1<= j1 && j1 <= l2){return 1;}
                                                                else{return 0;}
            }
    }
}
int detectCollsionShip( struct velocityvector * obj1,struct velocityvector * ship) {

         if (detectCollision(obj1,ship)==1) {
                death(ship);
                death(obj1);

                return 1;
        }
        else {
            return 0;
        }
}
//ny ift master
int detectCollisionSeagull( struct velocityvector * shot ,struct velocityvector * seagull){
    if (detectCollision(shot,seagull)==1) {
        death(shot);
        death(seagull);

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

void drawSeagull(struct velocityvector * seagull){
    int x=seagull->x-1;
    int y=seagull->y-4;
    if (seagull->alive==1){
        if (seagull->ani==0){
            gotoxy(x,y);
            // måge position står
            printf("%c%c%c%c%c%c%c%c%c",' ',' ',47,92,' ',47,92,' ',' ');
            gotoxy(x+1,y);
            printf("%c%c%c%c%c%c%c%c%c",' ',35,' ',' ',153,' ',' ',35,' ');
            gotoxy(x+2,y);
            printf("%c%c%c%c%c%c%c%c%c",' ', 118,' ',' ',35,' ',' ',118,' ');
        }
        else if (seagull->ani==1){
            // måge position flyver
            gotoxy(x,y);
            printf("%c%c%c%c%c%c%c%c%c",' ',47,35,92,' ',47,35,92,' ');
            gotoxy(x+1,y);
            printf("%c%c%c%c%c%c%c%c%c",35,' ',' ',' ',153,' ',' ',' ',35);
            gotoxy(x+2,y);
            printf("%c%c%c%c%c%c%c%c%c", 118,' ',' ',' ',35,' ',' ',' ',118);
        }
    }
}

void cleanSeagull(struct velocityvector * seagull){
    int x;
    int y;
            if (seagull->vy>0){
                    //mågen bevæger sig i positiv y-putty retning (positiv x-retning)
                //skal være 1 større, da den har bevæget sig 1 plads i y.
                y=seagull->y-1;
            }
            else if (seagull->vy<0){
                //mågen bevæger sig i negativ x-retning (y_putty)
                y=seagull->y+1;
            }
            if (seagull->vx>0){
                //Afstanden fra massemidpunkt til start tegneposition - 1 ekstra i x, da den bevæger sig denne vej.
                x=seagull->x-2;
                y=seagull->y-3;
            }
            else if (seagull->vx<0){
                //Afstanden fra massemidpunkt til start tegneposition + 1 ekstra i x, da den bevæger sig denne vej.
                x=seagull->x+2;
                y=seagull->y-3;

            }

        gotoxy(x,y);
        printf("%*c",7,' ');
}

void moveSeagull(struct velocityvector * shot, struct velocityvector * seagull, struct box * gameBox){
    int32_t xo;
    int32_t yo;

        int32_t vxold=seagull->vx;
        int32_t vyold=seagull->vy;
    if (seagull->ani==1){
        detectBarrier(gameBox,seagull);
        detectCollisionSeagull(shot, seagull);

        updateVelocityVector(seagull);
        drawSeagull(seagull);
        if (vxold==seagull->vx){
            cleanSeagull(seagull);
        }
    }
    // her skal vi have seagull til at bevæge sig

}

void drawBox(struct box * gameBox) {
    int i;
    for (i=gameBox->y1; i<= gameBox->y2;  i++) {
        gotoxy(gameBox->x1,i);
        if (i==gameBox->y1){
                printf("%c",201);  // øverst venstre hjørne
        }
        if (i==gameBox->y2) {
            printf("%c",187);  // øverst højre hjørne
        }
        else {
            printf("%c",205); // gulv/loft
        }
    }
    for (i= gameBox->x1+1; i <= gameBox->x2-1; i++) {
        gotoxy(i,gameBox->y1);
        printf("%c",186);
        gotoxy(i,gameBox->y2);
        printf("%c",186);        // væg
    }

    for (i=gameBox->y1; i<= gameBox->y2;  i++) {
        gotoxy(gameBox->x2,i);
        if (i==gameBox->y1){
                printf("%c",200); // nederst venstre hjørne
        }
        if (i==gameBox->y2) {
            printf("%c",188);   // nederst højre hjørne
        }
        else {
            printf("%c",205);  // gulv/loft
        }
    }

    // skriver title

    gotoxy(gameBox->x1,gameBox->y1+2);
    printf("%c",185);
    printf(" %s ", gameBox->title);
    printf("%c",204);
    gotoxy(1,1);
}


