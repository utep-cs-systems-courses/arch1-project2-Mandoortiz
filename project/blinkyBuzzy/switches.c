#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"
char sw1_down, sw2_down, sw3_down,sw4_down, switch_state_changed;
/* effectively boolean */

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  sw1_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  sw2_down = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  sw3_down = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  sw4_down = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */

  /* Used to trigger different states for State Machine*/
  if(sw1_down){
    state = 1;
  }
  if(sw2_down){
    state = 2;
  }
  if(sw3_down){
    state = 3;
  }
  if(sw4_down){
    state = 4;
  }
  switch_state_changed = 1;
  
}
