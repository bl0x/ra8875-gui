#include <widget.h>
#include <gui.h>

Widget::Widget(Gui *_gui, int x, int y)
	: gui(_gui), screen(nullptr), parent(nullptr), position(x, y),
	size(0, 0), clickable(false), size_known(false), drawn(false) {}
Widget::Widget() : Widget(nullptr, 0, 0) {}
Widget::Widget(int x, int y) : Widget(nullptr, x, y) {}

bool
Widget::is_at(Point2 _pos)
{
	if (!size_known) {
		calc_size();
	}
	return (position.x < _pos.x) && ((position.x + size.x) > _pos.x)
	    && (position.y < _pos.y) && ((position.y + size.y) > _pos.y);
}

Rect
Widget::rect()
{
	if (!size_known) {
		calc_size();
	}
	return Rect(position.x, position.y, size.x, size.y);
}

void
Widget::add_widget(Widget *widget)
{
	widgets.push_back(widget);
	widget->parent = this;
	widget->screen = screen;
	widget->gui = gui;
}

