#pragma once
#include <Arduino.h>
#include <widget.h>
#include <stdint.h>

struct Point2;

#define RA8875_ORANGE TO565(0xff, 0x88, 0x00)

#define GUI_GRAPH_DEFAULT_COLOR_BG    RA8875_BLACK
#define GUI_GRAPH_DEFAULT_COLOR_AXES  RA8875_WHITE
#define GUI_GRAPH_DEFAULT_COLOR_GRID  RA8875_BLUE
#define GUI_GRAPH_DEFAULT_COLOR_LINE1 RA8875_YELLOW
#define GUI_GRAPH_DEFAULT_COLOR_LINE2 RA8875_ORANGE
#define GUI_GRAPH_DEFAULT_COLOR_LINE3 RA8875_RED
#define GUI_GRAPH_DEFAULT_COLOR_LINE4 RA8875_CYAN

#define GRAPH_MAX_LINES 4

class GraphLine
{
	public:
	GraphLine() : xs(), ys(), size(0), color(0) {}
	std::vector<float> xs;
	std::vector<float> ys;
	size_t size;
	uint16_t color;

	void clear()
	{
		xs.clear();
		ys.clear();
		size = 0;
	}

	void add_point(float x, float y)
	{
		xs.push_back(x);
		ys.push_back(y);
		size++;
	}
};

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
	void draw_line(int i);
	void draw_labels(void);
	Point2 transform(int i, float a, float b);

	void clear(int i)
	{
		lines[i].clear();
		drawn = false;
	}
	void add_point(int i, float x, float y)
	{
		lines[i].add_point(x, y);
		drawn = false;
	}


	void set_xrange(float min, float max) {
		if ((max - min) <= 0) {
			return;
		}
		xmin = min;
		xmax = max;
		xscale = size.x / (max - min);
	}
	void set_yrange(int i, float min, float max) {
		if ((max - min) <= 0) {
			return;
		}
		ymin[i] = min;
		ymax[i] = max;
		yscale[i] = size.y / (max - min);
	}

	int width;
	int height;
	int n_gridlines;

	float xmin, xmax;
	float ymin[GRAPH_MAX_LINES], ymax[GRAPH_MAX_LINES];
	float xscale;
	float yscale[GRAPH_MAX_LINES];

	uint16_t color_bg;
	uint16_t color_grid;
	uint16_t color_axes;

	String xmin_text;
	String xmax_text;
	String ymin_text;
	String ymax_text;

	GraphLine lines[GRAPH_MAX_LINES];
};
