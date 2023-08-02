#pragma once
#include <widget.h>
#include <stdint.h>

#define RA8875_ORANGE TO565(0xff, 0x88, 0x00)

#define GUI_GRAPH_DEFAULT_COLOR_BG    RA8875_BLACK
#define GUI_GRAPH_DEFAULT_COLOR_AXES  RA8875_WHITE
#define GUI_GRAPH_DEFAULT_COLOR_GRID  RA8875_BLUE
#define GUI_GRAPH_DEFAULT_COLOR_LINE1 RA8875_YELLOW
#define GUI_GRAPH_DEFAULT_COLOR_LINE2 RA8875_ORANGE
#define GUI_GRAPH_DEFAULT_COLOR_LINE3 RA8875_RED
#define GUI_GRAPH_DEFAULT_COLOR_LINE4 RA8875_CYAN

#define GRAPH_MAX_LINES 4

class Graph : public Widget
{
	public:
	Graph(int x, int y, int width, int height);
	Graph() : Graph(0, 0, 10, 10) {}

	void draw(void);
	void handle_touch(Point2 pos);
	void calc_size(void);

	void draw_bg(void);
	void draw_grid(void);
	void draw_axes(void);
	void draw_lines(void);

	int width;
	int height;
	int n_gridlines;

	uint16_t color_bg;
	uint16_t color_grid;
	uint16_t color_axes;
	uint16_t color_line[GRAPH_MAX_LINES];
};
