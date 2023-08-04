#include <graph.h>
#include <gui.h>

/* TODO: autoscale ? */

Graph::Graph(int x, int y, int _width, int _height)
	: Widget(x, y), width(_width), height(_height)
	, n_gridlines(3)
	, color_bg(GUI_GRAPH_DEFAULT_COLOR_BG)
	, color_grid(GUI_GRAPH_DEFAULT_COLOR_GRID)
	, color_axes(GUI_GRAPH_DEFAULT_COLOR_AXES)
	, xmin(0), xmax(1), ymin(0), ymax(1), xscale(1), yscale(1)
{
	lines[0].color = GUI_GRAPH_DEFAULT_COLOR_LINE1;
	lines[1].color = GUI_GRAPH_DEFAULT_COLOR_LINE2;
	lines[2].color = GUI_GRAPH_DEFAULT_COLOR_LINE3;
	lines[3].color = GUI_GRAPH_DEFAULT_COLOR_LINE4;
}

void
Graph::draw()
{
	gui->debugln("Graph draw begin.");
	draw_bg();
	draw_grid();
	draw_axes();
	draw_lines();
	draw_labels();
	drawn = true;
	gui->debugln("Graph draw end.");
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

	gui->debug("grid lines n_x=");
	gui->debug(n_x);
	gui->debug(" n_y=");
	gui->debugln(n_y);

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
Graph::draw_lines()
{
	for (int i = 0; i < GRAPH_MAX_LINES; ++i) {
		draw_line(i);
	}
}

Point2
Graph::transform(float a, float b)
{
	int x, y;
	x = position.x + (a - xmin) * xscale;
	y = position.y + size.y - ((b - ymin) * yscale);
	return {x, y};
}

void
Graph::draw_line(int i)
{
	auto line = lines[i];
	Point2 p;
	int xprev, yprev;
	if (line.size == 0) {
		return;
	}
	gui->tft.graphicsMode();
	p = transform(line.xs[0], line.ys[0]);
	gui->tft.setCursor(p.x, p.y);
	xprev = p.x;
	yprev = p.y;
	for (int i = 1; i < line.size; ++i) {
		p = transform(line.xs[i], line.ys[i]);
		if (p.x != xprev) {
			gui->tft.drawLine(xprev, yprev, p.x, p.y, line.color);
			xprev = p.x;
			yprev = p.y;
		} else {
			/* remember min/max */
		}
	}
}

void
Graph::draw_labels()
{
	int th = 16;
	int tw = 8;
	int pad = 5;
	int tlx = position.x;
	int tly = position.y;
	int blx = tlx;
	int bly = tly + size.y;
	int brx = blx + size.x;
	int bry = bly;

	xmin_text = String((int)xmin) + String("     ");
	xmax_text = String("     ") + String((int)xmax);
	ymin_text = String("     ") + String((int)ymin);
	ymax_text = String("     ") + String((int)ymax);

	gui->tft.textMode();
	gui->tft.textColor(RA8875_WHITE, RA8875_BLACK);
	gui->tft.textSetCursor(blx - tw * ymin_text.length() - pad, bly - th);
	gui->tft.textWrite(ymin_text.c_str());
	gui->tft.textSetCursor(tlx - tw * ymax_text.length() - pad, tly);
	gui->tft.textWrite(ymax_text.c_str());
	gui->tft.textSetCursor(blx, bly + pad);
	gui->tft.textWrite(xmin_text.c_str());
	gui->tft.textSetCursor(brx - tw * xmax_text.length(), bry + pad);
	gui->tft.textWrite(xmax_text.c_str());
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

