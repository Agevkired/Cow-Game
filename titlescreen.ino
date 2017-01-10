#include <SNESpad.h>
#include <SPI.h>
#include <GD.h>

#include "image.h"
#include "sprite.h"
#include "grass.h"
#include "crosshair.h"
#include "player.h"
#include "wolf.h"

#define BG_BLUE 33
#define BG_ZERO  1
#define BG_COW  24
#define BG_B    21
#define BG_TIME 11

int state=0;
//static int cowup, cowdown, cowleft, cowright, coweat;  //implement cow control
//static int crossup, crossdown, crossleft, crossright, crossfire;  //implement crosshair control
SNESpad nintendo(5,6,7);
struct cow player;
struct crosshair pcrosshair;
struct grass grasses[10];
struct wolf wolves[10];
static unsigned long highscore;
static unsigned long score;
static uint8_t bonus;
static unsigned long bonustimer;
static uint8_t lives;
static boolean lefty;
static byte switchsidetimer;
static byte bonuslife;
static unsigned long bonusscore;
static boolean title;
static boolean holdselect;

void gameloop();

static uint16_t atxy(byte x, byte y)
{
  return RAM_PIC + 64 * y + x;
}

static void draw_score(uint16_t dst, long n)
{
  GD.wr(dst + 0, BG_ZERO + (n / 1000000) % 10); // millions
  GD.wr(dst + 1, BG_ZERO + (n / 100000) % 10);  // hundred-thousands
  GD.wr(dst + 2, BG_ZERO + (n / 10000) % 10);   // ten-thousands
  GD.wr(dst + 3, BG_ZERO + (n / 1000) % 10);    // thousands
  GD.wr(dst + 4, BG_ZERO + (n / 100) % 10);     // hundreds
  GD.wr(dst + 5, BG_ZERO + (n / 10) % 10);      // tens
  GD.wr(dst + 6, BG_ZERO + n % 10);             // ones
}

static void draw_bonus(uint8_t dst, byte n)
{
  GD.wr(dst, BG_ZERO + (n / 10) % 10);          // tens
  GD.wr(dst + 1, BG_ZERO + n % 10);             // ones
}

static void draw_BG()
{
  for(int n=0; n<50; n++) //CLEARS TOP ROW
  {
    GD.wr(n, BG_BLUE);
  }

  long x=20;
  for(int n=24; n>16; n--) //DRAWS SCORE AND HI-SCORE
  {
    GD.wr(atxy(n,0), x);
    if(n>19)
    {
      GD.wr(atxy(n,1), x);
    }
    x--;
  }
  for(int n=26; n<33; n++)
  {
    GD.wr(atxy(n,0), BG_ZERO);
    GD.wr(atxy(n,1), BG_ZERO);
  }

  GD.wr(atxy(38,1), BG_B);   //DRAWS BONUS
  GD.wr(atxy(39,1), BG_B-3);
  GD.wr(atxy(40,1), BG_B+2);
  GD.wr(atxy(41,1), BG_B+1);
  GD.wr(atxy(42,1), BG_B-5);
  GD.wr(atxy(43,1), BG_B-9);
  GD.wr(atxy(44,1), BG_ZERO);
  GD.wr(atxy(45,1), BG_ZERO);

  GD.wr(atxy(4,1), BG_COW); //DRAW LIVES
  GD.wr(atxy(5,1), BG_B-9);
  GD.wr(atxy(6,1), BG_ZERO);
  GD.wr(atxy(7,1), BG_ZERO);
  
  for(byte n=0; n<50; n++)
  {
    GD.wr(atxy(n,39), 24);
  }
  GD.wr(atxy(21,2), 25); //LEFT DRAW CONTROL SCHEME
  GD.wr(atxy(28,2), 26); //RIGHT
  GD.wr(atxy(27,2), 27); //CROSSHAIR
  GD.wr(atxy(22,2), BG_COW);
}

void checkbonus()
{
  if(bonus!=0)
  {
    if(bonustimer>360)
    {
      bonus--;
      bonustimer=0;
    }
    else
    {
      bonustimer++;
    }
  }
}

