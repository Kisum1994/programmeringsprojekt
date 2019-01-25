#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stm32f30x_conf.h" // STM32 config

#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"
#include "interface.h"

#define ESC 0x1B




    // OBJEKTER:
// Sætter objekter til døde, ved at printe mellemrum over dem og sætte relevante værdier i deres structs til 0.
void death(struct velocityvector * deadObject){
    int xc;
    int yc;
    if(deadObject->alive>0){

        // printer "blank" på dens position
        //hvis skud
        if (deadObject->width==1) {
            gotoxy(deadObject->x,deadObject->y);
            printf("%c",' ');
            deadObject->alive=0;
            deadObject->x=0;
            deadObject->y=0;
        }

        if (deadObject->width==3 && deadObject->enabled==1){
            xc=deadObject->x-1;
            yc=deadObject->y-1;
            gotoxy(xc,yc);
            printf("%*c",3,' ');
            gotoxy(xc+1,yc);
            printf("%*c",3,' ');
            gotoxy(xc+2,yc);
            printf("%*c",3,' ');
        }



        // hvis skib
        if (deadObject->width==3 && deadObject->time==0){
            deadObject->alive--;
            setFreq(587);
            for(int q=0; q<=1<<19;q++){
            }
            setFreq(523);
            for(int q=0; q<=1<<20;q++){
            }
            setFreq(0);
            deadObject->time=20;// tiendedele sekunder - iFrames
            drawShip(deadObject);
            if (deadObject->alive==0) {
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
            }
        }
        // hvis måge
        if (deadObject->width==9) {
            setFreq(2093);
            for(int q=0; q<=1<<19;q++){
            }
            setFreq(0);
            xc=deadObject->x-1;
            yc=deadObject->y-4;
            while(1){
                    gotoxy(xc,yc);
                    printf("%c%c%c%c%c%c%c%c%c",45,242,47,35,171,242,47,45,242);
                    gotoxy(xc+1,yc);
                    printf("%c%c%c%c%c%c%c%c%c",171,' ',' ',' ',35,' ',' ',' ',123);
                    gotoxy(xc+2,yc);
                    printf("%c%c%c%c%c%c%c%c%c",59,' ',' ',' ',37,' ',' ',' ',92);
                    if (updateSeagull1(30)==1){
                        gotoxy(xc,yc);
                        printf("%*c",9,' ');
                        gotoxy(xc+1,yc);
                        printf("%*c",9,' ');
                        gotoxy(xc+2,yc);
                        printf("%*c",9,' ');
                        break;
                    }
            }
            deadObject->alive=0;
            deadObject->x=0;
            deadObject->y=0;


        }
        // reseter objectets værdier til nul
        deadObject->vx=0;
        deadObject->vy=0;

        deadObject->impulseX=0;
        deadObject->impulseY=0;
    }
}

// Giver startværdier til alle structs.
void initObjects(struct velocityvector * ship,
                 struct velocityvector * shot0,
                 struct velocityvector * shot1,
                 struct velocityvector * shot2,
                 struct box * gameBox,
                 struct velocityvector * seagull0,
                 struct velocityvector * seagull1,
                 struct velocityvector * seagull2,
                 struct velocityvector * seagull3,
                 struct velocityvector * asteroidS,
                 struct velocityvector * asteroidL,
                 struct velocityvector * powerUp0,
                 struct velocityvector * powerUp1,
                 struct velocityvector * powerUp2) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=35;
        ship->y=57;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=0;
        ship->impulseX=0;
        ship->impulseY=0;
        ship->time=0;

    // SHOT0
        shot0->x=0;
        shot0->vx=0;
        shot0->y=0;
        shot0->vy=0;
        shot0->alive=0;
        shot0->height=1;
        shot0->width=1;
        shot0->impulseX=0;
        shot0->impulseY=0;


        // SHOT1
        shot1->x=0;
        shot1->vx=0;
        shot1->y=0;
        shot1->vy=0;
        shot1->alive=0;
        shot1->height=1;
        shot1->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


        // SHOT2
        shot2->x=0;
        shot2->vx=0;
        shot2->y=0;
        shot2->vy=0;
        shot2->alive=0;
        shot2->height=1;
        shot2->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

   // MÅGER
    // MÅGE 0

        seagull0->x=0;
        seagull0->y=0;
        seagull0->vy=0;
        seagull0->vx=0;
        seagull0->alive=0;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde
        seagull0->impulseX=0; //
        seagull0->impulseY=0;
        seagull0->time=0;

    // MÅGE 1

        seagull1->x=0;
        seagull1->y=0;
        seagull1->vy=0;
        seagull1->vx=0;
        seagull1->alive=0;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde
        seagull1->impulseX=0; //
        seagull1->impulseY=0;
        seagull1->time=0;

    // MÅGE 2

        seagull2->x=0;
        seagull2->y=0;
        seagull2->vy=0;
        seagull2->vx=0;
        seagull2->alive=0;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde
        seagull2->impulseX=0; //
        seagull2->impulseY=0;
        seagull2->time=0;

    // MÅGE 3

        seagull3->x=0;
        seagull3->y=0;
        seagull3->vy=0;
        seagull3->vx=0;
        seagull3->alive=0;
        seagull3->width=9;
        seagull3->height=3;
        seagull3->ang=0; //
        seagull3->ani=0; // 1 = vinger ude, og 0= vinger inde
        seagull3->impulseX=0; //
        seagull3->impulseY=0;
        seagull3->time=0;

	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=0;
        asteroidS->y=0;
        asteroidS->width=3;
        asteroidS->height=3;
        asteroidS->alive=0;
        asteroidS->G=10;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=0;
        asteroidL->y=0;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=0;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;

        // POWERUPS

        powerUp0->vx=0;
        powerUp0->vy=0;
        powerUp0->x=0;
        powerUp0->y=0;
        powerUp0->height=3;
        powerUp0->width=3;
        powerUp0->alive=0;
        powerUp0->enabled=0;

        powerUp1->vx=0;
        powerUp1->vy=0;
        powerUp1->x=0;
        powerUp1->y=0;
        powerUp1->height=1;
        powerUp1->width=1;
        powerUp1->alive=0;
        powerUp1->enabled=0;

        powerUp2->vx=0;
        powerUp2->vy=0;
        powerUp2->x=0;
        powerUp2->y=0;
        powerUp2->height=1;
        powerUp2->width=1;
        powerUp2->alive=0;
        powerUp2->enabled=0;
}

