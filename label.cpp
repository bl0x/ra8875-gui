#include <string.h>
#include <stdint.h>

#include <label.h>
#include <gui.h>

Label::Label(int x, int y, const char *_text)
	: Widget(x, y)
	, color_background(GUI_LABEL_DEFAULT_COLOR_BACKGROUND)
	, color_text(GUI_LABEL_DEFAULT_COLOR_TEXT)
	, scale(GUI_TEXT_SCALE_NORMAL)
{
	set_text(_text);
}

void
Label::draw()
{
	gui->debugln("Label draw begin.");
	gui->debug("  text = ");
	gui->debugln(text);
	gui->tft.textMode();
	gui->tft.textEnlarge(scale);
	gui->tft.textSetCursor(position.x, position.y);
	gui->tft.textColor(color_text, color_background);
	gui->tft.textWrite(text);
	gui->tft.textEnlarge(GUI_TEXT_SCALE_NORMAL);
	gui->debugln("Label draw end.");
	drawn = true;
}

void
Label::handle_touch(Point2 pos) {}

void
Label::calc_size()
{
	size.x = GUI_DEFAULT_FONT_WIDTH * len * (scale + 1);
	size.y = GUI_DEFAULT_FONT_HEIGHT * (scale + 1);
	size_known = true;
}
