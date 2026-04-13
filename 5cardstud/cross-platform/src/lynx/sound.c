#include <lynx.h>
#include <tgi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


// Simple delay loop
void delay(unsigned int d) {
    unsigned int i;
    for (i = 0; i < d; ++i) { }
}

void initSound(void) {
    MIKEY.mstereo = 0;

   /*
    unsigned char volume;       // fd20
    unsigned char feedback;     // fd21
    unsigned char dac;          // fd22
    unsigned char shiftlo;      // fd23
    unsigned char reload;       // fd24
    unsigned char control;      // fd25
    unsigned char count;        // fd26
    unsigned char other;        // fd27
    */

    MIKEY.channel_a.volume = 0;
    MIKEY.channel_a.shiftlo = 0;
    MIKEY.channel_a.control = 0x18;
    MIKEY.channel_a.feedback = 1; 
    MIKEY.channel_a.other = 0;

}

// Join Game (ascending tone)
void soundJoinGame(void) {
    // Bright initial "ding"
    MIKEY.channel_a.volume = 127;
    MIKEY.channel_a.control = 0x18;

    MIKEY.channel_a.reload = 90;   // high pitch
    delay(2000);

    // Softer trailing tone
    MIKEY.channel_a.volume = 80;
    MIKEY.channel_a.reload = 140;  // slightly lower pitch
    delay(4000);

    MIKEY.channel_a.volume = 0;
}

// My Turn (double beep alert)
void soundMyTurn(void) {
	unsigned char i;

    MIKEY.channel_a.volume = 127;
    MIKEY.channel_a.control = 0x18;
    	
    for (i = 0; i < 2; i++) {
        MIKEY.channel_a.reload = 120;
        delay(5000);

        MIKEY.channel_a.volume = 0;
        delay(3000);

        MIKEY.channel_a.volume = 127;
    }

    MIKEY.channel_a.volume = 0;
}

// Game Done (descending tone)
void soundGameDone(void) {
    MIKEY.channel_a.volume = 127;
    MIKEY.channel_a.control = 0x18;

    // Initial low tone
    MIKEY.channel_a.reload = 180;
    delay(3000);

    // Drop lower for “bong” feel
    MIKEY.channel_a.volume = 90;
    MIKEY.channel_a.reload = 220;
    delay(5000);

    MIKEY.channel_a.volume = 0;
}

// Deal Card (short click)
void soundDealCard(void) {
    MIKEY.channel_a.control = 0x1E;
    MIKEY.channel_a.volume = 0x2F;
    MIKEY.channel_a.reload = 220;
    delay(1500);
    MIKEY.channel_a.volume = 0;
}

// Tick (metronome style)
void soundTick(void) {
    MIKEY.channel_a.control = 0x1E;
    MIKEY.channel_a.volume = 0x1F;
    MIKEY.channel_a.reload = 200;
    delay(1000);
    MIKEY.channel_a.volume = 0;
}

// Player Join (two-tone chirp)
void soundPlayerJoin(void) {
    MIKEY.channel_a.control = 0x18;
    MIKEY.channel_a.volume = 0x3F;
    MIKEY.channel_a.reload = 180;
    delay(2000);
    MIKEY.channel_a.reload = 120;
    delay(2000);
    MIKEY.channel_a.volume = 0;
}

// Player Left (descending “sad” blip)
void soundPlayerLeft(void) {
    MIKEY.channel_a.control = 0x18;
    MIKEY.channel_a.volume = 0x3F;
    MIKEY.channel_a.reload = 120;
    delay(2000);
    MIKEY.channel_a.reload = 180;
    delay(3000);
    MIKEY.channel_a.volume = 0;
}

// Select Move (soft UI tick)
void soundSelectMove(void) {
    MIKEY.channel_a.control = 0x1E;
    MIKEY.channel_a.volume = 0x1F;
    MIKEY.channel_a.reload = 160;
    delay(1200);
    MIKEY.channel_a.volume = 0;
}

// Cursor Move (light, fast click)
void soundCursor(void) {
    MIKEY.channel_a.control = 0x1E;
    MIKEY.channel_a.volume = 0x127;
    MIKEY.channel_a.reload = 220;
    delay(800);
    MIKEY.channel_a.volume = 0;
}

// Invalid Input (buzz/error)
void soundCursorInvalid(void) {
	unsigned char i;

    MIKEY.channel_a.control = 0x18;
    MIKEY.channel_a.volume = 0x1F;

    for (i = 0; i < 3; i++) {
        MIKEY.channel_a.reload = 100;
        delay(1500);

        MIKEY.channel_a.reload = 140;
        delay(1500);
    }

    MIKEY.channel_a.volume = 0;
}

// Take Chips (scales with amount)
void soundTakeChip(int counter) {
	int i;
    unsigned char basePitch = 200;

    MIKEY.channel_a.volume = 0x3F;

    // Cap to avoid super long loops
    if (counter > 20) counter = 20;

    for (i = 0; i < counter; i++) {
        MIKEY.channel_a.reload = basePitch - (i * 3);  // rising pitch
        delay(1200);
    }

    MIKEY.channel_a.volume = 0;
}
