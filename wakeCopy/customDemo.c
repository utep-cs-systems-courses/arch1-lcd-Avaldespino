#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15


static char

switch_update_interrupt_sense()

{

  char p2val = P2IN;

  /* update switch interrupt to detect changes from current buttons */

  P2IES |= (p2val & SWITCHES);/* if switch up, sense down */

  P2IES &= (p2val | ~SWITCHES);/* if switch down, sense up */

  return p2val;

}



void

switch_init()/* setup switch */

{

  P2REN |= SWITCHES;/* enables resistors for switches */

  P2IE |= SWITCHES;/* enable interrupts from switches */

  P2OUT |= SWITCHES;/* pull-ups for switches */

  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  switch_update_interrupt_sense();

}



int switches = 0;



void

switch_interrupt_handler()

{

  char p2val = switch_update_interrupt_sense();

  switches = ~p2val & SWITCHES;

}





// axis zero for col, axis 1 for row

short drawPos[2] = {10,10}, controlPos[2] = {10,10};

short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};



short redrawScreen = 1;

u_int controlFontColor = COLOR_GREEN;


void wdt_c_handler()

{

  static int secCount = 0;



  secCount ++;

  if (secCount >= 5) {/* 10/sec */

    secCount = 0;
    redrawScreen = 1;

  }

}
/* Switch on S2 */

void

__interrupt_vec(PORT2_VECTOR) Port_2(){

  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */

    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */

    switch_interrupt_handler();/* single handler for all switches */

  }

}




void main(){
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  
  while(1)
    {
      if(redrawScreen){
	redrawScreen = 0;
	//drawString8x12(10,90,"Test",COLOR_PINK,COLOR_WHITE);
	update_shape();
      }

      
    }
    P1OUT &= ~LED;	/* led off */
    or_sr(0x10);	/**< CPU OFF */
    //P1OUT |= LED;	/* led on */
  }

 
void update_shape()
{
  short originRow = LONG_EDGE_PIXELS/2;

  short originCol = SHORT_EDGE_PIXELS/2;



  /*for(int row=0;row < 10;row++){

    for(int col = 0; col < 20; col++){

      drawPixel(originCol+col,originRow+row,COLOR_WHITE);

      drawPixel(originCol-col,originRow+row,COLOR_WHITE);

    }

    }*/

  int col_limit = 10;

  for(int row = 0; row <= 10;row++){

    col_limit--;

    for(int col = 0; col<=col_limit;col++ ){

      drawPixel(originCol+col,originRow+row,COLOR_WHITE);

      drawPixel(originCol-col,originRow-row,COLOR_WHITE);



    }

  }

}