//Giver startværdier for tutorial til alle structs.
void initTutorial(struct velocityvector * ship,
                 struct velocityvector * shot0,
                 struct box * gameBox)
{

 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=47;
        ship->y=45;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=10;
        ship->impulseX=0;
        ship->impulseY=0;

    // SHOT0
        shot0->x=0;
        shot0->vx=0;
        shot0->y=0;
        shot0->vy=0;
        shot0->alive=0;
        shot0->height=1;
        shot0->width=1;
        shot0->impulseX=0;
        shot0->impulseY=0;
        shot0->time=0;

    // GAMEBOX
        gameBox->x1=37;
        gameBox->x2=57;  //standard for fullscreen: 70
        gameBox->y1=35;
        gameBox->y2=60;  //standard for fullscreen: 170
        strcpy(gameBox->title,"Tutorial Sandbox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

}

// Giver startværdier for level 1 til alle structs.
void initLevel1(struct velocityvector * ship,
                 struct velocityvector * shot0,
                 struct velocityvector * shot1,
                 struct velocityvector * shot2,
                 struct box * gameBox,
                 struct velocityvector * seagull0,
                 struct velocityvector * seagull1,
                 struct velocityvector * seagull2,
                 struct velocityvector * seagull3,
                 struct velocityvector * asteroidS,
                 struct velocityvector * asteroidL,
                 struct velocityvector * powerUp0,
                 struct velocityvector * powerUp1,
                 struct velocityvector * powerUp2)
                {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

  // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=35;
        ship->y=57;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=3;
        ship->impulseX=0;
        ship->impulseY=0;

    // SHOT0
        shot0->x=0;
        shot0->vx=0;
        shot0->y=0;
        shot0->vy=0;
        shot0->alive=0;
        shot0->height=1;
        shot0->width=1;
        shot0->impulseX=0;
        shot0->impulseY=0;


        // SHOT1
        shot1->x=0;
        shot1->vx=0;
        shot1->y=0;
        shot1->vy=0;
        shot1->alive=0;
        shot1->height=1;
        shot1->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


        // SHOT2
        shot2->x=0;
        shot2->vx=0;
        shot2->y=0;
        shot2->vy=0;
        shot2->alive=0;
        shot2->height=1;
        shot2->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

   // MÅGER
    // MÅGE 0

        seagull0->x=10;
        seagull0->y=10;
        seagull0->vy=1;
        seagull0->vx=1;
        seagull0->alive=1;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 1

        seagull1->x=60;
        seagull1->y=10;
        seagull1->vy=1;
        seagull1->vx=-1;
        seagull1->alive=0;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=10;
        seagull2->y=110;
        seagull2->vy=-1;
        seagull2->vx=1;
        seagull2->alive=0;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 3

        seagull3->x=0;
        seagull3->y=0;
        seagull3->vy=0;
        seagull3->vx=0;
        seagull3->alive=0;
        seagull3->width=9;
        seagull3->height=3;
        seagull3->ang=0; //
        seagull3->ani=0; // 1 = vinger ude, og 0= vinger inde



	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=50;
        asteroidS->y=90;
        asteroidS->width=3;
        asteroidS->height=3;
        asteroidS->alive=1;
        asteroidS->G=10;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=0;
        asteroidL->y=0;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=0;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;

        // POWERUPS

        powerUp0->vx=0;
        powerUp0->vy=0;
        powerUp0->x=0;
        powerUp0->y=0;
        powerUp0->height=3;
        powerUp0->width=3;
        powerUp0->alive=0;


        powerUp1->vx=0;
        powerUp1->vy=0;
        powerUp1->x=0;
        powerUp1->y=0;
        powerUp1->height=1;
        powerUp1->width=1;
        powerUp1->alive=0;


        powerUp2->vx=0;
        powerUp2->vy=0;
        powerUp2->x=0;
        powerUp2->y=0;
        powerUp2->height=1;
        powerUp2->width=1;
        powerUp2->alive=0;


                }

// Giver startværdier for level 2 til alle structs.
void initLevel2(struct velocityvector * ship,
                 struct velocityvector * shot0,
                 struct velocityvector * shot1,
                 struct velocityvector * shot2,
                 struct box * gameBox,
                 struct velocityvector * seagull0,
                 struct velocityvector * seagull1,
                 struct velocityvector * seagull2,
                 struct velocityvector * seagull3,
                 struct velocityvector * asteroidS,
                 struct velocityvector * asteroidL,
                 struct velocityvector * powerUp0,
                 struct velocityvector * powerUp1,
                 struct velocityvector * powerUp2) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=38;
        ship->y=60;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=3;
        ship->impulseX=0;
        ship->impulseY=0;

    // SHOT0
        shot0->x=0;
        shot0->vx=0;
        shot0->y=0;
        shot0->vy=0;
        shot0->alive=0;
        shot0->height=1;
        shot0->width=1;
        shot0->impulseX=0;
        shot0->impulseY=0;


        // SHOT1
        shot1->x=0;
        shot1->vx=0;
        shot1->y=0;
        shot1->vy=0;
        shot1->alive=0;
        shot1->height=1;
        shot1->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


