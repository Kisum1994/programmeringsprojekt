#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"
#include "interface.h"
/* This file contains all interface functions for the game */

int menuMain(){
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
    /*printf(" Please choose an option from the main menu: ");*/

    //place marker
    int px=x+3;
    int choice;
    gotoxy(px,n-2);
    printf("%c",219);

    while (1) {
        char str[4]={""};
        if (keyboardInput(str)>0) {
            if (arrowInput(str)==0x20) {
                    px=px+2;
                    gotoxy(px-2,n-2);
                    printf("%c",' ');
            }
            if (px>x+10){// wrap around fra bunden
                    px=x+3;
            }


            if (arrowInput(str)==0x10){
                    px=px-2;
                    gotoxy(px+2,n-2);
                    printf("%c",' ');
            }
            if (px<x+2){  //wrap around fra bunden
                    px=x+9;
            }
            gotoxy(px,n-2);
            printf("%c",219);

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
            printf("Starting Game\n");
            gotoxy(x,n);
            printf("%*c",13,' ');
            // går videre fra menuMain functionen
            return 1;
    }
    if (choice==2){
            return (menuLevel()); //går til choose level menu

    }
    if (choice==3){
            printf("introduction\n");
            // køre en tutorial??
            return 4;
    }
    if (choice==4){
            clrscr();
            gotoxy(x,n);
            printf("Ending game\n");
            gotoxy(x,n);
            printf("%*c",11,' ');
            return 0; // exit-> return 0; så man ikke starter et spil
    }
}


int menuLevel(){
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
    int level=0;
    int px=x+3;
    gotoxy(px,n-2);
    printf("%c",219);

    while (1) {
        char str[4]={""};
        if (keyboardInput(str)>0) {
            if (arrowInput(str)==0x20) {
                    px=px+2;
                    gotoxy(px-2,n-2);
                    printf("%c",' ');
            }
            if (px>x+9){
                    px=x+3;
            }


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
            //wait -> tæl til 4 000 000 i et for loop
            return 1;
        }
        if (choice==2){
            clrscr();
            gotoxy(x,n);
            printf("Level 2 initialising\n");
            //wait
            return 2;
        }
        if (choice==3){
            clrscr();
            gotoxy(x,n);
            printf("Level 3 initialising\n");
            //wait
            return 3;
        }
        else if (choice==4){
            clrscr();
            menuMain();
        }
}

void tutorial(){
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
    // måge position står
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

int bossKey(char * str, //bossKey skal kende alt for at kunne tegne det igen
            struct velocityvector * ship,
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
        if (arrowInput(str)==0x30){

        TIM2->CR1 &= ~0x0001;
        clrscr();
        gotoxy(0,0);
        printf("\nC:/Dokumenter/HardAtWork.doc\n\n");
        printf("Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n\nInteger nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi.\nNulla quis sem at nibh elementum imperdiet.\n\nDuis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta.\nMauris massa. Vestibulum lacinia arcu eget nulla\nClass aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.\nCurabitur sodales ligula in libero.\n\nSed dignissim lacinia nunc.\n ");
        strcpy(str,"");
        while(1){
            if(keyboardInput(str)>0) {
                if(arrowInput(str)==0x30){
                    clrscr();
                    TIM2->CR1 |= 0x0001;
                    drawBox(gameBox);
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
                        moveShot(shot0);
                    }
                    if(shot1->alive==1){
                        moveShot(shot1);
                    }
                    if(shot2->alive==1){
                        moveShot(shot2);
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


void scoreCount(int kill,int16_t * scoreTemp) {
   static int killOld;
   if(killOld!=kill) {
       *scoreTemp+=50* ((1<<20/((getS()+getM()*60))));
       killOld=kill;
   }
}

void splashScreen() { // ændr puttys vindue til 175 "columns" og 70 "rows" i /change settings->window, checkmark "change the size of the font".
   /* printf("                                                                                                                                                         .., ,,,,:::, .......\n");
    printf("                                                                                                                                                      ..,,:: ,................\n");
    printf("                                                                                                                                               ..  ,,,,,,,,,,:,, .  .:,....\n");
    printf("                                                                                                                                           ..  ,,,,,,:::cccclllll:. .  ...\n");
    printf("                                                                                                                                    ..  ,,,,::::::::::::cccllc  . ...    \n");
    printf("                                                                                                                                    ...  ,,,::::::::,,,,,,,::cccl:......\n");
    printf("                                                                                                                                 ..  ,,,::::::,,,     ,,::,,:ccc:.....\n");
    printf("                                                                                                                              ..  ,,,:::,,  ........... ,:,::cc: ....\n");
    printf("                                                                                                                              .,,,::,, .......   .......,:::cc:.....\n");
    printf("                                                                                                                              . ,  .....           .... ,::cc,....\n");
    printf("                                                                                     .......................                   ....                ... ,::c: ....\n");
    printf("                                                                                ...............    ...............                                ... ,:c:,....\n");
    printf("                                                                           ............     ,,,,,,,,      ............                           ... ::c: ...\n");
    printf("                                                                        ........     ,,,,,:::::::::,         ............                       .. ,:c:,....\n");
    printf("                                                                      ......  ,,,,,,:::::::cccc:::,,,,,,,,           ......                    .. :::: ...\n");
    printf("                                                                   .....  ,,::::::::::::cclllc::::::,,:,,,,,,,,  ,,,  .......                .. ,::: ...\n");
    printf("                                                                .....  ,:::::::::::cccclooolc::::::::::,,,,,,,,,:,,,      .....             ..,:::, ..\n");
    printf("                                                              ....  ,:::::::::ccccclloddolc::::::::::::::::::::::,,,,,,,,  ......         ..,:::, ..\n");
    printf("                                                            .... ,:::::::::ccccclloddddoc:::::::::::::::::::::::,,,,,,,,,,  ......      ..,:::, ..\n");
    printf("                                                          .... ,::::::ccccclllloddxxdolc::c::::::::::::::::::::,,,,::::,,,   .....    .. :::, ..\n");
    printf("                                                        ...  ,::::::cccllllloodxxxdolcccccccc::::::::::::::::,,,::::::,,,,,   ...   ..,:::, ..\n");
    printf("                                                      ... ,,:::::cccllllloodxxxxdolccccccccccc::ccc::cc:::::::::::::::,,,,,, ..   ..,:::, ..\n");
    printf("                                                     ..  ,::::cccllllloodxxkxxdllccccclccccccccccccccc:::::::::cc::::::,,,,...  ..,:::: ..\n");
    printf("                                                    .. ,::::ccllllloodxxkkxdolllllllllcccccccccccccc::::::::cccc:::::::,, .. ...,:ccc:,.\n");
    printf("                                                   ..,:::ccllllloodxxkkkxdollllllllllccccccccccccc:::::::ccllcc:::::::, .. .. ::cllc:,.\n");
    printf("                                                  . :::clllllooddxxxkxdolllllllllllllccccllllcc::::::::ccllccc::::::: .. .. :cclcc::, .\n");
    printf("                                                 . ::cclllooddxxxxddooollllllllllllllllclllcc::::::::cllllcccccc::: .....,:cllc::::::,.\n");
    printf("                                                 .,:ccllodddxxdddoodoooolllllllllllllllllc::::::::clllllccccccc:: .....,:cllc:::cclc:,..\n");
    printf("                                               . :cllooddddoollooodoooollllllllllllllcc::::::cclllolllcccccc:: .... ::lllc:::coooll:,..\n");
    printf("                                                .:cllooooollllllooooolllllllooolllllc:::::::cllooollllllccc:,..... ::lllc:::lodddooc:,.\n");
    printf("                                                .:ccllllllllllllloollllllllooooolcc::::::cllooollllllllcc: .....,:clllc::cloddxddollc:.\n");
    printf("                                                 :cccllllllllllllllllooooooooolc:::::cclloooollllllllc:: .... ,:cllc:::clddxxxdddoolc,.\n");
    printf("                                                 :ccllllllllllllllooooooooolc::::::cllooooolllllllcc:,..... ::lllc:::codxxxxxdddddol: .\n");
    printf("                                                 :ccccllcccllllloooooooolcc::::ccllooooollooolllc:,..... ,:cllc::::lodxxkkxxxxxxxdoc:.\n");
    printf("                                                .::ccccccclllllloooollc:::::ccllooooooolooollc: ......,:ccllc:::cldxxkkkkxxxxxxxdol: .\n");
    printf("                                                .::cccclllllllooollc::::ccclloooooolooooolc:,...... ,:cllc::::lodxkkkkkkxxkkkkxdolc,.\n");
    printf("                                                .:ccclllllooollcc::::ccclloooooolloooollc:...... ,:cllc::::codxkkkOOkkkkkkkkkxdolc:.\n");
    printf("                                              .. :cllllooollcc:::cccllooooooolllooollc: ..... ::ccllc:::cloxkkkOOOkkkkkkOkkkxdooc:.\n");
    printf("                                            ... ,:cllllllcc::ccclloooooooolloollllc: .. .. ,:clllc:::clodxkOOOOOOkkOOOOkkkxxddoc,.\n");
    printf("                                          ... ,:, ,:cccccccclloooddooollllllollc: .. ...,:clllc::::lodxkOOOOOOOkkOOOOOkkxxxdol: .\n");
    printf("                                        ... ,:, .. .:lllloooodoooollllllllllc: .. ... ::lllc:::clodxkOO00OOOOOOOOOOOkkxxxxdoc,.\n");
    printf("                                      ... ,:, ..    .:loooooolllllllllllc:, .. ... ::cllc:::codxkkOO0000OOOOOOOOOOkkxxxxdoc:..\n");
    printf("                                    ... ::: ..       .,cllccccccccccc::,... ... ::cllcccccodxkOOO00000OOOO0000OOOkkkkxxoc:..\n");
    printf("                                  ... ,::,...          .:::ccccc:::, ..  ... ::cllcc:clodxkOOO00000OOO000000OOkkkkkkxoc:..\n");
    printf("                                ... ,::, ..             . ::::, ...   ... ,:cllcccccodxkOO00000OOO00000000Okkkkkkxdo:,..\n");
    printf("                              ....,::, ..                 ....     ... ::cclcccclodxkOO0000OOOOOO000000OOkkkkkxxoc: ..\n");
    printf("                             ...,::, ...                        ... ::cclccccldxkkOOO000OOOOOO00000OOOOOkkkkxdl:,..\n");
    printf("                           ... :::, ...                      ... ,:cclccclodxkkOOOOOOOOOOOOOOOOOOOOkkkkkkxdl:,..\n");
    printf("                         ....,:::, ...                   ... ,::,,::::cldxkkOOOOkOOkOOOOOOOOOOkkkkkkkxxol: ..\n");
    printf("                       .... ::,,, ...                ...  ,::,,, ... . :codxxxkkkkkkkkOOOkkkkkxxxxdol:,..\n");
    printf("                      ....,::,,, ....           ..... ,:::,,, ...        .. ,::clloooooooollcc:,, ..\n");
    printf("                    .....,:::,, ................. ,,:::,,  ...                    .........\n");
    printf("                   .....::::,,, ...........  ,,::::,,,  ..\n");
    printf("                  .....:::::,,:,,       ,,:::::,,,,  ..\n");
    printf("                 .....:c::::,,,,,,, ,,:::::,,,,  ...\n");
    printf("                ....  :cc::::::,,,,:::::,,,   ..\n");
    printf("               .. .. .:ccc:::::::,,,,,    ...\n");
    printf("              ..., .  .  ,,,          ...\n");
    printf("             ....,:, .....    ,  ...\n");
    printf("             ..... ,,,,,,,,  ...\n");
    printf("             ..............\n");
    printf("               ..\n");
 */
    int n=40;
    gotoxy(20,1);
    printf("%*c _______\n",n);
    printf("%*c|   _   .-----.---.-.----.-----. \n",n);
    printf("%*c|   1___|  _  |  _  |  __|  -__| \n",n);
    printf("%*c|____   |   __|___._|____|_____| \n",n);
    printf("%*c|:  1   |__|  \n",n);
    printf("%*c|::.. . |  \n",n);
    printf("%*c`-------' \n",n);
    printf("%*c _______       __ __\n",n);
    printf("%*c|   _   .--.--|  |  .-----. \n",n);
    printf("%*c|.  |___|  |  |  |  |__ --| \n",n);
    printf("%*c|.  |   |_____|__|__|_____| \n",n);
    printf("%*c|:  1   |         .--.--.-----. \n",n);
    printf("%*c|::.. . |         |  |  |__ --|_  \n",n);
    printf("%*c`-------'          \\___/|_____|__| \n",n);
    printf("%*c  _______ __    __              \n",n);
    printf("%*c |   _   |  |--|__.-----.-----. \n",n);
    printf("%*c |   1___|     |  |  _  |__ --| \n",n);
    printf("%*c |____   |__|__|__|   __|_____| \n",n);
    printf("%*c |:  1   |        |__|          \n",n);
    printf("%*c |::.. . | \n",n);
    printf("%*c `-------' \n",n);

    gotoxy(60,45);
    printf("\e[5m");
    printf("Press 'Enter' to start!");
    printf("\e[25m");
     while (1) {
        char str[4]={""};
        keyboardInput(str);
         if (arrowInput(str)==0x30){
                 break;
         }
     }
}
