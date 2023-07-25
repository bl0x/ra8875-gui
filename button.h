#pragma once
#include <stdint.h>
#include <widget.h>

typedef void(*on_click_function)(void);

#define GUI_BUTTON_DEFAULT_COLOR_BUTTON RA8875_WHITE
#define GUI_BUTTON_DEFAULT_COLOR_TEXT   RA8875_BLACK

class Button : public Widget
{
	public:
	Button(int x, int y, const char *text, on_click_function);

	void set_text(const char *_text) {
		text_len = strlen(_text);
		text = _text;
		size_known = false;
	}
	void set_scale(uint8_t _scale) {
		scale = _scale;
	}
	void set_color(uint16_t text, uint16_t button) {
		color_text = text;
		color_button = button;
	}
	void draw(void);
	void handle_touch(Point2 pos);
	void calc_size(void);

	const char *text;
	int text_len;
	on_click_function clicked;

	uint16_t color_button;
	uint16_t color_text;
	uint8_t scale;
	Point2 pad;
};