        // SHOT2
        shot2->x=0;
        shot2->vx=0;
        shot2->y=0;
        shot2->vy=0;
        shot2->alive=0;
        shot2->height=1;
        shot2->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

   // MÅGER
    // MÅGE 0

        seagull0->x=10;
        seagull0->y=20;
        seagull0->vy=1;
        seagull0->vx=1;
        seagull0->alive=1;
        seagull0->width=9;
        seagull0->height=3;
        seagull0->ang=0; //
        seagull0->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 1

        seagull1->x=30;
        seagull1->y=30;
        seagull1->vy=-2;
        seagull1->vx=1;
        seagull1->alive=0;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=50;
        seagull2->y=20;
        seagull2->vy=1;
        seagull2->vx=-2;
        seagull2->alive=0;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 3

        seagull3->x=45;
        seagull3->y=45;
        seagull3->vy=1;
        seagull3->vx=1;
        seagull3->alive=0;
        seagull3->width=9;
        seagull3->height=3;
        seagull3->ang=0; //
        seagull3->ani=0; // 1 = vinger ude, og 0= vinger inde


	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=55;
        asteroidS->y=60;
        asteroidS->width=3;
        asteroidS->height=3;
        asteroidS->alive=1;
        asteroidS->G=10;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=35;
        asteroidL->y=95;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;

        // POWERUPS

        powerUp0->vx=0;
        powerUp0->vy=0;
        powerUp0->x=20;
        powerUp0->y=80;
        powerUp0->height=3;
        powerUp0->width=3;
        powerUp0->alive=0;
        powerUp0->time=0;


        powerUp1->vx=0;
        powerUp1->vy=0;
        powerUp1->x=20;
        powerUp1->y=20;
        powerUp1->height=3;
        powerUp1->width=3;
        powerUp1->alive=0;
        powerUp1->time=0;


        powerUp2->vx=0;
        powerUp2->vy=0;
        powerUp2->x=0;
        powerUp2->y=0;
        powerUp2->height=3;
        powerUp2->width=3;
        powerUp2->alive=0;
        powerUp2->time=0;

}

// Giver startværdier for level 3 til alle structs.
void initLevel3(struct velocityvector * ship,
                 struct velocityvector * shot0,
                 struct velocityvector * shot1,
                 struct velocityvector * shot2,
                 struct box * gameBox,
                 struct velocityvector * seagull0,
                 struct velocityvector * seagull1,
                 struct velocityvector * seagull2,
                 struct velocityvector * seagull3,
                 struct velocityvector * asteroidS,
                 struct velocityvector * asteroidL,
                 struct velocityvector * powerUp0,
                 struct velocityvector * powerUp1,
                 struct velocityvector * powerUp2) {
 // De individuelle structs SKAL initialiseres i main(), men initObject() definerer elementer af structs'ne

   // SHIP
        ship->vx=0;
        ship->vy=0;
        ship->x=35;
        ship->y=57;
        ship->ang=0;
        ship->height=3;
        ship->width=3;
        ship->alive=3;
        ship->impulseX=0;
        ship->impulseY=0;

    // SHOT0
        shot0->x=0;
        shot0->vx=0;
        shot0->y=0;
        shot0->vy=0;
        shot0->alive=0;
        shot0->height=1;
        shot0->width=1;
        shot0->impulseX=0;
        shot0->impulseY=0;


        // SHOT1
        shot1->x=0;
        shot1->vx=0;
        shot1->y=0;
        shot1->vy=0;
        shot1->alive=0;
        shot1->height=1;
        shot1->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


        // SHOT2
        shot2->x=0;
        shot2->vx=0;
        shot2->y=0;
        shot2->vy=0;
        shot2->alive=0;
        shot2->height=1;
        shot2->width=1;
        shot1->impulseX=0;
        shot1->impulseY=0;


    // GAMEBOX
        gameBox->x1=5;
        gameBox->x2=70;  //standard for fullscreen: 70
        gameBox->y1=5;
        gameBox->y2=115;  //standard for fullscreen: 170
        strcpy(gameBox->title,"BoxyBox" ); // Husk at gøre definationen af title[x] i objects.h længere, hvis stringen er længere
        gameBox->style=1;

   // MÅGER
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
        seagull1->alive=0;
        seagull1->width=9;
        seagull1->height=3;
        seagull1->ang=0; //
        seagull1->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 2

        seagull2->x=50;
        seagull2->y=50;
        seagull2->vy=-1;
        seagull2->vx=-1;
        seagull2->alive=0;
        seagull2->width=9;
        seagull2->height=3;
        seagull2->ang=0; //
        seagull2->ani=0; // 1 = vinger ude, og 0= vinger inde

    // MÅGE 3

        seagull3->x=30;
        seagull3->y=80;
        seagull3->vy=-1;
        seagull3->vx=-1;
        seagull3->alive=0;
        seagull3->width=9;
        seagull3->height=3;
        seagull3->ang=0; //
        seagull3->ani=0; // 1 = vinger ude, og 0= vinger inde


	// ASTEROIDR
        // Asteroid Small

        asteroidS->vx=0;
        asteroidS->vy=0;
        asteroidS->x=30;
        asteroidS->y=55;
        asteroidS->width=3;
        asteroidS->height=3;
        asteroidS->alive=1;
        asteroidS->G=10;

        // Asteroid Large

        asteroidL->vx=0;
        asteroidL->vy=0;
        asteroidL->x=50;
        asteroidL->y=30;
        asteroidL->height=5;
        asteroidL->width=5;
        asteroidL->alive=1;
        asteroidL->G=25;  // 25 er en passende værdi som Gravity() er nu;

        // POWERUPS

        powerUp0->vx=0;
        powerUp0->vy=0;
        powerUp0->x=20;
        powerUp0->y=80;
        powerUp0->height=3;
        powerUp0->width=3;
        powerUp0->alive=0;


        powerUp1->vx=0;
        powerUp1->vy=0;
        powerUp1->x=20;
        powerUp1->y=20;
        powerUp1->height=3;
        powerUp1->width=3;
        powerUp1->alive=0;


        powerUp2->vx=0;
        powerUp2->vy=0;
        powerUp2->x=20;
        powerUp2->y=20;
        powerUp2->height=3;
        powerUp2->width=3;
        powerUp2->alive=0;

}

