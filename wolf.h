#ifndef WOLF_H
#define WOLF_H

//#include "Arduino.h"

#define chaser_neutral 	42
#define chaser_walk		43
#define chaser_walk3	45

#define charger_neutral 46
#define charger_walk	47
#define charger_walk3	49

#define spawned 	B10000000
#define animframe 	B01000000
#define charging 	B00100000
#define avoid 		B00010000
#define wolfstate 	B00000011
//					B00100000

#define speed 1 //future use
#define chargespeed 2

#define nborder 64
#define sborder 256
#define wborder 32
#define eborder 368

#define chargerscore 100

class wolf
{
	public:
		//functions
		void activate(int cowx, int cowy, unsigned long score, bool printit, byte id);
		void wolfspawn(unsigned long score);
		void wolfanim();
		void wolfblink(); //makes wolf flicker
		void randomwolfmove();
		void wolfcharging();
		void wolfchase(int cowx, int cowy); //CHASE COW
		void wolfmove(int cowx, int cowy, unsigned long score);
		void setup(long tempscorespawn, word respawn);
		void killed(word respawn);
		//getters
		int getx();
		int gety();
		byte getframe();
		byte getrotate();
		bool getspawn();
		void setavoid();
		byte getstatus();
	private:
		//functions
		void settrue(byte flag);
		void setfalse(byte flag);
		bool getflag(byte flag);
		//variables
		int x, y;
		word counter;   //counter
		//**handled in spawning
		word spawntimer; //time needed to respawn
		byte type; //type of wolf  0:normal 1:charge
		//**animation
		byte rotate;
		byte frame; //which sprite to display
		byte animtimer; //timer for animation
		//**movement
		byte chasespeed; //sets speed of chase, currently 1/2 speed (use for later)
		byte chasecounter; //counter for chasing, used with chasespeed
		byte moveduration; //how long specific movement will last (chaser=random)		
		//****random movement
		word ranmovingtimer;  //time until starts moving in another direction
		word ranmoving; //counter for moving
		byte movedirection; //direction for moving 0-7 N,NE,E,SE,S,SW,W,NW
		/*spawned, animframe, charging, avoid, empty, empty, empty, emnpty
		 *spawned: if spawned
		 *animframe: switch between 3 frames in order 1,3,2,3,1,3,2,3...
		 *charging: for charging wolf
		 *avoid: move random when targeted
		 */
		byte status;
		//byte wstate; //test
		
		//bool spawn; //if spawned
		//bool animframe; //helps switch between 3 frames in order 1,3,2,3,1,3,2,3...
		//bool charging;  //
		//bool avoid; //	
//		byte moveswitch; //checks if movement will go a certain way, use random()
//		byte movecounter; //counter for movement type
//		long scorespawn; //how much points needed for this to spawn	
};

