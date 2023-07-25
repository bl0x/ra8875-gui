#pragma once

#include <point.h>
#include <widget.h>

class Gui;

class Screen
{
	public:
	Screen(Gui *_gui) : gui(_gui), clear_all(false) {}
	std::vector<Widget *>widgets;

	void draw(void);
	void redraw_all(void);
	void add_widget(Widget *widget);
	void handle_touch(Point2 pos);

	virtual void build(void) = 0;

	Gui *gui;
	bool clear_all;
};

