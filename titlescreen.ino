#include <SNESpad.h>
#include <SPI.h>
#include <GD.h>

#include "image.h"
#include "sprite.h"
#include "grass.h"
#include "crosshair.h"
#include "player.h"
#include "wolf.h"

#define greenbg 0x03E0  //green 0 0 31 0
#define whitebg 0x7FFF
#define skyblue 0x1E7B //0x0C7F

#define BG_BLUE		1
#define BG_ZERO		2
#define BG_A		12
#define BG_TIME		38
#define BG_AMOUNT	39
#define BG_DASH		40
#define BG_COW		41
#define BG_CTRL		42
#define BG_CTRR		43
#define BG_CROSS	44

#define FENCE_UL 45
#define FENCE_UM 47 //4 pieces
#define FENCE_UR 51
#define FENCE_L  53
#define FENCE_R  55
#define FENCE_LL 57
#define FENCE_LM 59 //4 pieces
#define FENCE_LR 63

#define COW_TITLE	7
#define COW_TAIL	19
#define GAME_TITLE	21

int state=0;
//static int cowup, cowdown, cowleft, cowright, coweat;  //implement cow control
//static int crossup, crossdown, crossleft, crossright, crossfire;  //implement crosshair control
SNESpad nintendo(5,6,7);
cow player;
crosshair pcrosshair;
grass grasses[10];
wolf wolves[10];

static unsigned long highscore;
static unsigned long score;
static uint8_t bonus;
static unsigned long bonustimer;
static uint8_t lives;
static bool lefty;
static byte switchsidetimer;
static byte bonuslife;
static unsigned long bonusscore;
static bool title;
static bool holdselect;

void gameloop();

static uint16_t atxy(byte x, byte y)
{
  return RAM_PIC + 64 * y + x;
}

byte fetchletter(char x)
{
	byte result;
	result = byte(x - 65); //assumes capital letter
	result += BG_A; //offsets
	return result;
}

void drawtitleCOW(byte x, byte y)
{
  for(int n=0; n<6; n++)
  {
    draw_sprite(x+16*n, y,    COW_TITLE+2*n,   0);
    draw_sprite(x+16*n, y+16, COW_TITLE+1+2*n, 0);
  }
  draw_sprite(x+16*6, y+16, COW_TAIL,   0);
  draw_sprite(x+16*7, y+16, COW_TAIL+1, 0);
}

void drawtitleGAME(byte x, byte y)
{
  for(int n=0; n<8; n++)
  {
    draw_sprite(x+16*n, y,    GAME_TITLE+2*n,   0);
    draw_sprite(x+16*n, y+16, GAME_TITLE+1+2*n, 0);
  }
}

void draw_title(byte xcow, byte ycow, byte xgame, byte ygame)
{
  drawtitleCOW(xcow, ycow);
  drawtitleGAME(xgame, ygame);
}

static void draw_fence()
{
	//CORNERS
	GD.wr(atxy(2,5), FENCE_UL);
	GD.wr(atxy(2,6), FENCE_UL+1);
	GD.wr(atxy(47,5), FENCE_UR);
	GD.wr(atxy(47,6), FENCE_UR+1);
	GD.wr(atxy(2,33), FENCE_LL);
	GD.wr(atxy(2,34), FENCE_LL+1);
	GD.wr(atxy(47,33), FENCE_LR);
	GD.wr(atxy(47,34), FENCE_LR+1);
	//TOP BOTTOM MIDDLE
	for(int n=0; n<22; n++)
	{
		GD.wr(atxy(3+2*n,5), FENCE_UM);
		GD.wr(atxy(3+2*n,6), FENCE_UM+1);
		GD.wr(atxy(4+2*n,5), FENCE_UM+2);
		GD.wr(atxy(4+2*n,6), FENCE_UM+3);
		GD.wr(atxy(3+2*n,33), FENCE_LM);
		GD.wr(atxy(3+2*n,34), FENCE_LM+1);
		GD.wr(atxy(4+2*n,33), FENCE_LM+2);
		GD.wr(atxy(4+2*n,34), FENCE_LM+3);		
	}
	//SIDES
	for(int n=0; n<13; n++)
	{
		GD.wr(atxy(2,7+2*n), FENCE_L);
		GD.wr(atxy(2,8+2*n), FENCE_L+1);
		GD.wr(atxy(47,7+2*n), FENCE_R);
		GD.wr(atxy(47,8+2*n), FENCE_R+1);
	}		
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
  GD.wr(dst,     BG_ZERO + (n / 10) % 10);      // tens
  GD.wr(dst + 1, BG_ZERO + n % 10);             // ones
}

