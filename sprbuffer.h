#ifndef SPRBUFFER_H
#define SPRBUFFER_H

//#include "Arduino.h"

#define MAXSPRITES 30

class sprbuffer
{
	public:
		void insert(int xx, int yy, byte spr, byte rot);
		void sortbuffer();
		int getx(byte select);
		int gety(byte select);
		byte getspr(byte select);
		byte getrot(byte select);
		byte getcounter();
		void resetcounter();
		//Default Constructor
		sprbuffer(){
			counter = 0;
		}
	private:
		int x[MAXSPRITES], y[MAXSPRITES];
		byte counter;
		byte sprite[MAXSPRITES];
		byte rotate[MAXSPRITES];
};

void sprbuffer::insert(int xx, int yy, byte spr, byte rot)
{
	x[counter] = xx;
	y[counter] = yy;
	sprite[counter] = spr;
	rotate[counter] = rot;
	if(counter < MAXSPRITES)
	{
		counter++;
	}
}

void sprbuffer::sortbuffer() //bubble sort currently
{
	int itemp;
	byte btemp;
	for(int n=0; n<counter-1; n++){
		for(int i=n+1; i<counter; i++){
			if(y[n] > y[i]){ //sort all by y position
				itemp = y[n]; //sort y position
				y[n] = y[i];
				y[i] = itemp;
				
				itemp = x[n]; //sort x position
				x[n] = x[i];
				x[i] = itemp;

				btemp = sprite[n]; //sort sprite
				sprite[n] = sprite[i];
				sprite[i] = btemp;

				btemp = rotate[n]; //sort rotate
				rotate[n] = rotate[i];
				rotate[i] = btemp;
			}
		}
	}
}

int sprbuffer::getx(byte select)
{
	return x[select];
}

int sprbuffer::gety(byte select)
{
	return y[select];
}

byte sprbuffer::getspr(byte select)
{
	return sprite[select];
}


byte sprbuffer::getrot(byte select)
{
	return rotate[select];
}

byte sprbuffer::getcounter()
{
	return counter;
}

void sprbuffer::resetcounter()
{
	counter = 0;
}

#endif
