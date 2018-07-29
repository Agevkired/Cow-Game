#define crosshair_black 38
#define crosshair_red	39
#define shot_spr	40

class crosshair
{
  public:
  int x, y;
  bool fire;
  bool buttondown;
  bool overwolf;
  int up, down, left, right, action;
  byte flashtimer; //how long gun flash linger
  int flashx, flashy; //flash coord
  //function
  void crosshairmove(int state, byte *crosshairspr);
};

void crosshair::crosshairmove(int state, byte *crosshairspr)
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
        //draw_sprite(400, 400, 9, 0);
      }
      else
      {
        //draw_sprite(x, y, 9, 0);
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
	  //draw_sprite(400, 400, 9, 0);
    }
    if(flashtimer < 3){ //gunshot flash lasts 3 frames
		draw_sprite(flashx, flashy, shot_spr, 0);
		flashtimer++;
    }
    else{
		draw_sprite(400, 400, shot_spr, 0); //park sprite off screen
    }
	(*crosshairspr) = GD.spr;
	if(overwolf){
		draw_sprite(x, y, crosshair_black, 0);
	}
	else{
		draw_sprite(x, y, crosshair_red, 0);
	}
	//draw_sprite(x, y, 7, 0);
	/*Serial.print("cross x: ");
	Serial.print(x);
	Serial.print(" cross y: ");
	Serial.println(y);*/
}
