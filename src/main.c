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

#include <string.h>
#include <stdio.h>
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
//init ur
initTimer();
TIM2_IRQHandler();

// init structs, deres værdier bliver skrevet i initObjects(); - denne findes i objects.c
struct box gameBox;
struct box gameBoxT;
struct velocityvector shot;
struct velocityvector ship;
struct velocityvector seagull0;
struct velocityvector seagull1;
struct velocityvector seagull2;
struct velocityvector seagull3;
struct velocityvector asteroidS;
struct velocityvector asteroidL;




// ryder op på skærmen
initJoystick();
clrscr();
gotoxy(0,0);
while (1){
    int readold=readJoystick();
        if (readold !=readJoystick()){
            printf("%x",readJoystick());
        }
}

//Viser splash screen og derefter main menu
/*splashScreen();
// Start først tid når spiller starter
TIM2->CR1 = 0x0001; //  <-- start timer 2
    // printf("\e[?25l"); // gør cursor usynlig


printf("Pre-alpha stage: Everything you see is subject to change.\n");


int won=0;
int level=0;
int kill;
while (1){
    if (won == 0 || level>=3){
        level=menuMain();
    }
    if (level==4){
    while(1){
    tutorial();
    initObjects(&ship,&shot,&gameBoxT,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
    drawBox(&gameBoxT);
    drawShip(&ship);
    int turn=0, moved=0, shotFired=0;
        while(turn<7){
            char str0[4]={""};
            if(shipControlsTutorialTurn(str0,&ship)==1){
                turn++;
            }
        }
        gotoxy(64,15);
        printf("You have succesfully turned the ship. Now try to move the ship\n");
        while(moved<4){
            char str1[4]={""};
            if(shipControlsTutorialMove(str1,&ship)==1){
                moved++;
            }
        }
        gotoxy(66,15);
        printf("You have succesfully moved the ship. Now try to shoot with the ship\n");
        while(shotFired<3){
            char str2[4]={""};
            if(shipControlsTutorialShoot(str2,&ship,&shot)==1){
                shotFired++;
            }
            moveShot(&shot,&gameBoxT,3);
            drawShip(&ship);
        }
    gotoxy(68,15);
    printf("You have completed the tutorial\n");
    for(int q=0; q<=1<<24;q++){
    }
    break;
    }
    continue;
    }

    if (won==1){
    level++;
    won=0;
    }

    if (level >0){
        kill=0;
        clrscr();
        if (level==1){
            initLevel1(&ship,&shot,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
        }
        else if (level==2){
            initLevel2(&ship,&shot,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
        }
        else if (level==3){
            initLevel3(&ship,&shot,&gameBox,&seagull0,&seagull1,&seagull2,&seagull3,&asteroidS,&asteroidL);
        }
    drawBox(&gameBox);
    moveAsteroid(&asteroidS);
    moveAsteroid(&asteroidL);

    drawShip(&ship);

    uart_clear();

    while (1) {
          // styring af skib
        char str[4]={""}; // denne SKAL deklares i main
        shipControls(str, &ship, &shot, &gameBox);

         // shotHandler(); -> ??


        if (moveShot(&shot,&gameBox,3)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.
            //detectAsteroid(&shot, &asteroidL);
        }
        if (shot.alive>0) {
            Gravity(&shot,&asteroidL);
        }

        // indfør evt. if Alive til tjek om collision
       detectCollisionSeagull(&ship,&seagull0);
        detectCollisionSeagull(&ship,&seagull1);
        detectCollisionSeagull(&ship,&seagull2);
        detectCollisionSeagull(&ship,&seagull3);
        detectCollsionShip(&shot,&ship);

        if(detectCollisionSeagull(&shot,&seagull0)==1){
            kill++;
        }

        if(detectCollisionSeagull(&shot,&seagull3)==1){
            kill++;
        }
        if(detectCollisionSeagull(&shot,&seagull1)==1){
            kill++;
        }

        if(detectCollisionSeagull(&shot,&seagull2)==1){
            kill++;
        }

        detectCollsionShip(&asteroidL,&ship);
        detectCollsionShip(&asteroidS,&ship);


        if(kill==0){
            if (updateSeagull1(10)==1){
                moveSeagull(&shot,&seagull0,&gameBox);
            }
        }
        if (kill>0){
                if (updateSeagull1(10)==1){
                    moveSeagull(&shot,&seagull1,&gameBox);
                    moveSeagull(&shot,&seagull2,&gameBox);
                }


             if (level>1){
                if (kill==1){
                    reviveSeagull(&seagull0,30,50,-1,1);
                }

                if(updateSeagull2(5)==1){
                    moveSeagull(&shot,&seagull0,&gameBox);
                    moveSeagull(&shot,&seagull3,&gameBox);
                }
            }

            if (level==3){
                    if (kill>=5){
                        if(kill==5){
                          reviveSeagull(&seagull0,50,30,-1,1);
                          reviveSeagull(&seagull1,30,50,-1,-1);
                          reviveSeagull(&seagull2,50,80,-1,1);
                          reviveSeagull(&seagull3,60,40,1,1);
                        }



                        if(updateSeagull2(1)==1){
                                moveSeagull(&shot,&seagull0,&gameBox);
                                moveSeagull(&shot,&seagull3,&gameBox);
                        }
                        if(updateSeagull1(2)==1){
                                moveSeagull(&shot,&seagull1,&gameBox);
                                moveSeagull(&shot,&seagull2,&gameBox);
                        }
                    }
            }
        }



    if (level==1){
        if (kill==3){
        clrscr();
        gotoxy(3,25);
        printf("You have passed level 1");
        for(int q=0; q<=1<<24;q++){
            }
        //press enter to continue
        won=1;
        break;
    }
    }

    if (level==2){
        if (kill==5){
        clrscr();
        gotoxy(3,25);
        printf("You have passed level 2");
        for(int q=0; q<=1<<24;q++){
            }
        won=1;
        break;
    }
    }

    if (level==3){
        if (kill==9){
        clrscr();
        gotoxy(3,25);
        printf("You have passed level 3 and have won the game");
        for(int q=0; q<=1<<24;q++){
            }
        won=0;
        break;
    }
    }




        // skibets hastighed sættes til nul igen skal gøres efter detectCollisions, ellers er der ingen pointe med collisions.
        ship.vx = 0;
        ship.vy = 0;
        if (ship.alive==0){
            clrscr();
            gotoxy(25,25);
            printf("U DEAD HA HA HA!\n");
            for(int q=0; q<=1<<24;q++){
            }
            kill=0;
            break;
        }

     } // enden af programmets whileloop




    }
    //Dette else hører til if statement i toppen.

    else{
        printf("You have quit the game\n");
        break;
    }
    continue;
}
*/
while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
