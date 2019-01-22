
#include <string.h>
#include <stdlib.h>

#include "stm32f30x_conf.h" // STM32 config

#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"

#define ESC 0x1B




    // OBJEKTER:
void death(struct velocityvector * deadObject){
        int xc;
        int yc;
        if(deadObject->alive>0){
        // printer "blank" på dens position
        //hvis skud
        if (deadObject->width==1) {
            gotoxy(deadObject->x,deadObject->y);
            printf("%c",' ');
        }
        // hvis skib
        if (deadObject->width==3){
            xc=deadObject->x-1;
            yc=deadObject->y-1;
            while (1){
                gotoxy(xc,yc);
                printf("%c%c%c",45,242,47);
                gotoxy(xc+1,yc);
                printf("%c%c%c",171,35,123);
                gotoxy(xc+2,yc);
                printf("%c%c%c",59,37,92);
                if (getTime()==100){
                    gotoxy(xc,yc);
                    printf("%*c",3,' ');
                    gotoxy(xc+1,yc);
                    printf("%*c",3,' ');
                    gotoxy(xc+2,yc);
                    printf("%*c",3,' ');
                    break;
                }
            }
            deadObject->y=1;
        }
        // hvis måge
        if (deadObject->width==9) {
            xc=deadObject->x-1;
            yc=deadObject->y-4;
            gotoxy(xc,yc);
            printf("%*c",9,' ');
            gotoxy(xc+1,yc);
            printf("%*c",9,' ');
            gotoxy(xc+2,yc);
            printf("%*c",9,' ');

            deadObject->y=30;
        }
        // reseter objectets værdier til nul
        deadObject->vx=0;
        deadObject->vy=0;
        deadObject->x=0;

        deadObject->ang=0;
        deadObject->alive=0;
    }
}


void initObjects(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBoxT,struct box * gameBox, struct velocityvector * seagull0,struct velocityvector * seagull1,struct velocityvector * seagull2,struct velocityvector * seagull3,struct velocityvector * asteroidS, struct velocityvector * asteroidL) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=47;
        ship->y=45;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=1;

    // SHOT
        shot->x=0;
        shot->vx=0;
        shot->y=0;
        shot->vy=0;
        shot->height=1;
        shot->width=1;
        shot->alive=0;

    // Tutorial GAMEBOX
        gameBoxT->x1=37;
        gameBoxT->x2=57;  //standard for fullscreen: 70
        gameBoxT->y1=35;
        gameBoxT->y2=60;  //standard for fullscreen: 170
        strcpy(gameBoxT->title,"Tutorial box" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBoxT->style=1;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

    // MÅGE 0

        seagull0->x=30;
        seagull0->y=40;
        seagull0->vy=1;
        seagull0->vx=1;
        seagull0->alive=1;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 1

        seagull1->x=30;
        seagull1->y=40;
        seagull1->vy=1;
        seagull1->vx=1;
        seagull1->alive=1;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=50;
        seagull2->y=50;
        seagull2->vy=-1;
        seagull2->vx=-1;
        seagull2->alive=1;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=30;
        asteroidS->y=50;
        asteroidS->width=3;
        asteroidS->height=1;
        asteroidS->alive=1;
        asteroidS->G=1;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=50;
        asteroidL->y=30;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;
}


void initLevel1(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox, struct velocityvector * seagull0,struct velocityvector * seagull1,struct velocityvector * seagull2,struct velocityvector * seagull3,struct velocityvector * asteroidS, struct velocityvector * asteroidL) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=25;
        ship->y=25;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=1;

    // SHOT
        shot->x=0;
        shot->vx=0;
        shot->y=0;
        shot->vy=0;
        shot->height=1;
        shot->width=1;
        shot->alive=0;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

    // MÅGE 0

        seagull0->x=30;
        seagull0->y=40;
        seagull0->vy=1;
        seagull0->vx=1;
        seagull0->alive=1;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 1

        seagull1->x=30;
        seagull1->y=40;
        seagull1->vy=1;
        seagull1->vx=1;
        seagull1->alive=1;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=50;
        seagull2->y=50;
        seagull2->vy=-1;
        seagull2->vx=-1;
        seagull2->alive=1;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=30;
        asteroidS->y=50;
        asteroidS->width=3;
        asteroidS->height=1;
        asteroidS->alive=1;
        asteroidS->G=1;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=50;
        asteroidL->y=30;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;
}

