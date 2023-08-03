#pragma once
#include <stdint.h>
#include <string.h>
#include <widget.h>

#define GUI_LABEL_DEFAULT_COLOR_BACKGROUND RA8875_BLACK
#define GUI_LABEL_DEFAULT_COLOR_TEXT       RA8875_WHITE

class Label : public Widget
{
	public:
	Label(int x, int y, const char *text);

	void set_text(const char *_text) {
		len = strlen(_text);
		text = _text;
		size_known = false;
		drawn = false;
	}
	void set_scale(uint8_t _scale) {
		scale = _scale;
		size_known = false;
		drawn = false;
	}
	void draw(void);
	void handle_touch(Point2 pos);
	void calc_size(void);

	const char *text;
	int len;
	
	uint16_t color_background;
	uint16_t color_text;
	uint8_t scale;
};
