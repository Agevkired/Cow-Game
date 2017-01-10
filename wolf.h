struct wolf
{
  int x, y;
  boolean spawn; //if spawned
  uint16_t spawntimer; //time needed to respawn
  uint16_t spawning;   //counter
  uint16_t blinktimer; //time needed to start moving
  byte type; //type of wolf  0:normal 1:charge
  byte rotate;
  byte frame; //which sprite to display
  byte animtimer; //timer for animation
  boolean animframe; //helps switch between 3 frames in order 1,3,2,3,1,3,2,3...
  boolean charging;  //for charging wolf
  boolean avoid; //move random when targeted
  uint16_t movingtimer;  //time until starts moving in another direction
  uint16_t moving; //counter for moving
  byte movedirection; //direction for moving 0-7 N,NE,E,SE,S,SW,W,NW
  byte chasespeed; //sets speed of chase
  byte chasecounter; //counter for chasing
  byte moveswitch; //checks if movement will go a certain way, use random()
  byte moveduration; //how long specific movement will last
  byte movecounter; //counter for movement type
  long scorespawn; //how much points needed for this to spawn
};

void wolfspawn(struct wolf *wolf, long score)
{
  if((!wolf->spawn)&&(score>wolf->scorespawn)) //IF HASN'T SPAWN YET AND POINTS PAST A THRESHOLD
  {
    if(wolf->spawning>wolf->spawntimer)
    {
      byte location = random(127)%4;
      if(location==0) //NORTH
      {
        wolf->y=32;
        wolf->x=random(24,377); //24-376
      }
      else if(location==1) //EAST
      {
        wolf->x=392;
        wolf->rotate=0;
        wolf->y=random(64,257); //64-256
      }
      else if(location==2) //SOUTH
      {
        wolf->y=288;
        wolf->x=random(24,377);
      }
      else if(location==3) //WEST
      {
        wolf->x=8;
        wolf->rotate=2;
        wolf->y=random(64,257);
      }
      wolf->movingtimer=random(216,289);
      if(score>1000) //WHEN TO SPAWN CHARGERS
      {
        wolf->type=random(63)%2;
        if(wolf->type==1)
        {
          wolf->movingtimer=random(36,73);
        }
      }
      //wolf->chasespeed=(random(99))%2;
      wolf->chasespeed=0;
      wolf->spawn=true;
      wolf->moveswitch=random(150)%10;
      //wolf->spawning=0;
    }
    else
    {
      wolf->spawning++;
      wolf->x=420;
      wolf->y=420;
    }
  }
  //draw_sprite(wolf->x, wolf->y, wolf->frame, wolf->rotate);
}

void wolfanim(struct wolf *wolf)
{
  if(wolf->animtimer>5) //frames each animation lasts
  {
    if(wolf->frame==13+(wolf->type*4))
    {
      if(wolf->animframe)
      {
        wolf->frame=12+(wolf->type*4);
        wolf->animframe=false;
      }
      else
      {
        wolf->frame=11+(wolf->type*4);
        wolf->animframe=true;
      }
    }
    else
    {
      wolf->frame=13+(wolf->type*4);
    }
    wolf->animtimer=0;
  }
  else
  {
    wolf->animtimer++;
  }
}

void wolfblink(struct wolf *wolf) //makes wolf flicker
{
  if(wolf->animtimer>5) //hopefully 3 times a second
  {
    wolf->animtimer=0;
    if(wolf->frame==14)
    {
      //wolf->frame=10+(wolf->type*4);
      wolf->frame=10;
    }
    else
    {
      //wolf->frame=9;
      wolf->frame=14;
    }
  }
  else
  {
    wolf->animtimer++;
  }
}

void randomwolfmove(struct wolf *wolf)
{
	if(wolf->moving > wolf->movingtimer)
	{
		wolf->moving=0;
		wolf->movedirection=random(40)%8;
	}
	else
	{
		wolf->moving++;
		if((wolf->movedirection==0)||(wolf->movedirection==1)||(wolf->movedirection==7)){//NORTH
			if(wolf->y > 63){
				wolf->y--;
			} 
			wolfanim(wolf);
		}//END NORTH
		if((wolf->movedirection==1)||(wolf->movedirection==2)||(wolf->movedirection==3)){//EAST
			if(wolf->x < 376){
				wolf->x++;
			}
			wolf->rotate=2; 
			wolfanim(wolf);
		}//END EAST
		if((wolf->movedirection==3)||(wolf->movedirection==4)||(wolf->movedirection==5)){//SOUTH
			if(wolf->y < 256){
				wolf->y++;
			} 
			wolfanim(wolf);
		}//END SOUTH
		if((wolf->movedirection==5)||(wolf->movedirection==6)||(wolf->movedirection==7)){//WEST
			if(wolf->x > 23){
				wolf->x--;
			}
			wolf->rotate=0; 
			wolfanim(wolf);
		}//END WEST
		//draw_sprite(wolf->x, wolf->y, wolf->frame, wolf->rotate);
	}
}

