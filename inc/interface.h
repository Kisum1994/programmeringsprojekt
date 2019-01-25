
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdio.h>
#include <stdio.h>



int menuMain(void);
int menuLevel(void);
void tutorial(void);
void splashScreen(void);

void scoreCount(int kill,int16_t * scoreTemp);

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
            struct velocityvector * powerUp2);

#endif
