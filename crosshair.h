#ifndef CROSSHAIR_H
#define CROSSHAIR_H

//#include "Arduino.h"

#define crosshair_red	38
#define crosshair_black 39
#define shot_spr		40

class crosshair
{
	public:
		void crosshairmove(int state);
		void setup();
		void setcontrols(int u, int d, int l, int r, int a);
		void setoverwolf(bool set);
		void draw();
		//getters
		int getx();
		int gety();
		int getfx();
		int getfy();
		bool getfire();
	private:
		int x, y;
		int flashx, flashy; //flash coord
		bool overwolf;
		bool fire;
		bool buttondown;
		int up, down, left, right, action;
		byte flashtimer; //how long gun flash linger
};

void crosshair::crosshairmove(int state)
{
    if (state & up)
    {
		if(y>32)
		{
			y--;
			y--;
		}
    }
    if (state & down)
    {
		if(y<288)
		{
			y++;
			y++;
		}
    }
    if (state & left)
    {
		if(x>8)
		{
			x--;
			x--;
		}
    }
    if (state & right)
    {
		if(x<392)
		{
			x++;
			x++;
		}
    }
    if (state & action)
    {
		if(buttondown)
		{
			fire = false;
		}
		else
		{
			fire = true;
			flashtimer = 0;
			flashx = x;
			flashy = y;
		}
		buttondown = true;
    }
    else
    {
		buttondown = false;
    }
	/*Serial.print("cross x: ");
	Serial.print(x);
	Serial.print(" cross y: ");
	Serial.println(y);*/
}

void crosshair::setup()
{
	x = 200; //starts crosshair
	y = 170;
	fire = false;
	buttondown = false;
	flashx = 0;
	flashy = 0;
	flashtimer = 3; //set to flashtimer limit
	overwolf = false;
}

void crosshair::setcontrols(int u, int d, int l, int r, int a)
{
	up=u;
	down=d; 
	left=l;
	right=r;
	action=a;
}

void crosshair::setoverwolf(bool set)
{
	overwolf = set;
}

void crosshair::draw()
{
	if(flashtimer < 3){ //gunshot flash lasts 3 frames
		draw_sprite(flashx, flashy, shot_spr, 0);
		flashtimer++;
    }
    else{
		draw_sprite(400, 400, shot_spr, 0); //park sprite off screen
    }
	if(overwolf){
		draw_sprite(x, y, crosshair_red, 0);
	}
	else{
		draw_sprite(x, y, crosshair_black, 0);
	}
}

//getters
int crosshair::getx(){return x;}
int crosshair::gety(){return y;}
int crosshair::getfx(){return flashx;}
int crosshair::getfy(){return flashy;}
bool crosshair::getfire(){return fire;}

#endif
