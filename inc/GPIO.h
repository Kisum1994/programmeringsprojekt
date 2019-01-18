#include <stdio.h>

#ifdef _GPIO_H_
#define _GPIO_H_

// funktioner
void initJoystick ();
void initTimer();
void TIM2_IRQHandler();
int8_t readJoystick ();
void PCtimer(int * input);
int8_t keyboardInput(char * text);
int arrowInput(char * str);



#endif
