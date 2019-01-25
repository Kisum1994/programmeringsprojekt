#include <stdio.h>

#ifdef _GPIO_H_
#define _GPIO_H_

// funktioner

int getTime();
int getTime_();
int getS();
int getS_();
int getM();
int getH();

void initJoystick (void);
int8_t readJoystick (void);
void initLED(void);
void setLED(int rgb[3]);
void LEDjoystick(void);


void initTimer(void);
void TIM1_BRK_TIM15_IRQHandler(void);

void initBuzzer(void);
void setFreq(uint16_t freq);

int8_t get_char(char * text, int length);

void resetWatch(void);

void PCtimer (int * input);
int userInput(char * str);

int8_t keyboardInput(char * text);
int arrowInput(char * str);

void lcd_write_string(uint8_t * buffer, char * str,int locationLine,int numberLine)
void lcd_update(uint8_t * buffer, char * str);

int updateSeagull1(int speed);
int updateSeagull2(int speed);

int updateShot0(int speed);
int updateShot1(int speed);
int updateShot2(int speed);

int updateShip1(int speed);
int updateShip2(int speed);


void PCtimer(int * input);
int8_t keyboardInput(char * text);
int arrowInput(char * str);



#endif