void setupgame()
{
  player.x = 200; //start player
  player.y = 150;
  player.frame = 0;
  player.rotate = 0;
  player.eatingtimer = 0;
  player.animframe = false;
  player.eating = false;
  player.dead = false;
  
  pcrosshair.x = 200; //starts crosshair
  pcrosshair.y = 170;
  pcrosshair.fire = false;
  pcrosshair.buttondown = false;
  pcrosshair.flashx = 0;
  pcrosshair.flashy = 0;
  pcrosshair.flashtimer = 3; //set to flashtimer limit
  pcrosshair.overwolf = false;

  for(uint8_t n=0; n<10; n++) //set up grasses
  {
    grasses[n].spawn = false;
    grasses[n].spawntimer = 72;
    grasses[n].spawning = 0;
  }
  
  bonus=0;
  score=0;
  lives=3;
  bonuslife=0;
  bonusscore=500+(250*bonuslife*bonuslife);

  long tempscorespawn=10;
  for(uint8_t n=0; n<10; n++) //set up wolves
  {
	wolves[n].x = 420;
	wolves[n].y = 420;
	wolves[n].spawn=false;
    wolves[n].spawntimer=720+(360*n);
    wolves[n].spawning=0;
    wolves[n].rotate=0;
    wolves[n].charging=false;
    wolves[n].blinktimer=144;
    wolves[n].type=0;
    wolves[n].frame=10;
    wolves[n].moveswitch=0;
    wolves[n].moveduration=random(36,145);
    wolves[n].movecounter=0;
	wolves[n].avoid = false;
	tempscorespawn=tempscorespawn+(10*n*n);
    wolves[n].scorespawn=tempscorespawn;
    tempscorespawn=wolves[n].scorespawn;
  }
  
  if(!lefty)
  {
    player.up=SNES_UP; //COW RIGHT HAND CONTROL
    player.down=SNES_DOWN; 
    player.left=SNES_LEFT;
    player.right=SNES_RIGHT;
    player.action=SNES_L;
    pcrosshair.up=SNES_X; //CROSSHAIR RIGHT HAND CONTROL
    pcrosshair.down=SNES_B; 
    pcrosshair.left=SNES_Y; 
    pcrosshair.right=SNES_A;
    pcrosshair.action=SNES_R;
  }
  else
  {
    player.up=SNES_X; //COW LEFT HAND CONTROL
    player.down=SNES_B; 
    player.left=SNES_Y;
    player.right=SNES_A;
    player.action=SNES_R;
    pcrosshair.up=SNES_UP; //CROSSHAIR LEFT HAND CONTROL
    pcrosshair.down=SNES_DOWN; 
    pcrosshair.left=SNES_LEFT; 
    pcrosshair.right=SNES_RIGHT;
    pcrosshair.action=SNES_L;
  }
}

void setup()
{
  GD.begin();
  for (byte y = 0; y < 37; y++) //DEFAULT BG
    GD.copy(RAM_PIC + y * 64, image_pic + y * 50, 50);
  GD.copy(RAM_CHR, image_chr, sizeof(image_chr));
  GD.copy(RAM_PAL, image_pal, sizeof(image_pal));

  //SPRITES
  GD.copy(RAM_SPRPAL, sprite_sprpal, sizeof(sprite_sprpal));
  GD.copy(RAM_SPRIMG, sprite_sprimg, sizeof(sprite_sprimg));

  // For show, randomly scatter the frames on the screen
  /*GD.__wstartspr(0);
   for (int anim = 0; anim < SPRITE_FRAMES; anim++)
   draw_sprite(random(400), random(300), anim, 0);*/
  //GD.__end();

  draw_BG();

  lefty=false;
  title = true;
  holdselect = false;
  
  //setupgame();
  
  switchsidetimer=0;
  
  Serial.begin(57600);
}

void loop(){
	
	state = nintendo.buttons();
	if(!title){
		Serial.print(lefty);
		gameloop();
		state = 0; //just in case
	}
	GD.waitvblank();
    if(holdselect){ //SELECT changes left hand mode
        if(!(state & SNES_SELECT)){
            holdselect = false;
        }
    }
    else
    {
        if(state & SNES_SELECT){
			holdselect = true;
			if(lefty){
				lefty = false;
				GD.wr(atxy(22,2), BG_COW);
				GD.wr(atxy(27,2), 27);
			}
			else{
				lefty = true;
				GD.wr(atxy(22,2), 27);
				GD.wr(atxy(27,2), BG_COW);
            }
        }
	} //END
	if(state & SNES_START){ //START the game
		title = false;
		for(uint8_t m=13; m<=35; m++){
			for(uint8_t n=9; n<=17; n++){
				GD.wr(atxy(m,n), 0);
			}
		}
		//Serial.print(lefty);
	}
	//Serial.print(lefty);
}

