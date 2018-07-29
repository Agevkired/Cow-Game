#define SPRITE_FRAMES 51
static void draw_sprite(int x, int y, byte anim, byte rot, byte jk = 0)
    {
		char xx = -8;
		char yy = -8;
      switch (anim) {
/***COLOR 4A***/
//COW
//0
case 0: //neutral-eating2
GD.xsprite(x, y, xx, yy, 0, B1000, rot, jk);
break;
case 1: //Walk 1
GD.xsprite(x, y, xx, yy, 0, B1010, rot, jk);
break;
case 2: //Walk 2
GD.xsprite(x, y, xx, yy, 0, B1100, rot, jk);
break;
case 3: //Walk 3
GD.xsprite(x, y, xx, yy, 0, B1110, rot, jk);
break;
//1
case 4: //starting eat
GD.xsprite(x, y, xx, yy, 1, B1000, rot, jk);
break;
case 5: //eating 1
GD.xsprite(x, y, xx, yy, 1, B1010, rot, jk);
GD.xsprite(x, y, xx, yy, 9, B1001, rot, jk);
break;
case 6: //eating 2
GD.xsprite(x, y, xx, yy, 0, B1000, rot, jk);
if(rot!=0)
{
	GD.xsprite(x-1, y, xx, yy, 9, B1001, rot, jk);
}
else
{
	GD.xsprite(x+1, y, xx, yy, 9, B1001, rot, jk);
}
break;
//TITLE
case 7: //“COW” C1
GD.xsprite(x, y, xx, yy, 1, B1100, rot, jk);
break;
case 8: //C2
GD.xsprite(x, y, xx, yy, 1, B1110, rot, jk);
break;
//2
case 9: //C3-O1
GD.xsprite(x, y, xx, yy, 2, B1000, rot, jk);
break;
case 10: //C4-O2
GD.xsprite(x, y, xx, yy, 2, B1010, rot, jk);
break;
case 11: //O3
GD.xsprite(x, y, xx, yy, 2, B1100, rot, jk);
break;
case 12: //O4
GD.xsprite(x, y, xx, yy, 2, B1110, rot, jk);
break;
//3
case 13: //O5-W1
GD.xsprite(x, y, xx, yy, 3, B1000, rot, jk);
break;
case 14: //O6-W2
GD.xsprite(x, y, xx, yy, 3, B1010, rot, jk);
break;
case 15: //W3
GD.xsprite(x, y, xx, yy, 3, B1100, rot, jk);
break;
case 16: //W4
GD.xsprite(x, y, xx, yy, 3, B1110, rot, jk);
break;
//4
case 17: //W5, 
GD.xsprite(x, y, xx, yy, 4, B1000, rot, jk);
break;
case 18: //W6-Tail 1
GD.xsprite(x, y, xx, yy, 4, B1010, rot, jk);
break;
case 19: //Tail 2
GD.xsprite(x, y, xx, yy, 4, B1100, rot, jk);
break;
case 20: //Tail 3
GD.xsprite(x, y, xx, yy, 4, B1110, rot, jk);
break;
//5
case 21: //”GAME” G1
GD.xsprite(x, y, xx, yy, 5, B1000, rot, jk);
break;
case 22: //G2
GD.xsprite(x, y, xx, yy, 5, B1010, rot, jk);
break;
case 23: //G3
GD.xsprite(x, y, xx, yy, 5, B1100, rot, jk);
break;
case 24: //G4
GD.xsprite(x, y, xx, yy, 5, B1110, rot, jk);
break;
//6
case 25: //A1
GD.xsprite(x, y, xx, yy, 6, B1000, rot, jk);
break;
case 26: //A2
GD.xsprite(x, y, xx, yy, 6, B1010, rot, jk);
break;
case 27: //A3-M1
GD.xsprite(x, y, xx, yy, 6, B1100, rot, jk);
break;
case 28: //A4-M2
GD.xsprite(x, y, xx, yy, 6, B1110, rot, jk);
break;
//7
case 29: //M3
GD.xsprite(x, y, xx, yy, 7, B1000, rot, jk);
break;
case 30: //M4
GD.xsprite(x, y, xx, yy, 7, B1010, rot, jk);
break;
case 31: //M5-E1
GD.xsprite(x, y, xx, yy, 7, B1100, rot, jk);
break;
case 32: //M6-E2
GD.xsprite(x, y, xx, yy, 7, B1110, rot, jk);
break;
//8
case 33: //E3
GD.xsprite(x, y, xx, yy, 8, B1000, rot, jk);
break;
case 34: //E4
GD.xsprite(x, y, xx, yy, 8, B1010, rot, jk);
break;
case 35: //E5
GD.xsprite(x, y, xx, yy, 8, B1100, rot, jk);
break;
case 36: //E6
GD.xsprite(x, y, xx, yy, 8, B1110, rot, jk);
break;
/***COLOR 4B***/
//OTHER
//9
case 37: //mouth
GD.xsprite(x, y, xx, yy, 9, B1001, rot, jk);
break;
case 38: //crosshair black
GD.xsprite(x, y, xx, yy, 9, B1011, rot, jk);
break;
case 39: //crosshair red
GD.xsprite(x, y, xx, yy, 9, B1010, rot, jk);
break;
case 40: //shot
GD.xsprite(x, y, xx, yy, 9, B1101, rot, jk);
break;
/***COLOR 16A***/
//10
case 41: //grass
GD.xsprite(x, y, xx, yy, 10, B0100, rot, jk);
break;
//WOLVES
//chaser
case 42: //chaser neutral
GD.xsprite(x, y, xx, yy, 10, B0110, rot, jk);
break;
//11
case 43: //chaser walk 1
GD.xsprite(x, y, xx, yy, 11, B0100, rot, jk);
break;
case 44: //chaser walk 2
GD.xsprite(x, y, xx, yy, 11, B0110, rot, jk);
break;
//12
case 45: //chaser walk 3
GD.xsprite(x, y, xx, yy, 12, B0100, rot, jk);
break;
//charger
case 46: //charger neutral
GD.xsprite(x, y, xx, yy, 12, B0110, rot, jk);
break;
//13
case 47: //charger walk 1
GD.xsprite(x, y, xx, yy, 13, B0100, rot, jk);
break;
case 48: //charger walk 2
GD.xsprite(x, y, xx, yy, 13, B0110, rot, jk);
break;
//14
case 49: //charger walk 3
GD.xsprite(x, y, xx, yy, 14, B0100, rot, jk);
break;
case 50: //alert
GD.xsprite(x, y, xx, yy, 14, B0110, rot, jk);
break;
        }
    }
    
