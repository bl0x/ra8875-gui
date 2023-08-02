#include <graph.h>
#include <gui.h>

Graph::Graph(int x, int y, int _width, int _height)
	: Widget(x, y), width(_width), height(_height)
	, n_gridlines(3)
	, color_bg(GUI_GRAPH_DEFAULT_COLOR_BG)
	, color_grid(GUI_GRAPH_DEFAULT_COLOR_GRID)
	, color_axes(GUI_GRAPH_DEFAULT_COLOR_AXES)
	, color_line {
	    GUI_GRAPH_DEFAULT_COLOR_LINE1,
	    GUI_GRAPH_DEFAULT_COLOR_LINE2,
	    GUI_GRAPH_DEFAULT_COLOR_LINE3,
	    GUI_GRAPH_DEFAULT_COLOR_LINE4}
{}

void
Graph::draw()
{
	gui->infoln("Graph draw begin.");
	draw_bg();
	draw_grid();
	draw_axes();
	draw_lines();
	drawn = true;
	gui->infoln("Graph draw end.");
}

void
Graph::draw_bg()
{
	gui->tft.graphicsMode();
	gui->tft.setCursor(position.x, position.y);
	gui->tft.fillRect(position.x, position.y, size.x, size.y, color_bg);
}

void
Graph::draw_grid()
{
	int x0, x1, y0, y1;
	int n_x, n_y;
	float aspect;
	x0 = position.x;
	y0 = position.y;
	x1 = position.x + size.x;
	y1 = position.y + size.y;
	if (size.x == 0 || size.y == 0) {
		return;
	}
	aspect = (float)size.x / (float)size.y;

	if (aspect < 1) {
		n_x = n_gridlines;
		n_y = n_gridlines / aspect;
	} else {
		n_y = n_gridlines;
		n_x = n_gridlines * aspect;
	}

	gui->info("grid lines n_x=");
	gui->info(n_x);
	gui->info(" n_y=");
	gui->infoln(n_y);

	gui->tft.graphicsMode();

	/* horizontal grid lines */
	float dy = size.y / n_y;
	for (int i = 0; i < n_y; ++i) {
		int y = y0 + (int)(dy * i);
		gui->tft.drawLine(x0, y, x1, y, color_grid);
	}

	/* vertical grid lines */
	float dx = size.x / n_x;
	for (int i = 0; i < n_x; ++i) {
		int x = x0 + (int)(dx * i);
		gui->tft.drawLine(x, y0, x, y1, color_grid);
	}
}

void
Graph::draw_axes()
{
	int x0, x1, y0, y1;
	x0 = position.x;
	y0 = position.y;
	x1 = position.x + size.x;
	y1 = position.y + size.y;

	gui->tft.graphicsMode();
	gui->tft.drawLine(x0, y1, x1, y1, color_axes);
	gui->tft.drawLine(x0, y0, x0, y1, color_axes);
}

void
Graph::calc_size()
{
	size.x = width;
	size.y = height;
	size_known = true;
}

void
Graph::handle_touch(Point2 pos)
{
}
