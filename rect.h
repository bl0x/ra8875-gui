#pragma once

struct Rect
{
	int x;
	int y;
	int w;
	int h;
	Rect(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
	Rect() : Rect(0, 0, 0, 0) {}
	Rect(Point2 topleft, Point2 bottomright)
	    : Rect(topleft.x, topleft.y, bottomright.x - topleft.x,
		bottomright.y - topleft.y) {}
};
