#include <scale.h>
#include <math.h>
#include <gui.h>

Scale::Scale(int x, int y, int width, int height)
	: Widget(x, y)
	, color_border(GUI_SCALE_DEFAULT_COLOR_BORDER)
	, color_background(GUI_SCALE_DEFAULT_COLOR_BACKGROUND)
	, color_marker(GUI_SCALE_DEFAULT_COLOR_MARKER)
	, width(width)
	, height(height)
	, border_width(1)
	, border_pad(1)
	, min(0), max(100), value(0)
{
}

void
Scale::draw()
{
	bool too_low = false;
	bool too_high = false;
	int marker_width = 10;
	int max_pixels_x = size.x - 2 * border_width - 2 * border_pad
	    - marker_width;
	int max_pixels_y = size.y - 2 * border_width - 2 * border_pad;
	float marker_percent = (value - min) / (max - min);
	if (marker_percent < 0) {
		marker_percent = 0;
		too_low = true;
	}
	if (marker_percent > 1) {
		marker_percent = 1;
		too_high = true;
	}
	int center_pixel = ceil(max_pixels_x * marker_percent);
	int marker_left = center_pixel - marker_width / 2;

	gui->debugln("Scale draw begin.");
	gui->tft.graphicsMode();
	gui->tft.setCursor(position.x, position.y);
	/* draw border */
	gui->tft.fillRect(position.x, position.y, size.x, size.y,
	    color_border);
	gui->tft.fillRect(position.x + border_width,
	    position.y + border_width,
	    size.x - border_width, size.y - border_width, color_background);
	/* draw marker */
	gui->tft.fillRect(
	    position.x + border_width + border_pad
	               + marker_width / 2 + marker_left,
	    position.y + border_width + border_pad,
	    marker_width, max_pixels_y, color_marker);
	/* draw text */
	uint16_t text_color;
	if (value <= min || value >= max) {
		text_color = RA8875_RED;
	} else {
		text_color = RA8875_WHITE;
	}
	int tw = 8;
	int th = 16;
	int pad = 5;
	val_text = String((int)value) + String("     ");
	min_text = String((int)min) + String("     ");
	max_text = String("     ") + String((int)max);
	gui->tft.textMode();
	gui->tft.textColor(RA8875_WHITE, RA8875_BLACK);
	gui->tft.textSetCursor(position.x, position.y + size.y + pad);
	gui->tft.textWrite(min_text.c_str());
	gui->tft.textSetCursor(position.x + size.x - tw * max_text.length(),
	    position.y + size.y + pad);
	gui->tft.textWrite(max_text.c_str());
	gui->tft.textSetCursor(position.x + size.x + pad, position.y);
	gui->tft.textColor(text_color, RA8875_BLACK);
	gui->tft.textWrite(val_text.c_str());
	gui->debugln("Scale draw end.");
	drawn = true;
}

void
Scale::calc_size()
{
	size.x = width;
	size.y = height;
	size_known = true;
}

void
Scale::handle_touch(Point2 pos)
{
	(void)pos;
}

void
Scale::set_min(float _min)
{
	if (_min > max) {
		return;
	}
	min = _min;
}

void
Scale::set_max(float _max)
{
	if (_max < min) {
		return;
	}
	max = _max;
}

void Scale::set_value(float _value)
{
	value = _value;
}