//Ida
//Genopliver døde rumhavmåger
void reviveSeagull(struct velocityvector * seagull,int x, int y, int vx, int vy) {
    if (seagull->alive==0){
        seagull->x=x;
        seagull->y=y;
        seagull->vy=vy;
        seagull->vx=vx;
        seagull->alive=1;
        seagull->ani=0;
    }
}

    //ANIMATION AF OBJEKTER:

//Jakob
// shipControls benyttes til at styre skibet.
//Sammenholder input fra brugeren med både rotations bevægelser, fremadrettet bevægelse og skud.
void shipControls(char * str,struct velocityvector * ship,struct velocityvector * shot0,struct velocityvector * shot1,struct velocityvector * shot2, struct box * gameBox, struct velocityvector * powerUp0, struct velocityvector * powerUp1 , struct velocityvector * powerUp2) {
// char str[4]={""};   <-- denne SKAL defineres i main

    //kører kun hvis skibet er i live
    if (ship->alive>0){

            if (arrowInput(str)==4) { // venstre rotation af skib - venstre pil
                ship->ang++;
                if (ship->ang >=8) {
                    ship->ang=0;
                }
            }
            else if (arrowInput(str)==8){ //højre rotation af skib - højre pil
                ship->ang--;
                if (ship->ang<0) {
                    ship->ang=7;
                }
            }

            if(arrowInput(str)==0x01){ // skyde  - spacebar
                    if(shot0->alive==0){
                        shoot(shot0,ship);
                    }
                    //hvis powerUp er enabled aktiveres 2 skud mere.
                    else if (shot0->alive > 0 && powerUp0->enabled==1 && shot1->alive==0) {
                        shoot(shot1,ship);
                    }
                    else if (shot0->alive > 0 && shot1->alive>0 && powerUp0->enabled==1 && shot2->alive==0 ) {
                        shoot(shot2,ship);
                    }
            }
            if (arrowInput(str)==16){ // flyv fremad - pil op
                ship->enabled=1; // tjekker om skibet er ved at tilføre impuls
                if ( (ship->ang==7 || ship->ang==0 || ship->ang==1)){
                    ship->impulseX--;
                }
                if (ship->ang==1 || ship->ang==2 || ship->ang==3) {
                    ship->impulseY--;
                }
                if (ship->ang==3 || ship->ang==4 || ship->ang==5) {
                    ship->impulseX++;
                }
                if (ship->ang==5 || ship->ang==6 || ship->ang==7) {
                        ship->impulseY++;
                }
            }
    }
}

