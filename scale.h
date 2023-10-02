#pragma once
#include <Arduino.h>
#include <stdint.h>
#include <widget.h>

class Scale;

#define GUI_SCALE_DEFAULT_COLOR_BORDER     RA8875_WHITE
#define GUI_SCALE_DEFAULT_COLOR_MARKER     RA8875_GREEN     
#define GUI_SCALE_DEFAULT_COLOR_BACKGROUND RA8875_BLACK

class Scale : public Widget
{
	public:
	Scale(int x, int y, int width, int height);

	void set_min(float);
	void set_max(float);
	void set_value(float);

	void draw(void);
	void handle_touch(Point2 pos);
	void calc_size(void);

	uint16_t color_border;
	uint16_t color_background;
	uint16_t color_marker;
	int width;
	int height;
	int border_width;
	int border_pad;
	float min, max;
	float value;

	String min_text;
	String max_text;
	String val_text;
};