void wolf::activate(int cowx, int cowy, unsigned long score, bool printit, byte id)
{
	if((status & wolfstate) == 0)
	//if(wstate == 0)
	{
		//SPAWNING
		//Serial.println("state 0");
		wolfspawn(score);
	}
	else if((status & wolfstate) == 1)
	//else if(wstate == 1)
	{
		//BLINK
		//Serial.println("state 1");
		wolfblink();
	}
	else if((status & wolfstate) == 2)
	//else if(wstate == 2)
	{
		//ACTION
		//Serial.println("state 2");
		wolfmove(cowx, cowy, score);
	}
	else if((status & wolfstate) == 3)
	//else if(wstate == 3)
	{
		//DEAD
	}
	if(printit)
	{
		Serial.print("Wolf ");
		Serial.print(id);
		Serial.print(":");
		Serial.print(" type: ");
		Serial.print(type);
		Serial.print(" x: ");
		Serial.print(x);
		Serial.print(" y: ");
		Serial.print(y);
		Serial.print(" counter: ");
		Serial.print(counter);
		Serial.print(" state: ");
		Serial.println(status & wolfstate);
		//Serial.println(wstate);
		//Serial.print();
	}
}
//STATE 0
void wolf::wolfspawn(unsigned long score)
{
//	if(!getflag(spawned)) //IF HASN'T SPAWN YET
//	{
		if(counter>spawntimer)
		{	
			//PLACE WOLF IN RANDOM LOCATION OUTSIDE FENCE
			byte location = random(127)%4;
			if(location==0) //NORTH
			{
				y=32;
				x=random(24,377); //24-376
			}
			else if(location==1) //EAST
			{
				x=392;
				rotate=0;
				y=random(64,257); //64-256
			}
			else if(location==2) //SOUTH
			{
				y=288;
				x=random(24,377);
			}
			else if(location==3) //WEST
			{
				x=8;
				rotate=2;
				y=random(64,257);
			}
			//DETERMINE WOLF TYPE
			type = 0; //default to chaser
			ranmovingtimer=random(216,289); //redo this
			if(score > chargerscore) //WHEN TO SPAWN CHARGERS
			{
				type=random(63)%2;
				if(type==1)
				{
					ranmovingtimer=random(36,73); //redo this
				}
			}
			//chasespeed=(random(99))%2;
			chasespeed=0;
			settrue(spawned); //set spawn to true
//			moveswitch=random(150)%10;
			counter=0;
			status = status & B11111100;
			status = status | 1; //move to blinking
			//wstate++; //1
		}
		else
		{
			//Serial.print("state 0 counter: ");
			//Serial.println(counter);
			counter++;
			x=420;
			y=420;
		}
//	}
}
//STATE 1
void wolf::wolfblink() //makes wolf flicker
{
	if(counter < 144) //2 seconds
	{
		if((counter%9) == 0) //hopefully 3 times a second
		{
			if(frame==charger_neutral)
			{
				frame=chaser_neutral;
			}
			else
			{
				frame=charger_neutral;
			}
		}
		counter++;
	}
	else
	{
		counter = 0;
		status = status & B11111100;
		status = status | 2; //move to action
		//wstate++; //2
	}
}
//STATE 2
void wolf::wolfmove(int cowx, int cowy, unsigned long score)
{
	//CHASING TYPE
	if(type==0)
	{
		//Serial.println("In state 2 chasing");
		//wolfchase(wolf, cow);
		//random movement
		if((getflag(avoid)) && (counter < moveduration) && (score > 500))
		{
			//Serial.println("Chasing random");
			randomwolfmove();
			counter++;
			//Serial.println("End Chasing random");
		}
		//normal movement
		else
		{
			//Serial.println("Chasing normal");
			moveduration=random(36,72); //how long wolf will avoid when targeted
			setfalse(avoid);
			counter = 0; //set avoid counter to 0
			ranmoving = 0;
			movedirection=random(40)%8; //randomize movement when called
			if(chasecounter > chasespeed)//CHASE BLOCK
			{
				wolfchase(cowx, cowy);
				chasecounter=0; //chase every other frame
			}
			else
			{
				chasecounter++;
			} //END CHASE BLOCK
			//Serial.println("End Chasing normal");
			//wolfanim(); //animate 2x
		}
		//Serial.println("End In state 2 chasing");
	}
	//CHARGING TYPE
	else if(type==1) 
	{
		if(getflag(charging))
		{
			//Serial.print("Charge active: ");
			//Serial.println(getflag(charging));
			wolfcharging();
		}
		else
		{
			//Serial.print("Random. Charge should be false: ");
			//Serial.println(getflag(charging));
			randomwolfmove();
			if((x < cowx+2) && (x > cowx-2)) //CHECKS IF COW IS ON X+-1 TO WOLF
			{
				if(y > cowy) //IF WOLF IS BELOW
				{
					movedirection = 0;
					settrue(charging);
				}
				else if(y < cowy) //ABOVE
				{
					movedirection = 4;
					settrue(charging);
				}
			}
			else if((y < cowy+2) && (y > cowy-2)) //CHECKS IF COW IS Y+-1
			{
				if(x > cowx) //IF WOLF IS TO THE RIGHT
				{
					movedirection = 6;
					rotate = 0;
					settrue(charging);
				}
				else if(x < cowx) //LEFT
				{
					movedirection = 2;
					rotate = 2;
					settrue(charging);
				}
			}
		}
	}
}

//CYCLES THE WALKING FRAMES
void wolf::wolfanim()
{
	//Serial.println("Wolf anim");
	if(animtimer>5) //frames each animation lasts
	{
		if(frame == chaser_walk3+(type*4))
		{
			if(getflag(animframe))
			{
				frame=chaser_walk+1+(type*4);
				setfalse(animframe); //set to false
			}
			else
			{
				frame=chaser_walk+(type*4);
				settrue(animframe); //set to true
			}
		}
		else
		{
			frame=chaser_walk3+(type*4);
		}
		animtimer=0;
	}
	else
	{
		animtimer++;
	}
	//Serial.println("End Wolf anim");
}

void wolf::randomwolfmove()
{
	//Serial.print("Wolf random: ");
	//Serial.println(movedirection);
	int dx=0, dy=0;
	if(ranmoving > ranmovingtimer)
	{
		ranmoving=0;
		ranmovingtimer = random(36,73);
		movedirection=random(40)%8;
	}
	else
	{
		ranmoving++;
		if((movedirection==0)||(movedirection==1)||(movedirection==7))//NORTH
		{
			if(y > nborder)
			{
				dy--;
			} 
			wolfanim();
		}//END NORTH
		if((movedirection==1)||(movedirection==2)||(movedirection==3))//EAST
		{
			if(x < eborder)
			{
				dx++;
			}
			rotate=2; 
			wolfanim();
		}//END EAST
		if((movedirection==3)||(movedirection==4)||(movedirection==5))//SOUTH
		{
			if(y < sborder)
			{
				dy++;
			} 
			wolfanim();
		}//END SOUTH
		if((movedirection==5)||(movedirection==6)||(movedirection==7))//WEST
		{
			if(x > wborder)
			{
				dx--;
			}
			rotate=0; 
			wolfanim();
		}//END WEST
		x += dx * speed; //for future use
		y += dy * speed;
	}
}

