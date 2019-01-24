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
    uart_clear();
    clrscr();
    gotoxy(0,0);

    //init ur
    initTimer();

    TIM1_BRK_TIM15_IRQHandler();

    // init structs, deres værdier bliver skrevet i initObjects(); - denne findes i objects.c

    struct box gameBox;
    struct velocityvector shot0;
    struct velocityvector shot1;
    struct velocityvector shot2;
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



    int rgb[3]; // lysinfo til powerUps!
    rgb[0]=1;
    rgb[1]=0;
    rgb[2]=0;

    initLED();
    setLED(rgb);
    lcd_init();

    printf("\e[?25l"); // gør cursor usynlig
/*
     drawBox(&gameBox);
        moveAsteroid(&asteroidS);
        moveAsteroid(&asteroidL);

        drawShip(&ship);

        drawPowerUp(&powerUp0);
 */
    printf("BETA stage: Everything you see is subject to change.\n");


    // HER BEGYNDER IDAS MAINS SCRIPT!!

    TIM15->CR1 = 0x0001; //  <-- start timer 15
    //Viser splash screen og derefter main menu
    splashScreen();




    int16_t score=0;
    int16_t scoreWon=0;

    int won=0;
    int level=0;
    int kill;
while (1) {
    if (won == 0 || level>=3){
        level=menuMain();
        score=0;
    }
    if (level==4){
        while(1){
            tutorial();
            initTutorial(&ship,&shot0,&gameBox);
            drawBox(&gameBox);
            drawShip(&ship);
            int turn=0, moved=0, shotFired=0;
            gotoxy(64,15);
            printf("Now try to turn the ship!\n");

            while(turn<7){
                char str0[4]={""};
                if(shipControlsTutorialTurn(str0,&ship)==1){
                    turn++;
                }
            }
            gotoxy(64,15);
            printf("You have succesfully turned the ship.\n");
            gotoxy(66,15);
            printf("Now try to move the ship!\n");

            while(moved<4){
                char str1[4]={""};
                if(shipControlsTutorialMove(str1,&ship)==1){
                    moveShip(&ship,&gameBox);
                    moved++;
                }
            }
            gotoxy(66,15);
            printf("You have succesfully moved the ship.\n");
            gotoxy(68,15);
            printf("Now try to shoot the ship!\n");

            while(shotFired<3){
                char str2[4]={""};
                if(shipControlsTutorialShoot(str2,&ship,&shot0)==1){
                    shotFired++;
                }
                moveShot(&shot0,&gameBox,3);
                drawShip(&ship);
            }
            gotoxy(68,15);
            printf("You have completed the tutorial\n");
            for(int q=0; q<=1<<24;q++){
                    //"wait-funktion"
            }
            break;
        }
        continue;
        }

        if (won==1){
            level++;
            scoreWon=score;
            won=0;
        }

    // HER STARTER EGENTLIGE LEVELS

    if (level >0){  //reset ting her tak.
         initObjects(&ship,
                &shot0,&shot1,&shot2,
                &gameBox,
                &seagull0,&seagull1,&seagull2,&seagull3,
                &asteroidS,&asteroidL,
                &powerUp0,&powerUp1,&powerUp2);
        resetWatch();
        score=scoreWon;

        kill=0;
        clrscr();

        if (level==1){
            initLevel1(&ship,
                &shot0,&shot1,&shot2,
                &gameBox,
                &seagull0,&seagull1,&seagull2,&seagull3,
                &asteroidS,&asteroidL,
                &powerUp0,&powerUp1,&powerUp2);
        }
        else if (level==2){
            initLevel2(&ship,
                &shot0,&shot1,&shot2,
                &gameBox,
                &seagull0,&seagull1,&seagull2,&seagull3,
                &asteroidS,&asteroidL,
                &powerUp0,&powerUp1,&powerUp2);
        }
        else if (level==3){
            initLevel3(&ship,
                &shot0,&shot1,&shot2,
                &gameBox,
                &seagull0,&seagull1,&seagull2,&seagull3,
                &asteroidS,&asteroidL,
                &powerUp0,&powerUp1,&powerUp2);
        }
        drawBox(&gameBox);
        drawAsteroid(&asteroidS);
        drawAsteroid(&asteroidL);
        drawShip(&ship);
        uart_clear();

        // PHYSICS UPDATER STARTER HER
        while (1) {
          // STYRING AF SKIB SAMT BOSSKEY
            char text[4]={""};  // denne SKAL deklares i main
            if(keyboardInput(text)>0) {
                shipControls(text,
                             &ship,
                             &shot0,
                             &shot1,
                             &shot2,
                             &gameBox,
                             &powerUp0,
                             &powerUp1,
                             &powerUp2);
                bossKey(text,&ship,
                    &shot0,&shot1,&shot2,
                    &gameBox,
                    &seagull0,&seagull1,&seagull2,&seagull3,
                    &asteroidS,&asteroidL,
                    &powerUp0,&powerUp1,&powerUp2);
            }
            if(keyboardInput(text)==0) {
                ship.enabled=0;
            }
            moveShip(&ship,&gameBox);

            // Beregner og skriver score til Display
            scoreCount(kill,&score);
            char *lcdStrScore[24];
            if (ship.alive==3){
                sprintf(lcdStrScore,"SCORE: %04d               HEALTH: <3 <3 <3 ",score);
            }
            else if (ship.alive==2){
                sprintf(lcdStrScore,"SCORE: %04d               HEALTH: <3 <3 ",score);
            }
            else if (ship.alive==1){
                sprintf(lcdStrScore,"SCORE: %04d               HEALTH: <3",score);
            }
            else {
                sprintf(lcdStrScore,"SCORE: %04d               HEALTH: ",score);
            }
            int8_t buffer[512];
            memset(buffer,0x00,512);


            lcd_write_string(buffer,lcdStrScore,20);
            lcd_push_buffer(buffer);





            //POWERUP ENABLES

            enablePowerUp(&ship,&powerUp0,rgb);

            // HANDLE AF SKUD


            if(updateShot0(3)==1){
                if (moveShot(&shot0,&gameBox,&asteroidL,&asteroidS)==1) { // move tjekker om skud er i live!
            // herinde er ting der skal ske samtidig med skudets bevægelse.

                    Gravity(&shot0,&asteroidL);
                    Gravity(&shot0,&asteroidS);
                }
            }
            if(updateShot1(3)==1){
                if (moveShot(&shot1,&gameBox,&asteroidL,&asteroidS)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.

                    Gravity(&shot1,&asteroidL);
                    Gravity(&shot1,&asteroidS);
                }
            }
            if(updateShot2(3)==1){
                if (moveShot(&shot2,&gameBox,&asteroidL,&asteroidS)==1) {
            // herinde er ting der skal ske samtidig med skudets bevægelse.

                    Gravity(&shot2,&asteroidL);
                    Gravity(&shot2,&asteroidS);
                }


            }



        // ------------------COLLISION DETECTION--------------------

            //man kan skyde måger og tælle sine kills!
            if(    detectCollisionSeagull(&shot0,&seagull0)==1
                || detectCollisionSeagull(&shot0,&seagull1)==1
                || detectCollisionSeagull(&shot0,&seagull2)==1
                || detectCollisionSeagull(&shot0,&seagull3)==1
                || detectCollisionSeagull(&shot1,&seagull0)==1
                || detectCollisionSeagull(&shot1,&seagull1)==1
                || detectCollisionSeagull(&shot1,&seagull2)==1
                || detectCollisionSeagull(&shot1,&seagull3)==1
                || detectCollisionSeagull(&shot2,&seagull0)==1
                || detectCollisionSeagull(&shot2,&seagull1)==1
                || detectCollisionSeagull(&shot2,&seagull2)==1
                || detectCollisionSeagull(&shot2,&seagull3)==1){
                kill++;
            }

            // Skud kan bounce på asteroider
            detectAsteroid(&shot0, &asteroidL);
            detectAsteroid(&shot0, &asteroidS);

            detectAsteroid(&shot1, &asteroidL);
            detectAsteroid(&shot1, &asteroidS);

            detectAsteroid(&shot2, &asteroidL);
            detectAsteroid(&shot2, &asteroidS);


            //man kan skyde sig selv #selvmord
            detectCollsionShip(&shot0,&ship);
            detectCollsionShip(&shot1,&ship);
            detectCollsionShip(&shot2,&ship);


            //man kan flyve ind i asteroider! avs!
            detectCollsionShip(&asteroidS,&ship);
            detectCollsionShip(&asteroidL,&ship);


            //måger kan æde en                    EVT. et tjek om måger levende
            detectCollsionShip(&seagull0,&ship);
            detectCollsionShip(&seagull1,&ship);
            detectCollsionShip(&seagull2,&ship);
            detectCollsionShip(&seagull3,&ship);



    //  ---------------------------------------------------


            // HER STARTER EGENTLIG SCRIPT AF LEVELS

            if(kill==0){
                if (updateSeagull1(10)==1){
                    moveSeagull(&seagull0,&gameBox,&asteroidL,&asteroidS);
                }
            }
            if (kill>0){
                if (kill==1){
                        reviveSeagull(&seagull1,60,10,-1,1);
                        reviveSeagull(&seagull2,10,110,1,-1);
                }
                if (updateSeagull1(10)==1){
                    moveSeagull(&seagull1,&gameBox,&asteroidL,&asteroidS);
                    moveSeagull(&seagull2,&gameBox,&asteroidL,&asteroidS);
                }


                if (level>1){
                    if (getS()==15 && powerUp0.alive==0) {
                            powerUp0.alive=1;
                            drawPowerUp(&powerUp0);
                    }

                    if (kill==1){
                        reviveSeagull(&seagull0,30,40,-1,1);
                        reviveSeagull(&seagull3,60,110,-1,-1);
                    }
                    if(updateSeagull2(5)==1){
                        moveSeagull(&seagull0,&gameBox,&asteroidL,&asteroidS);
                        moveSeagull(&seagull3,&gameBox,&asteroidL,&asteroidS);
                    }
                }
                if (level==3){
                    if (kill>=5){
                        if(kill==5){
                            reviveSeagull(&seagull0,50,60,-1,1);
                            reviveSeagull(&seagull1,10,50,-1,-1);
                            reviveSeagull(&seagull2,45,80,-1,1);
                            reviveSeagull(&seagull3,60,40,1,1);
                        }
                        if(updateSeagull2(1)==1){
                                moveSeagull(&seagull0,&gameBox,&asteroidL,&asteroidS);
                                moveSeagull(&seagull3,&gameBox,&asteroidL,&asteroidS);
                        }
                        if(updateSeagull1(2)==1){
                                moveSeagull(&seagull1,&gameBox,&asteroidL,&asteroidS);
                                moveSeagull(&seagull2,&gameBox,&asteroidL,&asteroidS);
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
                            //press enter to continue istedet for "wait"-for loop?
                    }
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
                            //press enter to continue istedet for "wait"-for loop?
                    }
                    won=1;
                    break;
                }
            }
            if (level==3){
                if (kill==9){
                    clrscr();
                    gotoxy(40,45);
                    printf("You have passed level 3 and have won the game");
                    gotoxy(42,45);
                    printf("Total Score %d",score);
                    for(int q=0; q<=1<<23;q++){
                    }
                    gotoxy(44,45);
                    printf("Press 'Space' or 'Enter' to continue",score);
                    uart_clear();
                    while(keyboardInput(text)==0){}

                    won=0;
                    break;
                }
            }
            if (ship.alive==0){
                clrscr();
                gotoxy(40,45);
                printf("U DEAD HA HA HA!");
                gotoxy(42,45);
                printf("Total Score: %d",score);
                    for(int q=0; q<=1<<23;q++){
                    }
                    gotoxy(44,45);
                    printf("Press 'Space' or 'Enter' to continue",score);
                    uart_clear();
                    while(keyboardInput(text)==0){}
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




  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
