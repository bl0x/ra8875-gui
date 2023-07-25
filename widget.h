#pragma once
#include <vector>
#include <point.h>
#include <rect.h>

class Gui;
class Screen;

class Widget
{
	public:
	Widget();
	Widget(Gui *gui, int, int);
	Widget(int x, int y);

	virtual void draw(void) = 0;
	virtual void handle_touch(Point2 pos) = 0;
	virtual void calc_size(void) = 0;

	Rect rect(void);
	bool is_at(Point2 pos);

	Gui *gui;
	Screen *screen;
	std::vector<Widget *>children;	
	Point2 position;
	Point2 size;
	bool clickable;
	bool size_known;
	bool drawn;
};
