#ifndef BOXCOLL_H
#define BOXCOLL_H

/*
 * Created by agevkired 6/28/19
 * Hitbox starts at origin and extends right and down
 */

//Takes x, y coordinates and size of 2 objects, assumes square hitbox
//off are offsets for origin point which default to current position
//Returns if collided
bool squcoll(int ax, int ay, int as, int bx, int by, int bs, int aoff=0, int boff=0)
{
	bool cx, cy; //x and y collision flags
	if(ax < bx) //ax is behind bx, use a's hitbox
	{
		cx = ax + aoff + as > bx + boff;
	}
	else
	{
		cx = bx + boff + bs > ax + aoff;
	}
	if(ay < by)
	{
		cy = ay + aoff + as > by + boff;
	}
	else
	{
		cy = by + boff + bs > ay + aoff;
	}
	return cx & cy;
}

bool rectcoll(int ax, int ay, int ahx, int ahy, int bx, int by, int bhx, int bhy)
{
	bool cx, cy; //x and y collision flags
	if(ax < bx) //ax is behind bx, use a's hitbox
	{
		cx = (bx - ax) < ahx;
	}
	else
	{
		cx = (ax - bx) < bhx;
	}
	if(ay < by)
	{
		cy = (by - ay) < ahy;
	}
	else
	{
		cy = (ay - by) < bhy;
	}
	return cx & cy;
}

#endif
