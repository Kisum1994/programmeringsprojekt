#ifndef _OBJECTS_H_
#define _OBJECTS_H_


#include <stdio.h>

// initStructs funktionerne

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
        int health;
    };

    struct box{
        int x1;
        int x2;
        int y1;
        int y2;
        char title[10];
        int style;
    };





#endif
