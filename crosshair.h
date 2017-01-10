struct crosshair
{
  int x, y;
  boolean fire;
  boolean buttondown;
  boolean overwolf;
  int up, down, left, right, action;
  byte flashtimer; //how long gun flash linger
  int flashx, flashy; //flash coord
};

void crosshairmove(int state, struct crosshair *player, byte *crosshairspr)
{
    if (state & player->up)
    {
      if(player->y>32)
      {
        player->y--;
        player->y--;
      }
    }
    if (state & player->down)
    {
      if(player->y<288)
      {
        player->y++;
        player->y++;
      }
    }
    if (state & player->left)
    {
      if(player->x>8)
      {
        player->x--;
        player->x--;
      }
    }
    if (state & player->right)
    {
      if(player->x<392)
      {
        player->x++;
        player->x++;
      }
    }
    if (state & player->action)
    {
      if(player->buttondown)
      {
        player->fire = false;
        //draw_sprite(400, 400, 9, 0);
      }
      else
      {
        //draw_sprite(player->x, player->y, 9, 0);
        player->fire = true;
		player->flashtimer = 0;
		player->flashx = player->x;
		player->flashy = player->y;
      }
      player->buttondown = true;
    }
    else
    {
      player->buttondown = false;
	  //draw_sprite(400, 400, 9, 0);
    }
    if(player->flashtimer < 3){ //gunshot flash lasts 3 frames
		draw_sprite(player->flashx, player->flashy, 9, 0);
		player->flashtimer++;
    }
    else{
		draw_sprite(400, 400, 9, 0);
    }
	(*crosshairspr) = GD.spr;
	if(player->overwolf){
		draw_sprite(player->x, player->y, 18, 0);
	}
	else{
		draw_sprite(player->x, player->y, 7, 0);
	}
	//draw_sprite(player->x, player->y, 7, 0);
	/*Serial.print("cross x: ");
	Serial.print(player->x);
	Serial.print(" cross y: ");
	Serial.println(player->y);*/
}
