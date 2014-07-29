#include "GnusbuinoMIDI.h"

#define s1 0
#define s2 1
#define s3 4
#define z 2

int channel;
unsigned char values[8] = {0,0,0,0,0,0,0,0};
unsigned char values_old[8] = {1,1,1,1,1,1,1,1};

void setup ( ) {
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  
  pinMode(z, INPUT);
}

void loop () {
  
  for (channel = 0; channel < 8; channel++) {
    // set switch to output (not sure why, but must be set everytime..)
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    
    // select channel
    digitalWrite(s1, (channel & 0x01));
    digitalWrite(s2, ((channel>>1) & 0x01));
    digitalWrite(s3, ((channel>>2) & 0x01));
      
    // read value
    values[channel] = analogRead(z)>>3;
      
    if (values[channel] != values_old[channel]) {
        MIDI.write(MIDI_CONTROLCHANGE, channel+1, values[channel]);
        values_old[channel] = values[channel];
    }
  }
  
}

