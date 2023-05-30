#include "include/soundDriver.h"

extern uint8_t inb(uint16_t in1);
extern void outb(uint16_t out1, uint8_t in1);

//Play sound using built in speaker
 static void play_sound(uint32_t nFrequence) {              // code source: https://wiki.osdev.org/PC_Speaker
 	uint32_t Div;
 	uint8_t tmp;
 
        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));
 
        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }
 
//make it shutup
 static void nosound() {
 	uint8_t tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
 }
 
 
 //Make a beep
 void beep(int freq, int time) {
 	 play_sound(freq);
 	 sleepms(time);
 	 nosound();
          //set_PIT_2(old_frequency);
 }
 

