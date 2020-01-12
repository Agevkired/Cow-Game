#ifndef PLAYER_H
#define PLAYER_H

//#include "Arduino.h"

#define framelength 5
#define eatinglength 5
#define neutral 0
#define walking 1 //+1, other side +2, all legs up
#define eat 4 //starting +1,+2: chewing left and right
#define COW_SPIRIT 54
#define COW_DEAD 55

class cow
{
	public:
		//functions
		void cowwalking();
		void coweating();
		void cowmove(int state);
		void setup();
		void setcontrols(int u, int d, int l, int r, int a);
		void died();
		void setrotate(byte rot);
		//getters
		int getx();
		int gety();
		int getsx();
		int getsy();
		byte getframe();
		byte getrotate();
		bool getdead();
		bool geteating();
	private:
		int x, y; //position
		int sx, sy; //position on screen
		byte frame;
		byte animtimer;
		byte eatingtimer;
		byte rotate;
		//byte animbuffer[10];
		bool animframe;
		bool eating;
		bool dead;
		int up, down, left, right, action;		
};

void cow::cowwalking()
{
	if(animtimer > framelength)
	{
		if(frame==3)
		{
			if(animframe)
			{
				frame = walking+1;
				animframe=false;
			}
			else
			{
				frame = walking;
				animframe=true;
			}
		}
		else
		{
			frame = walking+2;
		}
		animtimer=0;
	}
	else
	{
		animtimer++;
	}
}

void cow::coweating()
{
	if(eatingtimer < eatinglength)
	{
		if(animtimer > framelength)
		{
			if(frame==neutral)
			{
				if(animframe)
				{
					frame = eat+2;
					animframe=false;
					eatingtimer++;
				}
				else
				{
					frame = eat+1;
					animframe=true;
					eatingtimer++;
				}
			}
			else
			{
				frame=neutral;
			}
			animtimer=0;
		}
		else
		{
			animtimer++;
		}
	}
	else
	{
		eatingtimer=0;
		eating=false;
	}
}

void cow::cowmove(int state)//, struct crosshair *cross)
{
	if(eating)
	{
		coweating();
	}
	else //MOVING
	{
		if (state & up)
		{
			if(y>72)
			{
				y--;
			}
			cowwalking();
			//Serial.print("UP ");
		}
		if (state & down)
		{
			//if(y<256)
			if(y<472)
			{
				y++;
			}
			cowwalking();
			//Serial.print("DOWN ");
		}
		if (state & left)
		{
			if(x>32)
			{
				x--;
			}
			rotate=0;
			cowwalking();
			//Serial.print("LEFT ");
		}
		if (state & right)
		{
			//if(x<368)
			if(x<480)
			{
				x++;
			}
			rotate=2;
			cowwalking();
			//Serial.print("RIGHT ");
		}
		if (state & action)
		{
			eating=true;
			frame=eat;
		}
		if (state == 0) //Causes frame to lock if any button is held including start
		{
			frame=neutral;
			animtimer=0;
		}
	}
	//POSITION ON SCREEN (480, 464) (368, 256)
	//x position
	if((x >= 200) && (x < 311)) //scrolling
	{
		sx = 200;
	}
	else if(x < 200) //left (origin)
	{
		sx = x;
	}
	else //right
	{
		sx = 200+x-311; //400+111=511
	}
	//y position
	if((y >= 150) && (y < 361)) //scrolling
	{
		sy = 150;
	}
	else if(y < 150) //up (origin)
	{
		sy = y;
	}
	else //down
	{
		sy = 150+y-361; //300+211=511
	}
	//draw_sprite(x, y, frame, rotate);
/*	
	Serial.print("x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.print(y);
	Serial.print(" sx: ");
	Serial.print(sx);
	Serial.print(" sy: ");
	Serial.println(sy);
*/
	//delay(300);
}

void cow::setup()
{
	x = 200; //start player
	y = 150;
	sx = 200;
	sy = 150;
	frame = 0;
	rotate = 0;
	eatingtimer = 0;
	animframe = false;
	eating = false;
	dead = false;
}

void cow::setcontrols(int u, int d, int l, int r, int a)
{
	up=u;
	down=d; 
	left=l;
	right=r;
	action=a;
}

void cow::died()
{
	dead = true;
}

void cow::setrotate(byte rot)
{
	rotate = rot;
}

//GETTERS
int cow::getx(){return x;}
int cow::gety(){return y;}
int cow::getsx(){return sx;}
int cow::getsy(){return sy;}
byte cow::getframe(){return frame;}
byte cow::getrotate(){return rotate;}
bool cow::getdead(){return dead;}
bool cow::geteating(){return eating;}

#endif
