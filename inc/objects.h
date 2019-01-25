#ifndef _OBJECTS_H_
#define _OBJECTS_H_


#include <stdio.h>

// initStructs funktionerne

   //STRUCT-TYPER
struct velocityvector{
        int32_t x;
        int32_t y;
        int32_t vx;
        int32_t vy;
        int ang;
        int alive;
        int ani;
        int width;
        int height;
        int G;
        int time;
        int impulseX;
        int impulseY;
        int enabled;


};

struct box{
        int x1;
        int x2;
        int y1;
        int y2;
        char title[40];
        int style;
};

   // FUNKTIONER

void death(struct velocityvector * deadObject);
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
                 struct velocityvector * powerUp2);

void initTutorial(struct velocityvector * ship,
                 struct velocityvector * shot0,
                 struct box * gameBox);

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
                 struct velocityvector * powerUp2);

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
                 struct velocityvector * powerUp2);

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
                 struct velocityvector * powerUp2);

void reviveSeagull(struct velocityvector * seagull,int x, int y, int vx, int vy);

void shipControls(char * str,struct velocityvector * ship,struct velocityvector * shot0,struct velocityvector * shot1,struct velocityvector * shot2, struct box * gameBox, struct velocityvector * powerUp0, struct velocityvector * powerUp1 , struct velocityvector * powerUp2);
int shipControlsTutorialTurn(char * str,struct velocityvector * ship);
int shipControlsTutorialMove(char * str,struct velocityvector * ship);
int shipControlsTutorialShoot(char * str,struct velocityvector * ship,struct velocityvector * shot);
void moveShip(struct velocityvector * ship,struct box * gameBox);

void updateVelocityVector(struct  velocityvector * velovector);


int moveShot(struct velocityvector * shot,struct box * gameBox,struct velocityvector * asteroidL,struct velocityvector * asteroidS);
void moveSeagull(struct velocityvector * seagull, struct box * gameBox,struct velocityvector * asteroidL,struct velocityvector * asteroidS,struct velocityvector *powerUp);

int detectBarrier( struct box * gameBox, struct velocityvector * velovector);
int detectAsteroid(struct velocityvector * velovector,struct velocityvector * asteroid);

void shoot(struct velocityvector * shot,struct velocityvector * ship);


int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2);
int detectCollsionShip( struct velocityvector * obj1,struct velocityvector * ship);
int detectCollsionAsteroid( struct velocityvector * obj1,struct velocityvector * asteroid);

void Gravity(struct velocityvector * shot, struct velocityvector * asteroid);


void drawBox(struct box * gameBox);

void drawShip(struct velocityvector * ship);
void cleanShip(struct velocityvector * ship);

void drawAsteroid(struct velocityvector * asteroid);
void cleanAsteroid(struct velocityvector * asteroid);

void drawSeagull(struct velocityvector * seagull);
void cleanSeagull(struct velocityvector * seagull);

void drawPowerUp(struct velocityvector * powerUp);
int enablePowerUp(struct velocityvector * ship, struct velocityvector * powerUp, int rgb[3]);




#endif
