struct grass
{
  int x, y;
  boolean spawn;
  uint16_t spawntimer; //time needed to respawn
  uint16_t spawning;   //counter
};

void spawn(struct grass *grasses)
{
  if(!grasses->spawn)
  {
    if(grasses->spawning>grasses->spawntimer)
    {
      grasses->x=random(32,369);//32-368
      grasses->y=random(64,257);//64-256
      grasses->spawn=true;
      grasses->spawning=0;
    }
    else
    {
      grasses->spawning++;
      grasses->x=400;
      grasses->y=400;
    }
  }
  draw_sprite(grasses->x, grasses->y, 8, 0);
}
