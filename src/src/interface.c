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
        keyboardInput(str);
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
    if (choice==1){
            clrscr();
            gotoxy(x,n);
            printf("Starting Game\n");
            gotoxy(x,n);
            printf("%*c",13,' ');
            // g�r videre fra menuMain functionen
            return 1;
    }
    if (choice==2){
            return (menuLevel()); //g�r til choose level menu

    }
    if (choice==3){
            printf("introduction\n");
            // k�re en tutorial??
            return 1;
    }
    if (choice==4){
            clrscr();
            gotoxy(x,n);
            printf("Ending game\n");
            gotoxy(x,n);
            printf("%*c",11,' ');
            return 0; // exit flag s� man ikke starter et spil
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
        keyboardInput(str);
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
        if (choice==1){
                clrscr();
                gotoxy(x,n);
                printf("Level 1 initialising\n");

                gotoxy(x,n);
                printf("%*c",19, ' ');
                return 1;
        }
        if (choice==2){
                clrscr();
                gotoxy(x,n);
                printf("Level 2 initialising\n");
                gotoxy(x,n);
                printf("%*c",19, ' ');
                return 2;
        }
        if (choice==3){
                clrscr();
                gotoxy(x,n);
                printf("Level 3 initialising\n");
                gotoxy(x,n);
                printf("%*c",19, ' ');
                return 3;
        }
        else if (choice==4){
                clrscr();
                menuMain();
        }
    }

void splashScreen() { // �ndr puttys vindue til 175 "columns" og 70 "rows" i /change settings->window, checkmark "change the size of the font".
    printf("                                                                                                                                                         .., ,,,,:::, .......\n");
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

    int n=30;
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
    printf("%*c`-------'          \___/|_____|__| \n",n);
    printf("%*c  _______ __    __              \n",n);
    printf("%*c |   _   |  |--|__.-----.-----. \n",n);
    printf("%*c |   1___|     |  |  _  |__ --| \n",n);
    printf("%*c |____   |__|__|__|   __|_____| \n",n);
    printf("%*c |:  1   |        |__|          \n",n);
    printf("%*c |::.. . | \n",n);
    printf("%*c `-------' \n",n);

    gotoxy(60,75);
    printf("Press 'Enter' to start!");
     while (1) {
        char str[4]={""};
        keyboardInput(str);
         if (arrowInput(str)==0x30){
                 break;
         }
     }
}
