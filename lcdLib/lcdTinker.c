/** \file lcdTinker.c
 *  \brief A simple demo that draws a string and square modified
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLACK);
  short originRow = LONG_EDGE_PIXELS/2;
  short originCol = SHORT_EDGE_PIXELS/2;

  for(short c = 0; c<30;c++){
    drawPixel(originCol+c,originRow+c,COLOR_WHITE);
    drawPixel(originCol+c,originRow-c,COLOR_WHITE);
    drawPixel(originCol-c,originRow+c,COLOR_WHITE);
    drawPixel(originCol-c,originRow-c,COLOR_WHITE);
  }
  short topLine = originRow+30;
  short bottomLine = originRow-30;
  short straightLine = originCol - 30;
   for(short c = 0; c<60;c++){
    drawPixel(straightLine+c,topLine,COLOR_WHITE);
    drawPixel(straightLine+c,bottomLine,COLOR_WHITE);
   }
  /*short col = 30;
  short startc = 30, startr = 30;
  for (col = 0; col < 30;){
    short row = col;
    short leftEdge = -col;
    short rightEdge = col;
    for(short c = leftEdge; c <= rightEdge; c++){
      drawPixel(startc+c, startr+row, COLOR_PINK);
      col +=1;
    }
    //drawPixel(startc+leftEdge,row+startr, COLOR_PINK);
    //drawPixel(startc+rightEdge,row+startr, COLOR_PINK);
    //drawPixel(col,90, COLOR_PINK);
    //drawPixel(30+col,90, COLOR_PINK);
    
    col +=1;
  }
  */

  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
