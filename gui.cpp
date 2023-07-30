#include <gui.h>
#include <screen.h>

Gui::Gui()
  : screen(nullptr), next_screen_index(-1)
  , screen_index(-1), verbosity(GV_INFO), uart(&Serial), data(nullptr)
  , last_loop(0), min_interval(1000 / GUI_MAX_LOOP_FREQ_HZ)
  , touch_interval(GUI_MIN_TOUCH_INTERVAL_MILLISECONDS), touched(false)
#ifdef USE_SUMOTOY
  , tft(RA8875(RA8875_CS, RA8875_RESET, RA8875_MOSI, RA8875_SCLK, RA8875_MISO))
#endif
#ifdef USE_ADAFRUIT
  , tft(Adafruit_RA8875(RA8875_CS, RA8875_RESET))
#endif
{}

bool
Gui::begin()
{
	uart->begin();
	delay(2000);

	infoln("GUI begin.");

#ifdef USE_SUMOTOY
	tft.begin(RA8875_DISPLAY);
	tft.useINT(RA8875_INT);
	tft.touchBegin();
	info("Rotation: "); infoln(tft.getRotation());
	info("Status: "); infoln(tft.readStatus());
#endif

#ifdef USE_ADAFRUIT
	SPI.setTX(RA8875_MOSI);
	SPI.setRX(RA8875_MISO);
	SPI.setSCK(RA8875_SCLK);
	bool rc = tft.begin(RA8875_800x480);
	if (!rc) {
		infoln("RA8875 not found");
		while (1) { delay(1000); infoln("HALTED"); }
	}
	tft.displayOn(true);
	// Enable TFT - display enable tied to GPIOX
	tft.GPIOX(true);
	// PWM output for backlight
	tft.PWM1config(true, RA8875_PWM_CLK_DIV1024);
	tft.PWM1out(255);
	tft.fillScreen(RA8875_BLACK);
	tft.touchEnable(true);
#endif

	return true;
}

void
Gui::set_data(void *_data)
{
	data = _data;
}

void
Gui::add_screen(int index, Screen *screen)
{
	info("Adding screen at index "); infoln(index);
	screen->build();
	screens.insert(std::make_pair(index, screen));
	screen->gui = this;
}

void
Gui::do_change()
{
	info("Change to screen "); infoln(next_screen_index);
	auto r = screens.find(next_screen_index);
	screen_index = r->first;
	screen = r->second;
	screen->redraw_all();
}

void
Gui::change(int index)
{
	info("Schedule change to screen "); infoln(index);
	next_screen_index = index;
}

void
Gui::loop(void)
{
	/* limit update rate */
	unsigned long now;
	do {
		now = millis();
		delay(10);
	} while ((now - last_loop) < min_interval);

	last_loop = now;

	debug("GUI loop: "); debugln(now);

	/* check, if screen change was scheduled */
	if (next_screen_index != screen_index) {
		do_change();
	}

	/* check touchpad */
	Point2 pos;
	touched = false;
	if (tft.touched()) {
		if ((now - last_touched) < touch_interval) {
		} else {
			uint16_t x, y;
			tft.touchRead(&x, &y);
			pos = calibrate(x, y);
			touched = true;
			last_touched = now;
		}
	}

	if (touched) {
		handle_touch(pos);
	}

	screen->draw();
}

void
Gui::handle_touch(Point2 pos)
{
	screen->handle_touch(pos);
}
	
Point2
Gui::calibrate(uint16_t x, uint16_t y)
{
	Point2 p;
	p.x = ((cal_an * x) + (cal_bn * y) + cal_cn) / cal_div;
	p.y = ((cal_dn * x) + (cal_en * y) + cal_fn) / cal_div;
	return p;
}
