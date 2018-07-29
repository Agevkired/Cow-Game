#define grass_spr 41

class grass
{
  public:
  int x, y;
  bool spawned;
  uint16_t spawntimer; //time needed to respawn
  uint16_t spawning;   //counter
  //function
  void spawn();
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
  draw_sprite(x, y, grass_spr, 0);
}