//Ida
// benyttes i tutorial til at rotere skibet.
//sammenholder input fra brugeren med rotationsbevægelse, da man i første del af tutorial kun skal kunne rotere.
int shipControlsTutorialTurn(char * str,struct velocityvector * ship) {
// char str[4]={""};   <-- denne SKAL defineres i main
    int draw=0;
    int moved=0;
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

//Ida
// benyttes i tutorial til at registrere fremadrettet bevægelse af skibet.
//sammenholder input fra brugeren med rotationsbevægelse og fremadrettet bevægelse, men returnerer kun 1 ved fremadrettet bevægelse.
int shipControlsTutorialMove(char * str,struct velocityvector * ship) {
  if (keyboardInput(str)>0) {

            if (arrowInput(str)==4) { // venstre rotation af skib - venstre pil
                ship->ang++;
                if (ship->ang >=8) {
                    ship->ang=0;
                }
            }
            else if (arrowInput(str)==8){ //højre rotation af skib - højre pil
                ship->ang--;
                if (ship->ang<0) {
                    ship->ang=7;
                }
            }


            if (arrowInput(str)==16){ // flyv fremad - pil op

                ship->enabled=1; // tjekker om skibet er ved at tilføre impuls til moveShip
                if ( (ship->ang==7 || ship->ang==0 || ship->ang==1)){
                    ship->impulseX--;
                        //ship->vx=-1;
                }
                if (ship->ang==1 || ship->ang==2 || ship->ang==3) {
                    ship->impulseY--;
                      //  ship->vy=-1;
                }
                if (ship->ang==3 || ship->ang==4 || ship->ang==5) {
                    ship->impulseX++;
                       // ship->vx=1;
                }
                if (ship->ang==5 || ship->ang==6 || ship->ang==7) {
                        ship->impulseY++;
                      //  ship->vy=1;
                }
                return 1;                                      // Denne kan tændes hvis skibet skal kunne bevæge sig fremad i dens retnin
            }
            else{
                return 0;
            }
  }
}

//Ida
// benyttes i tutorial til at registrere skud af skibet.
int shipControlsTutorialShoot(char * str,struct velocityvector * ship,struct velocityvector * shot){
    if (keyboardInput(str)>0) {
            if(arrowInput(str)==1){
                shoot(shot,ship);
                return 1;
            }
            else {
                return 0;
            }
    }
}

//Jakob
//
void moveShip(struct velocityvector * ship,struct box * gameBox) {
            //Her benyttes en static variable, da den gamle værdi af angOld skal hentes, hver gang funktionen kører.
            static int angOld;
            // "friktion" fjerner impuls
            //updateShip kører så skibets impuls kun opdateres hvert 10 del sekund. ship->enabled==0 skal undersøges, da denne værdi tjekker om piletasten holdes inde.
            //Det ønskes kun at fratrække impuls, når piletasten er sluppet.
            if (updateShip1(10)==1 && ship->enabled==0) {
                if (ship->time>0){
                    ship->time--;
                }
                if (ship->impulseX>0) {
                    ship->impulseX--;
                }
                if (ship->impulseX<0) {
                    ship->impulseX++;
                }
                if (ship->impulseY>0) {
                    ship->impulseY--;
                }
                if (ship->impulseY<0) {
                    ship->impulseY++;
                }
            }

            // sørger for at skibet ikke kan flyve ud af gameboxen
            if ((ship->x+ship->vx<=gameBox->x1+2 && (ship->ang==7 || ship->ang==0 || ship->ang==1)) || (ship->x+ship->vx<=gameBox->x1+2 && ship->impulseX<0) ){
                ship->impulseX=0;
            }
            if((ship->x+ship->vx>=gameBox->x2-2 && (ship->ang==3 || ship->ang==4 || ship->ang==5)) ||  (ship->x+ship->vx>=gameBox->x2-2 && ship->impulseX>0) ) {
                ship->impulseX=0;
            }
            if((ship->y+ship->vy<=gameBox->y1+2 && (ship->ang==1 || ship->ang==2 || ship->ang==3))  ||  (ship->y+ship->vy<=gameBox->y1+2 && ship->impulseY<0) ) {
                ship->impulseY=0;
            }
            if((ship->y+ship->vy>=gameBox->y2-2 && (ship->ang==5 || ship->ang==6 || ship->ang==7) ) ||  (ship->y+ship->vy>=gameBox->y2-2 && ship->impulseY>0)) {
                ship->impulseY=0;
            }

            // oversætter impuls til velocity
            if (abs(ship->impulseX)>=1) {
                    ship->vx=1*(ship->impulseX/abs(ship->impulseX));
            }
            if (abs(ship->impulseX)>=5) {
                  ship->vx=2*(ship->impulseX/abs(ship->impulseX));
            }
            if (abs(ship->impulseX)>=10) {
                    ship->impulseX=10*(ship->impulseX/abs(ship->impulseX));
            }

            if (abs(ship->impulseX)==0) {
                    ship->vx=0;
            }
            if (abs(ship->impulseY)>=1) {
                    ship->vy=1*(ship->impulseY/abs(ship->impulseY));
            }
            if (abs(ship->impulseY)>=5) {
                   ship->vy=2*(ship->impulseY/abs(ship->impulseY));
            }
            if (abs(ship->impulseY)>=10) {
                    ship->impulseY=10*(ship->impulseY/abs(ship->impulseY));
            }
            //Hvis impulsen er 0, skal skibets hastighed også sættes til 0.
            if (abs(ship->impulseY)==0) {
                    ship->vy=0;
            }

            //Hvis der er impuls, skal skibets position opdateres (ud fra hastigheden).
            if (ship->impulseX!=0 || ship->impulseY!=0) {
                if (updateShip2(5)==1) {
                    updateVelocityVector(ship);
                    cleanShip(ship);
                    drawShip(ship);

                }
            }
            //Tester om skibet er blevet drejet, således at skibet tegnes, når skibet drejes.
            if (ship->ang!=angOld) {
                drawShip(ship);
                angOld=ship->ang;
            }


}

//Jesper
//opdaterer positionen af inputtet ud fra hastigheden hvormed inputtet bevæger sig.
void updateVelocityVector(struct  velocityvector * velovector){
velovector->x = velovector->x+velovector->vx;
velovector->y = velovector->y+velovector->vy;
};

//Jesper
//Tegner et projektil på placeringen (x,y)
void drawShot(int32_t x, int32_t y){
gotoxy(x,y);
printf("%s","o");
}

//Jakob og Jesper
//Funktionen kalder en række andre funktioner, der styrer hvordan projektilet kommer til at bevæge sig.
int moveShot(struct velocityvector * shot,struct box * gameBox,struct velocityvector * asteroidL,struct velocityvector * asteroidS){
    int32_t xo=shot->x;
    int32_t yo=shot->y;

 if (shot->alive>0){
        //undersøger projektilets nuværende impuls og justerer hastigheden af projektilet ud fra denne.
            if (shot->impulseX>=1) {
                    shot->vx=shot->impulseX/10;
            }
            if (shot->impulseX<=-1) {
                    shot->vx=shot->impulseX/10;
            }
            if (shot->impulseY>=1) {
                    shot->vy=shot->impulseY/10;
            }
            if (shot->impulseY<=-1) {
                    shot->vy=shot->impulseY/10;
            }
            if(shot->impulseX==0) {
                    shot->vx=0;
            }
            if(shot->impulseY==0) {
                    shot->vy=0;
            }
        // clearer projektilets position
            gotoxy(xo,yo);
            printf("%c",' ');
        // Undersøger om projektilet har ramt gameboxen eller nogle af asteroiderne og fjerner et liv fra skuddet hvis dette er tilfældet
            if (detectBarrier(gameBox,shot)==1) {
                shot->alive--;
            }
            if (detectAsteroid(shot,asteroidL)==1 || detectAsteroid(shot,asteroidS)==1) {
                shot->alive--;
            }
        //sætter skuddet til dødt hvis det ikke har flere liv eller time er blevet 0. Time parameteren skyldet at skuddet kan låses i kredsløb rundt om asteroiderne.
            if (shot->alive==0){
                death(shot);
            }
            if (shot->time==0) {
                death(shot);
            }
            shot->time--;
        //Såfremt skuddet er i live opdateres skuddets hastighed og det tegnes i sin nye position
            if (shot->alive>0){
                updateVelocityVector(shot);
                drawShot(shot->x,shot->y);
                //returnerer 1 for kunne se hvornår bolden har rykket sig. (Kan være praktisk)
                return 1;
            }

    }
    else {
        return 0;
    }
};

// Jakob
//Funktionen kalder en række andre funktioner, der styrer hvordan mågen kommer til at bevæge sig.
void moveSeagull(struct velocityvector * seagull, struct box * gameBox,struct velocityvector * asteroidL,struct velocityvector * asteroidS,struct velocityvector *powerUp){
    //sørger for at seagull kun bliver opdateret, hvis den er i live.
    if (seagull->alive==1){

            int32_t vxold=seagull->vx;// forrige hastighed gemmes så dan kan sammenlignes med den nye

            detectBarrier(gameBox,seagull);
            detectAsteroid(seagull,asteroidL);
            detectAsteroid(seagull,asteroidS);
            detectAsteroid(seagull,powerUp);

            //sørger for at mågen kun skifter position når den har vingerne slået up.
            if (seagull->ani==1) {
                updateVelocityVector(seagull);
            }

            if (vxold==seagull->vx){ // på grund af bounce på væggene skal den kun cleane når der ikke er sket en ændring i dens x-retning.
                cleanSeagull(seagull);
            }
            drawSeagull(seagull);
    }
}


    //INTERAKTION MELLEM OBJEKTER:

//Jesper
//checkker om der skabes en collision mellem gamebox og input (velovector) i næste updatering, hvis ja, så skiftes fortegn på en overtrædende hastighed
int detectBarrier(struct box * gameBox, struct velocityvector * velovector){
    int bounce=0;
    // tjekker om input er en måge
    if (velovector->width==9){
        //tjekker om der vil ske kollision ved næste update. Her skal der tages højde for height og width, da koordinatsættet i input structen er midtpunktet af figuren.
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
    }
    // tjekker om input er et projektil.
    else if(velovector->width == 1){
        if( velovector->x+velovector->vx  <=  gameBox->x1+1 ){
                velovector->impulseX=velovector->impulseX*(-1);
                bounce=1;
        }
        if (velovector->x+velovector->vx  >=  gameBox->x2-1 ){
                velovector->impulseX=velovector->impulseX*(-1);
                bounce=1;
        }
        if (velovector->y+velovector->vy  <=  gameBox->y1+1 ){
                velovector->impulseY=velovector->impulseY*(-1);
                bounce=1;
        }
        if (velovector->y+velovector->vy  >=  gameBox->y2-1 ){
                velovector->impulseY=velovector->impulseY*(-1);
                bounce=1;
        }
    }
    if (bounce==1) {
            return 1;
    }
    else return 0;
}

//Jakob
//Tjekker om der skabes kollision mellem en asteroide og velovektor ved den næste opdatering. Hvis ja, så skiftes fortegnene på hastighed eller impuls af velovector.
int detectAsteroid(struct velocityvector * velovector,struct velocityvector * asteroid){
    int bouncex=0;
    int bouncey=0;
    //funktionen skal kun køre hvis inputtet (velovector) er i live.
    if (velovector->alive>0){
    // tjekker om der er sket en kollision og undersøger  velovektors position i forhold til asteroiden. For at undersøge i hvilken retning velovector skal bounce.
        if (detectCollision(velovector,asteroid)==1 && velovector->x<asteroid->x-(asteroid->height-1)/2){
            bouncex=1;
        }
        else if (detectCollision(velovector,asteroid)==1 && velovector->x>asteroid->x-(asteroid->height-1)/2){
            bouncex=1;
        }
        if (detectCollision(velovector,asteroid)==1 && velovector->y<asteroid->y-(asteroid->height-1)/2){
            bouncey=1;
        }
        else if (detectCollision(velovector,asteroid)==1 && velovector->y>asteroid->y-(asteroid->height-1)/2){
            bouncey=1;
        }

        if (bouncex==1) {
                //ændrer retningen af impulsen i x retningen.
                velovector->impulseX*=(-1);
                // Mågerne har ingen impuls, men skal stadigvæk have skiftet fortegnet på deres hastighed, når de kolliderer med en asteoride.
                if (velovector->impulseX==0 && velovector->impulseY==0){
                        velovector->vx*=(-1);
                }
        }
        if (bouncey==1) {
                //ændrer retningen af impulsen i y retningen.
                velovector->impulseY*=(-1);
                //mågerne får skiftet fortegnet på deres hastighed.
                if (velovector->impulseX==0 && velovector->impulseY==0){
                        velovector->vy*=(-1);
                }
        }
        if (bouncex==1 || bouncey==1) {
                return 1;

        }
    }
    else return 0;
}

//Jakob
//Affyrer et projektil. Retning, position og impuls af skuddet bestemmes ud fra vinkel og position af inputtet ship
void shoot(struct velocityvector * shot,struct velocityvector * ship) {
    //reseter projektilets værdi, hvis det er dødt.
    if (shot->alive<1) {
    death(shot);
    int impulse=10;
    shot->alive=3;
    shot->time=300;
    shot->impulseX=0;
    shot->impulseY=0;

     // detect collisions med shot inden i, skal sætte shot->alive=0;
    //tjekker vinklen af skibet, for at give projektilet impuls i den rigtige retning.
    if(ship->ang==0){
                shot->x=ship->x-3;
                shot->y=ship->y;
                shot->impulseX=-impulse+ship->impulseX;
                shot->impulseY=0+ship->impulseY;
    }
    else if(ship->ang==1){
                shot->x=ship->x-3;
                shot->y=ship->y-3;
                shot->impulseX=-impulse+ship->impulseX;
                shot->impulseY=-impulse+ship->impulseY;
    }
    else if(ship->ang==2){
                shot->x=ship->x;
                shot->y=ship->y-3;
                shot->impulseX=0+ship->impulseX;
                shot->impulseY=-impulse+ship->impulseY;
    }
    else if(ship->ang==3){
                shot->x=ship->x+3;
                shot->y=ship->y-3;
                shot->impulseX=impulse+ship->impulseX;
                shot->impulseY=-impulse+ship->impulseY;
    }
    else if(ship->ang==4){
                shot->x=ship->x+3;
                shot->y=ship->y;
                shot->impulseX=impulse+ship->impulseX;
                shot->impulseY=0+ship->impulseY;
    }
    else if(ship->ang==5){
                shot->x=ship->x+3;
                shot->y=ship->y+3;
                shot->impulseX=impulse+ship->impulseX;
                shot->impulseY=impulse+ship->impulseY;
    }
    else if(ship->ang==6){
                shot->x=ship->x;
                shot->y=ship->y+3;
                shot->impulseX=0+ship->impulseX;
                shot->impulseY=impulse+ship->impulseY;
    }
    else if(ship->ang==7){
                shot->x=ship->x-3;
                shot->y=ship->y+3;
                shot->impulseX=-impulse+ship->impulseX;
                shot->impulseY=impulse+ship->impulseY;
    }
}
}

// Jakob og Jesper
//Detekterer kollision mellem obj1 og obj2. Sætter parametre der svarer til de fire hjørner inputsne, obj1 og obj2 og undersøger overlap.
int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2){

    int hitx=0;
    int hity=0;
    //øverste venstre hjørne af obj1
    int i1=(obj1->x+obj1->vx)-(obj1->height-1)/2;
    int j1=(obj1->y+obj1->vy)-(obj1->width-1)/2;
    //nedeste højre hjørne af obj1
    int i2=i1+obj1->height;
    int j2=j1+obj1->width;
    //øverste venstre hjørne af obj2
    int k1=(obj2->x+obj2->vx-((obj2->height-1)/2));
    int l1=(obj2->y+obj2->vy-((obj2->width-1)/2));
    //nedeste højre hjørne af obj2.
    int k2=k1+obj2->height;
    int l2=l1+obj2->width;

    // Undersøger om obj1's del i x ligger indenfor obj2.
    if (k2 > i1 && k1 < i2){
            hitx=1;
    }
    // Undersøger om obj1's del i y ligger indenfor obj2.
    if (l2 > j1 && l1 < j2) {
            hity=1;
    }
    // Hvis obj1 ligger indenfor intervallet af obj2 i både x og y, så er der en kollision og der returneres 1.
    if (hitx==1 && hity==1) {
        return 1;
    }
    else {
        return 0;
    }

}

