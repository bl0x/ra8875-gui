#include <progress.h>
#include <math.h>
#include <gui.h>

Progress::Progress(int x, int y, int width, int height)
	: Widget(x, y)
	, color_border(GUI_PROGRESS_DEFAULT_COLOR_BORDER)
	, color_fill(GUI_PROGRESS_DEFAULT_COLOR_FILL)
	, color_background(GUI_PROGRESS_DEFAULT_COLOR_BACKGROUND)
	, width(width)
	, height(height)
	, border_width(1)
	, border_pad(1)
	, min(0), max(100), progress(0)
{
}

void
Progress::draw()
{
	int max_pixels_x = size.x - 2 * border_width - 2 * border_pad;
	int max_pixels_y = size.y - 2 * border_width - 2 * border_pad;
	float fill_percent = (progress - min) / (max - min);
	int fill_pixels = ceil(max_pixels_x * fill_percent);
	gui->debugln("Progress draw begin.");
	gui->tft.graphicsMode();
	gui->tft.setCursor(position.x, position.y);
	gui->tft.fillRect(position.x, position.y, size.x, size.y,
	    color_border);
	gui->tft.fillRect(
	    position.x + border_width, position.y + border_width,
	    size.x - 2 * border_width, size.y - 2 * border_width,
	    color_background);
	gui->tft.fillRect(position.x + border_width + border_pad,
	    position.y + border_width + border_pad,
	    fill_pixels, max_pixels_y, color_fill);
	gui->debugln("Progress draw end.");
	drawn = true;
}

void
Progress::calc_size()
{
	size.x = width;
	size.y = height;
	size_known = true;
}

void
Progress::handle_touch(Point2 pos)
{
	(void)pos;
}

void
Progress::set_min(float _min)
{
	if (_min > max) {
		return;
	}
	min = _min;
	drawn = false;
}

void
Progress::set_max(float _max)
{
	if (_max < min) {
		return;
	}
	max = _max;
	drawn = false;
}

void Progress::set_progress(float _progress)
{
	if (_progress < min) {
		_progress = min;
	}
	if (_progress > max) {
		_progress = max;
	}
	progress = _progress;
	drawn = false;
}
