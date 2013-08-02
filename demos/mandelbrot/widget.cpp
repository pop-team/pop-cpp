#include <qimage.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qevent.h>
#include <qgridview.h>
#include <qthread.h>
#include <qpainter.h>


#include "tile.h"
#include "widget.h"



Widget::Widget(int w, int h, QApplication *a)
    : QWidget(0, 0, WStaticContents)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setFixedSize(w, h);
	image.create(w, h, 32);
	image.fill(qRgba(0, 0, 0, 0));
	app = a;
}


void Widget::newRow(int row, unsigned int v[])
{
	int i;

	for (i=0; i<width(); i++)
		image.setPixel(i, row, v[i]);
	app->postEvent(this, new QPaintEvent(QRect(0, row, width(),1)));
}


void Widget::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);
	painter.drawImage(ev->rect().topLeft(), image, ev->rect());
}
