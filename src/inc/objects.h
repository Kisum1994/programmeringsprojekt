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
void initObjects(struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox, struct velocityvector * seagull0,struct velocityvector * seagull1,struct velocityvector * seagull2,struct velocityvector * seagull3,struct velocityvector * asteroidS, struct velocityvector * asteroidL);

void shipControls(char * str,struct velocityvector * ship,struct velocityvector * shot,struct box * gameBox);
void updateVelocityVector(struct  velocityvector * velovector);
int moveShot(struct velocityvector * shot,struct box * gameBox, int speed);
int detectBarrier( struct box * gameBox, struct velocityvector * velovector);
void shoot(struct velocityvector * shot,struct velocityvector * ship);
int detectCollision(struct velocityvector * obj1,struct velocityvector * obj2);
int detectCollsionShip( struct velocityvector * obj1,struct velocityvector * ship);

void drawBox(struct box * gameBox);
void drawShip(struct velocityvector * ship);
void cleanShip(); //TOM FUNKTOIN skal laves
void drawAsteroid(struct velocityvector * asteroid);
void cleanAsteroid(struct velocityvector * asteroid);





#endif