void initLevel2(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox, struct velocityvector * seagull0,struct velocityvector * seagull1,struct velocityvector * seagull2,struct velocityvector * seagull3,struct velocityvector * asteroidS, struct velocityvector * asteroidL) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=25;
        ship->y=25;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=1;

    // SHOT
        shot->x=0;
        shot->vx=0;
        shot->y=0;
        shot->vy=0;
        shot->height=1;
        shot->width=1;
        shot->alive=0;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

    // MÅGE 0

        seagull0->x=30;
        seagull0->y=40;
        seagull0->vy=1;
        seagull0->vx=1;
        seagull0->alive=1;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 1

        seagull1->x=30;
        seagull1->y=40;
        seagull1->vy=1;
        seagull1->vx=1;
        seagull1->alive=1;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=50;
        seagull2->y=50;
        seagull2->vy=-1;
        seagull2->vx=-1;
        seagull2->alive=1;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 3

        seagull3->x=50;
        seagull3->y=50;
        seagull3->vy=-1;
        seagull3->vx=-1;
        seagull3->alive=1;
        seagull3->width=9;
        seagull3->height=3;
        seagull3->ang=0; //
        seagull3->ani=0; // 1 = vinger ude, og 0= vinger inde

	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=30;
        asteroidS->y=50;
        asteroidS->width=3;
        asteroidS->height=1;
        asteroidS->alive=1;
        asteroidS->G=1;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=50;
        asteroidL->y=30;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;
}

void initLevel3(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox, struct velocityvector * seagull0,struct velocityvector * seagull1,struct velocityvector * seagull2,struct velocityvector * seagull3,struct velocityvector * asteroidS, struct velocityvector * asteroidL) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=25;
        ship->y=25;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=1;

    // SHOT
        shot->x=0;
        shot->vx=0;
        shot->y=0;
        shot->vy=0;
        shot->height=1;
        shot->width=1;
        shot->alive=0;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

    // MÅGE 0

        seagull0->x=30;
        seagull0->y=40;
        seagull0->vy=1;
        seagull0->vx=1;
        seagull0->alive=1;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 1

        seagull1->x=30;
        seagull1->y=40;
        seagull1->vy=1;
        seagull1->vx=1;
        seagull1->alive=1;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=50;
        seagull2->y=50;
        seagull2->vy=-1;
        seagull2->vx=-1;
        seagull2->alive=1;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 3

        seagull3->x=50;
        seagull3->y=50;
        seagull3->vy=-1;
        seagull3->vx=-1;
        seagull3->alive=1;
        seagull3->width=9;
        seagull3->height=3;
        seagull3->ang=0; //
        seagull3->ani=0; // 1 = vinger ude, og 0= vinger inde

	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=30;
        asteroidS->y=50;
        asteroidS->width=3;
        asteroidS->height=1;
        asteroidS->alive=1;
        asteroidS->G=1;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=50;
        asteroidL->y=30;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;
}
    //ANIMATION AF OBJEKTER:
void reviveSeagull(struct velocityvector * seagull,int x, int y, int vx, int vy){
if (seagull->alive==0){
        seagull->x=x;
        seagull->y=y;
        seagull->vy=vy;
        seagull->vx=vx;
        seagull->alive=1;
        seagull->ani=0;
}

}

void shipControls(char * str,struct velocityvector * ship,struct velocityvector * shot, struct box * gameBox) {
// char str[4]={""};   <-- denne SKAL defineres i main
    int draw=0;
    int moved=0;
    if (ship->alive==1){

        if (keyboardInput(str)>0) {

            if (arrowInput(str)==4) { // venstre rotation af skib
                ship->ang++;
                if (ship->ang >=8) {
                    ship->ang=0;
                }
                draw=1;
            }
            else if (arrowInput(str)==8){ //højre rotation af skib
                ship->ang--;

                if (ship->ang<0) {
                    ship->ang=7;
                }
                draw=1;
            }

            if(arrowInput(str)==0x01){
                shoot(shot,ship);
            }


              // Denne kan tændes hvis skibet skal kunne bevæge sig fremad i dens retning
            else if (arrowInput(str)==16){

                if (ship->x==gameBox->x1+2 && (ship->ang==7 || ship->ang==0 || ship->ang==1) ){
                }
                else if(ship->x==gameBox->x2-2 && (ship->ang==3 || ship->ang==4 || ship->ang==5) ) {
                }
                else if(ship->y==gameBox->y1+2 && (ship->ang==1 || ship->ang==2 || ship->ang==3) ) {
                }
                else if(ship->y==gameBox->y2-2 && (ship->ang==5 || ship->ang==6 || ship->ang==7) ) {
                }
                else {
                    draw=1;
                    moved=1;
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
                }
            }
            if (draw==1) {
                drawShip(ship);
                draw=0;
                if (moved==1) {
                    cleanShip(ship);
                }
            }
        }

    }
}


