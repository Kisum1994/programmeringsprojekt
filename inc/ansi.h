#include <stdio.h>
#include <string.h>

#ifdef _ANSI_H_
#define _ANSI_H_
#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void gotoxy(int x;int y);
void clrscr(void);
void clreol(void);
void underline(uint8_t on);


#endif /* _ANSI_H_ */
