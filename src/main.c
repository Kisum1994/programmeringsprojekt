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

    int time;
    int s;
    int s_;
    int m;
    int h;

int main(void) {
    uart_init( 9600 ); //initialize USB serial emulation at 9600 baud
    // Start globale variable
    // startUP();
    printf("\e[?25l");
    lcd_init();
    int flag=0;
    initTimer();
    TIM2->CR1=0x0001;
    TIM2_IRQHandler();

    //initLED();






    //  Her starter kode til 6.2
    char str[]="Ida er leakker";


    int8_t buffer[512];
    memset(buffer,0x00,512);

    lcd_write_string(buffer,str,0);

    lcd_push_buffer(buffer);

        //char str[21];
    //str[2]="2";
    //PCtimer();
    clrscr();

    // første koordinat nedad og 2 koordinat til siden
    int k=0;
    int g=0;
    int position=4;
    // tegn rumhavmåger
    while (1){

        if (time%10==0){
        //tegn stor asteroide
            drawAsteroide(5,position+5,0);
            CleanAsteroide(5, 0, position+5, 1, 0);
        // tegn lille asteroide
            drawAsteroide(10,position+7,1);
            CleanAsteroide(10, 0, position+7, 1, 1);
        // tegn flyvende rumhavmåge
            if (g<2){
                drawSeagull(position,position,k);
                CleanSeagull(position,1,position,1,k);
                if (k==0){
                    k=1;
                    position++;
                }
                else if (k==1){
                    k=0;
                }
            }
        }
        if (time%60==0){
            g++;
                if (g==2){
                    deleteSeagull(position,1,position,1);
                }
        }
    }

    // skriv den tomme ldc_update fil

    // først skal der laves en funktion lcd_write_string()
     while (1) {
        if (flag=1) {
            lcd_update(buffer,str);
            lcd_push_buffer(buffer);
            flag=0;
        }
    }

  while(1) {}
}