int shipControlsTutorialTurn(char * str,struct velocityvector * ship) {
// char str[4]={""};   <-- denne SKAL defineres i main
    int draw=0;
    int moved=0;

 /*   if (ship->alive==1){
*/
       if (keyboardInput(str)>0) {
            if (arrowInput(str)==4) { // venstre rotation af skib
                ship->ang++;
                if (ship->ang >=8) {
                    ship->ang=0;
                }
                draw=1;
            }
            else if (arrowInput(str)==8){ //højre rotation af skib
                ship->ang--;

                if (ship->ang<0) {
                    ship->ang=7;
                }
                draw=1;

            }
            if (draw==1) {
                drawShip(ship);
                draw=0;
                return 1;
            }
       }
}

int shipControlsTutorialMove(char * str,struct velocityvector * ship) {
// char str[4]={""};   <-- denne SKAL defineres i main
    int draw=0;
    int moved=0;

 /*   if (ship->alive==1){
*/
       if (keyboardInput(str)>0) {
            if (arrowInput(str)==4) { // venstre rotation af skib
                ship->ang++;
                if (ship->ang >=8) {
                    ship->ang=0;
                }
                draw=1;
            }
            else if (arrowInput(str)==8){ //højre rotation af skib
                ship->ang--;

                if (ship->ang<0) {
                    ship->ang=7;
                }
                draw=1;
            }
            // Denne kan tændes hvis skibet skal kunne bevæge sig fremad i dens retning
        if (arrowInput(str)==16){
                    draw=1;
                    moved=1;
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
                }

            if (draw==1) {
                drawShip(ship);
                draw=0;
                if (moved==1) {
                   cleanShip(ship);
                    return 1;
                }
            }
    }
}

int shipControlsTutorialShoot(char * str,struct velocityvector * ship,struct velocityvector * shot){
    if (keyboardInput(str)>0) {
            if(arrowInput(str)==1){
                shoot(shot,ship);
                return 1;
            }
            else{return 0;
            }
    }
}


void updateVelocityVector(struct  velocityvector * velovector){
velovector->x = velovector->x+velovector->vx;
velovector->y = velovector->y+velovector->vy;
};

void drawShot(int32_t x, int32_t y){
gotoxy(x,y);
printf("%c",248);
}

int moveShot(struct velocityvector * shot,struct box * gameBox,int speed){
    int32_t xo=shot->x;
    int32_t yo=shot->y;
    if (shot->alive>0){
        if (updateShot(speed)==1){

            gotoxy(xo,yo);
            printf("%c",' ');


            if (detectBarrier(gameBox,shot)==1) {
                shot->alive--;
                if (shot->alive==0){
                        death(shot);
                }
            }
            if (shot->alive>0){
                updateVelocityVector(shot);
                drawShot(shot->x,shot->y);
                return 1;
            }


        }
    }
    else {
        return 0;
    }
};

void moveSeagull(struct velocityvector * shot, struct velocityvector * seagull, struct box * gameBox/*,int speed*/){
    if (seagull->alive==1){
       // if (updateSeagull(speed)==1){
            int32_t vxold=seagull->vx; // forrige hastighed gemmes så dan kan sammenlignes med den nye
            int32_t vyold=seagull->vy; // for mågen behøves vy ikke, men kan være nødvendig for andre objekter.
            detectBarrier(gameBox,seagull);
            detectCollisionSeagull(shot,seagull);
            if (seagull->ani==1) {
                updateVelocityVector(seagull);
            }
            if (vxold==seagull->vx){ // på grund af bounce på væggene skal den kun cleane nå der ikke er sket en ændring i dens retning.
                cleanSeagull(seagull);
            }
            drawSeagull(seagull);
        }
    //}
}

void moveAsteroid(struct velocityvector * velovector){
    int32_t xo;
    int32_t yo;
    updateVelocityVector(velovector);
    if (velovector->width==5){
            drawAsteroid(velovector);
            cleanAsteroid(velovector);
    }
    else if (velovector->width==3){
            drawAsteroid(velovector);
            cleanAsteroid(velovector);
    }
};


    //INTERAKTION MELLEM OBJEKTER:


