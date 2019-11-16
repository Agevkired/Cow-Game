#ifndef GRASS_H
#define GRASS_H

//#include "Arduino.h"

#define grass_spr 41

class grass
{
	public:
		void spawn();
		void setup();
		void eaten();
		byte spr();		
		//getters
		int getx();
		int gety();
	private:
		int x, y;
		bool spawned;
		uint16_t spawntimer; //time needed to respawn
		uint16_t spawning;   //counter
};

void grass::spawn()
{
	if(!spawned)
	{
		if(spawning>spawntimer)
		{
			x=random(32,369);//32-368
			y=random(64,257);//64-256
			spawned=true;
			spawning=0;
		}
		else
		{
			spawning++;
			x=400;
			y=400;
		}
	}
	//draw_sprite(x, y, grass_spr, 0);
}

void grass::setup()
{
		spawned = false;
		spawntimer = 72;
		spawning = 0;
}

void grass::eaten()
{
	x=400;//move grass out of way
	y=400;
	spawned=false;
}

int grass::getx()
{
	return x;
}

int grass::gety()
{
	return y;
}

byte grass::spr()
{
	return grass_spr;
}


#endif
