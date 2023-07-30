#pragma once
#include <SPI.h>
#include <gui_config.h>
#ifdef USE_SUMOTOY
#include <RA8875.h>
#endif
#ifdef USE_ADAFRUIT
#include <Adafruit_GFX.h>
#include <Adafruit_RA8875.h>
#endif
#include <map>

#include <point.h>

#define TO565(r, g, b)   (((uint16_t)(r & 0xf8)) << 8 \
    			| ((uint16_t)(g & 0xfc)) << 3 \
			| ((uint16_t)(b >> 3)))

#define GUI_DEFAULT_FONT_HEIGHT 16
#define GUI_DEFAULT_FONT_WIDTH   8

class Screen;

enum GuiVerbosity {GV_OFF, GV_INFO, GV_DEBUG};

class Gui
{
	public:
	Gui(void);
	bool begin(void);
	void set_data(void *data);
	void add_screen(int index, Screen *screen);
	void change(int index);
	void do_change();
	void loop(void);
	void handle_touch(Point2 pos);
	Point2 calibrate(uint16_t x, uint16_t y);

	template <typename T>
	void info(T t) { if (verbosity >= GV_INFO) { uart->print(t); }}
	template <typename T>
	void infoln(T t) { if (verbosity >= GV_INFO) { uart->println(t); }}
	template <typename T>
	void debug(T t) { if (verbosity >= GV_DEBUG) { uart->print(t); }}
	template <typename T>
	void debugln(T t) { if (verbosity >= GV_DEBUG) { uart->println(t); }}

	std::map<int, Screen *>screens;
	Screen *screen;
	int next_screen_index;
	int screen_index;
	int verbosity;
	SerialUSB *uart;
	void *data;

	unsigned long last_loop;
	unsigned long last_touched;
	unsigned long min_interval;
	unsigned long touch_interval;
	bool touched;

	/* RA8875 tft; */
	Adafruit_RA8875 tft;
};