static void draw_BG()
{
  for(int n=0; n<50; n++) //CLEARS TOP 3 ROWS
  {
    GD.wr(atxy(n,0), BG_BLUE);
    GD.wr(atxy(n,1), BG_BLUE);
    GD.wr(atxy(n,2), BG_BLUE);
  }

  GD.wr(atxy(17,0), fetchletter('H')); //DRAWS SCORE AND HI-SCORE
  GD.wr(atxy(18,0), fetchletter('I'));
  GD.wr(atxy(19,0), BG_DASH);
  GD.wr(atxy(20,0), fetchletter('S'));
  GD.wr(atxy(20,1), fetchletter('S'));
  GD.wr(atxy(21,0), fetchletter('C'));
  GD.wr(atxy(21,1), fetchletter('C'));
  GD.wr(atxy(22,0), fetchletter('O'));
  GD.wr(atxy(22,1), fetchletter('O'));
  GD.wr(atxy(23,0), fetchletter('R'));
  GD.wr(atxy(23,1), fetchletter('R'));
  GD.wr(atxy(24,0), fetchletter('E'));
  GD.wr(atxy(24,1), fetchletter('E'));
  
  for(int n=26; n<33; n++)
  {
    GD.wr(atxy(n,0), BG_ZERO);
    GD.wr(atxy(n,1), BG_ZERO);
  }

  GD.wr(atxy(38,1), fetchletter('B'));   //DRAWS BONUS
  GD.wr(atxy(39,1), fetchletter('O'));
  GD.wr(atxy(40,1), fetchletter('N'));
  GD.wr(atxy(41,1), fetchletter('U'));
  GD.wr(atxy(42,1), fetchletter('S'));
  GD.wr(atxy(43,1), BG_AMOUNT);
  GD.wr(atxy(44,1), BG_ZERO);
  GD.wr(atxy(45,1), BG_ZERO);

  GD.wr(atxy(4,1), BG_COW); //DRAW LIVES
  GD.wr(atxy(5,1), BG_AMOUNT);
  GD.wr(atxy(6,1), BG_ZERO);
  GD.wr(atxy(7,1), BG_ZERO);
  
  for(byte n=0; n<50; n++)
  {
    GD.wr(atxy(n,39), 0);
  }
  GD.wr(atxy(21,2), BG_CTRL); //LEFT DRAW CONTROL SCHEME
  GD.wr(atxy(28,2), BG_CTRR); //RIGHT
  GD.wr(atxy(27,2), BG_CROSS); //CROSSHAIR
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
    grasses[n].spawned = false;
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
  GD.copy(RAM_CHR, image_chr, sizeof(image_chr));
  GD.copy(RAM_PAL, image_pal, sizeof(image_pal));

  //SPRITES
  GD.copy(PALETTE4A, sprite_sprpal_4a, sizeof(sprite_sprpal_4a));
  GD.copy(PALETTE4B, sprite_sprpal_4b, sizeof(sprite_sprpal_4b));
  GD.copy(PALETTE16A, sprite_sprpal_16a, sizeof(sprite_sprpal_16a));
  GD.copy(RAM_SPRIMG, sprite_sprimg, sizeof(sprite_sprimg));


  GD.wr16(BG_COLOR, greenbg); //set bg transparent color
  draw_BG();
  draw_fence();
  //draw_title(13, 9, 21, 14);

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
		GD.__wstartspr(0);
		draw_title(100, 400, 100, 400);
		while(GD.spr < 255)
		{
			GD.xhide();
		}
		GD.__end();
		GD.waitvblank();
		Serial.print(lefty);
		gameloop();
		state = 0; //just in case
	}
	
	GD.__wstartspr(0);
	draw_title(104, 72, 168, 112);
	while(GD.spr < 255)
	{
		GD.xhide();
	}
	GD.__end();
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
				GD.wr(atxy(27,2), BG_CROSS);
			}
			else{
				lefty = true;
				GD.wr(atxy(22,2), BG_CROSS);
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
		grasses[n].spawn();
		//draw_sprite(grasses[n].x, grasses[n].y, 8, 0);
	  }

	  cowspr=GD.spr; //player action
	  player.cowmove(state);
	  //draw_sprite(player.x, player.y, player.frame, player.rotate);
	  
	  for(uint8_t n=0; n<10; n++) //spawns wolves
	  {
		wolves_spr[n]=GD.spr;
		wolves[n].wolfspawn(score);
		if(wolves[n].spawn){
			wolves[n].wolfmove(player.x, player.y, score);
		}
		draw_sprite(wolves[n].x, wolves[n].y, wolves[n].frame, wolves[n].rotate);
	  }
	  shotspr=GD.spr;
	  pcrosshair.crosshairmove(state, &crosshairspr);
	  while(GD.spr < 255)
	  {
		  GD.xhide();
	  }
	  GD.__end();
	  
	  //BEGIN COLLISION DETECTION
	  GD.waitvblank();
	  bool grasscoll[10], wolfcoll[10], crosscoll[10], shotcoll[10];
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
			grasses[n].spawned=false;
			
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
	GD.wr(atxy(20,2), fetchletter('G')); //G DRAW GAME OVER
	GD.wr(atxy(21,2), fetchletter('A')); //A 
	GD.wr(atxy(22,2), fetchletter('M')); //M
	GD.wr(atxy(23,2), fetchletter('E')); //E
	GD.wr(atxy(26,2), fetchletter('O')); //O
	GD.wr(atxy(27,2), fetchletter('V')); //V
	GD.wr(atxy(28,2), fetchletter('E')); //E
	GD.wr(atxy(29,2), fetchletter('R')); //R
	delay(3000);
	GD.copy(RAM_CHR, image_chr, sizeof(image_chr));
	GD.copy(RAM_PAL, image_pal, sizeof(image_pal));
	
	GD.wr16(BG_COLOR, greenbg); //set bg transparent color
	draw_BG();
	draw_fence();
	draw_title(13, 9, 21, 14);
	
	draw_score(atxy(26, 0), highscore);
	lefty=false; //RESET TO TITLE
	title = true;
	holdselect = false;
	state = 0; //just in case
}

