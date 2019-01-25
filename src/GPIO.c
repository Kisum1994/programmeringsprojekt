#include "30010_io.h"

#include "ansi.h"
#include "GPIO.h"
#include "charset.h"
#include "lut.h"
#include "objects.h"

#define ESC 0x1B

// gloable varibler:  !brug get-funktionerne når de globale variabler skal bruges andre steder end i GPIO.c
    int time;
    int time_;
    int s;
    int s_;
    int m;
    int h;
    int tmpship1;
    int tmpship2;
    int tmpseagull1;
    int tmpseagull2;
    int tmpshot0;
    int tmpshot1;
    int tmpshot2;



int getTime() {return time;}
int getTime_() {return time_;}
int getS() {return s;}
int getS_() {return s_;}
int getM() {return m;}
int getH() {return h;}

// Jakob, Ida og Jesper
// Skriver til registers. Fortæller hvilke porte der skal aktiveres.
void initJoystick (void) {
 RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
 RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
 RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
  // Enable clock for GPIO Port A
                        // Set pin PA4 to input
 GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
 GPIOA->MODER |= (0x00000000 << (4 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
 GPIOA->PUPDR |= (0x00000002 << (4 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PB0 to input
 GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000000 << (0 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
 GPIOB->PUPDR |= (0x00000002 << (0 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PB5 to input
 GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000000 << (5 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
 GPIOB->PUPDR |= (0x00000002 << (5 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PC0 to input
 GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000000 << (0 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
 GPIOC->PUPDR |= (0x00000002 << (0 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PC1 to input
 GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000000 << (1 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
 GPIOC->PUPDR |= (0x00000002 << (1 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */
}

// Jakob, Ida og Jesper
//
int8_t readJoystick (void) {

    //Skriver til
    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);
    uint16_t valNed = GPIOB->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);
    uint16_t valHojre = GPIOC->IDR & (0x0001 << 0);
    uint16_t valVenstre = GPIOC->IDR & (0x0001 << 1);
    int8_t valJ;
    int i=0;

        if (valUp > 0 && i==0) {
            valJ= 0x01;
            i=1;
        }
         else if (valNed > 0 && i==0) {
            valJ= 0x02;
            i=1;
        }
        else if (valCenter > 0 && i==0) {
            valJ= 0x10;
            i=1;
        }
        else if (valHojre > 0 && i==0) {
            valJ= 0x08;
            i=1;
        }
        else if (valVenstre > 0 && i==0) {
            valJ= 0x04;
            i=1;
        } else {
            valJ = 0x00;
            i=0;
        }


    if (i!=0) {
        return valJ;
        i=0;
    }
    else {
    return 0;
    }
}

//Jakob, Ida og Jesper
//
void initLED(void) {
 RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
 RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
 RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
  // Enable clock for GPIO Port A through C


  // Set pin PA9 to output */
 GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
 GPIOA->OSPEEDR |= (0x00000002 << (9 * 2));
 /* set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz) */

 GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
 GPIOA->OTYPER |= (0x0000 << (9));
 /* Set output type register (0x00 - Push pull, 0x01 - Open drain) */

 GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
 GPIOA->MODER |= (0x00000001 << (9 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */



 // Set pin PB4 to output */
 GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
 GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));
 /* set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz) */

 GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
 GPIOB->OTYPER |= (0x0000 << (4));
 /* Set output type register (0x00 - Push pull, 0x01 - Open drain) */

 GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000001 << (4 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */



 // Set pin PC7 to output */
 GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
 GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));
 /* set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz) */

 GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
 GPIOC->OTYPER |= (0x0000 << (7));
 /* Set output type register (0x00 - Push pull, 0x01 - Open drain) */

 GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000001 << (7 * 2));
 /* Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */

}

//Jakob og Jesper
//
void setLED(int rgb[3]) {

    GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high = off
    GPIOB->ODR |= (0x0001 << 4); //Set pin PA9 to high = off
    GPIOC->ODR |= (0x0001 << 7); //Set pin PA9 to high = off

    //tænder blå
    if(rgb[2]==1) {
        GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to low = on
    }
    // tænder rød
    if(rgb[0]==1) {
        GPIOB->ODR &= ~(0x0001 << 4); //Set pin PA9 to low = on
    }
    // tænder grøn
    if(rgb[1]==1) {
        GPIOC->ODR &= ~(0x0001 << 7); //Set pin PA9 to low = on
    }
}

// Jakob
//
void LEDjoystick(void) {
 /* skriv dette i main for at bruge
    int j;
    int i;
    while (1){
        LEDjoystick();
    }
    */
    int valJ[3]={0,0,0};
    int j=0;
    int i=0;
    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);
    uint16_t valNed = GPIOB->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);
    uint16_t valHojre = GPIOC->IDR & (0x0001 << 0);
    uint16_t valVenstre = GPIOC->IDR & (0x0001 << 1);

        if (valUp > 0) {
            valJ[0]= 1;
            i=1;
        }
        else if (valNed > 0) {
            valJ[1]= 1;
            i=1;
        }
        else if (valCenter > 0) {
            valJ[2]= 1;
            i=1;
        }
        else if (valHojre > 0) {
            valJ[1]= 1;
            valJ[2]= 1;
            i=1;
        }
        else if (valVenstre > 0) {
            valJ[0]= 1;
            valJ[1]= 1;
            i=1;
        } else {

            i=0;
        }

        if (i!=j) {
            setLED(valJ);
            j = i;
        }
}

// Jakob, Ida og Jesper.
//
void initTimer (void){ // TIM 15
 RCC->APB2ENR |= RCC_APB2Periph_TIM15; // Enable clock line to timer 2;
 TIM15->CR1 &= ~0x0001; // Configure timer 2
 TIM15->ARR = 63999; // Set reload value
 TIM15->PSC = 9; // Set prescale value
 TIM15->DIER |= 0x0001; // Enable timer 2 interrupts
 NVIC_SetPriority(0x0018, 0x0); // Set interrupt priority
 NVIC_EnableIRQ(0x0018);// Enable interrupt
// // TIM2->CR1 = 0x0001; --- start timer 2 -- skriv dette i main for at starte timeren
}

// Jesper
//vi har ændret timeren?
void TIM1_BRK_TIM15_IRQHandler(void){
        //Do whatever you want here, but make sure it doesn’t take too much time!
        // OMREGN TIL SEKUNDER! fra 1/100 dele sek
        // dette er hvad der sker ved en interrupt i timer 5
    if (time>=100) {
            s++;
            time -= 100;
            if (s>=60) {
                m++;
                //s=0;
            }
            if (m>=60) {
                h++;
                m=0;
            }
    }
    //globale tidsvariable der opdateres hver gang der foretages en interrupt.
    time++;
    tmpship1++;
    tmpship2++;
    tmpseagull1++;
    tmpseagull2++;
    tmpshot0++;
    tmpshot1++;
    tmpshot2++;

    TIM15->SR &= ~0x0001; // Clear interrupt bit, skal gøre for at kunne bruge interrupt igen.

}

//Jesper

void initBuzzer(void){
     RCC->APB1ENR |= 0x00000001; // Enable clock line to timer 2;
     TIM2->CR1 = 0x0000; // Disable timer
     TIM2->ARR = 0x03e7; // Set auto reload value
     TIM2->PSC = 0x027f; // Set pre-scaler value
     TIM2->CR1 |= 0x0001; // Enable timer

     TIM2->CCER &= ~TIM_CCER_CC3P; // Clear CCER register
     TIM2->CCER |= 0x00000001 << 8; // Enable OC3 output
     TIM2->CCMR2 &= ~TIM_CCMR2_OC3M; // Clear CCMR2 register
     TIM2->CCMR2 &= ~TIM_CCMR2_CC3S;
     TIM2->CCMR2 |= TIM_OCMode_PWM1; // Set output mode to PWM1
     TIM2->CCMR2 &= ~TIM_CCMR2_OC3PE;
     TIM2->CCMR2 |= TIM_OCPreload_Enable;
     TIM2->CCR3 = 500; // Set duty cycle to 50 %
     RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable clock line for GPIO bank B
     GPIOB->MODER &= ~(0x00000003 << (10 * 2)); // Clear mode register
     GPIOB->MODER |= (0x00000002 << (10 * 2)); // Set mode register
     GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);

}

//Jesper
//
void setFreq(uint16_t freq) {
     uint32_t reload = 64e6 / freq / (0x027f + 1) - 1;
     TIM2->ARR = reload; // Set auto reload value
     TIM2->CCR3 = reload/2; // Set compare register
     TIM2->EGR |= 0x01;
}

//Jakob, Ida og Jesper
//
int8_t get_char(char * text, int length) {

    /* INDSÆT SÅLEDES I MAIN: HVIS MAN F.EKS. VIL PRINTE DEN INDTASTEDE STRING. !man behøver ikke at printe stringen!
    Der defineres en string  str[length+1] main som man "overskriver" ved hjælp af get_char når get_char har ændret str vil den returne 1
    uart_clear();
    char str[4];  <-- defineret string der ændres af get_char
    while (1) {
        if (get_char(str, 3)>0) {
            printf("%s",str);
        }
    }*/

    //Static variabel, da der ønskes at skrive til den gamle værdi af buffcount. Static variable gør at den husker sin placering (værdi fra før)
    static int buffCount=0;


    if (buffCount<length) {
        if (0<uart_get_count()) {
            text[buffCount]=uart_get_char();
            buffCount++;
        }
        if (text[buffCount-1]==0x0d) {
            buffCount--;
            text[buffCount]=0x00;
            buffCount = 0;
            return 1;
            uart_clear();
        }
    }
    if(buffCount==length){
        text[buffCount]=0x00;
        buffCount = 0;
        return 1;
        uart_clear();
    }
    return 0;
}

// Ida og Jakob
//Reseter følgende globale tidsvariable.
void resetWatch(void){
    time=0;
    s=0;
    m=0;
    h=0;
}


// stopur der kan kontrolleres med get_char og userInput funktionerne. Brug userInput(readKeyboard()) som input.
void PCtimer (int * input) {

                    if (input[0]==0x10) {  // tænder ur
                        TIM2->CR1 = 0x0001;
                        printf("Ur startet");
                    }

                    if (input[0]==0x01) {  // reseter ur
                        time=0;
                        s=0;
                        m=0;
                        h=0;
                        printf("%02d.%02d.%02d\n",h,m,s);
                        printf("Ur reset");
                    }

                    if (s!=s_) { // printer tiden når uret "tikker".
                            printf("%02d.%02d.%02d\n",h,m,s);

                            (s_)=(s);
                    }

                    if (input[0]==0x08) { // split 1

                            printf("Split 1: %02d.%02d.%02d\n",h,m,s);
                    }

                    if (input[0]==0x04) { // split 2

                           printf("Split 2: %02d.%02d.%02d\n",h,m,s);
                    }

                    if (input[0]==0x20) { // stopper ur
                            TIM2->CR1 = 0x0000;
                            printf("Ur stopppet");
                    }
}

//
// til keyboard styring af PCtimer();
// brug den som input til PCtimer(); i et while loop i main
int userInput(char * str) {

        if (strcmp(str,"start")==0) {
            return 0x10;
        }
        else if (strcmp(str,"stop")==0 ) {
            return 0x20;
        }
        else if (strcmp(str,"split1" )==0) {
            return 0x08;
        }
        else if (strcmp(str,"split2")==0 ) {
            return 0x04;
        }
        else if (strcmp(str,"reset" )==0) {
            return 0x01;
        }
        else {
            return 0;
        }
}

//Jakob
// fungerer som get_char(); men har en grænse på 3 karakterer for piletasterne
int8_t keyboardInput(char * text) {
    //Static variabel, da der ønskes at skrive til den gamle værdi af buffcount. Static variable gør at den husker sin placering (værdi fra før)
    static uint8_t buffCount=0;
    if (buffCount<3) {
        if (0<uart_get_count()) {
            text[buffCount]=uart_get_char();
            buffCount++;
        }
        if (buffCount!=0) {
            if (text[buffCount-1]==0x0d) {
                text[buffCount]=0x00;
                buffCount = 0;
                uart_clear();
                return 1;

            }
            else if (text[buffCount-1]==0x20) {
                text[buffCount]=0x00;
                buffCount = 0;
                uart_clear();
                return 1;
            }
        }
    }
    if(buffCount==3){
        buffCount = 0;
        uart_clear();
        return 1;

    }
    else {
        strcpy(text,"");
        return 0;
    }
}

//Ida og Jakob
//
void lcd_write_string(uint8_t * buffer, char * str,int locationLine,int numberLine){
    int i=0;
    int j=0;

    while (str[i]!=0x00) {
            for (j=0;j<5;j++) {
               int L =(i*5+j)+locationLine+128*numberLine;
               if (L>512){
                    L-=512;
               }
                buffer[(i*5+j)+locationLine+128*numberLine] = character_data[str[i]-0x20][j];
            }
            i++;
    }
}

//Ida og Jakob
//
void lcd_update(uint8_t * buffer, char * str){
    static int i=0;
    static int j=0;
    if (i==50) {
        memset(buffer,0x00,512);
        lcd_push_buffer(buffer);
        lcd_write_string(buffer,str,j,0);
        i-=50;
        j++;
        if (j==512){
                j=0;
        }
    }
    i++;
}

//Jakob
//
int arrowInput(char * str) {  // keypoardInput bliver oversat til HEX-tal
// char str[4]={""};   <-- denne SKAL defineres i main

        if (str[2]==65) { //pil op
            return 0x10;
            str[2]=0x00;
        }
        if (str[2]==66) { // pil ned
            return 0x20;
            str[2]=0x00;
        }
        if (str[2]==67) { // pil højre
            return 0x08;
            str[2]=0x00;
        }
        if (str[2]==68) { // pil venstre
            return 0x04;
            str[2]=0x00;
        }

        if (str[0]==0x20) { //mellemrum
            return 0x01;
        }
        if (str[0]==0x0d) { //enter
            return 0x30;
        }
        else {
            return 0;
        }
}

//Ida
/*Funktioner til at kontrollere hastigheden af måger og skud.
Her er flere styks hvilket skyldes at den globale tidsvariable resetes hver gang den respektive update funktion køres.
Ønskes det at have flere objekter med forskellige hastigheder, skal der derfor bruges flere stort set identiske funktioner.
(ens på nær forskellige globale tidsvariable)*/
int updateSeagull1(int speed) {
    //tmpseagull sættes til 0, hver gang værdien af speed nås.
    if ( tmpseagull1 >= speed ){
        tmpseagull1 = 0;
        return 1;
    }
    else{
        return 0;
    }
}

int updateSeagull2(int speed) {
    //tmpseagul2 sættes til 0, hver gang værdien af speed nås.
    if ( tmpseagull2 >= speed ){
        tmpseagull2 = 0;
        return 1;
    }
    else{
        return 0;
    }
}

int updateShot0(int speed) {
    if ( tmpshot0 >= speed ){
        tmpshot0 = 0;
        return 1;
    }
    else{
    return 0;
    }
}

int updateShot1(int speed) {
    if ( tmpshot1 >= speed ){
        tmpshot1 = 0;
        return 1;
    }
    else{
    return 0;
    }
}

int updateShot2(int speed) {
    if ( tmpshot2 >= speed ){
        tmpshot2 = 0;
        return 1;
    }
    else{
    return 0;
    }
}


int updateShip1(int speed) {
    if ( tmpship1 >= speed ){
        tmpship1 = 0;
        return 1;
    }
    else{
        return 0;
    }
}

int updateShip2(int speed) {
    if ( tmpship2 >= speed ){
        tmpship2 = 0;
        return 1;
    }
    else{
        return 0;
    }
}