//checkker om der skabes en collision i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
int detectBarrier( struct box * gameBox, struct velocityvector * velovector){
    int bounce=0;
    if( velovector->x+velovector->vx-((velovector->height-1)/2)  <=  gameBox->x1 ){
            velovector->vx=velovector->vx*(-1);
            bounce=1;
    }
    if (velovector->x+velovector->vx+((velovector->height-1)/2)  >=  gameBox->x2 ){
            velovector->vx=velovector->vx*(-1);
            bounce=1;
    }
    if (velovector->y+velovector->vy-((velovector->width)/2)  <=  gameBox->y1 ){
            velovector->vy=velovector->vy*(-1);
            bounce=1;
    }
    if (velovector->y+velovector->vy+((velovector->width)/2)  >=  gameBox->y2 ){
            velovector->vy=velovector->vy*(-1);
            bounce=1;
    }
    if (bounce==1) {
            return 1;
    }
    else return 0;
}


void shoot(struct velocityvector * shot,struct velocityvector * ship) {
    if (shot->alive<1) {
    death(shot);
    shot->alive=3; // detect collisions med shot inden i, skal sætte shot->alive=0;
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
}

int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2){
    // forsøg at brug så obj2 er større end obj1 for mindske iterartions i for loops
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
                    if(k1 <= i1 && i1 <= k2 && l1<= j1 && j1 <= l2){
                        return 1;
                    }
                    else {
                        return 0;
                    }
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

int detectCollisionSeagull( struct velocityvector * obj1 ,struct velocityvector * seagull){
    if (seagull->alive>0){
        if (detectCollision(obj1,seagull)==1) {
            death(seagull);
            death(obj1);
            return 1;
        }
    }
        else {
            return 0;
        }
}

int detectCollsionAsteroid( struct velocityvector * obj1,struct velocityvector * asteroid) {
    if (detectCollision(obj1,asteroid)==1) {
        death(obj1);
        return 1;
    }
    else {
        return 0;
    }
}

void Gravity(struct velocityvector * shot, struct velocityvector * asteroid){
    //brug 32 for at undgå overflow. Vi har burg for at shifte for at opnå præccision når vi kigger på kredsløb.
    //afstand til asteroide

    static int32_t Dvx;
    static int32_t Dvy;

    int32_t countLimit=1<<13;

    int32_t dx=(asteroid->x-shot->x);
    int32_t dy=(asteroid->y-shot->y);

    int32_t r = (sqrtI2I(dx*dx+dy*dy)*sqrtI2I(dx*dx+dy*dy));// *sqrtI2I(dx*dx+dy*dy));
    r=r<<11;// Hvad vi gerne vil er at beregne en hastighedsændring som følge af asteroiden.  Dvs: v=v+Delta v
    int32_t G=asteroid->G<<14;
 /*
    // Der beregnes en hastighedsændring i hhv. x og i y som følge af den store asteroide:
    // Der shiftes med 15 pladser til højre svarende til at der divideres 2^15.
    int32_t Dvx= ((dx/abs(dx))*G/(r))/abs(((dx/abs(dx))*G/(r))) ;
    int32_t Dvy= ((dy/abs(dy))*G/(r))/abs(((dy/abs(dy))*G/(r))) ;

         shot->vx = (shot->vx+Dvx);
         shot->vy = (shot->vy+Dvy);                       */


    int32_t Dvxold=Dvx;
    int32_t Dvyold=Dvy;
    if (shot->alive<=0){
            Dvx=0;
            Dvy=0;
    }
    if (Dvxold>Dvx ){ // for negativ til positv ændring
            Dvx=0;
    }
    if (Dvyold>Dvy ){
            Dvy=0;
    }

    Dvx=Dvx+  ((dx/abs(dx))  *G/(r));
    Dvy=Dvy+  ((dy/abs(dy))  *G/(r));

    if (Dvx>=countLimit || Dvx<=-(countLimit)) {
        shot->vx = (shot->vx+(Dvx/abs(Dvx)));
        Dvx=0;
    }
    if (Dvy>=countLimit || Dvy<=-(countLimit)){
        shot->vy = (shot->vy+(Dvy/abs(Dvy)));
        Dvy=0;
    }

}

    //GRAFIK AF OBJEKTER:

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

        gotoxy(gameBox->x2,i);
        if (i==gameBox->y1){
                printf("%c",200); // nederst venstre hjørne
        }
        if (i==gameBox->y2) {
            printf("%c",188);   // nederst højre hjørne
        }
        else {
            printf("%c",205); // gulv/loft
        }
    }
    for (i= gameBox->x1+1; i <= gameBox->x2-1; i++) {
        gotoxy(i,gameBox->y1);
        printf("%c",186);
        gotoxy(i,gameBox->y2);
        printf("%c",186);        // vægge
    }

    // skriver title

    gotoxy(gameBox->x1,gameBox->y1+2);
    printf("%c",185);
    printf(" %s ", gameBox->title);
    printf("%c",204);
    gotoxy(1,1);
}


