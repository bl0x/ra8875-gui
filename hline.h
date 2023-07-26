#pragma once
#include <stdint.h>
#include <widget.h>

class HLine : public Widget
{
	public:
	HLine(int x, int y, int length, int width, uint16_t color);
	void draw(void);
	void handle_touch(Point2 pos);
	void calc_size(void);
	uint16_t color;
};
