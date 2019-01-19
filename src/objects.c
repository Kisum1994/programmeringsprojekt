#include "stm32f30x_conf.h" // STM32 config

#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"
#include <stdio.h>
#include "interface.h"
#include "fpsqrt.h"

#define ESC 0x1B

void death(struct velocityvector deadObject[]){
        deadObject->vx=0;
        deadObject->vy=0;
        deadObject->x=0;
        deadObject->y=0;
        deadObject->ang=0;
        deadObject->alive=0;
}


void initObjects(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox, struct velocityvector * seagull, struct velocityvector * asteroidS, struct velocityvector * asteroidL ) {  // kan man dette med funktion?
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship[0].vx=0;
        ship[0].vy=0;
        ship[0].x=15;
        ship[0].y=25;
        ship[0].ang=0;
        ship[0].height=3;
        ship[0].width=3;
        ship[0].alive=1;

    // SHOT 1
        shot[0].x=0;
        shot[0].vx=0;
        shot[0].y=0;
        shot[0].vy=0;
        shot[0].width=3;
        shot[0].height=3;
        shot[0].alive=1;
        shot[0].G=0;

    // SHOT 2
        shot[1].x=0;
        shot[1].vx=0;
        shot[1].y=0;
        shot[1].vy=0;
        shot[1].width=3;
        shot[1].height=3;
        shot[1].alive=1;
        shot[1].G=0;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=35;
        gameBox->y1=5;
        gameBox->y2=90;
        gameBox->title[6]="title"; // omkriv længde inden i [], til "længde af titel"+1
        gameBox->style=1;

    // MÅGER1
        seagull[0].vx=1;
        seagull[0].vy=1;
        seagull[0].x=10;
        seagull[0].y=15;
        seagull[0].width=9;
        seagull[0].height=3;
        seagull[0].alive=1;
        seagull[0].ani=1;

    // MÅGER2
        seagull[1].vx=-1;
        seagull[1].vy=-1;
        seagull[1].x=40;
        seagull[1].y=30;
        seagull[1].width=9;
        seagull[1].height=3;
        seagull[1].alive=1;
        seagull[1].ani=1;

    // MÅGER3
        seagull[2].vx=-1;
        seagull[2].vy=1;
        seagull[2].x=10;
        seagull[2].y=15;
        seagull[2].width=9;
        seagull[2].height=3;
        seagull[2].alive=1;
        seagull[2].ani=1;

    // Asteroide Small 1
        asteroidS[0].vx=0;
        asteroidS[0].vy=0;
        asteroidS[0].x=15;
        asteroidS[0].y=15;
        asteroidS[0].width=3;
        asteroidS[0].height=1;
        asteroidS[0].alive=1;
        asteroidS[0].G=1;

    // Asteroide Small 2
        asteroidS[1].vx=0;
        asteroidS[1].vy=0;
        asteroidS[1].x=15;
        asteroidS[1].y=15;
        asteroidS[1].width=3;
        asteroidS[1].height=1;
        asteroidS[1].alive=1;
        asteroidS[1].G=1;

    // Asteroide Large 1
        asteroidL[0].vx=1;
        asteroidL[0].vy=1;
        asteroidL[0].x=20;
        asteroidL[0].y=20;
        asteroidL[0].height=3;
        asteroidL[0].width=5;
        asteroidL[0].alive=1;
        asteroidL[0].G=2;

    // Asteroide Large 2
        asteroidL[1].vx=1;
        asteroidL[1].vy=1;
        asteroidL[1].x=20;
        asteroidL[1].y=20;
        asteroidL[1].height=3;
        asteroidL[1].width=5;
        asteroidL[1].alive=1;
        asteroidL[1].G=2;





}

    //ANIMATION AF OBJEKTER:
void shipControls(char * str,struct velocityvector ship[],struct velocityvector * shot, struct box * gameBox) {
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
                shoot(shot,ship[0]);
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
                    //ship som den får er allerede ship[0]
                drawShip(ship);
                draw=0;
                if (moved==1) {
                    cleanShip(ship);
                }
            }
        }

    }
}


void updateVelocityVector(struct  velocityvector velovector[]){
velovector->x = velovector->x+velovector->vx;
velovector->y = velovector->y+velovector->vy;
};

void drawShot(int32_t x, int32_t y){
gotoxy(x,y);
printf("o");
}


