#define framelength 5
#define eatinglength 5
#define neutral 0
#define walking 1 //+1, other side +2, all legs up
#define eat 4 //starting +1,+2: chewing left and right

class cow
{
  public:
  int x, y; //position
  byte frame;
  byte animtimer;
  byte eatingtimer;
  byte rotate;
  byte animbuffer[10];
  bool animframe;
  bool eating;
  bool dead;
  int up, down, left, right, action;
  //functions
  void cowwalking();
  void coweating();
  void cowmove(int state);
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
      if(y>64)
      {
        y--;
      }
      cowwalking();
      //Serial.print("UP ");
    }
    if (state & down)
    {
      if(y<256)
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
      if(x<368)
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
  draw_sprite(x, y, frame, rotate);
  //Serial.print("x: ");
  //Serial.print(x);
  //Serial.print(" y: ");
  //Serial.println(y);
  //delay(300);
}
