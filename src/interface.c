#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"
#include "interface.h"
/* This file contains all interface functions for the game */

//Ida
//Hovedmenuen for spillet
int menuMain(void){
    //printer menuen
    clrscr();
    int n=15;
    int x=5;
    gotoxy(x,n);
    printf("        Game menu");
    gotoxy(x+1,n);
    printf("------------------------------------------");

    gotoxy(x+3,n);
    printf("Start new game.");
    gotoxy(x+5,n);
    printf("Choose level.");
    gotoxy(x+7,n);
    printf("Get an introduction to the game.");
    gotoxy(x+9,n);
    printf("Exit game");

    //laver en place marker
    int px=x+3;
    int choice;
    gotoxy(px,n-2);
    printf("%c",219);

    // K�rer et hvile loop s� l�nge brugeren ikke har trykket p� enter
    while (1) {
        char str[4]={""};
        if (keyboardInput(str)>0) {
            //hvis input er pil ned skal cursoren g� til n�ste menu option.
            if (arrowInput(str)==0x20) {
                    px=px+2;
                    gotoxy(px-2,n-2);
                    printf("%c",' ');
            }
            if (px>x+10){// wrap around fra bunden
                    px=x+3;
            }

            //hvis input er pil op skal cursoren g� til overst�ende menu option.
            if (arrowInput(str)==0x10){
                    px=px-2;
                    gotoxy(px+2,n-2);
                    printf("%c",' ');
            }
            if (px<x+2){  //wrap around fra bunden
                    px=x+9;
            }
            //printer cursoren i den korrekte position
            gotoxy(px,n-2);
            printf("%c",219);

            //hvis brugeren trykker enter gemmes menuvalget i form af choice og while looped breakes
            if (arrowInput(str)==0x30){
                    if (px==x+3){
                            choice=1;
                            break;
                    }
                    if (px==x+5){
                            choice=2;
                            break;
                    }
                    if (px==x+7){
                            choice=3;
                            break;
                    }
                    if (px==x+9){
                            choice=4;
                            break;
                    }
            }
        }
    }
    // S�tter korrekte ting i gang ud fra v�rdi af choice
    if (choice==1){
            clrscr();
            gotoxy(x,n);
            printf("Starting Game\n");
            gotoxy(x,n);
            printf("%*c",13,' ');
            // g�r videre fra menuMain functionen
            //returnerer v�rdien 1, som derved initialiserer level 1 i main
            return 1;
    }
    if (choice==2){
            //g�r til menuen menuLevel og returnerer v�rdien af det level, der v�lges der
            return (menuLevel());

    }
    if (choice==3){
            printf("introduction\n");
            // k�rer en tutorial n�r v�rdien 4 returneres i main
            return 4;
    }
    if (choice==4){
            clrscr();
            gotoxy(x,n);
            printf("Ending game\n");
            gotoxy(x,n);
            printf("%*c",11,' ');
            return 0; // exit-> return 0; s� man ikke starter et spil
    }
    else return 0;
}

