#include <hline.h>
#include <gui.h>

HLine::HLine(int x, int y, int length, int width, uint16_t _color)
	: Widget(x, y), color(_color)
{
	size.x = length;
	size.y = width;
}

void
HLine::draw()
{
	gui->infoln("HLine draw begin.");
	gui->tft.graphicsMode();
	gui->tft.fillRect(position.x, position.y, size.x, size.y, color);
	gui->infoln("HLine draw end.");
	drawn = true;
}

void
HLine::calc_size()
{
	size_known = true;
}

void
HLine::handle_touch(Point2 pos) {}

