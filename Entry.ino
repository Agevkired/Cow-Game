#include <SNESpad.h>
#include <SPI.h>
#include <GD.h>

#include "image.h"
#include "sprite.h"
#include "grass.h"
#include "crosshair.h"
#include "player.h"
#include "wolf.h"
#include "sprbuffer.h"
#include "splitscreen.h"
#include "boxcoll.h"

//SINGLE COLOR TILES
#define greenbg 0x03E0  //green 0 0 31 0
#define whitebg 0x7FFF
#define skyblue 0x1E7B //0x0C7F

//VARIOUS BG TILES
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

//TITLE
#define COW_TITLE	7
#define COW_TAIL	19
#define GAME_TITLE	21

//CONSTANTS
#define THRESHOLD 100
#define MAXOBJECTS 10
#define SPRITESIZE 16
#define CROSSCOLL 8
#define CROSSOFF 4

#define NOROT 0
#define ROTX 2

int state=0;
//static int cowup, cowdown, cowleft, cowright, coweat;  //implement cow control
//static int crossup, crossdown, crossleft, crossright, crossfire;  //implement crosshair control
SNESpad nintendo(5,6,7);
cow player;
crosshair pcrosshair;
grass grasses[MAXOBJECTS];
wolf wolves[MAXOBJECTS];

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
static bool printit;

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
	//BOUNDS
	byte begx = 2;
	byte endx = 47;//61;
	byte begy = 5;
	byte endy = 33;//59;
	//CORNERS
	GD.wr(atxy(begx, begy), FENCE_UL);
	GD.wr(atxy(begx, begy+1), FENCE_UL+1);
	GD.wr(atxy(endx, begy), FENCE_UR); //61
	GD.wr(atxy(endx, begy+1), FENCE_UR+1); //61
	GD.wr(atxy(begx, endy), FENCE_LL); //59
	GD.wr(atxy(begx, endy+1), FENCE_LL+1); //60
	GD.wr(atxy(endx, endy), FENCE_LR); //61, 59
	GD.wr(atxy(endx, endy+1), FENCE_LR+1); //61, 60
	//TOP BOTTOM MIDDLE
	for(int n=0; n<22; n++) //change to 29
	{	//increment x to position next to corner
		//Upper Fence
		GD.wr(atxy(begx+1 +2*n, begy), FENCE_UM);
		GD.wr(atxy(begx+1 +2*n, begy+1), FENCE_UM+1);
		GD.wr(atxy(begx+2 +2*n, begy), FENCE_UM+2);
		GD.wr(atxy(begx+2 +2*n, begy+1), FENCE_UM+3);
		//Lower Fence
		GD.wr(atxy(begx+1 +2*n, endy), FENCE_LM); //59
		GD.wr(atxy(begx+1 +2*n, endy+1), FENCE_LM+1); //60
		GD.wr(atxy(begx+2 +2*n, endy), FENCE_LM+2); //59
		GD.wr(atxy(begx+2 +2*n, endy+1), FENCE_LM+3); //60
	}
	//SIDES
	for(int n=0; n<13; n++) //change to 26
	{
		GD.wr(atxy(begx, begy+2 +2*n), FENCE_L);
		GD.wr(atxy(begx, begy+3 +2*n), FENCE_L+1);
		GD.wr(atxy(endx, begy+2 +2*n), FENCE_R); //61
		GD.wr(atxy(endx, begy+3 +2*n), FENCE_R+1); //61
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
	player.setup();

	pcrosshair.setup();

	for(uint8_t n=0; n<MAXOBJECTS; n++) //set up grasses
	{
		grasses[n].setup();
	}

	bonus=0;
	score=0;
	lives=3;
	bonuslife=0;
	bonusscore=500+(250*bonuslife*bonuslife);

	long tempscorespawn=10;
	for(uint16_t n=0; n<MAXOBJECTS; n++) //set up wolves
	{
		//tempscorespawn=tempscorespawn+(long)(10*n*n);
		//wolves[n].setup(tempscorespawn, 720+(360*n));
		wolves[n].killed(72);
	}
  
	//up, down, left, right, action
	if(!lefty)
	{
		//COW RIGHT HAND CONTROL
		player.setcontrols(SNES_UP, SNES_DOWN, SNES_LEFT, SNES_RIGHT, SNES_L);
		//CROSSHAIR RIGHT HAND CONTROL
		pcrosshair.setcontrols(SNES_X, SNES_B, SNES_Y, SNES_A, SNES_R);
	}
	else
	{
		//COW LEFT HAND CONTROL
		player.setcontrols(SNES_X, SNES_B, SNES_Y, SNES_A, SNES_R);
		//CROSSHAIR LEFT HAND CONTROL
		pcrosshair.setcontrols(SNES_UP, SNES_DOWN, SNES_LEFT, SNES_RIGHT, SNES_L);
	}
}

