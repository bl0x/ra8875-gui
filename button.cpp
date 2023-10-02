#include <string.h>
#include <button.h>
#include <gui.h>

Button::Button(int x, int y, const char *_text, on_click_function f,
    void *_data)
	: Widget(x, y), clicked(f), data(_data)
	, color_button(GUI_BUTTON_DEFAULT_COLOR_BUTTON)
	, color_text(GUI_BUTTON_DEFAULT_COLOR_TEXT)
	, pad(5, 5)
	, scale(GUI_TEXT_SCALE_NORMAL)
{
	set_text(_text);
	clickable = true;
}

void
Button::draw()
{
	uint16_t fill_color;
	uint16_t text_color;

	if (enabled) {
		fill_color = color_button;
		text_color = color_text;
	} else {
		fill_color = RA8875_GRAY;
		text_color = RA8875_BLACK;
	}

	gui->debugln("Button draw begin.");
	gui->debug("  text = "); gui->debugln(text);
	gui->tft.graphicsMode();
	gui->tft.setCursor(position.x, position.y);
	gui->tft.fillRect(position.x, position.y, size.x, size.y,
	    fill_color);
	gui->tft.textMode();
	gui->tft.textEnlarge(scale);
	gui->tft.textSetCursor(position.x + pad.x, position.y + pad.y);
	gui->tft.textTransparent(text_color);
	gui->tft.textWrite(text);
	gui->tft.textEnlarge(GUI_TEXT_SCALE_NORMAL);
	gui->debugln("Button draw end.");
	drawn = true;
}

void
Button::calc_size()
{
	int text_width = GUI_DEFAULT_FONT_WIDTH * text_len;
	int text_height = GUI_DEFAULT_FONT_HEIGHT;
	size.x = (text_width * (scale + 1)) + 2 * pad.x;
	size.y = (text_height * (scale + 1)) + 2 * pad.y;
	size_known = true;
}

void
Button::handle_touch(Point2 pos)
{
	if (!enabled) {
		gui->info("Button disabled: "); gui->infoln(text);
		return;
	}
	gui->info("Button pressed: "); gui->infoln(text);
	if (clicked != nullptr) {
		clicked(this, data);
	}
}
