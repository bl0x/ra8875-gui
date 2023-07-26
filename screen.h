#pragma once

#include <point.h>
#include <widget.h>

#define SCREEN_TITLE_REFRESH_SECONDS 1
#define SCREEN_STATUS_REFRESH_SECONDS 1
#define SCREEN_DEFAULT_PROCESS_MILLISECONDS 1000

class Gui;

class Screen
{
	public:
	Screen(Gui *_gui, void *_data, const char *_title) : gui(_gui),
		data(_data), clear_all(false),
       		show_title(true), show_status(true), title_text(_title),
       		title(nullptr), status(nullptr),
		last_title_update(0), last_status_update(0),
       		process_interval(SCREEN_DEFAULT_PROCESS_MILLISECONDS),
		last_processed(0) {}
	std::vector<Widget *>widgets;

	void draw(void);
	void redraw_all(void);
	void add_widget(Widget *widget);
	void handle_touch(Point2 pos);

	virtual void build(void) = 0;
	virtual void process(void) {};

	Gui *gui;
	void *data;
	bool clear_all;
	bool show_title;
	bool show_status;
	const char *title_text;

	Widget *title;
	Widget *status;

	/* all in milliseconds */
	unsigned long last_title_update;
	unsigned long last_status_update;
	unsigned long process_interval;
	unsigned long last_processed;
};

