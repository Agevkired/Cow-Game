#define chaser_neutral 	42
#define chaser_walk		43
#define chaser_walk3	45

#define charger_neutral 46
#define charger_walk	47
#define charger_walk3	49

class wolf
{
  public:
  int x, y;
  bool spawn; //if spawned
  uint16_t spawntimer; //time needed to respawn
  uint16_t spawning;   //counter
  uint16_t blinktimer; //time needed to start moving
  byte type; //type of wolf  0:normal 1:charge
  byte rotate;
  byte frame; //which sprite to display
  byte animtimer; //timer for animation
  bool animframe; //helps switch between 3 frames in order 1,3,2,3,1,3,2,3...
  bool charging;  //for charging wolf
  bool avoid; //move random when targeted
  uint16_t movingtimer;  //time until starts moving in another direction
  uint16_t moving; //counter for moving
  byte movedirection; //direction for moving 0-7 N,NE,E,SE,S,SW,W,NW
  byte chasespeed; //sets speed of chase
  byte chasecounter; //counter for chasing
  byte moveswitch; //checks if movement will go a certain way, use random()
  byte moveduration; //how long specific movement will last
  byte movecounter; //counter for movement type
  long scorespawn; //how much points needed for this to spawn
  //functions
  void wolfspawn(long score);
  void wolfanim();
  void wolfblink(); //makes wolf flicker
  void randomwolfmove();
  void wolfcharging();
  void wolfchase(int cowx, int cowy); //CHASE COW
  void wolfmove(int cowx, int cowy, unsigned long score);
};

void wolf::wolfspawn(long score)
{
  if((!spawn)&&(score>scorespawn)) //IF HASN'T SPAWN YET AND POINTS PAST A THRESHOLD
  {
    if(spawning>spawntimer)
    {
	  type = 0; //default to chaser
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
      movingtimer=random(216,289); //redo this
      if(score>1000) //WHEN TO SPAWN CHARGERS
      {
        type=random(63)%2;
        if(type==1)
        {
          movingtimer=random(36,73); //redo this
        }
      }
      //chasespeed=(random(99))%2;
      chasespeed=0;
      spawn=true;
      moveswitch=random(150)%10;
      //spawning=0;
    }
    else
    {
      spawning++;
      x=420;
      y=420;
    }
  }
  //draw_sprite(x, y, frame, rotate);
}

void wolf::wolfanim()
{
  if(animtimer>5) //frames each animation lasts
  {
    if(frame==chaser_walk3+(type*4))
    {
      if(animframe)
      {
        frame=chaser_walk+1+(type*4);
        animframe=false;
      }
      else
      {
        frame=chaser_walk+(type*4);
        animframe=true;
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
}

void wolf::wolfblink() //makes wolf flicker
{
  if(animtimer>5) //hopefully 3 times a second
  {
    animtimer=0;
    if(frame==charger_neutral)
    {
      //frame=10+(type*4);
      frame=chaser_neutral;
    }
    else
    {
      //frame=9;
      frame=charger_neutral;
    }
  }
  else
  {
    animtimer++;
  }
}

void wolf::randomwolfmove()
{
	if(moving > movingtimer)
	{
		moving=0;
		movedirection=random(40)%8;
	}
	else
	{
		moving++;
		if((movedirection==0)||(movedirection==1)||(movedirection==7))//NORTH
		{
			if(y > 63)
			{
				y--;
			} 
			wolfanim();
		}//END NORTH
		if((movedirection==1)||(movedirection==2)||(movedirection==3))//EAST
		{
			if(x < 376)
			{
				x++;
			}
			rotate=2; 
			wolfanim();
		}//END EAST
		if((movedirection==3)||(movedirection==4)||(movedirection==5))//SOUTH
		{
			if(y < 256)
			{
				y++;
			} 
			wolfanim();
		}//END SOUTH
		if((movedirection==5)||(movedirection==6)||(movedirection==7))//WEST
		{
			if(x > 23)
			{
				x--;
			}
			rotate=0; 
			wolfanim();
		}//END WEST
		//draw_sprite(x, y, frame, rotate);
	}
}

void wolf::wolfcharging()
{
  if(movedirection==0)//GOING UP
  {
    if(y > 64)
	{
	  y-=3;
	}
    else
	{
	  charging=false;
	}
  }
  else if(movedirection==2)//GOING RIGHT
  {
    if(x < 377)
	{
	  x+=3; 
	  rotate=2;
	}
    else
	{
	  charging=false;
	}
  }
  else if(movedirection==4)//GOING DOWN
  {
    if(y < 257)
	{
	  y+=3;
	}
    else
	{
	  charging=false;
	}
  }
  else if(movedirection==6)//GOING LEFT
  {
    if(x > 24)
	{
	  x-=3; 
	  rotate=0;
	}
    else
	{
	  charging=false;
	}
  }
  wolfanim();
  wolfanim();
  wolfanim();
}

void wolf::wolfchase(int cowx, int cowy) //CHASE COW
{
  if(x < cowx)
  {
    x++; 
	wolfanim(); 
	rotate=2;
  }
  else if(x > cowx)
  {
	x--; 
	wolfanim(); 
	rotate=0;
  }
  if(y < cowy)
  {
	y++; 
	wolfanim();
  }
  else if(y > cowy)
  {
	y--; 
	wolfanim();
  }
}

void wolf::wolfmove(int cowx, int cowy, unsigned long score)
{
  if(spawning > (blinktimer+spawntimer))
  {
	  
    if(type==0) //CHASING TYPE
    {
		//wolfchase(wolf, cow);
		if((avoid)&&(movecounter < moveduration)&&(score > 500))
		{
			randomwolfmove();
			movecounter++;
		}
		else
		{
			moveduration=random(36,72); //how long wolf will avoid when targeted
			avoid = false;
			movecounter = 0; //set avoid counter to 0
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
			wolfanim();
		}
    }
	
    else if(type==1) //CHARGING TYPE
    {
      if(!charging)
      {
        randomwolfmove();
        if((x < cowx+1) && (x > cowx-1)) //CHECKS IF COW IS ON X+-1 TO WOLF
        {
          if(y > cowy) //IF WOLF IS BELOW
          {
            movedirection = 0;
            charging = true;
          }
          else if(y < cowy) //ABOVE
          {
            movedirection = 4;
            charging = true;
          }
        }
        else if((y < cowy+1) && (y > cowy-1)) //CHECKS IF COW IS Y+-1
        {
          if(x > cowx) //IF WOLF IS TO THE RIGHT
          {
            movedirection = 6;
            rotate = 0;
            charging = true;
          }
          else if(x < cowx) //LEFT
          {
            movedirection = 2;
            rotate = 2;
            charging = true;
          }
        }
      }
      if(charging)
      {
        wolfcharging();
      }
    }
    //draw_sprite(x, y, frame, rotate);
  }
  else
  {
    spawning++;
    wolfblink();
    //draw_sprite(x, y, frame, rotate);
  }
}