// Jakob og Jesper
//kører detectCollision på et objekt og skibet.
int detectCollsionShip( struct velocityvector * obj1,struct velocityvector * ship) {
    //Her tjekkes det om obj1 og skibet kolliderer.
    if (detectCollision(obj1,ship)==1) {
        death(ship);

       if (obj1->time>0){ //hvis det er et skud, og ikke en måge. Måger har time=0.
            death(obj1);
       }
        return 1;
    }
    else {
        return 0;
    }
}

// Jekob og Jesper
//kører detectCollision på et objekt og mågen.
int detectCollisionSeagull( struct velocityvector * seagull ,struct velocityvector * obj1){
    if (seagull->alive > 0) {
        if (detectCollision(obj1,seagull)==1) {
            death(obj1);
            //slår mågen ihjel netop hvis kollisionen er mellem måge og et projektil.
            if (obj1->width==1) {
                death(seagull);
            }
            return 1;
        }
    }
    else {
        return 0;
    }
}

// Jakob og Jesper
//kører detectCollision på et objekt og en asteroide
int detectCollsionAsteroid( struct velocityvector * obj1,struct velocityvector * asteroid) {
    if (detectCollision(obj1,asteroid)==1) {
        //sætter det objekt der støder ind i asteroiden til dødt.
        death(obj1);
        return 1;
    }
    else {
        return 0;
    }
}

