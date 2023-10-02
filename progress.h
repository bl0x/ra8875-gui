#pragma once
#include <stdint.h>
#include <widget.h>

class Progress;

#define GUI_PROGRESS_DEFAULT_COLOR_BORDER     RA8875_WHITE
#define GUI_PROGRESS_DEFAULT_COLOR_FILL       RA8875_GREEN
#define GUI_PROGRESS_DEFAULT_COLOR_BACKGROUND RA8875_BLACK

class Progress : public Widget
{
	public:
	Progress(int x, int y, int width, int height);

	void set_min(float);
	void set_max(float);
	void set_progress(float);

	void draw(void);
	void handle_touch(Point2 pos);
	void calc_size(void);

	uint16_t color_border;
	uint16_t color_fill;
	uint16_t color_background;
	int width;
	int height;
	int border_width;
	int border_pad;
	float min, max;
	float progress;
};