void wolfcharging(struct wolf *wolf)
{
  if(wolf->movedirection==0)//GOING UP
  {
    if(wolf->y > 64){wolf->y-=3;}
    else(wolf->charging=false);
  }
  else if(wolf->movedirection==2)//GOING RIGHT
  {
    if(wolf->x < 377){wolf->x+=3; wolf->rotate=2;}
    else(wolf->charging=false);
  }
  else if(wolf->movedirection==4)//GOING DOWN
  {
    if(wolf->y < 257){wolf->y+=3;}
    else(wolf->charging=false);
  }
  else if(wolf->movedirection==6)//GOING LEFT
  {
    if(wolf->x > 24){wolf->x-=3; wolf->rotate=0;}
    else(wolf->charging=false);
  }
  wolfanim(wolf);
  wolfanim(wolf);
  wolfanim(wolf);
}

void wolfchase(struct wolf *wolf, struct cow *cow) //CHASE COW
{
  if(wolf->x < cow->x){wolf->x++; wolfanim(wolf); wolf->rotate=2;}
  else if(wolf->x > cow->x){wolf->x--; wolfanim(wolf); wolf->rotate=0;}
  if(wolf->y < cow->y){wolf->y++; wolfanim(wolf);}
  else if(wolf->y > cow->y){wolf->y--; wolfanim(wolf);}
}

void wolfmove(struct wolf *wolf, struct cow *cow, unsigned long sco)
{
  if(wolf->spawning > ((wolf->blinktimer)+(wolf->spawntimer)))
  {
	  
    if(wolf->type==0) //CHASING TYPE
    {
		//wolfchase(wolf, cow);
		if((wolf->avoid)&&(wolf->movecounter < wolf->moveduration)&&(sco > 500))
		{
			randomwolfmove(wolf);
			wolf->movecounter++;
		}
		else
		{
			wolf->moveduration=random(36,72); //how long wolf will avoid when targeted
			wolf->avoid = false;
			wolf->movecounter = 0; //set avoid counter to 0
			wolf->movedirection=random(40)%8; //randomize movement when called
			if(wolf->chasecounter > wolf->chasespeed)//CHASE BLOCK
			{
				wolfchase(wolf, cow);
				wolf->chasecounter=0; //chase every other frame
			}
			else
			{
				wolf->chasecounter++;
			} //END CHASE BLOCK
			wolfanim(wolf);
		}
	  
      /*if(wolf->movecounter > wolf->moveduration) //OLD STUFF
      {
        wolf->moveswitch=random(150)%10;
        wolf->moveduration=random(36,145);
        wolf->movecounter=0;
      }
      else
      {
        wolf->movecounter++;
      }
      
      if(wolf->moveswitch!=5)
      {
		if(wolf->chasecounter > wolf->chasespeed)//CHASE BLOCK
        {
            wolfchase(wolf, cow);
            wolf->chasecounter=0;
        }
        else
        {
            wolf->chasecounter++;
        }
        wolfanim(wolf);
      }
      else
      {
      	randomwolfmove(wolf);
      }*/
    }
	
    else if(wolf->type==1) //CHARGING TYPE
    {
      if(!wolf->charging)
      {
        randomwolfmove(wolf);
        if((wolf->x < cow->x+1) && (wolf->x > cow->x-1)) //CHECKS IF COW IS ON X+-1 TO WOLF
        {
          if(wolf->y > cow->y) //IF WOLF IS BELOW
          {
            wolf->movedirection = 0;
            wolf->charging = true;
          }
          else if(wolf->y < cow->y) //ABOVE
          {
            wolf->movedirection = 4;
            wolf->charging = true;
          }
        }
        else if((wolf->y < cow->y+1) && (wolf->y > cow->y-1)) //CHECKS IF COW IS Y+-1
        {
          if(wolf->x > cow->x) //IF WOLF IS TO THE RIGHT
          {
            wolf->movedirection = 6;
            wolf->rotate = 0;
            wolf->charging = true;
          }
          else if(wolf->x < cow->x) //LEFT
          {
            wolf->movedirection = 2;
            wolf->rotate = 2;
            wolf->charging = true;
          }
        }
      }
      if(wolf->charging)
      {
        wolfcharging(wolf);
      }
    }
    //draw_sprite(wolf->x, wolf->y, wolf->frame, wolf->rotate);
  }
  else
  {
    wolf->spawning++;
    wolfblink(wolf);
    //draw_sprite(wolf->x, wolf->y, wolf->frame, wolf->rotate);
  }
}