//Ida
// Level menu, hvor man kan starte spilet fra enten level 1,2 eller 3. Eller man kan v�lge at g� tilbage til hovedmenuen.
int menuLevel(void){
    clrscr();
    int n=15;
    int x=5;
    gotoxy(x,n);
    printf("        Level menu");
    gotoxy(x+1,n);
    printf("------------------------------------------");

    gotoxy(x+3,n);
    printf("Choose level 1");
    gotoxy(x+5,n);
    printf("Choose level 2");
    gotoxy(x+7,n);
    printf("Choose level 3");
    gotoxy(x+9,n);
    printf("Return to main menu");

    //place marker
    int choice=0;
    int px=x+3;
    gotoxy(px,n-2);
    printf("%c",219);

    // K�rer et hvile loop s� l�nge brugeren ikke har trykket p� enter
    while (1) {
        char str[4]={""};
        if (keyboardInput(str)>0) {
            //hvis input er pil ned skal cursoren g� til n�ste menu option.
            if (arrowInput(str)==0x20) {
                    px=px+2;
                    gotoxy(px-2,n-2);
                    printf("%c",' ');
            }
            if (px>x+9){
                    px=x+3;
            }

            //hvis input er pil op skal cursoren g� til n�ste menu option.
            if (arrowInput(str)==0x10){
                    px=px-2;
                    gotoxy(px+2,n-2);
                    printf("%c",' ');
            }
            if (px<x+3){
                    px=x+9;
            }
            gotoxy(px,n-2);
            printf("%c",219);
            //hvis brugeren trykker enter gemmes menuvalget i form af choice og while looped breakes
            if (arrowInput(str)==0x30){
                    if (px==x+3){
                            choice=1;
                            break;

                    }
                    if (px==x+5){
                            choice=2;
                           break;
                    }
                    if (px==x+7){
                            choice=3;
                            break;
                    }
                    if (px==x+9){
                            choice=4;
                            break;
                    }
            }
        }

    }
    if (choice==1){
            clrscr();
            gotoxy(x,n);
            printf("Level 1 initialising\n");
            //wait -> t�l til 4 000 000 i et for loop
            //returnerer 1 til menuMain, hvorefter v�rdien gemmes som level i main
            return 1;
    }
    if (choice==2){
            clrscr();
            gotoxy(x,n);
            printf("Level 2 initialising\n");
            //wait
            //returnerer 2 til menuMain, hvorefter v�rdien gemmes som level i main
            return 2;
    }
    if (choice==3){
            clrscr();
            gotoxy(x,n);
            printf("Level 3 initialising\n");
            //wait
            //returnerer 3 til menuMain, hvorefter v�rdien gemmes som level i main
            return 3;
    }
    else if (choice==4){
            clrscr();
            //viser hoved menuen igen.
            menuMain();
            return 0;
    }
    else return 0;
}

//Ida
// Viser tutorial tekst.
void tutorial(void){
    clrscr();
    int n=15;
    int x=0;
    gotoxy(x,n);
    printf("  _   _                 _                _             ");
    gotoxy(x+1,n);
    printf(" | | | | _____      __ | |_ ___    _ __ | | __ _ _   _ ");
    gotoxy(x+2,n);
    printf(" | |_| |/ _ \\ \\ /\\ / / | __/ _ \\  | '_ \\| |/ _` | | | |");
    gotoxy(x+3,n);
    printf(" |  _  | (_) \\ V  V /  | || (_) | | |_) | | (_| | |_| |");
    gotoxy(x+5,n);
    printf(" |_| |_|\\___/ \\_/\\_/    \\__\\___/  | .__/|_|\\__,_|\\__, |");
    gotoxy(x+6,n);
    printf("                                  |_|            |___/ ");

    gotoxy(x+10,n);
    printf("The goal of the game is to shoot the space seagulls, as the one seen below:");
    // m�ge position st�r
    gotoxy(x+15,n+25);
    printf("%c%c%c%c%c%c%c%c%c",' ',' ',47,92,' ',47,92,' ',' ');
    gotoxy(x+16,n+25);
    printf("%c%c%c%c%c%c%c%c%c",' ',35,' ',' ',153,' ',' ',35,' ');
    gotoxy(x+17,n+25);
    printf("%c%c%c%c%c%c%c%c%c",' ', 118,' ',' ',35,' ',' ',118,' ');

    gotoxy(x+20,n);
    printf("_______________________________________________________________");
    gotoxy(x+23,n);
    printf("To control the ship you use the arrows and space on the keyboard");

    gotoxy(x+25,n);
    printf("If the right arrow is pressed the ship rotates clockwise");
    gotoxy(x+27,n);
    printf("If the left arrow is pressed the ship rotates counter clockwise");
    gotoxy(x+29,n);
    printf("If the up arrow is pressed the ship moves forward");
    gotoxy(x+31,n);
    printf("If space is pressed the ship shoots");
}

