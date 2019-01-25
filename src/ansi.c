#include "ansi.h"
#include "lut.h"
#include "objects.h"
#define ESC 0x1B
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )

#define ESC 0x1B

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(void) {
    printf("\e[2J");
}

void clreol(void) {
    printf("\e[K");
}

void gotoxy(int x , int y) {
    printf("\e[%d;%dH",x,y);
}

void underline(uint8_t on) {
    if (on==1) {
        printf("\e[4m");
    }
    else if (on==0) {
        printf("\e[24m");
    }
}



void printFix(int32_t i) {
 // Prints a signed 16.16 fixed point number
 if ((i & 0x80000000) != 0) { // Handle negative numbers
 printf("-");
 i = ~i + 1;
 }
 printf("%ld.%04ld", i >> 16, 10000 * (uint32_t)(i & 0xFFFF) >> 16);
 // Print a maximum of 4 decimal digits to avoid overflow
 }

int32_t expand(int32_t i) {
 // Converts an 18.14 fixed point number to 16.16
 return i << 2;
 }

 void fix(int32_t i){
 printFix(expand(i));
 }

int32_t calcsin(int deg) {
int32_t input = (deg*512)/360;
return (int32_t)(sinus[input&0x1FF]);
}

int32_t calccos(int deg) {
int32_t input = ((deg+90)*512)/360;
return (int32_t)(sinus[input&0x1FF]);
}

struct vector_t {
 int32_t x, y;
 };

int32_t rotatev(struct vector_t * v, int32_t deg) {
    v->x=FIX14_MULT(v->x,calccos(deg))-FIX14_MULT(v->y,calcsin(deg)); // FIX14_MULT bliver brugt til at gange fixed point tal sammn
    v->y=FIX14_MULT(v->x,calcsin(deg))+FIX14_MULT(v->y,calccos(deg));

};
