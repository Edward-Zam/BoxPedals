// Use ArduinoDSP for optimization
// Credit to Kyle McDonald
#include "dsp.h"

// Create an array for the delay
byte delayarray[2000];

// Define variables
int j;
int fx;
int mode;
int step50;
int step300;
int step10000;
int delayed;

void setup()
{
	setupIO();
	// Instantiate variables
	j = 50;
	step50 = 50;
	step300 = 300;
	step10000 = 1000;
	delayed = 0;

	// Analog input pins 
	modeKnob = 2;
	ammountKnob = 3;
}

void loop()
{
	// Grab knob voltage
	readKnobs();

	// **********************
	// **** Effect Codes ****
	// **********************

	// Bit Crusher: produces a distortion by the reduction 
	// of the resolution or bandwidth of digital audio data.
	if(mode == 6)
	{
		value300 = 1 + ((float)fx / (float)3);
		if(delayed > value300)
		{
			// Read input from guitar
			byte input = analogRead(left);
			// Bit crush by shifting twice
			input = (input >> 6 << 6);
			output(left, input);
			delayed = 0;
		}
		delayed++;
	}

	// Overdrive (medium distortion): 
	if(mode == 7)
	{
		value50 = 1 + ((float) fx / (float) 20);
		// Read input from guitar
		byte input = analogRead(left);
		// Create overdrive by increasing amplitude
		// in order to saturate the signal (clip the
		// signal).
		input = (input * value50);
		output(left, input);
	}

	// Delay: Created by storing audio samples in 
	// audio buffer and then playing them back
	// after a period of time. In this case they
	// are played back once the loop resets. Delayed
	// by 2000 samples.
	if(mode == 9)
	{	
		// Setup loop to store audio in buffer
		for(int i = 0; i <2000; i++)
		{	
			// Output will be audio sample delayed 
			// by 2000 samples.
			output(left, array[i]);
			array[i] = analogRead(left);
						
		}
	}

	if(mode == 10)
	{

	}

	if(mode == 11)
	{

	}

	if(mode ==12)
	{

	}


}

void readKnobs()
{
	// Grab analog input value
	// from mode knob and 
	// determine which mode 
	// it's in. Dividing by 75 
	// will result in clear-cut 
	// values.

	mode = analogRead(modeKnob);
	mode = mode/75;

	// Read analog input value
	// from ammount knob to 
	// to adjust how much "effect"
	// will be applied.
	fx = analogRead(ammountKnob);
}