void drawShip(struct velocityvector * ship) {
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

void cleanShip(struct velocityvector * ship) {
    int xc=ship->x-1;
    int yc=ship->y-1;

    if (ship->ang==0) {
        gotoxy(xc+3,yc);
        printf("%*c",3,' ');
    }
    if (ship->ang==1) {
        gotoxy(xc+2,yc+3);
        printf("%c",' ');
        gotoxy(xc+3,yc+2);
        printf("%*c",2,' ');
    }
     if (ship->ang==2) {
        gotoxy(xc,yc+3);
        printf("%c",' ');
        gotoxy(xc+1,yc+3);
        printf("%c",' ');
        gotoxy(xc+2,yc+3);
        printf("%c",' ');
    }
    if (ship->ang==3) {
        gotoxy(xc-1,yc+2);
        printf("%*c",2,' ');
        gotoxy(xc,yc+3);
        printf("%*c",1,' ');
    }
    if (ship->ang==4) {
        gotoxy(xc-1,yc);
        printf("%*c",3,' ');
    }
    if (ship->ang==5) {
        gotoxy(xc-1,yc-1);
        printf("%*c",2,' ');
        gotoxy(xc,yc-1);
        printf("%*c",1,' ');
    }
    if (ship->ang==6) {
        gotoxy(xc,yc-1);
        printf("%c",' ');
        gotoxy(xc+1,yc-1);
        printf("%c",' ');
        gotoxy(xc+2,yc-1);
        printf("%c",' ');
    }
    if (ship->ang==7) {
        gotoxy(xc+2,yc-1);
        printf("%c",' ');
        gotoxy(xc+3,yc-1);
        printf("%*c",2,' ');
    }
}


void drawAsteroid(struct velocityvector * asteroid){

        if (asteroid->width==5){ // Asteroide size stor
            int x=asteroid->x-1;
            int y=asteroid->y-2;
            gotoxy(x,y);
            printf("%c%c%c%c%c",220,219,219,219,' ');
            gotoxy(x+1,y);
            printf("%c%c%c%c%c",219,178,219,219,219);
            gotoxy(x+2,y);
            printf("%c%c%c%c%c",223,219,219,219,223);
        }
        else if (asteroid->width==3){ // Asteroide size lille
            gotoxy(asteroid->x,asteroid->y-1);
            printf("%c%c%c",254,219,254);
        }
}

void cleanAsteroid(struct velocityvector * asteroid){
    int xold = asteroid->x-asteroid->vx;
    int yold = asteroid->y-asteroid->vy;
    int x,y;
        if (asteroid->width==5){ // stor asteroide
            if (asteroid->vy>0){
                //Asteroiden bevæger sig i positiv y-putty retning (positiv x-retning)
                //skal være 1 mindre end afstand fra massemidtpunkt, da den har bevæget sig 1 plads i y.
                y=yold-2;
                x=xold-1;
                // asteroid->print blank
                gotoxy(x,y);
                printf("%c",' ');
                gotoxy(x+1,y);
                printf("%c",' ');
                gotoxy(x+2,y);
                printf("%c",' ');
            }
            else if (asteroid->vy<0){
                //Asteroiden bevæger sig i negativ x-retning (y_putty) y skal være 1 større end afstand fra massemidtpunkt.
                y=yold+2;
                x=xold-1;
                // print blank
                gotoxy(x,y);
                printf("%c",' ');
                gotoxy(x+1,y);
                printf("%c",' ');
                gotoxy(x+2,y);
                printf("%c",' ');
            }
            if (asteroid->vx>0){
                //Asteroiden bevæger sig i positiv x-putty retning (positiv y-retning)
                x=xold-1;
                y=yold-2;
                gotoxy(x,y);
                printf("%*c",5,' ');
            }
            else if (asteroid->vx<0){
            //Afstanden fra massemidpunkt til start tegneposition + 1 ekstra i x, da den bevæger sig denne vej.
                x=xold+1;
                y=yold-2;
                gotoxy(x,y);
            printf("%*c",5,' ');
            }
        }

        else if (asteroid->width==3){
            if (asteroid->vy>0){
                    //Asteroiden bevæger sig i positiv y-putty retning (positiv x-retning)
                    //y skal være 1 mindre end afstand fra massemidtpunkt, da den har bevæget sig 1 plads i y.
                    x=xold;
                    y=yold-1;
                    gotoxy(x,y);
                    printf("%c",' ');
                }
            else if (asteroid->vy<0){
                    // Her bliver x og y til x og y
                    x=xold;
                    y=yold+1;
                    gotoxy(x,y);
                    printf("%c",' ');
                }
            if (asteroid->vx>0){
                //Asteroiden bevæger sig i positiv x-putty retning (positiv y-retning)
                //x skal være 1 mindre end afstand fra massemidtpunkt, da den har bevæget sig 1 plads i positiv x.
                x=xold;
                y=yold-1;
                gotoxy(x,y);
                printf("%*c",3,' ');
            }
            else if (asteroid->vx<0){
                //Asteroiden bevæger sig i negativ x-retning (y_putty) x skal være 1 større end afstand fra massemidtpunkt.
                x=xold;
                y=yold-1;
            gotoxy(x,y);
            printf("%*c",3,' ');
            }
        }
}

/*void deleteAsteroid(struct velocityvector * asteroid ){ // skal bare køres via death !hvis altså en asteroide skal kunne dø!
    int x,y;
    if (asteroid->width==5){
        x=asteroid->x-asteroid->vx-1;
        y=asteroid->y-asteroid->vy-2;
            gotoxy(x,y);
            printf("%*c",5,' ');
            gotoxy(x+1,y);
            printf("%*c",5,' ');
            gotoxy(x+2,y);
            printf("%*c",5,' ');
    }
    else if (asteroid->width==1){
        x=asteroid->x-asteroid->vx;
        y=asteroid->y-asteroid->vy-1;
            gotoxy(x,y);
            printf("%*c",5,' ');
            gotoxy(x+1,y);
            printf("%*c",5,' ');
            gotoxy(x+2,y);
            printf("%*c",5,' ');
    }
}*/


void drawSeagull(struct velocityvector * seagull){
    int xc=seagull->x-1;
    int yc=seagull->y-4;
    if (seagull->alive==1){
        if (seagull->ani==0){
            gotoxy(xc,yc);
            // måge position står
            printf("%c%c%c%c%c%c%c%c%c",' ',' ',47,92,' ',47,92,' ',' ');
            gotoxy(xc+1,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ',35,' ',' ',153,' ',' ',35,' ');
            gotoxy(xc+2,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ', 118,' ',' ',35,' ',' ',118,' ');
            seagull->ani=1;
        }
        else if (seagull->ani==1){
            // måge position flyver
            gotoxy(xc,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ',47,35,92,' ',47,35,92,' ');
            gotoxy(xc+1,yc);
            printf("%c%c%c%c%c%c%c%c%c",35,' ',' ',' ',153,' ',' ',' ',35);
            gotoxy(xc+2,yc);
            printf("%c%c%c%c%c%c%c%c%c", 118,' ',' ',' ',35,' ',' ',' ',118);
            seagull->ani=0;
        }
    }
}

void cleanSeagull(struct velocityvector * seagull){
    //  virker muligvis kun for hastigeder +- 1!!!
    int x;
    int y;
    if (seagull->vy > 0 || seagull->vy < 0){   //mågen bevæger sig i y-retning
        y=seagull->y-(3+(seagull->vy/abs(seagull->vy))); // "3" 4+-vy, derfor divideres hastigheden abs(vy) for at få fortegnet.
    }
    if (seagull->vx > 0 || seagull->vx < 0){   //mågen bevæger sig i x-retning
        x=seagull->x-(seagull->vx/abs(seagull->vx))*2; //fortegnet beregnes og ganges med (h-1)/2 =2
    }
    if (seagull->vx > 0 || seagull->vx < 0){
        gotoxy(x,y);
        printf("%*c",7,' ');
    }
}