static PROGMEM prog_uchar sprite_sprimg[] = {
//0: neutral-eating2, Walk 1, Walk 2, Walk 3
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0xAA, 0xAA, 0x80, 0xC0, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x00, 0x00,
0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xAA, 0xEA, 0xBF, 0xEA, 0xEA, 0xBF, 0xBF, 0xBF, 0xC0, 0x00,
0xAA, 0xFF, 0xFF, 0xBF, 0xFF, 0xBF, 0xEA, 0xFF, 0xAA, 0xFF, 0xFF, 0xEA, 0xAA, 0xAA, 0xFF, 0x80,
0x2A, 0xFF, 0xFF, 0xEA, 0xFF, 0xEA, 0xFF, 0xFF, 0xEA, 0xFF, 0xFF, 0xFF, 0xEA, 0xEA, 0xFF, 0xAA,
0x00, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA,
0x00, 0x3F, 0x7F, 0x55, 0x55, 0x55, 0x7F, 0xFF, 0xFF, 0xAA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xAA,
0x00, 0x00, 0x15, 0x55, 0x55, 0x55, 0xD5, 0xFF, 0xFF, 0xAA, 0xBF, 0xFF, 0xBF, 0xBF, 0xFF, 0x2A,
0x00, 0x00, 0x00, 0x15, 0xD5, 0xD5, 0xFF, 0xFF, 0xFF, 0xEA, 0xEA, 0xFF, 0xEA, 0xAA, 0xBF, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xEA, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xBF, 0xBF, 0x3F, 0x3F, 0xFF, 0xFF, 0xBF, 0xBF, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xBF, 0xBF, 0x3B, 0x3B, 0x00, 0x00, 0xBF, 0xBF, 0x2F, 0x2F, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0x2F, 0x22, 0x22, 0x00, 0x00, 0x3B, 0x3B, 0x0A, 0x0A, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00,

//1: starting eat, eating 1, “COW” C1, C2
0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xA0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x80, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xA0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
0x80, 0x80, 0xE0, 0xE0, 0xE0, 0xE0, 0xA0, 0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
0x80, 0xA0, 0xEC, 0xEC, 0xEC, 0xE8, 0xA8, 0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
0xA0, 0xAC, 0xEC, 0xEC, 0xEC, 0xE8, 0xA8, 0x28, 0x2C, 0x3A, 0x3A, 0x3F, 0x3F, 0x3F, 0x30, 0x30,
0xA8, 0xAC, 0xEC, 0xEC, 0xEC, 0xEC, 0xA8, 0x2C, 0x2B, 0x3F, 0x3F, 0x2A, 0x2A, 0x2A, 0x2F, 0x20,
0xA8, 0xAC, 0xEF, 0xEB, 0xEF, 0xEA, 0xEE, 0xAF, 0x3B, 0x3F, 0x2F, 0x0F, 0x0A, 0x0A, 0x0F, 0x0A,
0xA0, 0xAF, 0xEF, 0xEF, 0xEF, 0xEE, 0xEE, 0xFE, 0xBF, 0x2F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0A,
0xA2, 0xAF, 0xEF, 0xE7, 0xF7, 0xF7, 0xFE, 0xFF, 0xEE, 0x8A, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8A,
0xA2, 0xA3, 0xE7, 0xF6, 0xF7, 0xF6, 0xF7, 0xEF, 0xCE, 0xCA, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8A,
0xA0, 0xA3, 0xF3, 0xF7, 0xF7, 0xF7, 0xEF, 0xCF, 0xCF, 0xCA, 0xCA, 0xCF, 0x8A, 0x8A, 0x8F, 0x80,
0x20, 0xA3, 0xF3, 0xFD, 0xFD, 0xFD, 0xEF, 0xCF, 0xCF, 0xCF, 0xCF, 0xCF, 0x8F, 0x8A, 0x8A, 0x80,
0x20, 0x20, 0xB1, 0xFD, 0xFD, 0xFD, 0xED, 0xCF, 0xCF, 0xCF, 0xCF, 0x8F, 0x8F, 0x8F, 0x8F, 0x80,
0x20, 0x20, 0x30, 0xB1, 0xF1, 0xFD, 0xEF, 0xCF, 0xCF, 0xC0, 0xC0, 0xCF, 0x8F, 0x8F, 0x8F, 0x80,
0x20, 0x20, 0x30, 0x30, 0xB0, 0xFF, 0xEF, 0xCA, 0xCA, 0xC0, 0xC0, 0xCF, 0xCF, 0x8A, 0x8A, 0x80,
0x20, 0x20, 0x30, 0x30, 0x30, 0xBA, 0xAA, 0x80, 0x80, 0x80, 0x80, 0x8A, 0x8A, 0x80, 0x80, 0x80,

//2: C3-O1, C4-O2, O3, O4
0xC2, 0xE2, 0xA2, 0xE2, 0xE2, 0xE2, 0x62, 0x62, 0x62, 0xA2, 0x62, 0x60, 0xA8, 0x68, 0x68, 0x68,
0xA2, 0xE2, 0xB2, 0xF2, 0xF2, 0xE2, 0x62, 0x62, 0x62, 0x62, 0x62, 0x60, 0x68, 0x68, 0x78, 0x78,
0xA3, 0xB3, 0xB3, 0xF3, 0xE3, 0xE3, 0xE3, 0x63, 0x63, 0x63, 0x62, 0x60, 0x68, 0x68, 0x78, 0xFA,
0xB3, 0xF3, 0xB3, 0xF3, 0xF3, 0xE3, 0xE3, 0xE3, 0x63, 0x63, 0x62, 0x60, 0x68, 0x68, 0xEA, 0xFA,
0xB3, 0xF3, 0xB3, 0xF3, 0xF3, 0xF3, 0xE3, 0xE3, 0xE3, 0xE3, 0xE2, 0xE0, 0xE8, 0xEA, 0xEA, 0xFB,
0xF2, 0xF2, 0xB2, 0xF2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE2, 0xE0, 0xEA, 0xEA, 0xEB, 0xEB,
0xF0, 0xF0, 0xB0, 0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xFA, 0xFA, 0xFB, 0xFB,
0xF0, 0xF0, 0xA0, 0xF0, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF0, 0xFA, 0xEA, 0xEF, 0xFF,
0xF8, 0xF8, 0xA8, 0xF8, 0xF8, 0xF8, 0xF8, 0xE8, 0xE8, 0xF8, 0xF8, 0xF0, 0xFA, 0xEA, 0xEF, 0xFF,
0xF8, 0xF8, 0xE8, 0xB8, 0xF8, 0xF8, 0xF8, 0xE8, 0xF8, 0xF8, 0xF8, 0xF0, 0xFA, 0xEA, 0xFF, 0xFF,
0xF8, 0xF8, 0xE8, 0xF8, 0xBC, 0xBC, 0xBC, 0xAC, 0xAC, 0xBC, 0xB8, 0xB0, 0xBA, 0xAA, 0xAF, 0xBF,
0xF8, 0xF8, 0xE8, 0xF8, 0xF8, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xF8, 0xF0, 0xB2, 0xBA, 0xBF, 0xBF,
0xF8, 0xF8, 0xE8, 0xF8, 0xF8, 0xF8, 0xFC, 0xFC, 0xDC, 0xDC, 0xD8, 0x90, 0x92, 0x92, 0xBB, 0xBF,
0xF8, 0xF8, 0xE8, 0xF8, 0xF8, 0xF8, 0xFC, 0xDC, 0xDC, 0xDC, 0xD8, 0xD0, 0x92, 0x92, 0x93, 0xBB,
0xB8, 0xF8, 0xE8, 0xF8, 0xF8, 0xF8, 0xD8, 0xDC, 0xDC, 0xEC, 0xD8, 0xD0, 0xE2, 0x92, 0x93, 0x93,
0x38, 0xB8, 0xA8, 0xB8, 0xB8, 0xB8, 0x98, 0x98, 0x98, 0xA8, 0x98, 0x90, 0xA2, 0x92, 0x93, 0x93,

//3: O5-W1, O6-W2, W3, W4
0xEE, 0xEE, 0xAE, 0x0A, 0x8C, 0x8C, 0xCC, 0xCC, 0xC8, 0xC0, 0x8A, 0x0A, 0xAE, 0xAE, 0xAA, 0xAE,
0xAF, 0xEF, 0xAF, 0x0B, 0x8E, 0xCC, 0xCC, 0xCC, 0xC8, 0xC0, 0x8A, 0x0A, 0xAE, 0xAA, 0xEA, 0xEA,
0xBF, 0xFF, 0xAF, 0x8B, 0x8F, 0xCE, 0xCC, 0xCC, 0xC8, 0xC0, 0xCA, 0x8A, 0xAB, 0xAB, 0xFA, 0xFB,
0xBF, 0xFF, 0xAF, 0x8B, 0xCF, 0xCF, 0xCE, 0xCC, 0xC8, 0xC0, 0xCA, 0xCA, 0xAB, 0xAA, 0xFA, 0xFA,
0xAF, 0xBF, 0xAF, 0x8B, 0xCF, 0xCF, 0xCF, 0xCE, 0xC8, 0xC0, 0xCA, 0xCA, 0xEA, 0xAA, 0xFA, 0xFA,
0xAE, 0xAE, 0xAF, 0x8B, 0xCF, 0xCF, 0xCF, 0x8F, 0xCA, 0xC0, 0xCA, 0xCA, 0xEA, 0xEA, 0xFA, 0xFA,
0xAF, 0xAF, 0xAE, 0x8B, 0xCF, 0xCF, 0x8F, 0x0F, 0x8A, 0xC0, 0xCA, 0xCA, 0xEA, 0xEA, 0xFA, 0xEA,
0xAF, 0xAF, 0xAF, 0xCA, 0xCF, 0xCF, 0x8F, 0x0F, 0x8A, 0xC0, 0xCA, 0xCA, 0xEA, 0xEA, 0xEA, 0xEA,
0xAF, 0xFF, 0xEF, 0xCA, 0xCF, 0x8F, 0x0F, 0x0F, 0x0A, 0x80, 0xCA, 0xCA, 0xEA, 0xEA, 0xEA, 0xAA,
0xBF, 0xFF, 0xEB, 0xCE, 0xCF, 0x8F, 0x0F, 0x0F, 0x0A, 0x80, 0xCA, 0xCA, 0xEA, 0xEA, 0xAA, 0xAA,
0xFB, 0xFB, 0xEF, 0xCE, 0x8F, 0x0F, 0x0F, 0x0F, 0x0A, 0x00, 0x8A, 0xCA, 0xEB, 0xAB, 0xAA, 0xAB,
0xFB, 0xFB, 0xEB, 0xCE, 0x8F, 0x0F, 0x0F, 0x2B, 0x02, 0x00, 0x8A, 0xCA, 0xEF, 0xAB, 0xAB, 0xAF,
0xFB, 0xFB, 0xEB, 0x8A, 0x0F, 0x0F, 0x2B, 0x23, 0x22, 0x00, 0x0A, 0x8A, 0xEF, 0xEF, 0xAF, 0xAF,
0xFB, 0xFB, 0xEB, 0x8A, 0x0F, 0x0B, 0x23, 0x33, 0x22, 0x00, 0x0A, 0x8A, 0xEF, 0xEF, 0xAF, 0xAF,
0xFF, 0xFB, 0xAB, 0x0A, 0x0B, 0x23, 0x23, 0x33, 0x32, 0x20, 0x0A, 0x0A, 0xAF, 0xEF, 0xEF, 0xEF,
0xBB, 0xBB, 0xAB, 0x0A, 0x03, 0x23, 0x33, 0x33, 0x32, 0x20, 0x0A, 0x0A, 0xAB, 0xAB, 0xAB, 0xAB,

//4: W5, W6-Tail 1, Tail 2, Tail 3
0x0A, 0x0E, 0x0E, 0x0E, 0x0A, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xE, 0xE, 0xE, 0xE, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xF, 0xF, 0xF, 0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xF, 0xF, 0xF, 0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xF, 0xF, 0xF, 0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xF, 0xF, 0xF, 0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0,
0xE, 0xE, 0xF, 0xF, 0xA, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0, 0x80, 0x0, 0x0,
0xAE, 0xAE, 0xAE, 0xAF, 0xAA, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0x28,
0xFA, 0xFA, 0xFE, 0xEE, 0xAA, 0xAC, 0xAC, 0xAC, 0xAC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0x3C, 0x3C,
0xFA, 0xFA, 0xEA, 0xEF, 0xEA, 0xAC, 0xAC, 0xAC, 0xAC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0x3C, 0x3C,
0xFA, 0xFA, 0xFA, 0xEA, 0xEA, 0xAC, 0xAC, 0xAC, 0xAC, 0xBC, 0xBC, 0xBC, 0xBC, 0xBC, 0x3C, 0x3C,
0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0x28,
0xA, 0xA, 0xA, 0xB, 0xA, 0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0, 0x0,
0xA, 0xA, 0xB, 0xB, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x80, 0x0, 0x0,
0xE, 0xA, 0xB, 0xB, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0,
0xA, 0xB, 0xB, 0xB, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

//5: ”GAME” G1, G2, G3, G4
0x28, 0xA8, 0xA8, 0xA8, 0xAA, 0xAA, 0xAE, 0xAA, 0xA2, 0xE2, 0xE2, 0xC2, 0xC2, 0xC2, 0x82, 0x2,
0x28, 0xA8, 0xB8, 0xBA, 0xBA, 0xBE, 0xBE, 0xBA, 0xB2, 0xB2, 0xE2, 0xC2, 0xC2, 0xC2, 0x82, 0x2,
0x28, 0xA8, 0xBA, 0xBA, 0xBB, 0xBF, 0xBF, 0xBA, 0xB2, 0xB2, 0xE2, 0xC2, 0xC2, 0xC2, 0x82, 0x2,
0x28, 0xAA, 0xBA, 0xBB, 0xBB, 0xBF, 0xBF, 0xBA, 0xF2, 0xF2, 0xE2, 0xC2, 0xC2, 0xC2, 0x82, 0x2,
0x2A, 0x2A, 0x3B, 0x3B, 0x3F, 0xBF, 0xBF, 0xFA, 0xF2, 0xF2, 0xE2, 0xC2, 0xC2, 0xC2, 0x82, 0x2,
0x2A, 0x2A, 0x2F, 0x2F, 0x2F, 0xAF, 0xAF, 0xEB, 0xE2, 0xE2, 0xE2, 0xC2, 0xC2, 0xC2, 0x82, 0x2,
0xA, 0xA, 0xF, 0xF, 0xF, 0x8F, 0x8F, 0xCB, 0xC3, 0xC3, 0xC2, 0xC0, 0xC0, 0xC0, 0x80, 0x0,
0xA, 0xA, 0xF, 0xF, 0xF, 0x8F, 0x8F, 0xCF, 0xCB, 0xC2, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x0,
0x8A, 0x8A, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0xCF, 0xCE, 0x88, 0xC8, 0xC8, 0xC8, 0xC8, 0x88, 0x8,
0x8A, 0x8A, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0xCE, 0x8C, 0x8C, 0x88, 0xC8, 0xC8, 0xC8, 0x88, 0x8,
0xCA, 0x8A, 0x8F, 0x8F, 0x8F, 0x8F, 0x8F, 0x8E, 0x8C, 0x8C, 0x8C, 0x8C, 0xCC, 0xCC, 0x8C, 0xC,
0x82, 0x8A, 0x8E, 0x8E, 0x8F, 0x8F, 0x8F, 0x8E, 0x8C, 0x8C, 0x8C, 0xCC, 0xCC, 0xCC, 0x8C, 0xC,
0x82, 0x82, 0x8A, 0x8E, 0x8E, 0x8F, 0x8F, 0x8E, 0x8C, 0x8C, 0x8C, 0xCC, 0xCC, 0xCC, 0x8C, 0xC,
0x82, 0x82, 0x82, 0x8A, 0x8E, 0x8F, 0x8F, 0x8E, 0x8C, 0x8C, 0xCC, 0xCC, 0xCC, 0xCC, 0x8C, 0xC,
0xC2, 0xA2, 0xA2, 0xA2, 0xAA, 0xEE, 0xAF, 0xAE, 0xAC, 0xEC, 0xEC, 0xEC, 0xEC, 0xEC, 0xAC, 0xC,
0x82, 0xA2, 0xA2, 0xA2, 0xA2, 0xAA, 0xAB, 0xAA, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xB8, 0xA8, 0x8,

//6: A1, A2, A3-M1, A4-M2
0xE8, 0xE8, 0xE8, 0xE8, 0xE8, 0xEA, 0xEA, 0xEE, 0xCE, 0xCE, 0xCE, 0xCE, 0x8E, 0xE, 0xAE, 0xAE,
0xE8, 0xE8, 0xE8, 0xE8, 0xEA, 0xEA, 0xEA, 0xEA, 0xEE, 0xCE, 0xCE, 0xCE, 0x8E, 0xE, 0xAE, 0xAE,
0xE8, 0xE8, 0xE8, 0xEA, 0xFA, 0xFB, 0xFB, 0xFF, 0xFF, 0xEF, 0xCF, 0xCE, 0x8E, 0xE, 0xAE, 0xAE,
0xA8, 0xA8, 0xAA, 0xBA, 0xBB, 0xBB, 0xBB, 0xBB, 0xFB, 0xFB, 0xEB, 0xCA, 0x8A, 0xA, 0xAA, 0xAA,
0x28, 0x2A, 0x3A, 0x3B, 0x3B, 0x3F, 0xBB, 0xB3, 0xF3, 0xF3, 0xF3, 0xE3, 0x82, 0x2, 0xA2, 0xA2,
0x2A, 0x2A, 0x2B, 0x2F, 0x2F, 0x2F, 0xBB, 0xB2, 0xF2, 0xF2, 0xF2, 0xF2, 0xA2, 0x2, 0xA2, 0xA2,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xB2, 0xF0, 0xF0, 0xF0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xF0, 0xF0, 0xF0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xF0, 0xF0, 0xF0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xF0, 0xF0, 0xF0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xF0, 0xF0, 0xF0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xF0, 0xF0, 0xF0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xF0, 0xB0, 0xB0, 0xF0, 0xA0, 0x0, 0xA0, 0xA0,
0xA, 0xA, 0xF, 0xF, 0xF, 0xF, 0xAA, 0xA0, 0xB0, 0xB0, 0xB0, 0xB0, 0xA0, 0x0, 0xA0, 0xA0,
0x2A, 0x2A, 0x2E, 0x2E, 0x2E, 0x2F, 0xAA, 0xA2, 0xB2, 0xB2, 0xB2, 0xB2, 0xA2, 0x2, 0xA2, 0xA2,
0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0xBA, 0xB3, 0xB3, 0xB3, 0xB3, 0xB3, 0xA3, 0x3, 0xA3, 0xA3,

//7: M3, M4, M5-E1, M6-E2
0xAA, 0xEA, 0xEA, 0xEA, 0xAA, 0xEA, 0xE8, 0xE0, 0xA0, 0x8, 0xAC, 0xAC, 0xAC, 0xE8, 0xE0, 0xEA,
0xAA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xE0, 0xA0, 0x8, 0xAC, 0xAC, 0xAC, 0xA8, 0xE0, 0xEA,
0xBB, 0xFB, 0xEB, 0xEB, 0xEB, 0xEB, 0xFA, 0xF0, 0xA0, 0x0, 0xA8, 0xAC, 0xB8, 0xB0, 0xB2, 0xFA,
0xBB, 0xEB, 0xEB, 0xEB, 0xEB, 0xEF, 0xFB, 0xF2, 0xA0, 0x0, 0xA8, 0xAC, 0xB8, 0xB0, 0xB2, 0xBB,
0xBF, 0xEB, 0xEB, 0xEB, 0xEB, 0xEF, 0xEB, 0xF2, 0xA0, 0x0, 0xA0, 0xA8, 0xB0, 0xB2, 0xB2, 0xBB,
0xAF, 0xEF, 0xEF, 0xEB, 0xEF, 0xEF, 0xEB, 0xE3, 0xA2, 0x0, 0xA0, 0xA8, 0xB0, 0xB2, 0xB3, 0xBB,
0xAF, 0xEF, 0xEE, 0xAF, 0xAF, 0xEF, 0xEB, 0xE3, 0xA2, 0x0, 0xA0, 0xA0, 0xB2, 0xB2, 0xB3, 0xBB,
0xBE, 0xEE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAB, 0xF3, 0xA3, 0x2, 0xA0, 0xA0, 0xB2, 0xB3, 0xB3, 0xBB,
0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAA, 0xB3, 0xA3, 0x2, 0xA0, 0xA2, 0xB2, 0xB3, 0xB3, 0xBB,
0xBE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xBA, 0xB3, 0xA3, 0x3, 0xA2, 0xA2, 0xB3, 0xB3, 0xB3, 0xFB,
0xBE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xBB, 0xB3, 0xA3, 0x3, 0xA2, 0xA2, 0xB3, 0xB3, 0xF3, 0xFB,
0xBE, 0xBE, 0xAE, 0xAE, 0xAE, 0xAF, 0xAB, 0xF3, 0xA3, 0x3, 0xA3, 0xA3, 0xF3, 0xF3, 0xF3, 0xFB,
0xAE, 0xBE, 0xBE, 0xAE, 0xAE, 0xAF, 0xAA, 0xF2, 0xA3, 0x3, 0xA3, 0xA3, 0xF3, 0xF3, 0xF3, 0xFA,
0xAE, 0xBE, 0xBE, 0xAE, 0xAE, 0xAF, 0xEA, 0xF2, 0xA3, 0x3, 0xA3, 0xA3, 0xF3, 0xF3, 0xF3, 0xFA,
0xAE, 0xBE, 0xAE, 0xAE, 0xAE, 0xEF, 0xEA, 0xF0, 0xA2, 0x3, 0xA3, 0xA3, 0xF3, 0xF3, 0xF2, 0xFA,
0xAA, 0xBA, 0xBA, 0xAA, 0xAA, 0xAB, 0xBA, 0xB0, 0xA2, 0x3, 0xA3, 0xA3, 0xB3, 0xB3, 0xB2, 0xBA,

//8: E3, E4, E5, E6
0xAE, 0xAE, 0xAE, 0xAE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xA, 0xA, 0xA, 0xA,
0xAE, 0xAE, 0xAE, 0xAE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xE, 0xA, 0xA, 0xA,
0xBF, 0xBB, 0xBA, 0xAA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xB, 0xB, 0xB, 0xB,
0x3F, 0x3B, 0x32, 0x22, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, 0x3, 0x3, 0x3,
0x3F, 0x3B, 0x33, 0x22, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3,
0x2F, 0x2A, 0x22, 0x22, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0xF, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x8F, 0x8A, 0x88, 0x88, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8,
0x8F, 0x8A, 0x88, 0x88, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8,
0xCF, 0xCE, 0xCC, 0x8C, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0xC, 0xC, 0xC, 0xC,
0xEF, 0xEE, 0xEE, 0xAE, 0xE, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xE, 0xE, 0xE,
0xEF, 0xEE, 0xEE, 0xAE, 0xE, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xA, 0xE, 0xE,
0xEF, 0xEF, 0xEF, 0xAF, 0xF, 0xF, 0xB, 0xB, 0xB, 0xA, 0xA, 0xA, 0xA, 0xE, 0xE, 0xE,
0xAB, 0xAB, 0xAB, 0xAB, 0xB, 0xB, 0xB, 0xB, 0xB, 0xB, 0xB, 0xA, 0xA, 0xA, 0xA, 0xA,

/* DISPLAY EACH COLOR (E4 = 11100100) (CLEAR, PINK, BLACK, WHITE)
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4, 0xE4,
*/

//Color 4b
//9: mouth, crosshair, shot
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x8, 0x0, 0x28, 0x28, 0x28, 0x28, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x28, 0x10, 0x10, 0x10, 0x10, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x28, 0x10, 0x18, 0x30, 0x30, 0x18, 0x10, 0x28, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x28, 0x10, 0x30, 0x38, 0x38, 0x30, 0x10, 0x28, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x28, 0x10, 0x30, 0x38, 0x38, 0x30, 0x10, 0x28, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x28, 0x10, 0x18, 0x30, 0x30, 0x18, 0x10, 0x28, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x28, 0x10, 0x10, 0x10, 0x10, 0x28, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x2, 0xA, 0x0, 0x28, 0x28, 0x28, 0x28, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

//Color 16a
//10: Grass, Chaser Neutral
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x6, 0x5, 0x5, 0x6, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0,
0x0, 0x6, 0x6, 0x6, 0x0, 0x6, 0x6, 0x5, 0x5, 0x6, 0x6, 0x0, 0x6, 0x6, 0x6, 0x0,
0x0, 0x6, 0x5, 0x5, 0x6, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x6, 0x5, 0x5, 0x6, 0x0,
0x10, 0x6, 0x5, 0x5, 0x16, 0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x6, 0x5, 0x5, 0x6, 0x0,
0x10, 0x26, 0x25, 0x25, 0x15, 0x6, 0x5, 0x5, 0x5, 0x5, 0x6, 0x5, 0x5, 0x15, 0x16, 0x0,
0x26, 0x36, 0x25, 0x35, 0x25, 0x6, 0x5, 0x5, 0x5, 0x5, 0x6, 0x5, 0x15, 0x15, 0x26, 0x6,
0x6, 0x25, 0x25, 0x25, 0x15, 0x16, 0x15, 0x15, 0x15, 0x15, 0x16, 0x15, 0x15, 0x25, 0x5, 0x6,
0x6, 0x6, 0x46, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x25, 0x6, 0x6, 0x6,
0x6, 0x6, 0x5, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x5, 0x5, 0x6, 0x6,
0x0, 0x6, 0x6, 0x5, 0x15, 0x25, 0x25, 0x25, 0x15, 0x25, 0x25, 0x5, 0x5, 0x6, 0x6, 0x0,
0x0, 0x0, 0x6, 0x5, 0x15, 0x6, 0x16, 0x5, 0x15, 0x6, 0x16, 0x5, 0x5, 0x6, 0x0, 0x0,
0x0, 0x0, 0x6, 0x6, 0x26, 0x6, 0x20, 0x6, 0x26, 0x0, 0x26, 0x6, 0x6, 0x6, 0x0, 0x0,

//11: chaser walk 1, walk 2
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x11, 0x0, 0x0, 0x0, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x11, 0x22, 0x22, 0x22, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x11, 0x11, 0x0,
0x22, 0x33, 0x22, 0x33, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x11, 0x11, 0x22, 0x0,
0x0, 0x22, 0x22, 0x22, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x0, 0x0,
0x0, 0x0, 0x44, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x11, 0x22, 0x22, 0x22, 0x11, 0x22, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x21, 0x0, 0x12, 0x0, 0x12, 0x0, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x20, 0x0, 0x20, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0,

//12: chaser walk 3, charger neutral
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x1, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x21, 0x2, 0x2, 0x2, 0x21, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0,
0x22, 0x13, 0x12, 0x13, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x21, 0x22, 0x0,
0x10, 0x32, 0x12, 0x32, 0x11, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x21, 0x22, 0x10, 0x0,
0x0, 0x10, 0x14, 0x11, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x22, 0x10, 0x0, 0x0,
0x0, 0x0, 0x40, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x10, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x20, 0x21, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x20, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x22, 0x10, 0x12, 0x10, 0x22, 0x10, 0x12, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x20, 0x0, 0x20, 0x0, 0x20, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x10, 0x0, 0x10, 0x0, 0x10, 0x0, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0,

//13: charger walk 1, walk 2
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x22, 0x0, 0x0, 0x0, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x22, 0x11, 0x11, 0x11, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x22, 0x0,
0x11, 0x33, 0x11, 0x33, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x22, 0x22, 0x11, 0x0,
0x0, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x11, 0x0, 0x0,
0x0, 0x0, 0x44, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x11, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x22, 0x11, 0x11, 0x11, 0x22, 0x11, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x12, 0x0, 0x21, 0x0, 0x21, 0x0, 0x12, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x10, 0x0, 0x10, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,

//14: charger walk 3, alert
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x2, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x2, 0x1, 0x1, 0x1, 0x2, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x0, 0x2, 0x2, 0x0,
0x1, 0x3, 0x1, 0x3, 0x1, 0x0, 0x0, 0x30, 0x30, 0x0, 0x0, 0x0, 0x2, 0x2, 0x1, 0x0,
0x0, 0x1, 0x1, 0x1, 0x2, 0x2, 0x2, 0x32, 0x32, 0x2, 0x2, 0x2, 0x2, 0x1, 0x0, 0x0,
0x0, 0x0, 0x4, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x1, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x2, 0x1, 0x1, 0x31, 0x32, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x30, 0x31, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,

};

static PROGMEM prog_uchar sprite_sprpal_4a[] = {
//clear:0      pink:1      black:2     white:3
0xff, 0xff, 0xB8, 0x7E, 0x00, 0x00, 0xFF, 0x7F
};


static PROGMEM prog_uchar sprite_sprpal_4b[] = {
//clear:0    orange:1     red:2      yellow:3
0xff, 0xff, 0x42, 0x7d, 0x00, 0x7c, 0x40, 0x7f
};

static PROGMEM prog_uchar sprite_sprpal_16a[] = {
//clear:0     gray:1   light gray:2  yellow:3
0xFF, 0xFF, 0xEF, 0x3D, 0x7F, 0x5E, 0x40, 0x7F,
//black:4  light grn:5  dark grn:6   white:7
0x00, 0x00, 0xE0, 0x03, 0xE0, 0x11, 0xFF, 0x7F,
0xFF, 0xFF, 0xB8, 0x7E, 0x00, 0x00, 0xFF, 0xFF,
0x00, 0x7C, 0xFF, 0xFF, 0xFF, 0x7F, 0x42, 0x7D,
};