//Jakob
//Aktiverer asteroidernes gravitation.
void Gravity(struct velocityvector * shot, struct velocityvector * asteroid){
    //brug 32 for at undgå overflow. Vi har burg for at shifte for at opnå præccision når vi kigger på kredsløb.
    //afstand til asteroide

    int32_t Dvx=0;
    int32_t Dvy=0;

   // int32_t countLimit=1<<13;
    if(shot->alive>0){
    // afstand i hhv x og y mellem asteoride og skud
    int32_t dx=(asteroid->x-shot->x);
    int32_t dy=(asteroid->y-shot->y);

    //  radial afstand i anden
    int32_t r = (sqrtI2I(dx*dx+dy*dy))*(sqrtI2I(dx*dx+dy*dy));

    // Gravitations værdien bitshiftes for at gøre gravitationen kraftigere.
    int32_t G=asteroid->G*5;
    // Sætter en radius for den ring, hvor tyngdekraften skal virke indenfor.
    if (sqrtI2I(r)<=20) {
        dx=dx;
        dy=dy;
        //tilvækst i hastighed i hhv x og y som følge af asteroidernes gravitationelle kraftpåvirkning.
        Dvx =  (dx/sqrtI2I(r))*(G/(r));
        Dvy =  (dy/sqrtI2I(r))*(G/(r));

        //Hastighedsændringen lægges til projektilets impuls
        shot->impulseX += Dvx;
        shot->impulseY += Dvy;
    }
    }
}

    //GRAFIK AF OBJEKTER:

//Jakob
//Tegner gameboxen som spillet foregår i
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
}

