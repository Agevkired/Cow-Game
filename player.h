struct cow
{
  int x, y;
  byte frame;
  byte animtimer;
  byte eatingtimer;
  byte rotate;
  boolean animframe;
  boolean eating;
  boolean dead;
  int up, down, left, right, action;
};

void cowanim(struct cow *player)
{
  if(player->animtimer>5)
  {
    if(player->frame==3)
    {
      if(player->animframe)
      {
        player->frame=2;
        player->animframe=false;
      }
      else
      {
        player->frame=1;
        player->animframe=true;
      }
    }
    else
    {
      player->frame=3;
    }
    player->animtimer=0;
  }
  else
  {
    player->animtimer++;
  }
}

void coweating(struct cow *player)
{
  if(player->eatingtimer<5)
  {
    if(player->animtimer>5)
    {
      if(player->frame==0)
      {
        if(player->animframe)
        {
          player->frame=6;
          player->animframe=false;
          player->eatingtimer++;
        }
        else
        {
          player->frame=5;
          player->animframe=true;
          player->eatingtimer++;
        }
      }
      else
      {
        player->frame=0;
      }
      player->animtimer=0;
    }
    else
    {
      player->animtimer++;
    }
  }
  else
  {
    player->eatingtimer=0;
    player->eating=false;
  }
}

void cowmove(int state, struct cow *player, struct crosshair *cross)
{
  if(player->eating)
  {
    coweating(player);
  }
  else
  {
    if (state & player->up)
    {
      if(player->y>64)
      {
        player->y--;
        //cross->y--;
      }
      cowanim(player);
      //Serial.print("UP ");
    }
    if (state & player->down)
    {
      if(player->y<256)
      {
        player->y++;
        //cross->y++;
      }
      cowanim(player);
      //Serial.print("DOWN ");
    }
    if (state & player->left)
    {
      if(player->x>32)
      {
        player->x--;
        //cross->x--;
      }
      player->rotate=0;
      cowanim(player);
      //Serial.print("LEFT ");
    }
    if (state & player->right)
    {
      if(player->x<368)
      {
        player->x++;
        //cross->x++;
      }
      player->rotate=2;
      cowanim(player);
      //Serial.print("RIGHT ");
    }
    if (state & player->action)
    {
      player->eating=true;
      player->frame=4;
    }
    if (state == 0) //Causes frame to lock if any button is held including start
    {
      player->frame=0;
      player->animtimer=0;
    }
  }
  draw_sprite(player->x, player->y, player->frame, player->rotate);
  //Serial.print("x: ");
  //Serial.print(player->x);
  //Serial.print(" y: ");
  //Serial.println(player->y);
  //delay(300);
}
