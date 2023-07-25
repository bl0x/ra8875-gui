#include <screen.h>
#include <gui.h>

void
Screen::draw()
{
	gui->debugln("Screen draw begin.");

#ifdef USE_SUMOTOY
	gui->tft.clearMemory();
	gui->tft.clearWidthColor(false);
	gui->tft.displayOn(true);
#endif

#ifdef USE_ADAFRUIT
	if (clear_all) {
		gui->tft.fillScreen(RA8875_BLACK);
		clear_all = false;
	}
#endif

	for (auto w : widgets) {
		if (!w->drawn) {
			w->calc_size();
			w->draw();
		}
	}

	gui->debugln("Screen draw done.");
}

void
Screen::add_widget(Widget *widget)
{
	gui->infoln("Screen add widget.");
	widgets.push_back(widget);
	widget->screen = this;
	widget->gui = gui;
}

void
Screen::redraw_all()
{
	clear_all = true;
	for (auto w : widgets) {
		w->drawn = false;
	}
}

void
Screen::handle_touch(Point2 pos)
{
	gui->info("Screen touched at ("); gui->info(pos.x);
	gui->info(","); gui->info(pos.y); gui->infoln(")");

	for (auto w : widgets) {
		if (w->clickable) {
			if (w->is_at(pos)) {
				w->handle_touch(pos);
			}
		}
	}
}