int moveShot(struct velocityvector * shot,struct box * gameBox,int speed){
if (updateShot(speed)==1){

    for (int i=0; i<2; i++){
            if (shot[i].alive>0){
                int32_t xo=shot[i].x;
                int32_t yo=shot[i].y;
                        gotoxy(xo,yo);
                        printf("%c",' ');


                        if (detectBarrier(gameBox,shot[i])==1) {
                            shot[i].alive--;
                            if (shot[i].alive==0){
                                    death(&shot[i]);
                            }
                        }
                        if (shot[i].alive>0){
                            updateVelocityVector(&shot[i]);
                            drawShot(shot[i].x,shot[i].y);
                            return 1;
                        }


                    }
                else {
                    return 0;
                }
        }
    }

};

void moveSeagull(struct velocityvector * shot, struct velocityvector * seagull, struct box * gameBox, int * speed){
    for (int i=0;i<3; i++){
        if (seagull[i].alive==1){
            if (updateSeagull(speed)==1){
                int32_t vxold=seagull[i].vx; // forrige hastighed gemmes så dan kan sammenlignes med den nye
                int32_t vyold=seagull[i].vy; // for mågen behøves vy ikke, men kan være nødvendig for andre objekter.
                detectBarrier(gameBox,seagull[i]);
                detectCollisionSeagull(shot,seagull[i]);
                    if (seagull[i].ani==1) {
                        updateVelocityVector(&seagull[i]);
                    }
                    if (vxold==seagull[0].vx){ // på grund af bounce på væggene skal den kun cleane nå der ikke er sket en ændring i dens retning.
                        cleanSeagull(seagull[i]);
                    }
                drawSeagull(seagull[i]);
            }
    }
}
};

void moveAsteroid(struct velocityvector * velovector, int  s){
    int32_t xo;
    int32_t yo;
    if (speed(s)==1){
    /*updateVelocityVector(velovector);*/
    if (velovector->width==5){
            drawAsteroid(velovector);
            cleanAsteroid(velovector);
    }
    else if (velovector->width==3){
            drawAsteroid(velovector);
            cleanAsteroid(velovector);
    }
    }
};

    //INTERAKTION MELLEM OBJEKTER:


//checkker om der skabes en collision i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
//checkker om der skabes en collision i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
int detectBarrier( struct box * gameBox, struct velocityvector * velovector){
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
};

void shoot(struct velocityvector * shot,struct velocityvector * ship) {
    for (int i=0; i<2;i++){
            if (shot[i].alive==0){
                shot[i].alive=3; // detect collisions med shot inden i, skal sætte shot->alive=0;
                if(ship->ang==0){
                            shot[i].x=ship->x-2;
                            shot[i].y=ship->y;
                            shot[i].vx=-1;
                            shot[i].vy=0;
                }
                else if(ship->ang==1){
                            shot[i].x=ship->x-2;
                            shot[i].y=ship->y-2;
                            shot[i].vx=-1;
                            shot[i].vy=-1;
                }
                else if(ship->ang==2){
                            shot[i].x=ship->x;
                            shot[i].y=ship->y-2;
                            shot[i].vx=0;
                            shot[i].vy=-1;
                }
                else if(ship->ang==3){
                            shot[i].x=ship->x+2;
                            shot[i].y=ship->y-2;
                            shot[i].vx=1;
                            shot[i].vy=-1;
                }
                else if(ship->ang==4){
                            shot[i].x=ship->x+2;
                            shot[i].y=ship->y;
                            shot[i].vx=1;
                            shot[i].vy=0;
                }
                else if(ship->ang==5){
                            shot[i].x=ship->x+2;
                            shot[i].y=ship->y+2;
                            shot[i].vx=1;
                            shot[i].vy=1;
                }
                else if(ship->ang==6){
                            shot[i].x=ship->x;
                            shot[i].y=ship->y+2;
                            shot[i].vx=0;
                            shot[i].vy=1;
                }
                else if(ship->ang==7){
                        shot[i].x=ship->x-2;
                        shot[i].y=ship->y+2;
                        shot[i].vx=-1;
                        shot[i].vy=1;
                }
            }
}
}