void wolf::wolfcharging()
{
	//Serial.print("Wolf charging: ");
	//Serial.println(movedirection);
	int dx=0, dy=0;
	if(movedirection==0)//GOING UP
	{
		if(y > nborder)
		{
			dy-=1;
		}
		else
		{
			//Serial.println("Charge off");
			y = nborder;
			setfalse(charging); //stop after reaching fence/border
		}
	}
	else if(movedirection==2)//GOING RIGHT
	{
		if(x < eborder)
		{
			dx+=1; 
			rotate=2;
		}
		else
		{
			//Serial.println("Charge off");
			x = eborder;
			setfalse(charging);
		}
	}
	else if(movedirection==4)//GOING DOWN
	{
		if(y < sborder)
		{
			dy+=1;
		}
		else
		{
			//Serial.println("Charge off");
			y = sborder;
			setfalse(charging);
		}
	}
	else if(movedirection==6)//GOING LEFT
	{
		if(x > wborder)
		{
			dx-=1; 
			rotate=0;
		}
		else
		{
			//Serial.println("Charge off");
			x = wborder;
			setfalse(charging);
		}
	}
	x += dx * chargespeed; //for future use
	y += dy * chargespeed;
	wolfanim();
	wolfanim();
}

void wolf::wolfchase(int cowx, int cowy) //CHASE COW
{
	//Serial.println("Wolf Chase");
	int dx=0, dy=0;
	if(x < cowx)
	{
		dx++;
		wolfanim(); 
		rotate=2;
	}
	else if(x > cowx)
	{
		dx--;
		wolfanim(); 
		rotate=0;
	}
	if(y < cowy)
	{
		dy++;
		wolfanim();
	}
	else if(y > cowy)
	{
		dy--; 
		wolfanim();
	}
	x += dx * speed; //for future use
	y += dy * speed;
}

void wolf::setup(long tempscorespawn, word respawn)
{
	killed(respawn);
	rotate=0;
	setfalse(charging);
	type=0;
	frame=10;
//	moveswitch=0;
	moveduration=random(36,145);
//	movecounter=0;
	setfalse(avoid);
//	scorespawn=tempscorespawn;
}

void wolf::killed(word respawn)
{
	Serial.println("Killed");
	x = 450; y = 450;;
	counter = 0;   //counter
	//**handled in spawning
	spawntimer = respawn; //time needed to respawn
	type = 0; //type of wolf  0:normal 1:charge
	//**animation
	rotate = 0;
	frame = 10; //which sprite to display
	animtimer = 0; //timer for animation
	//**movement
	chasespeed = 0; //sets speed of chase, currently 1/2 speed (use for later)
	chasecounter = 0; //counter for chasing, used with chasespeed
	moveduration = random(36,145);; //how long specific movement will last (chaser=random)		
	//****random movement
	ranmovingtimer = 0;  //time until starts moving in another direction
	ranmoving = 0; //counter for moving
	movedirection = 0; //direction for moving 0-7 N,NE,E,SE,S,SW,W,NW
	/*spawned, animframe, charging, avoid, empty, empty, empty, emnpty
	 *spawned: if spawned
	 *animframe: switch between 3 frames in order 1,3,2,3,1,3,2,3...
	 *charging: for charging wolf
	 *avoid: move random when targeted
	 */
	status = 0;
	//wstate = 0;
}

//PRIVATE FUNCTIONS
void wolf::settrue(byte flag)
{
/*	Serial.print("Set TRUE: ");
	Serial.print(flag, BIN);
	Serial.print(" Status: ");
	Serial.print(status, BIN);
*/	
	status = status | flag;
/*	
	Serial.print(" Post-Status: ");
	Serial.println(status, BIN);
*/
}

void wolf::setfalse(byte flag)
{
/*	byte dummy = flag;
	Serial.print("Set FALSE: ");
	Serial.print(flag, BIN);
	Serial.print(" Status: ");
	Serial.print(status, BIN);
*/	
	status = status & (~flag);
	//status = status & !dummy;
/*	
	Serial.print(" Post-Status: ");
	Serial.print(status, BIN);
	Serial.print(" Negated: ");
	Serial.println(~flag, BIN);
	//Serial.println(!dummy, BIN);
*/
}

bool wolf::getflag(byte flag)
{
	bool x = ((status & flag) == flag);
	return x; //redundant but might fix quirk
}
//PRIVATE FUNCTIONS

void wolf::setavoid(){settrue(avoid);}

//getters
int wolf::getx(){return x;}
int wolf::gety(){return y;}
byte wolf::getframe(){return frame;}
byte wolf::getrotate(){return rotate;}
bool wolf::getspawn(){return status & spawned;}
byte wolf::getstatus(){return status;}

#endif
