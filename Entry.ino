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

//sprites
#define BG_BLUE_SPR	53
#define BG_CONTR_L	51
#define BG_CONTR_R	52
//foreground
#define FG_GAME_SPR 56
#define FG_OVER_SPR 57
#define FG_PAUSE_SPR 58
#define FG_A_SPR 56

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
#define MAXOBJECTS 15
#define SPRITESIZE 16
#define CROSSCOLL 8
#define CROSSOFF 4
#define DEADLENGTH 144 //72hz * 2, around 2 seconds 

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
static byte bonus;
static byte lives;
static bool lefty;
static byte bonuslife;
static unsigned long bonusscore;
static bool title;
//static bool printit;

char initial[4];

void titleloop();
void gameloop();
void drawword(char *str, byte align, int x, int y);

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

//*****DRAWING FUNCTIONS*****
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
	byte endx = 61;//47;//61;
	byte begy = 6;
	byte endy = 60;//33;//59;
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
	//for(int n=0; n<22; n++) //change to 29
	for(int n=0; n<29; n++) //change to 29
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
	//for(int n=0; n<13; n++) //change to 26
	for(int n=0; n<26; n++) //change to 26
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
	
	//34 35 36
	GD.wr(atxy(34,0), fetchletter(initial[0]-32));
	GD.wr(atxy(35,0), fetchletter(initial[1]-32));
	GD.wr(atxy(36,0), fetchletter(initial[2]-32));
  
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

//Draw a word using sprites
void drawword(char *str, byte align, int x, int y)
{
	/*
	Serial.print(str);
	Serial.print(": ");
	Serial.print(align);
	Serial.print(", size: ");
	Serial.println(strlen(str));
	*/
	//left
	if(align==0)
	{
		for(byte n=0; n < strlen(str); n++)
		{
			draw_sprite((x-2)+14*n, y, FG_A_SPR + str[n]-97, 0);
			//Serial.print(str[n]);
		}
	}
	//center
	else if(align==1)
	{
		for(byte n=0; n < strlen(str); n++)
		{
			if(str[n] != ' ')
			{
				draw_sprite((x-2) - 14*((strlen(str)/2) - n) + (7*((strlen(str)+1)%2)), y, FG_A_SPR + str[n]-97, 0);
			}
			//Serial.print(str[n]);
		}
	}
	//right
	else if(align==2)
	{
		for(int n=0; n < strlen(str); n++)
		{
			draw_sprite((x-2)+14*n-(14*(strlen(str)-1)), y, FG_A_SPR + str[n]-97, 0);
			//Serial.print(str[n]);
		}
	}
	//Serial.println(" ");
	//Serial.print(str[0]);
	//Serial.print(str[1]);
	//Serial.println(str[2]);
	//delay(10);
}

void drawletter(char str, int x, int y)
{
	draw_sprite(x-2, y, FG_A_SPR + str-97, 0);
}

void draw_blue_border()
{
	//draw blue border on upper part of screen
	for(int n=0; n<25; n++)
	{
		draw_sprite(8+16*n, 24, BG_BLUE_SPR, 0);
	}
	//draw controller
	draw_sprite(168, 24, BG_CONTR_L, 0);
	draw_sprite(232, 24, BG_CONTR_R, 0);
	//draw which side controls what (default L:cow R:farmer)
	if(lefty)
	{
		draw_sprite(216, 22, 0, 0); //draw cow
		draw_sprite(184, 24, 39, 0); //draw crosshair
	}
	else
	{
		draw_sprite(184, 22, 0, 0);
		draw_sprite(216, 24, 39, 0);
	}
}
//*****END DRAWING FUNCTIONS*****

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


//*****ARDUINO FUNCTIONS*****
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

	//INITIALIZE HIGH SCORE INITIAL STRING
	initial[0] = 'a';
	initial[1] = 'a';
	initial[2] = 'a';
	initial[3] = 0;

	GD.wr16(BG_COLOR, greenbg); //set bg transparent color
	draw_BG();
	draw_fence();
	//draw_title(13, 9, 21, 14);

	lefty=false;
	title = true;
	//holdselect = false;

	//setupgame();

	//switchsidetimer=0;
	//printit=false;
	
	//COPIED FROM GAMEDUINO SPLITSCREEN EXAMPLE
	GD.wr16(COMM+0, 0); //1st x position
	GD.wr16(COMM+2, 0); //1st y position, offset by 1 due to line 511 on top
	GD.wr16(COMM+4, 24);// split at line 24
	GD.wr16(COMM+6, 0); //2nd (camera) x position
	GD.wr16(COMM+8, 0); //2nd (camera) y position
	
	GD.microcode(splitscreen_code, sizeof(splitscreen_code));

	Serial.begin(9600);
	delay(100);
}