//ARDUINO FUNCTIONS
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
	
	//COPIED FROM GAMEDUINO SPLITSCREEN EXAMPLE
	GD.wr16(COMM+0, 0); //position of first x scroll
	GD.wr16(COMM+2, 1); //position of first y scroll, +1 due to showing line 511
	GD.wr16(COMM+4, 23);   // split at line 24
	GD.wr16(COMM+6, 0); //2nd xscroll
	GD.wr16(COMM+8, 0); //2nd yscroll, offset by 1

	switchsidetimer=0;
	printit=false;

	Serial.begin(9600);
}

void loop()
{
	state = nintendo.buttons();
	
	GD.__wstartspr(0);
	draw_title(104, 72, 168, 112);
	while(GD.spr < 255)
	{
		GD.xhide();
	}
	GD.__end();
	GD.waitvblank();
	
	//SELECT toggles left hand mode
    if(holdselect){ //prevent select being constantly detected when held
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
	}
	
	//START the game
	if(state & SNES_START){ 
		title = false;
		for(uint8_t m=13; m<=35; m++){
			for(uint8_t n=9; n<=17; n++){
				GD.wr(atxy(m,n), 0);
			}
		}
		//Hide all sprites
		GD.__wstartspr(0);
		while(GD.spr < 255)
		{
			GD.xhide();
		}
		GD.__end();
		GD.waitvblank();
		
		//Serial.print(lefty);
		gameloop();
		state = 0; //just in case
		//Serial.print(lefty);
	}
	//Serial.print("In Loop. Lefty: ");
	//Serial.println(lefty);
	//Serial.print("SNES state: ");
	//Serial.println(state);
	
	//if(!title)
	//{

	//}
}
//END ARDUINO FUNCTIONS

