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

//der er lige nu fejl i koden men dettte kan ændres ved at implementere den rigtige brug af pointers
struct velocityvector{int32_t x;int32_t y;int32_t vx;int32_t vy};
void updateVelocityVector(struct velocityvector velovector){
velovector.x=velovector.x+velovector.vx;
velovector.y=velovector.y+velovector.vy;
};
void makeball(int32_t x, int32_t y){
gotoxy(x,y);
printf("o");
}

void moveBall(struct velocityvector velovector){
   int32_t xo:
   int32_t yo;
updateVelocityVector(velovector);
makeball(velovector.x,velovector.y);
xo=velovector.x-velovector.vx;
yo=velovector.y-velovector.vy;
gotoxy(xo,yo);
printf("");
};

int degY(struct velocityvector velovector){
int degree;
degree=abs(velovector.y-velovector.vy)
}

bool detectBarrier( int x1, int y1, int x2, int y2, struct velocityvector velovector){
    if(velovector.x+velovector.vx=<x1 && velovector.y+velovector.vy>0){
            if(){

            }
            else if(){

            }
    }
    else if (velovector.x+velovector.vx==x2){
            if(){

            }
            else if(){

            }
    }
    else if (velovector.y+velovector.vy==y1){
            if(){

            }
            else if(){

            }
    }
    else if (velovector.y+velovector.vy==y2){
            if(){

            }
            else if(){

            }
    }

}



int main(void) {
    uart_init( 9600 ); //initialize USB serial emulation at 9600 baud
    //startUP();
    //initJoystick();
    //lcd_init();
    //initTimer();

    //initLED();

    //clrscr();
    clrscr();
    window(3,4,20,20,1,"test");
    struct velocityvector bold;
    bold.x=5;
    bold.y=5;
    bold.vx=1;
    bold.vy=1;
while(1){
    moveBall(bold);
}

    //initTimer();
        // TIM2->CR1 = 0x0001; <-- start timer 2
    //TIM2_IRQHandler();

/*
    //  Her starter kode til 6.2
    int8_t buffer[512];
    memset(buffer,0xAA,512);
    //int i;
    //for (i=0; i<=512; i++){
    //buffer[i]= 0xaa;
    //};
    lcd_push_buffer(buffer);
        //char str[21];
    //str[2]="2";
    //PCtimer();
    printf("test ");
    char str[21];
    int input=0;
    //int i=0;
    //int j=1;
    printf("STOPWATCH.exe\n");
    while(1){
        //for(int i=0;i<20;i++){
        //        str[i]="";
        //}
        if (get_char(str,20)==1){
            input=userInput(str);

        }
        if(input>0){
        printf("%d",input);
        }
        PCtimer(input);
        input=0;
    }
    printf("%s",str);
*/
  while(1) {}
}