void loop()
{
	//state = nintendo.buttons();
	bool startPressed = true;
	bool selectPressed = true;
	titleloop();
	gameloop();
}
//*****END ARDUINO FUNCTIONS*****

void titleloop()
{
	//state = nintendo.buttons();
	bool startPressed = true;
	bool selectPressed = true;
	int xscroll = 0, yscroll = 0; //scroll registers
	byte closest = 255;
	int distance = 0;
	int shortest = 2000;
	int cowmove = 0;
	bool grasscoll[MAXOBJECTS];
	sprbuffer buffer; //painters algorithm
	setupgame();
	
	int buttons[12] = {SNES_B, SNES_Y, SNES_SELECT, SNES_START, SNES_UP, SNES_DOWN, SNES_LEFT, SNES_RIGHT, SNES_A, SNES_X, SNES_L, SNES_R};
	
	byte printTimer = 0;
	bool printit = false;
	while(1)
	{
		state = nintendo.buttons();
		GD.__wstartspr(0);
		buffer.resetcounter();
		
		//*****BEGIN SPRITES*****
		for(uint8_t n=0; n<MAXOBJECTS; n++) //spawns grass
		{
			if(rectcoll(grasses[n].getx(), grasses[n].gety(), SPRITESIZE, SPRITESIZE, xscroll, yscroll, 400, 300-32, -8, -8, 0, 32)
				&& grasses[n].getspawned() ) //on screen
			{
				buffer.insert(grasses[n].getx() - xscroll, grasses[n].gety() - yscroll, grasses[n].spr(), 0); //0 = no rotation
			}
			else
			{
				buffer.insert(400, 400, grasses[n].spr(), 0); //0 = no rotation
			}
			grasses[n].spawn(); //ACTION
			//compare stored closest with current grass
			if(grasses[n].getspawned())
			{
				distance = abs(player.getx()-grasses[n].getx()) + abs(player.gety()-grasses[n].gety());
				if(distance < shortest)
				{
					shortest = distance;
					closest = n;
				}
				/*
				if(printit)
				{
					Serial.print("n: ");
					Serial.print(n);
					Serial.print(" distance: ");
					Serial.println(distance);
				}
				*/
			}
		}
		
		if(printTimer > 36)
		{
			printTimer = 0;
			//printit = true;
			Serial.print("shortest: ");
			Serial.print(shortest);
			Serial.print(" closest: ");
			Serial.println(closest);
		}
		else
		{
			//printTimer++;
			printit = false;
		}
		
		cowmove = 0; //reset direction
		if(printit)
		{
			Serial.print("cowmove should be 0: ");
			for(int n=11; n >= 0; n--)
			{
				if(cowmove & buttons[n])
				{
					Serial.print("1");
				}
				else
				{
					Serial.print("0");
				}
				delay(5);
			}
			Serial.println(",");
		}
		if(closest != 255)
		{
			//left right
			if(grasses[closest].getx() < player.getx())
			{
				cowmove |= SNES_LEFT;
			}
			else if(grasses[closest].getx() > player.getx())
			{
				cowmove |= SNES_RIGHT;
			}
			//up down
			if(grasses[closest].gety() < player.gety())
			{
				cowmove |= SNES_UP;
			}
			else if(grasses[closest].gety() > player.gety())
			{
				cowmove |= SNES_DOWN;
			}
			if(printit)
			{
				Serial.print("post move: ");
				for(int n=11; n >= 0; n--)
				{
					if(cowmove & buttons[n])
					{
						Serial.print("1");
					}
					else
					{
						Serial.print("0");
					}
					delay(5);
				}
				Serial.println(",");
			}
		}
		//cow collision with grass
		for(byte n=0; n<MAXOBJECTS; n++)
		{
			//if any is true
			grasscoll[n] = squcoll(grasses[n].getx(), grasses[n].gety(), SPRITESIZE, player.getx(), player.gety(), SPRITESIZE);
			if(grasscoll[n])
			{
				cowmove |= SNES_L;
				shortest = 2000;
				closest = 255;
			}
		}
		if(printit)
		{
			Serial.print("cowmove: ");
			for(int n=11; n >= 0; n--)
			{
				if(cowmove & buttons[n])
				{
					Serial.print("1");
				}
				else
				{
					Serial.print("0");
				}
				delay(5);
			}
			Serial.println(",");
		}
		player.cowmove(cowmove);
		buffer.insert(player.getsx(), player.getsy(), player.getframe(), player.getrotate());
		
		//DISPLAY SPRITES
		buffer.sortbuffer();
		for(byte n=0; n<buffer.getcounter(); n++)
		{
			draw_sprite(buffer.getx(n), buffer.gety(n), buffer.getspr(n), buffer.getrot(n));
		}
		
		draw_title(104, 72, 168, 112);
		draw_blue_border();
		drawword("press start", 1, 204, 152+16);
		drawword("select", 1, 204, 152+48);
		drawword("change controls", 1, 204, 152+68);
		while(GD.spr < 255)
		{
			GD.xhide();
		}
		GD.__end();
		GD.waitvblank();
		//*****END SPRITES*****
		
		//*****RESOLVE COLLISION*****
		if(player.geteating())//player eats grass
		{ 
			for(byte n=0; n<MAXOBJECTS; n++)
			{
				if(grasscoll[n] && grasses[n].getspawned())
				{
					if(grasses[n].getx() < player.getx())//make player face left if grass is to left
					{
						player.setrotate(NOROT);
					}
					else if(grasses[n].getx() > player.getx()) //opposite
					{
						player.setrotate(ROTX);
					}
					grasses[n].eaten();
				}
			}
		}
		
		//*****BEGIN CAMERA*****
		if((player.getx() >= 200) && (player.getx() < 311))
		{
			xscroll = player.getx() - 200;
		}
		else if(player.getx() < 200)
		{
			xscroll = 0;
		}
		else
		{
			xscroll = 111; //400+111=511
		}
		//y position
		if((player.gety() >= 150) && (player.gety() < 361))
		{
			yscroll = player.gety() - 150;
		}
		else if(player.gety() < 150)
		{
			yscroll = 0;
		}
		else
		{
			yscroll = 211; //300+211=511
		}
		GD.wr16(COMM+6, xscroll);
		GD.wr16(COMM+8, yscroll);
		/*
		Serial.print("xscroll: ");
		Serial.print(xscroll);
		Serial.print(" yscroll: ");
		Serial.println(yscroll);
		*/
		//*****END CAMERA*****
		
		//SELECT toggles left hand mode
		if(!(state & SNES_SELECT)){ //prevent select being constantly detected when held
			selectPressed = false;
		}
		else if((state & SNES_SELECT) && !selectPressed){
			selectPressed = true;
			//lefty ^= true;
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
		
		
		//START the game
		if((state & SNES_START) && !startPressed){ 
			startPressed = true;
			title = false;
			for(uint8_t m=13; m<=35; m++){
				for(uint8_t n=9; n<=17; n++){
					GD.wr(atxy(m,n), 0);
				}
			}
			//Hide all sprites
			GD.__wstartspr(0);
			draw_blue_border();
			while(GD.spr < 255)
			{
				GD.xhide();
			}
			GD.__end();
			GD.waitvblank();
			
			//Serial.print(lefty);
			//gameloop();
			state = 0; //just in case
			//Serial.print(lefty);
			break;
		}
		else if(!(state & SNES_START))
		{
			startPressed = false;
		}
		//Serial.print("In Loop. Lefty: ");
		//Serial.println(lefty);
		//Serial.print("SNES state: ");
		//Serial.println(state);
		
		//if(!title)
		//{

		//}
	}	
}

void gameloop()
{
	Serial.println("Inside gameloop");
	GD.waitvblank();
	int limitprint = 0;
	byte activewolves = 0;
	word deadtimer = 0;
	
	bool letterblink = false;
	byte letterblinktimer = 0;
	byte letterselect = 0;
	int buttonpressed = SNES_START; //prevent pausing upon starting game
	
	int xscroll = 0, yscroll = 0; //scroll registers
	bool pause = false;
	bool printit = false;
	
	int bonustimer = 0;

	unsigned long oldscore = highscore;

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
				//Serial.print(n);
				//Serial.print(": ");
				//Serial.println(wolves[n].getspawn());
				//Serial.println(wolves[n].getstatus(), BIN);
			}				
			limitprint = 0;
			//printit=true; //uncomment to enable
			//Serial.print("deadtimer: ");
			//Serial.print(deadtimer);
			//Serial.print(", DEADLENGTH: ");
			//Serial.println(DEADLENGTH + (int(lives==0)*144));
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
		buffer.resetcounter();
		//Grass
		for(uint8_t n=0; n<MAXOBJECTS; n++) //spawns grass
		//for(uint8_t n=0; n<3; n++) //spawns grass
		{
			if(rectcoll(grasses[n].getx(), grasses[n].gety(), SPRITESIZE, SPRITESIZE, xscroll, yscroll, 400, 300-32, -8, -8, 0, 32)
				&& grasses[n].getspawned() ) //on screen
			{
				/*if(printit)
				{
					Serial.print("grass[");
					Serial.print(n);
					Serial.print("]: 1  ");
					Serial.print("x: ");
					Serial.print(grasses[n].getx());
					Serial.print(" y: ");
					Serial.print(grasses[n].gety());
					Serial.print("  xscroll: ");
					Serial.print(xscroll);
					Serial.print(" yscroll: ");
					Serial.println(yscroll);
				}*/
				buffer.insert(grasses[n].getx() - xscroll, grasses[n].gety() - yscroll, grasses[n].spr(), 0); //0 = no rotation
			}
			else
			{
				/*if(printit)
				{
					Serial.print("grass[");
					Serial.print(n);
					Serial.print("]: 0  ");
					Serial.print("x: ");
					Serial.print(grasses[n].getx());
					Serial.print(" y: ");
					Serial.print(grasses[n].gety());
					Serial.print("  xscroll: ");
					Serial.print(xscroll);
					Serial.print(" yscroll: ");
					Serial.println(yscroll);
				}*/
				buffer.insert(400, 400, grasses[n].spr(), 0); //0 = no rotation
			}
			if(!pause)
			{
				grasses[n].spawn(); //ACTION
			}
			
			//buffer.insert(grasses[n].getx(), grasses[n].gety(), grasses[n].spr(), 0); //0 = no rotation
		}
		
		//Cow / Player
		//player.cowmove(state);
		//buffer.insert(player.getx(), player.gety(), player.getframe(), player.getrotate());
		if(player.getdead())
		{
			buffer.insert(player.getsx(), player.getsy(), COW_DEAD, player.getrotate());
		}
		else
		{
			if(!pause)
			{
				player.cowmove(state); //ACTION
			}
			buffer.insert(player.getsx(), player.getsy(), player.getframe(), player.getrotate());
		}
	  
		//Wolves
		activewolves = score / THRESHOLD;
		if(score / THRESHOLD > MAXOBJECTS)
		{
			activewolves = MAXOBJECTS;
		}
		for(byte n=0; n < activewolves; n++)
		//for(byte n=0; n< 2; n++)
		{
			//Serial.print(n);
			//Serial.println(" ACTIVE");
			if(!pause)
			{
				wolves[n].activate(player.getx(), player.gety(), score, printit, n); //ACTION
			}
			if(rectcoll(wolves[n].getx(), wolves[n].gety(), SPRITESIZE, SPRITESIZE, xscroll, yscroll, 400, 300-32, -8, -8, 0, 32)
				&& wolves[n].getspawned() ) //on screen
			{
				buffer.insert(wolves[n].getx() - xscroll, wolves[n].gety() - yscroll, wolves[n].getframe(), wolves[n].getrotate());
			}
			else
			{
				buffer.insert(400, 400, wolves[n].getframe(), wolves[n].getrotate());
			}
		}
		
		//Crosshair
		if(!pause)
		{
			pcrosshair.crosshairmove(state); //ACTION
		}
		//*****END SPRITES*****
		
		//*****DISPLAY SPRITES*****
		//All Sprites On Field
		buffer.sortbuffer();
		for(byte n=0; n<buffer.getcounter(); n++)
		{
			draw_sprite(buffer.getx(n), buffer.gety(n), buffer.getspr(n), buffer.getrot(n));
		}
		
		pcrosshair.draw(); //draw crosshair last
		
		//Blue Border and Current Controls Below Score
		draw_blue_border();
		
		//Cow Spirit
		if(player.getdead())
		{
			//do not draw if off screen
			if((player.getsy()-int(deadtimer)/3) > -20)
			{
				draw_sprite(player.getsx(), player.getsy()-deadtimer/3, COW_SPIRIT, player.getrotate());
				deadtimer++;
			}
		}
		//Game Over
		//Serial.print("Before game over buttonpressed: ");
		//Serial.println(buttonpressed);
		if(player.getdead() && (lives==0))
		{
			if(score > oldscore)
			{
				//draw game over above center
				drawword("game", 0, 204-60, 152-56);
				drawword("over", 2, 204+60, 152-56);
				//draw high score and initials close to center
				drawword("high score", 1, 204, 152-12);
				for(byte n=0; n<3; n++)
				{
					if((!letterblink) || (n != letterselect))
					{
						drawletter(initial[n], 204-14+(14*n), 152+12);
					}
				}
				//timer to blink selected letter
				letterblinktimer++;
				if(letterblinktimer > 18)
				{
					letterblinktimer = 0;
					letterblink ^= true;
				}
				//draw instructions to confirm input
				drawword("press start to confirm", 1, 204, 152+48);
			}
		}
		//Pause
		if(pause)
		{
			drawword("pause", 1, 204, 152);
		}

		//hide unused
		while(GD.spr < 255)
		{
			GD.xhide();
		}
		GD.__end();
		//*****END DISPLAY SPRITES*****
		
		//*****BEGIN COLLISION DETECTION*****
		GD.waitvblank();
		bool grasscoll[MAXOBJECTS], wolfcoll[MAXOBJECTS], crosscoll[MAXOBJECTS], shotcoll[MAXOBJECTS];
		for(byte n=0; n<MAXOBJECTS; n++)
		{
			//player collision with grass and wolves
			grasscoll[n] = squcoll(grasses[n].getx(), grasses[n].gety(), SPRITESIZE, player.getx(), player.gety(), SPRITESIZE); 
			wolfcoll[n] = squcoll(wolves[n].getx(), wolves[n].gety(), SPRITESIZE, player.getx(), player.gety(), SPRITESIZE); 
			//crosshair collision
			crosscoll[n] = squcoll(pcrosshair.getx(), pcrosshair.gety(), CROSSCOLL, wolves[n].getx()-xscroll, wolves[n].gety()-yscroll, SPRITESIZE, CROSSOFF); 
			shotcoll[n] = squcoll(pcrosshair.getfx(), pcrosshair.getfy(), CROSSCOLL, wolves[n].getx()-xscroll, wolves[n].gety()-yscroll, SPRITESIZE, CROSSOFF); 
		}
		//*****RESOLVE COLLISION*****
		if(player.geteating())//player eats grass
		{ 
			for(byte n=0; n<MAXOBJECTS; n++)
			{
				if(grasscoll[n] && grasses[n].getspawned())
				{
					if(grasses[n].getx() < player.getx())//make player face left if grass is to left
					{
						player.setrotate(NOROT);
					}
					else if(grasses[n].getx() > player.getx())//opposite
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
			if(wolfcoll[n] && wolves[n].getstate() && wolves[n].getspawned())
			{
				player.died();
			}
		}
		if(deadtimer > DEADLENGTH + (int(lives==0)*144))//player.getdead())
		{
			for(uint16_t n=0; n<MAXOBJECTS; n++)
			{
				wolves[n].killed(144+(144*n)); //72 = 1 second
			}
			bonus=0;
			if((lives==0) && (score <= oldscore))
			{
				title = true;
				//setupgame();
			}
			else if(lives > 0)
			{
				lives--;
				deadtimer = 0;
				player.setup();
				for(uint16_t n=0; n<MAXOBJECTS; n++)
				{
					wolves[n].killed(144+(144*n)); //72 = 1 second
				}
			}
		}
		pcrosshair.setoverwolf(false);
		//interaction with wolf and crosshair
		for(byte n=0; n<MAXOBJECTS; n++)
		{ 
			//crosshair touches wolf
			if(crosscoll[n] && wolves[n].getstate())
			{
				wolves[n].setavoid();
				pcrosshair.setoverwolf(true);
			}
			//wolf is shot
			if(shotcoll[n] && wolves[n].getstate())
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
		
		//GAME OVER
		if(player.getdead() && (lives==0))
		{
			pause = false;
			//if high score
			if(score > oldscore)
			{
				//select letter to edit
				if((state & SNES_LEFT) && !(buttonpressed & SNES_LEFT))//!dpadpressed)
				{
					buttonpressed |= SNES_LEFT | SNES_RIGHT | SNES_UP | SNES_DOWN;
					if(letterselect == 0)
					{
						letterselect = 2;
					}
					else
					{
						letterselect--;
					}
				}
				if((state & SNES_RIGHT) && !(buttonpressed & SNES_RIGHT))
				{
					buttonpressed |= SNES_LEFT | SNES_RIGHT | SNES_UP | SNES_DOWN;
					if(letterselect == 2)
					{
						letterselect = 0;
					}
					else
					{
						letterselect++;
					}
				}
				//cycle letter
				if((state & SNES_UP) && !(buttonpressed & SNES_UP))
				{
					buttonpressed |= SNES_LEFT | SNES_RIGHT | SNES_UP | SNES_DOWN;
					if(initial[letterselect] == 'a')
					{
						initial[letterselect] = 'z';
					}
					else
					{
						initial[letterselect]--;
					}
				}
				if((state & SNES_DOWN) && !(buttonpressed & SNES_DOWN))
				{
					buttonpressed |= SNES_LEFT | SNES_RIGHT | SNES_UP | SNES_DOWN;
					if(initial[letterselect] == 'z')
					{
						initial[letterselect] = 'a';
					}
					else
					{
						initial[letterselect]++;
					}
				}
					
				if(!(state & SNES_LEFT) && !(state & SNES_RIGHT) && !(state & SNES_UP) && !(state & SNES_DOWN))
				{
					buttonpressed &= ~SNES_LEFT & ~SNES_RIGHT & ~SNES_UP & ~SNES_DOWN;
					//Serial.print("Inside dpad buttonpressed: ");
					//Serial.println(buttonpressed);
				}
				//Serial.print("Inside game over buttonpressed: ");
				//Serial.println(buttonpressed);
				if((state & SNES_START) && !(buttonpressed & SNES_START))
				{
					title = true;
				}
			}
		}
		//UPDATE SCORES
		if(!pause) //don't check when paused
		{
			//ACTION
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
		//RESET GAME
		if((state & SNES_SELECT)&&(state & SNES_START))
		{
			//title = true;
			player.died();
			lives=0;
			//state = 0;
			buttonpressed |= SNES_START;
		}
		//PAUSE
		if((state & SNES_START) && !(buttonpressed & SNES_START)) //prevent repeated press and only pause when player is alive
		{
			if(!player.getdead())
			{
				pause ^= true;
			}
			buttonpressed |= SNES_START; 
			Serial.print("Inside pressed buttonpressed: ");
			Serial.println(buttonpressed);
		}
		if(!(state & SNES_START))
		{
			buttonpressed &= ~SNES_START; //clear start
			//Serial.print("Inside clear buttonpressed: ");
			//Serial.println(buttonpressed);
		}
		
		//*****UPDATE CAMERA POSITION*****  311, 361
		//x position
		if((player.getx() >= 200) && (player.getx() < 311))
		{
			xscroll = player.getx() - 200;
		}
		else if(player.getx() < 200)
		{
			xscroll = 0;
		}
		else
		{
			xscroll = 111; //400+111=511
		}
		//y position
		if((player.gety() >= 150) && (player.gety() < 361))
		{
			yscroll = player.gety() - 150;
		}
		else if(player.gety() < 150)
		{
			yscroll = 0;
		}
		else
		{
			yscroll = 211; //300+211=511
		}
		GD.wr16(COMM+6, xscroll);
		GD.wr16(COMM+8, yscroll);
		//*****END UPDATE CAMERA POSITION*****
	}
	//END OF GAME LOOP
	
	GD.__wstartspr(0);
	draw_blue_border();
	while(GD.spr < 255)
	{
		GD.xhide();
	}
	GD.__end();
	setupgame(); //RESET EVERYTHING EXCEPT HIGH SCORE
	GD.copy(RAM_CHR, image_chr, sizeof(image_chr));
	GD.copy(RAM_PAL, image_pal, sizeof(image_pal));
	
	//RESET CAMERA TO ORIGINAL STATE
	GD.wr16(COMM+6, 0);
	GD.wr16(COMM+8, 0); //offset by 1 due to line 511 being on top of screen

	GD.wr16(BG_COLOR, greenbg); //set bg transparent color
	draw_BG();
	draw_fence();
	draw_title(13, 9, 21, 14);

	draw_score(atxy(26, 0), highscore);
	lefty=false; //RESET TO TITLE
	//holdselect = false;
	state = 0; //just in case
	
	title = true;
}

