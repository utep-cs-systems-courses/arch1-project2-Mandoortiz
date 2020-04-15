#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "twinkleTwinkle.h"
#include "assembly.h"
char speed = 0;// set speed of interrupts
unsigned int state = 0;// set state for the state machine
char note = 0; // Set first note to 0
int notes[] = {C1,0,C1,0,G5,0,G5,0,A5,A5,G5,0,F4,F4,E3,E3,D2,D2,C1};

void state_advance()
{
  switch (state) {
  case 1: // red_green_chacha
    speed = 100;
    buzzer_set_period(0);
    red_green_chacha();
    led_update();
    break;
  case 2: // dim_lights
    speed = 1; // low enough number for lights to appear dim
    buzzer_set_period(0);
    dim_lights();
    led_update();
    break;
  case 3: // play_song
    speed = 120; // preferred speed for song
    buzzer_set_period(0);
    play_song();
    break;
  case 4:
    buzzer_set_period(0); // Used to mute buzzer and turn off lights.
    speed = 100;
    assembly_lightshow();
    led_update();
    break;
  }
}

//Alternates cases between red, green, and then both lights on and off
void red_green_chacha()
{
  static unsigned int red_green_state = 0;
  switch (red_green_state) {
  case 0:
    red_on = 1;
    green_on = 0;
    red_green_state++;
    break;
  case 1:
    red_on = 0;
    green_on = 1;
    red_green_state++;
    break;
  case 2:
    red_on = 1;
    green_on = 1;
    red_green_state++;
    break;
  case 3:
    red_on = 0;
    green_on = 0;
    red_green_state++;
    break;
  case 4:
    red_on = 1;
    green_on = 1;
    red_green_state++;
    break;
  case 5:
    red_on = 0;
    green_on = 0;
    red_green_state++;
    break;
  case 6:
    red_on = 1;
    green_on = 1;
    red_green_state++;
    break;
  case 7:
    red_on = 0;
    green_on = 0;
    red_green_state = 0;
    break;
  }
}

// Makes lights appear dim.
void dim_lights(){
  static unsigned int dim_lights_state = 0;
  switch (dim_lights_state) {
  case 0:
    red_on = 0; 
    green_on = 0;
    dim_lights_state++;
    break;
  case 1:
    red_on = 0;
    green_on = 0;
    dim_lights_state++;
    break;
  case 2:
    red_on = 1;
    green_on = 1;
    dim_lights_state = 0;
    break;
  }
}

// Used to play song 
void play_song()
{
  if (note < 19) { // If less than length of array play notes.
    buzzer_set_period(notes[note]);
    note++;
  }
  else { // Else turn off buzzer and start over.
    buzzer_set_period(0);
    note = 0;
  }
}