//Jesper
//Aktiverer bossKey. Funktionen skal kende alle ting i spillet for at kunne tegne det igen
void bossKey(char * str,struct velocityvector * ship,
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
            struct velocityvector * powerUp2){
        // N�r der trykkes p� enter cleares sk�rmen og der printes et falsk arbejdsdokument p� sk�rmen.
        if (arrowInput(str)==0x30){
        // Stopper tiden
        TIM2->CR1 &= ~0x0001;
        clrscr();
        gotoxy(4,4);
        printf("\nC:/Dokumenter/HardAtWork.doc");
        gotoxy(6,4);
        printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n\nInteger nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi.\nNulla quis sem at nibh elementum imperdiet.\n\nDuis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta.\nMauris massa. Vestibulum lacinia arcu eget nulla\nClass aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.\nCurabitur sodales ligula in libero.\n\nSed dignissim lacinia nunc.\n ");
        strcpy(str,"");
        // while loop der forts�tter indtil der trykkes enter igen
        //Alle inputs som var levende f�r bossKey blev trykket aktiveres
        while(1){
            if(keyboardInput(str)>0) {
                if(arrowInput(str)==0x30){
                    clrscr();
                    //Starter tiden igen
                    TIM2->CR1 |= 0x0001;
                    drawBox(gameBox);
                    //tjekker hvad der er levende og tegner det igen.
                    if(ship->alive>0){
                        drawShip(ship);
                    }
                    if (seagull0->alive==1){
                        drawSeagull(seagull0);
                    }
                    if (seagull1->alive==1){
                        drawSeagull(seagull1);
                    }
                    if (seagull2->alive==1){
                        drawSeagull(seagull2);
                    }
                    if (seagull3->alive==1){
                        drawSeagull(seagull3);
                    }
                    if (asteroidS->alive==1){
                        drawAsteroid(asteroidS);
                    }
                    if (asteroidL->alive==1){
                        drawAsteroid(asteroidL);
                    }
                    if(shot0->alive==1){
                        moveShot(shot0,gameBox,asteroidL,asteroidS);
                    }
                    if(shot1->alive==1){
                        moveShot(shot1,gameBox,asteroidL,asteroidS);
                    }
                    if(shot2->alive==1){
                        moveShot(shot2,gameBox,asteroidL,asteroidS);
                    }
                    if (powerUp0->alive==1) {
                        drawPowerUp(powerUp0);
                    }
                    if (powerUp1->alive==1) {
                        drawPowerUp(powerUp2);
                    }
                    if (powerUp2->alive==1){
                        drawPowerUp(powerUp2);
                    }
                    break;
                }
            }
        }
    }
}

//Jakob og Jesper
// Beregner scoren i l�bet af spillet.
void scoreCount(int kill,int16_t * scoreTemp) {
   //En static int til at gemme den gamle v�rdi af kill.
   static int killOld;
   //Der l�gges score til hvis der foretages et kill
   if(killOld!=kill) {
        // Scoren afh�nger af hurtighed.
        if((getS()+getM()*60)<200) {
            *scoreTemp+=(200-(getS()+getM()*60));
        }
        killOld=kill;
   }
}

//Jakob
//Tegner en startsk�rm
void splashScreen(void) { // Husk at �ndre puttys vindue til 175 "columns" og 70 "rows" i /change settings->window, checkmark "change the size of the font".

    int n=40;
    gotoxy(20,1);
    printf("%*c _______\n",n,' ');
    printf("%*c|   _   .-----.---.-.----.-----. \n",n,' ');
    printf("%*c|   1___|  _  |  _  |  __|  -__| \n",n,' ');
    printf("%*c|____   |   __|___._|____|_____| \n",n,' ');
    printf("%*c|:  1   |__|  \n",n,' ');
    printf("%*c|::.. . |  \n",n,' ');
    printf("%*c`-------' \n",n,' ');
    printf("%*c _______       __ __\n",n,' ');
    printf("%*c|   _   .--.--|  |  .-----. \n",n,' ');
    printf("%*c|.  |___|  |  |  |  |__ --| \n",n,' ');
    printf("%*c|.  |   |_____|__|__|_____| \n",n,' ');
    printf("%*c|:  1   |         .--.--.-----. \n",n,' ');
    printf("%*c|::.. . |         |  |  |__ --|_  \n",n,' ');
    printf("%*c`-------'          \\___/|_____|__| \n",n,' ');
    printf("%*c  _______ __    __              \n",n,' ');
    printf("%*c |   _   |  |--|__.-----.-----. \n",n,' ');
    printf("%*c |   1___|     |  |  _  |__ --| \n",n,' ');
    printf("%*c |____   |__|__|__|   __|_____| \n",n,' ');
    printf("%*c |:  1   |        |__|          \n",n,' ');
    printf("%*c |::.. . | \n",n,' ');
    printf("%*c `-------' \n",n,' ');

    gotoxy(60,45);
    printf("\e[5m");
    printf("Press 'Enter' to start!");
    printf("\e[25m");
    //Venter p� at brugeren trykker Enter
     while (1) {
        char str[4]={""};
        keyboardInput(str);
         if (arrowInput(str)==0x30){
                 break;
         }
     }
}
