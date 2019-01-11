#include "30010_io.h"

#include "GPIO.h"
#include "ansi.h"
#include "charset.h"
#include "lut.h"

#define ESC 0x1B
    int time;
    int s;
    int s_;
    int m;
    int h;
    int buffCount=0;

void startUP() {
    int time;
    int s;
    int s_;
    int m;
    int h;
    int buffCount=0;
}

void initJoystick () {
 RCC->AHBENR |= RCC_AHBPeriph_GPIOA;
 RCC->AHBENR |= RCC_AHBPeriph_GPIOB;
 RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
  // Enable clock for GPIO Port A
                        // Set pin PA4 to input
 GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
 GPIOA->MODER |= (0x00000000 << (4 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
 GPIOA->PUPDR |= (0x00000002 << (4 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PB0 to input
 GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000000 << (0 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
 GPIOB->PUPDR |= (0x00000002 << (0 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PB5 to input
 GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000000 << (5 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
 GPIOB->PUPDR |= (0x00000002 << (5 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PC0 to input
 GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000000 << (0 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
 GPIOC->PUPDR |= (0x00000002 << (0 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */

                        // Set pin PC1 to input
 GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000000 << (1 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */
 GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
 GPIOC->PUPDR |= (0x00000002 << (1 * 2));
 /* Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down) */
}

int8_t readJoystick () {
/* skriv dette i main for at bruge
    int j;
    int i;
    while (1){
        readJoystick();

    }
    */

    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);
    uint16_t valNed = GPIOB->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);
    uint16_t valHojre = GPIOC->IDR & (0x0001 << 0);
    uint16_t valVenstre = GPIOC->IDR & (0x0001 << 1);
    int8_t valJ;
    int j=0;
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
}

void initLED() {
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
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */



 // Set pin PB4 to output */
 GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
 GPIOB->OSPEEDR |= (0x00000002 << (4 * 2));
 /* set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz) */

 GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
 GPIOB->OTYPER |= (0x0000 << (4));
 /* Set output type register (0x00 - Push pull, 0x01 - Open drain) */

 GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000001 << (4 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */



 // Set pin PC7 to output */
 GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
 GPIOC->OSPEEDR |= (0x00000002 << (7 * 2));
 /* set speed register (0x01 - 10 MHz, 0x02 - 2 MHz, 0x03 - 50 MHz) */

 GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
 GPIOC->OTYPER |= (0x0000 << (7));
 /* Set output type register (0x00 - Push pull, 0x01 - Open drain) */

 GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000001 << (7 * 2));
 /* Set mode register (0x00 � Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out) */

}

void setLED(int rgb[3]) {

    GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high = off
    GPIOB->ODR |= (0x0001 << 4); //Set pin PA9 to high = off
    GPIOC->ODR |= (0x0001 << 7); //Set pin PA9 to high = off

    //t�nder bl�
    if(rgb[2]==1) {
        GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to low = on
    }
    // t�nder r�d
    if(rgb[0]==1) {
        GPIOB->ODR &= ~(0x0001 << 4); //Set pin PA9 to low = on
    }
    // t�nder gr�n
    if(rgb[1]==1) {
        GPIOC->ODR &= ~(0x0001 << 7); //Set pin PA9 to low = on
    }
}

void LEDjoystick() {
 /* skriv dette i main for at bruge
    int j;
    int i;
    while (1){
        LEDjoystick();

    }
    */

    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);
    uint16_t valNed = GPIOB->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);
    uint16_t valHojre = GPIOC->IDR & (0x0001 << 0);
    uint16_t valVenstre = GPIOC->IDR & (0x0001 << 1);
    int valJ[3]={0,0,0};
    int j;
    int i;

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

    if (j!=i) {
        setLED(valJ);
        j = i;
    }
}


void initTimer (){
 RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock line to timer 2;
 TIM2->CR1 = 0x0000; // Configure timer 2
 TIM2->ARR = 0x03E7; // Set reload value
 TIM2->PSC = 0x027F; // Set prescale value
 TIM2->DIER |= 0x0001; // Enable timer 2 interrupts
 NVIC_SetPriority(0x001C, 0x0); // Set interrupt priority
 NVIC_EnableIRQ(0x001C); // Enable interrupt
// // TIM2->CR1 = 0x0001; --- start timer 2 -- skriv dette i main for at starte timeren
}

 /* void TIM2_IRQHandler(void) {
        //Do whatever you want here, but make sure it doesn�t take too much time!
        // OMREGN TIL SEKUNDER! fra 1/100 dele s
    time++;
    printf("%d\n",time);

 TIM2->SR &= ~0x0001; // Clear interrupt bit
 } */
//----------------
/* int8_t timerJoystick () {

    uint16_t valUp = GPIOA->IDR & (0x0001 << 4);
    uint16_t valNed = GPIOB->IDR & (0x0001 << 0);
    uint16_t valCenter = GPIOB->IDR & (0x0001 << 5);
    uint16_t valHojre = GPIOC->IDR & (0x0001 << 0);
    uint16_t valVenstre = GPIOC->IDR & (0x0001 << 1);

        if (valUp > 0) {
            return  0x01;
        }
        else if (valNed > 0) {
            return  0x02;
        }
        else if (valCenter > 0) {
            return  0x10;
        }
        else if (valHojre > 0) {
            return  0x08;
        }
        else if (valVenstre > 0) {
            return  0x04;
        } else {
            return  0x00;
        }
} */

void timer () {
    while(1) {

        int i=0;
        int j=1;
        int k=0;
        int l_old=0;
            if (readJoystick()==0x00 && i!=j) {
                while (1) {

                    if (readJoystick()==0x10) {
                        TIM2->CR1 = 0x0001;
                        j=i;
                        l_old=1;
                        break;
                    }
                    if (readJoystick()==0x01) {
                        i=0;
                        j=1;

                        time=0;
                        s=0;
                        m=0;
                        h=0;
                        gotoxy(2,0);
                        clreol();
                        printf("%02d.%02d.%02d\n",h,m,s);
                        gotoxy(2,0);
                    }
                    if (readJoystick()==0x02) {
                        k=1;
                        break;
                    }
                }
            }

            if(k==1) {
                break;
            }

            else if (i==j) {
                while (1) {

                    if (s!=s_) {
                        printf("%02d.%02d.%02d\n",h,m,s);
                        gotoxy(2,0);
                        (s_)=(s);
                        l_old=0;
                    }
                    if (readJoystick()==0x08) {
                           gotoxy(3,0);
                           printf("Split 1: %02d.%02d.%02d\n",h,m,s);
                           gotoxy(2,0);
                           l_old=0;
                    }
                    if (readJoystick()==0x04) {
                           gotoxy(4,0);
                           printf("Split 2: %02d.%02d.%02d\n",h,m,s);
                           gotoxy(2,0);
                           l_old=0;
                    }
                    if (readJoystick()==0x10 && l_old==0) {
                        TIM2->CR1 = 0x0000;
                        i=0;
                        j=1;
                        break;
                    }

                }
            }
    }
}

void TIM2_IRQHandler(void) {


        //Do whatever you want here, but make sure it doesn�t take too much time!
        // OMREGN TIL SEKUNDER! fra 1/100 dele sek
        // dette er hvad der sker ved en interrupt i timer 2
    if (time>=100) {
            s++;
            time -= 100;
            if (s>=60) {
                m++;
                s=0;
            }
            if (m>=60) {
                h++;
                m=0;
            }
    }
    time++;
    TIM2->SR &= ~0x0001; // Clear interrupt bit
 }

int8_t get_char(char * text, int length) {



    if (buffCount<length) {
        if (0<uart_get_count()) {
            text[buffCount]=uart_get_char();
            buffCount++;
        }
        if (text[buffCount-1]==0x0d) {
            buffCount--;
            text[buffCount]=0x00;
            return text;
            uart_clear();
        }
    }
    if(buffCount==length){
        text[buffCount]=0x00;
        return text;
        uart_clear();
    }
}

void PCtimer () {
    printf("STOPWATCH.exe\n");
    while(1) {
        int input;
        int i=0;
        int j=1;
        int k=0;
        int l_old=0;
            if (i!=j) {
                while (1) {
                    input=0;
                    input=userInput();
                    if (input==0x10) {
                        TIM2->CR1 = 0x0001;
                        j=i;
                        l_old=1;
                        break;
                    }
                    else if (input==0x01) {
                        i=0;
                        j=1;

                        time=0;
                        s=0;
                        m=0;
                        h=0;
                        //gotoxy(2,0);
                        clreol();
                        printf("%02d.%02d.%02d\n",h,m,s);
                        //gotoxy(2,0);
                    }
                    //else if (input==0x02) {
                       // k=1;
                        //break;
                    //}
                }
            }

            //if(k==1) {
               // break;
            //}

            if (i==j) {
                input=0;
                //input=userInput();
                    while (1) {
                        if (uart_get_char()!=0) {
                                input=userInput();
                        }
                        if (s!=s_) {
                            printf("%02d.%02d.%02d\n",h,m,s);
                            // gotoxy(2,0);
                            (s_)=(s);
                            l_old=0;
                        }
                        if (input==0x08) {
                            gotoxy(3,0);
                            printf("Split 1: %02d.%02d.%02d\n",h,m,s);
                            gotoxy(2,0);
                            l_old=0;
                            input=0;
                        }
                        if (input==0x04) {
                           gotoxy(4,0);
                           printf("Split 2: %02d.%02d.%02d\n",h,m,s);
                           gotoxy(2,0);
                           l_old=0;
                           input=0;
                        }
                        if (input==0x10 && l_old==0) {
                            TIM2->CR1 = 0x0000;
                            i=0;
                            j=1;
                        break;
                    }

                }
            }
    }
}

int userInput() {

    char str[21];

    while(1) {
        get_char(str,20);

        if (strcmp(str,"start")==0) {
            return 0x10;
            break;
        } else if (strcmp(str,"stop")==0 ) {
            return 0x10;
            break;
        } else if (strcmp(str,"split1" )==0) {
            return 0x08;
            break;
        } else if (strcmp(str,"split2")==0 ) {
            return 0x04;
            break;
        } else if (strcmp(str,"reset" )==0) {
            return 0x01;
            break;
        }
        else {
            printf("Input not valid.\n");
        }
    }
}