void gameloop()
{
	Serial.println("Inside gameloop");
	GD.waitvblank();
	int limitprint = 0;

	sprbuffer buffer; //painters algorithm
	buffer.resetcounter();
	setupgame();
	GD.wr(SPR_DISABLE, 0);

	while(!title)
	{
		//PRINT TO SERIAL MONITOR EVERY 1/2 SECOND
		if(limitprint++ > 36)
		{
			for(uint8_t n=0; n<MAXOBJECTS; n++)
			//for(uint8_t n=0; n<1; n++)
			{
				Serial.print(n);
				Serial.print(": ");
				//Serial.println(wolves[n].getspawn());
				Serial.println(wolves[n].getstatus(), BIN);
			}				
			limitprint = 0;
			//printit=true; //uncomment to enable
		}
		else
		{
			printit=false;
		}
		//END PRINT
		state = nintendo.buttons();

		//GD.waitvblank();
		draw_score(atxy(26, 0), highscore); //draws high score, score, bonus, and lives
		draw_score(atxy(26, 1), score);
		draw_bonus(atxy(44, 1), bonus);
		draw_bonus(atxy( 6, 1), lives);
	  
		//*****BEGIN SPRITES*****
		GD.__wstartspr(0);
		//Grass
		for(uint8_t n=0; n<MAXOBJECTS; n++) //spawns grass
		{
			grasses[n].spawn();
			buffer.insert(grasses[n].getx(), grasses[n].gety(), grasses[n].spr(), 0); //0 = no rotation
		}
		
		//Cow / Player
		player.cowmove(state);
		buffer.insert(player.getx(), player.gety(), player.getframe(), player.getrotate());
	  
		//Wolves
		if(score / THRESHOLD < MAXOBJECTS)
		{
			for(byte n=0; n< score / THRESHOLD; n++)
			//for(byte n=0; n< 1; n++)
			{
				//Serial.print(n);
				//Serial.println(" ACTIVE");
				wolves[n].activate(player.getx(), player.gety(), score, printit, n);
				buffer.insert(wolves[n].getx(), wolves[n].gety(), wolves[n].getframe(), wolves[n].getrotate());
			}
		}
		else
		{
			for(byte n=0; n< MAXOBJECTS; n++)
			{
				wolves[n].activate(player.getx(), player.gety(), score, printit, n);
				buffer.insert(wolves[n].getx(), wolves[n].gety(), wolves[n].getframe(), wolves[n].getrotate());
			}
		}
		/*
		for(uint8_t n=0; n<MAXOBJECTS; n++) //spawns wolves
		{
			wolves[n].wolfspawn(score);
			if(wolves[n].getspawn()){
				wolves[n].wolfmove(player.getx(), player.gety(), score);
			}
			buffer.insert(wolves[n].getx(), wolves[n].gety(), wolves[n].getframe(), wolves[n].getrotate());
		}
		*/
		//Crosshair
		pcrosshair.crosshairmove(state);
		//*****END SPRITES*****
		
		//*****DISPLAY SPRITES*****
		buffer.sortbuffer();
		for(uint8_t n=0; n<buffer.getcounter(); n++)
		{
			draw_sprite(buffer.getx(n), buffer.gety(n), buffer.getspr(n), buffer.getrot(n));
		}
		pcrosshair.draw(); //draw crosshair last
		buffer.resetcounter();
		//hide unused
		while(GD.spr < 255)
		{
			GD.xhide();
		}
		GD.__end();
		//*****END DISPLAY SPRITES*****
		
		//*****BEGIN COLLISION DETECTION*****
		GD.waitvblank();
		bool grasscoll[10], wolfcoll[10], crosscoll[10], shotcoll[10];
		for(byte n=0; n<10; n++)
		{
			//player collision with grass and wolves
			grasscoll[n] = squcoll(grasses[n].getx(), grasses[n].gety(), SPRITESIZE, player.getx(), player.gety(), SPRITESIZE); 
			wolfcoll[n] = squcoll(wolves[n].getx(), wolves[n].gety(), SPRITESIZE, player.getx(), player.gety(), SPRITESIZE); 
			//crosshair collision
			crosscoll[n] = squcoll(pcrosshair.getx(), pcrosshair.gety(), CROSSCOLL, wolves[n].getx(), wolves[n].gety(), SPRITESIZE, CROSSOFF); 
			shotcoll[n] = squcoll(pcrosshair.getfx(), pcrosshair.getfy(), CROSSCOLL, wolves[n].getx(), wolves[n].gety(), SPRITESIZE, CROSSOFF); 
		}
		//RESOLVE COLLISION
		if(player.geteating())//player eats grass
		{ 
			for(byte n=0; n<10; n++)
			{
				if(grasscoll[n])
				{
					if(grasses[n].getx() < player.getx())//make player face left if grass is to left
					{
						player.setrotate(NOROT);
					}
					else //opposite
					{
						player.setrotate(ROTX);
					}
					grasses[n].eaten();

					if(bonus==0)
					{
						score++;
					}
					else
					{
						score+=bonus*5;
					}
					if(bonus!=99)
					{
						bonus++;
					}
					bonustimer=0;
				}
			}
		}
	  
		for(byte n=0; n<MAXOBJECTS; n++) //Wolves kill player
		{ 
			if(wolfcoll[n])
			{
				player.died();
			}
		}
		if(player.getdead())
		{
			for(uint16_t n=0; n<MAXOBJECTS; n++)
			{
				wolves[n].killed(144+(144*n)); //72 = 1 second
			}
			bonus=0;
			player.setup();
			if(lives==0)
			{
				title = true;
				//setupgame();
			}
			else
			{
				lives--;
			}
		}
		pcrosshair.setoverwolf(false);
		for(byte n=0; n<MAXOBJECTS; n++) //Player kills wolves
		{ 
			if(crosscoll[n])
			{
				wolves[n].setavoid();
				pcrosshair.setoverwolf(true);
			}
			if(shotcoll[n])
			{
				if(pcrosshair.getfire())
				{
					//Serial.println("Killed");
					wolves[n].killed((uint16_t)random(648,793));
					score+=bonus;
					if(bonustimer>0)
					{
						if(bonustimer>54)
						{
							bonustimer-=54;
						}
						else
						{
							bonustimer=0;
						}
					}
				}
			}
		}
		//*****END COLLISION*****
		
		//UPDATE SCORES
		checkbonus();
		if(score > 10000000)
		{
			score=9999999;
		}
		if(score>highscore)
		{
			highscore=score;
		}
		if(score>bonusscore)
		{
			lives++;
			if(bonuslife>7)
			{
				bonusscore=bonusscore+500+(250*bonuslife*bonuslife);
			}
			else
			{
				bonuslife++;
				bonusscore=500+(250*bonuslife*bonuslife);
			}
		}
		if((state & SNES_SELECT)&&(state & SNES_START))
		{
			title = true;
			state = 0;
		}
	}
	//END OF GAME LOOP
	
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
	holdselect = false;
	state = 0; //just in case
	
	
	title = true;
}

