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

/*
struct vector_t {
        int32_t x, y;
            };
struct vector_t *v;
void initVector(struct vector_t *v) {
 (*v).x = -4<<14;
 (*v).y = 2<<14;
 };
*/



int main(void) {
    uart_init( 9600 ); //initialize USB serial emulation at 9600 baud
    startUP();
    initJoystick();
    lcd_init();

    //initLED();

    clrscr();
    gotoxy(1,0);


    //initTimer();
        // TIM2->CR1 = 0x0001; <-- start timer 2
    //TIM2_IRQHandler();


    //  Her starter kode til 6.2
    lcd_init();
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


  while(1) {}
}
