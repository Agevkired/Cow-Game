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
	bool cx = false, cy = false; //x and y collision flags
	if(ax + aoff < bx + boff) //ax is behind bx, use a's hitbox
	{
		cx = (ax + aoff + as) > (bx + boff);
	}
	else
	{
		cx = (bx + boff + bs) > (ax + aoff);
	}
	if(ay + aoff < by + boff)
	{
		cy = (ay + aoff + as) > (by + boff);
	}
	else
	{
		cy = (by + boff + bs) > (ay + aoff);
	}
	return cx & cy;
}

//Takes x, y coordinates and size of 2 objects, assumes rectangular
//axs, ays, bxs, bys are length of x and y sides for each object
//off are offsets for origin point which default to current position
//Returns if collided
bool rectcoll(int ax, int ay, int axs, int ays, int bx, int by, int bxs, int bys, int axoff=0, int ayoff=0, int bxoff=0, int byoff=0)
{
	bool cx = false, cy = false; //x and y collision flags
	if(ax + axoff < bx + bxoff) //ax is behind bx, use a's hitbox
	{
		cx = (ax + axoff + axs) > (bx + bxoff);
	}
	else
	{
		cx = (bx + bxoff + bxs) > (ax + axoff);
	}
	if(ay + ayoff < by + byoff)
	{
		cy = (ay + ayoff + ays) > (by + byoff);
	}
	else
	{
		cy = (by + byoff + bys) > (ay + ayoff);
	}
	return cx & cy;
}

#endif