int detectCollision(struct velocityvector obj1[],struct velocityvector * obj2){
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

int detectCollsionShip( struct velocityvector * obj1,struct velocityvector * ship, int i) {
   for (int i=0; i<4;i++){
    if (detectCollision(&obj1[i],ship)==1) {
        death(ship);
        death(&obj1[i]);
        return 1;
    }
    else {
        return 0;
    }
   }
}


//detect seagull
int detectCollisionSeagull( struct velocityvector * obj1 ,struct velocityvector * seagull){

           for (int j=0; j<4;j++){
                if (detectCollision(&obj1[j],seagull)==1){
                    death(seagull);
                    death(obj1);
                    return 1;
                }
                else {
                    return 0;
                }
           }

}


    //GRAFIK AF OBJEKTER:
// funktion til at tegne en måge i bevægelse.
void drawSeagull(struct velocityvector * seagull){
    for (int i=0; i<3; i++){
    int xc=seagull[i].x-1;
    int yc=seagull[i].y-4;
    if (seagull[i].alive==1){
        if (seagull[i].ani==0){
            gotoxy(xc,yc);
            // måge position står
            printf("%c%c%c%c%c%c%c%c%c",' ',' ',47,92,' ',47,92,' ',' ');
            gotoxy(xc+1,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ',35,' ',' ',153,' ',' ',35,' ');
            gotoxy(xc+2,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ', 118,' ',' ',35,' ',' ',118,' ');
            seagull[i].ani=1;
        }
        else if (seagull[i].ani==1){
            // måge position flyver
            gotoxy(xc,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ',47,35,92,' ',47,35,92,' ');
            gotoxy(xc+1,yc);
            printf("%c%c%c%c%c%c%c%c%c",35,' ',' ',' ',153,' ',' ',' ',35);
            gotoxy(xc+2,yc);
            printf("%c%c%c%c%c%c%c%c%c", 118,' ',' ',' ',35,' ',' ',' ',118);
            seagull[i].ani=0;
        }
    }
    }
}

void cleanSeagull(struct velocityvector * seagull){
    //  virker muligvis kun for hastigeder +- 1!!!
    for (int i=0; i<3;i++){
    int x;
    int y;
    if (seagull[i].vy > 0 || seagull[i].vy < 0){   //mågen bevæger sig i y-retning
        y=seagull[i].y-(3+(seagull[i].vy/abs(seagull[i].vy))); // "3" 4+-vy, derfor divideres hastigheden abs(vy) for at få fortegnet.
    }
    if (seagull[i].vx > 0 || seagull[i].vx < 0){   //mågen bevæger sig i x-retning
        x=seagull[i].x-(seagull[i].vx/abs(seagull[i].vx))*2; //fortegnet beregnes og ganges med (h-1)/2 =2
    }
    if (seagull[i].vx > 0 || seagull[i].vx < 0){
        gotoxy(x,y);
        printf("%*c",7,' ');
    }
    }
}
void drawAsteroid(struct velocityvector * asteroid){

        if (asteroid->width==5){ // Asteroide size stor
            int x=asteroid->x-1;
            int y=asteroid->y-2;
            gotoxy(x,y);
            printf("%c%c%c%c%c",' ',35,35,35,' ');
            gotoxy(x+1,y);
            printf("%c%c%c%c%c",35,35,35,35,35);
            gotoxy(x+2,y);
            printf("%c%c%c%c%c",' ',35,35,35,' ');
        }
        else if (asteroid->width==3){ // Asteroide size lille
            gotoxy(asteroid->x,asteroid->y-1);
            printf("%c%c%c",35,35,35);
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

//
void deleteAsteroid(struct velocityvector * asteroid ){
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


void Gravity(struct velocityvector * shot, struct velocityvector * asteroid){
    //brug 32 for at undgå overflow. Vi har burg for at shifte for at opnå præccision når vi kigger på kredsløb.
    //afstand til asteroide
    int32_t dx=shot->x-asteroid->x;
    int32_t dy=shot->y-asteroid->y;
    // Hvad vi gerne vil er at beregne en hastighedsændring som følge af asteroiden.  Dvs: v=v+Delta v

    // shift gravitation parameter to achieve precission. Dette svarer til at der ganges med en faktor 2^15
    int32_t G=asteroid->G<<20;

    // Der beregnes en hastighedsændring i hhv. x og i y som følge af den store asteroide:
    // Der shiftes med 15 pladser til højre svarende til at der divideres 2^15.
    int32_t Dvx=(2*(dx)*G/(sqrtI2I((dx*dx+dy*dy)*(dx*dx+dy*dy)*(dx*dx+dy*dy)))) >>30;
    int32_t Dvy=((dy)*G/(sqrtI2I((dx*dx+dy*dy)*(dx*dx+dy*dy)*(dx*dx+dy*dy)))) >>30;

    shot->vx -=Dvx;
    shot->vy -=Dvy;
}