void gameloop()
{
	Serial.print(lefty);
	setupgame();
	GD.wr(SPR_DISABLE, 0);
	while(!title)
	{
	  state = nintendo.buttons();
	  byte grasses_spr[10];
	  byte cowspr;
	  byte wolves_spr[10];
	  byte crosshairspr;
	  byte shotspr;

	  //GD.waitvblank();
	  draw_score(atxy(26, 0), highscore); //draws high score, score, bonus, and lives
	  draw_score(atxy(26, 1), score);
	  draw_bonus(atxy(44, 1), bonus);
	  draw_bonus(atxy( 6, 1), lives);
	  
	  //BEGIN SPRITES
	  GD.__wstartspr(0);
	  for(uint8_t n=0; n<10; n++) //spawns grass
	  {
		grasses_spr[n]=GD.spr;
		spawn(&grasses[n]);
		//draw_sprite(grasses[n].x, grasses[n].y, 8, 0);
	  }

	  cowspr=GD.spr; //player action
	  cowmove(state, &player, &pcrosshair);
	  //draw_sprite(player.x, player.y, player.frame, player.rotate);
	  
	  for(uint8_t n=0; n<10; n++) //spawns wolves
	  {
		wolves_spr[n]=GD.spr;
		wolfspawn(&wolves[n], score);
		if(wolves[n].spawn){
			wolfmove(&wolves[n], &player, score);
		}
		draw_sprite(wolves[n].x, wolves[n].y, wolves[n].frame, wolves[n].rotate);
	  }
	  shotspr=GD.spr;
	  crosshairmove(state, &pcrosshair, &crosshairspr);
	  GD.__end();
	  
	  //BEGIN COLLISION DETECTION
	  GD.waitvblank();
	  boolean grasscoll[10], wolfcoll[10], crosscoll[10], shotcoll[10];
	  for(byte n=0; n<10; n++)
	  {
		grasscoll[n]=(GD.rd(COLLISION+cowspr)==grasses_spr[n]);
		wolfcoll[n]=(GD.rd(COLLISION+wolves_spr[n])==cowspr);
		crosscoll[n]=(GD.rd(COLLISION+crosshairspr)==wolves_spr[n]);
		shotcoll[n]=(GD.rd(COLLISION+shotspr)==wolves_spr[n]);
	  }
	  if(player.eating){ //player eats grass
		for(byte n=0; n<10; n++){
		  //byte touching=(GD.rd(COLLISION + cowspr)!=0xff);
		  if(grasscoll[n]){
			if(grasses[n].x<player.x){//make player face left if grass is to left
			  player.rotate=0;
			}
			else{//opposite
			  player.rotate=2;
			}
			grasses[n].x=400;//move grass out of way
			grasses[n].y=400;
			grasses[n].spawn=false;
			
			if(bonus==0){
			  score++;
			}
			else{
			  score+=bonus*5;
			}
			if(bonus!=99){
			  bonus++;
			}
			bonustimer=0;
		  }
		}
	  }
	  
	  for(byte n=0; n<10; n++){ //Wolves kill player
		if(wolfcoll[n]){
		  player.dead=true;
		}
	  }
	  if(player.dead)  {
		for(byte n=0; n<10; n++){
		  GD.waitvblank();
		  wolves[n].spawn=false;
		  wolves[n].spawning=0;
		  wolves[n].spawntimer=720+(360*n);
		  wolves[n].x=500;
		  wolves[n].y=500;
		}
		bonus=0;
		player.x=200;
		player.y=150;
		player.dead=false;
		if(lives==0){
			title = true;
			//setupgame();
		}
		else{
		  lives--;
		}
	  }
		pcrosshair.overwolf = false;
	  for(byte n=0; n<10; n++){ //Player kills wolves
		if(crosscoll[n]){
			wolves[n].avoid = true;
			pcrosshair.overwolf = true;
		}
		if(shotcoll[n]){
			if(pcrosshair.fire){
				wolves[n].spawn=false;
				wolves[n].spawning=0;
				wolves[n].spawntimer=random(648,793);
				wolves[n].x=500;
				wolves[n].y=500;
				score+=bonus;
				if(bonustimer>0){
				  if(bonustimer>54){
					bonustimer-=54;
				  }
				  else{
					bonustimer=0;
				  }
				}
			}
		}
	  }
	  
	  checkbonus();
	  if(score > 10000000) {
		score=9999999;
	  }
	  if(score>highscore){
		highscore=score;
	  }
	  if(score>bonusscore){
		lives++;
		if(bonuslife>7){
		  bonusscore=bonusscore+500+(250*bonuslife*bonuslife);
		}
		else{
		  bonuslife++;
		  bonusscore=500+(250*bonuslife*bonuslife);
		}
	  }
	  if((state & SNES_SELECT)&&(state & SNES_START)){
		  title = true;
		  state = 0;
	  }
	}
	setupgame(); //RESET EVERYTHING EXCEPT HIGH SCORE
	GD.wr(atxy(20,2), 30); //G DRAW GAME OVER
	GD.wr(atxy(21,2), 29); //A 
	GD.wr(atxy(22,2), 31); //M
	GD.wr(atxy(23,2), 20); //E
	GD.wr(atxy(26,2), 18); //O
	GD.wr(atxy(27,2), 32); //V
	GD.wr(atxy(28,2), 20); //E
	GD.wr(atxy(29,2), 19); //R
	delay(3000);
	GD.wr(SPR_DISABLE, 1);
	for (byte y = 0; y < 37; y++) //DEFAULT BG
    GD.copy(RAM_PIC + y * 64, image_pic + y * 50, 50);
	GD.copy(RAM_CHR, image_chr, sizeof(image_chr));
	GD.copy(RAM_PAL, image_pal, sizeof(image_pal));
	draw_BG(); //RESET TO TITLE BG
	draw_score(atxy(26, 0), highscore);
	lefty=false; //RESET TO TITLE
	title = true;
	holdselect = false;
	state = 0; //just in case
}

