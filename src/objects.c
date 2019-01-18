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

void death(struct velocityvector * deadObject){
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
        ship->vx=0;
        ship->vy=0;
        ship->x=15;
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
        shot->width=3;
        shot->height=3;
        shot->alive=1;

    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=35;
        gameBox->y1=5;
        gameBox->y2=90;
        gameBox->title[6]="title"; // omkriv længde inden i [], til "længde af titel"+1
        gameBox->style=1;

    // MÅGER
        seagull->vx=1;
        seagull->vy=1;
        seagull->x=7;
        seagull->y=7;
        seagull->width=9;
        seagull->height=3;
        seagull->alive=1;
        seagull->ani=1;

    // Asteroide Small
        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=15;
        asteroidS->y=15;
        asteroidS->width=3;
        asteroidS->height=1;
        asteroidS->alive=1;
        asteroidS->G=1;

    // Asteroide Large
        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=20;
        asteroidL->y=20;
        asteroidL->height=3;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=2;




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

void moveSeagull(struct velocityvector * shot, struct velocityvector * seagull){
    int32_t xo;
    int32_t yo;
    detectCollisionSeagull(shot, seagull);
    if (seagull->ani==1){
    updateVelocityVector(seagull);

    }
    // her skal vi have seagull til at bevæge sig
    drawSeagull(seagull);
    cleanSeagull(seagull);
};

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

/*int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2){
    if(obj1->x+obj1->vx==obj2->x+obj2->vx && obj1->y+obj1->vy==obj2->y+obj2->vy){
        return 1;

    } else {
    return 0;
    }
}*/

int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2){
    int i=(obj1->x+obj1->vx-((obj1->height-1)/2));
    int j=(obj1->y+obj1->vy-((obj1->width-1)/2));
    int k=(obj2->x+obj2->vx-((obj2->height-1)/2));
    int l=(obj2->y+obj2->vy-((obj2->width-1)/2));
    for(i;i<=(obj1->x+obj1->vx+((obj1->height+1)/2));i++)
        {
            for(j;j<=(obj1->y+obj1->vy+((obj1->width-1)/2));j++)
                {

                    for(k;k<=(obj2->x+obj2->vx+((obj2->height-1)/2));k++)
                        {
                            for(l;l<=(obj2->y+obj2->vy+((obj2->width-1)/2));l++)
                                {
                                    if(k==i && l==j)
                                        {
                                            return 1;
                                        }
                                    else
                                        {
                                            return 0;
                                        }
                                }
                        }
                }
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


//detect seagull
int detectCollisionSeagull( struct velocityvector * shot ,struct velocityvector * seagull){
    if (detectCollision(shot,seagull)==1) {
                seagull->alive=0;
                shot->alive=0;
                return 1;
        }
        else {
                return 0;
        }
}


    //GRAFIK AF OBJEKTER:
// funktion til at tegne en måge i bevægelse.
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
    // lav til delete funktion
    else if (seagull->alive==0){
        x=seagull->x-seagull->vx-1;
        y=seagull->y-seagull->vy-4;
            gotoxy(x,y);
            printf("%*c",9,' ');
            gotoxy(x+1,y);
            printf("%*c",9,' ');
            gotoxy(x+2,y);
            printf("%*c",9,' ');
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


int8_t keyboardInput(char * text) {
    // fungerer som get_char(); men har en grænse på 3 karakterer for piletasterne

    static int buffCount=0; //Husk at forklare static variable i rapport


    if (buffCount<3) {
        if (0<uart_get_count()) {
            text[buffCount]=uart_get_char();
            buffCount++;

        }
        if (text[buffCount-1]==0x0d) {

            text[buffCount]=0x00;
            buffCount = 0;
            return 1;
            uart_clear();
        }
        else if (text[buffCount-1]==0x20) {

            text[buffCount]=0x00;
            buffCount = 0;
            return 1;
            uart_clear();
        }
    }
     if(buffCount==3){

        buffCount = 0;
        return 1;
        uart_clear();

        }
return 0;
}

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


//////////////////  NY BOX-TEGNER //////////////

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