//Jakob
//Tegner rumskibet
void drawShip(struct velocityvector * ship) {
        //Positionen for det øverste venstre hjørne af figuren hvorfra rumskibet tegnes.
        int xc=ship->x-1;
        int yc=ship->y-1;
    gotoxy(xc,yc);
    if (ship->time>0) {  //blinker kun når skip er i iFrames
       printf("\e[5m");
    }
    //skibet tegnes forskelligt afhængigt af vinklen det er i.
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
    printf("\e[25m"); // slukker altid blink
}

//Jakob
//Renser skibets tidligere position
void cleanShip(struct velocityvector * ship) {
    //beregner tidligere position (x,y) er altid midtpunktskoordinaterne af skibet.
    int xc=ship->x-ship->vx-1;
    int yc=ship->y-ship->vy-1;
        //printer mellemrum i et felt der er 3x3, der hvor skibet var.
        gotoxy(xc,yc);
        printf("%*c",3,' ');
        gotoxy(xc+1,yc);
        printf("%*c",3,' ');
        gotoxy(xc+2,yc);
        printf("%*c",3,' ');

}

//Ida
//Tegner asteroider
void drawAsteroid(struct velocityvector * asteroid){
    //tjekker om asteroiden er alive. Begge asteroider er ikke med i alle 3 levels.
    if (asteroid->alive==1) {
        if (asteroid->width==5){ // Asteroid size Large
            int xc=asteroid->x-2;
            int yc=asteroid->y-2;
            gotoxy(xc,yc);
            printf("%c%c%c%c%c",220,219,219,219,' ');
            gotoxy(xc+1,yc);
            printf("%c%c%c%c%c",219,178,219,219,219);
            gotoxy(xc+2,yc);
            printf("%c%c%c%c%c",219,219,219,178,219);
            gotoxy(xc+3,yc);
            printf("%c%c%c%c%c",219,219,219,219,219);
            gotoxy(xc+4,yc);
            printf("%c%c%c%c%c",223,219,219,219,223);
        }
        else if (asteroid->width==3){ // Asteroid size Small
            int xc=asteroid->x-1;
            int yc=asteroid->y-1;
            gotoxy(xc,yc);
            printf("%c%c%c",220,219,220);
            gotoxy(xc+1,yc);
            printf("%c%c%c",219,219,219);
            gotoxy(xc+2,yc);
            printf("%c%c%c",223,219,223);
        }
    }
}

//Ida
// Tegner Rumhavmåger
void drawSeagull(struct velocityvector * seagull){
    //Koordinater af øverste venstre hjørne, hvorudfra mågen skal tegnes.
    int xc=seagull->x-1;
    int yc=seagull->y-4;
    if (seagull->alive==1){
        //ani tjekker hvilken position mågen er i. ani=1 vingerne ude. ani=0 vingerne inde.
        if (seagull->ani==0){
            gotoxy(xc,yc);
            // måge position vingerne inde
            printf("%c%c%c%c%c%c%c%c%c",' ',' ',47,92,' ',47,92,' ',' ');
            gotoxy(xc+1,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ',35,' ',' ',153,' ',' ',35,' ');
            gotoxy(xc+2,yc);
            printf("%c%c%c%c%c%c%c%c%c",' ', 118,' ',' ',35,' ',' ',118,' ');
            seagull->ani=1;
        }
        else if (seagull->ani==1){
            // måge position vingerne ude.
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

//Jakob
//renser mågens tidligere position.
void cleanSeagull(struct velocityvector * seagull){
    int x;
    int y;
    if (seagull->vy > 0 || seagull->vy < 0){   //mågen bevæger sig i y-retning
        // Der trækkes 3 fra for at komme til venstre side af figuren. Herefter lægges hastigheden til (med fortegn) for at tage højde for bevægelsesretning.
        // Hastigheden divideres med abs(vy) for at bibeholde fortegnet og tage højde for at hastigheden kan være andet en 1.
        y=seagull->y-(3+(seagull->vy/abs(seagull->vy)));
    }
    if (seagull->vx > 0 || seagull->vx < 0){   //mågen bevæger sig i x-retning
        x=seagull->x-(seagull->vx/abs(seagull->vx))*2; //fortegnet beregnes og ganges med (h-1)/2 =2
    }
    if (seagull->vx > 0 || seagull->vx < 0){
        gotoxy(x,y);
        // Der behøves kun at renses 7 pladser, da mågens animation (vingerne inde), gør at den yderste plads i hver side automatisk renses.
        printf("%*c",7,' ');
    }
}

//Jesper
// Tegner PowerUps
void drawPowerUp(struct velocityvector * powerUp){
    //Øverste venstre hjørne af kassen.
    int xc=powerUp->x-1;
    int yc=powerUp->y-1;
        gotoxy(xc,yc);
        printf("%c%c%c",169,196,170);
        gotoxy(xc+1,yc);
        printf("%c%c%c",186,49,186);
        gotoxy(xc+2,yc);
        printf("%c%c%c",192,196,217);
}

//Jesper
// detecterer at skibet har ramt en powerUp og aktiverer denne powerUp
int enablePowerUp(struct velocityvector * ship, struct velocityvector * powerUp, int rgb[3]){
    //tjekker om skibet er stødt sammen med powerUpen. Andet statement sørger for at funktionen ikke fortsætter så længe der detekteres en kollision.
    if(detectCollision(ship,powerUp)==1 && powerUp->enabled==0){
        //Aktiverer lyd
        setFreq(880);
        for(int q=0; q<=1<<18;q++){
        }
        setFreq(1320);
        for(int q=0; q<=1<<18;q++){
        }
        setFreq(0);
        //sætter enable værdien til 1, så powerUpen aktiveres.
        powerUp->enabled=1;
        death(powerUp);
        //Sætter LED til grøn
        rgb[0]=0;
        rgb[1]=1;
        rgb[2]=0;
        setLED(rgb);
        return 1;
    }
    else{
        return 0;
    }
}


