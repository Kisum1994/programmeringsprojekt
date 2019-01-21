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


#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // input/output library for this course
#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"
#include <string.h>




int16_t scale(const char * tone){
if(strcmp("A",tone)==0){
    return 440;
}
else if (strcmp("Ab",tone)==0){
    return 415;
}
else if (strcmp("G",tone)==0){
    return 392;
}
else if (strcmp("F#",tone)==0){
    return 367;
}
else if (strcmp("F",tone)==0){
    return 349;
}
else if (strcmp("E",tone)==0){
    return 329;
}
else if (strcmp("Eb",tone)==0){
    return 311;
}
else if (strcmp("D",tone)==0){
    return 294;
}
else if (strcmp("Db",tone)==0){
    return 277;
}
else if (strcmp("C",tone)==0){
    return 262;
}
else if (strcmp("B",tone)==0){
    return 247;
}
else if (strcmp("Bb",tone)==0){
    return 233;
}
}

const char * mario(int tone){
if(tone==1){
    return "E";
}
else if (tone==2){
    return "E";
}
else if (tone==3){
    return "E";
}
else if (tone==4){
    return "Bb";
}
else if (tone==5){
    return "E";
}
else if (tone==6){
    return "F#";
}
else if (tone==7){
    return "F#";
}
else if (tone==8){
    return "G";
}
else if (tone==9){
    return "C";
}
else if (tone==10){
    return "G";
}
else if (tone==11){
    return "E";
}
else if (tone==12){
    return "A";
}


}

int bossKey( char * text, struct velocityvector * seagull0, struct box gameBox, struct velocityvector * seagull1, struct velocityvector * seagull2, struct velocityvector * seagull3, struct velocityvector * ship, struct velocityvector * shot, struct velocityvector * asteroidS, struct velocityvector * asteroidL){

    if (arrowInput(text)==0x30){
    uart_clear();
    TIM15->CR1 |= 0x0000;
    clrscr();
    while(1){
        if(arrowInput(text)==0x30){
        TIM15->CR1 |= 0x0001;
        drawBox(gameBox);
        if(ship->alive==1){
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
        if(shot->alive==1){
        moveBall(shot);
        }
        }
    }
    }



}

int main(void) {
    uart_init( 9600 );
    clrscr();
    gotoxy(0,0);
    initTimer();
    TIM15->CR1 |= 0x0001; // Enable timer
    TIM1_BRK_TIM15_IRQHandler();
    uart_clear();

    struct box gameBox;
    struct velocityvector shot;
    struct velocityvector ship;
    struct velocityvector seagull;
    struct velocityvector asteroidS;
    struct velocityvector asteroidL;
    initObjects(&ship,&shot,&gameBox,&seagull,&asteroidS,&asteroidL);


    initBuzzer();
    int i=1;
    const char * m;
    int16_t s;
    while(1){
    if (getTime()==4)  {
    m=mario(i);
    s=scale(m);
    setFreq(s);
    i++;
    if(i==12)
        {i=1;
        }
    printf("%d",getS());
    }
    }


  while(1) {} // FJERN IKKE DETTE WHILE LOOP
}
