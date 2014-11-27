#include <qgridview.h>
#include <qapplication.h>
#include <qpainter.h>

#include <stdio.h>

#include "tile.h"
#include "widget.h"


class Grid : public QGridView {
	void paintCell(QPainter *, int, int){}
};


static QApplication *app;
static Grid *frame;


void initApp(int &argc, char **argv)
{
	app = new QApplication(argc, argv);
}


void initFrame(int dw, int dh, int dispn)
{
	int w = dw/dispn, h = dh/dispn;
	frame = new Grid();

	frame->setCaption(QObject::tr("Mandelbrot Fractal"));
	frame->setFrameShape(QFrame::NoFrame);
	frame->setNumRows(dispn);
	frame->setNumCols(dispn);
	frame->setCellWidth(w);
	frame->setCellHeight(h);
	frame->setGeometry(0, 0, dw, dh);
	app->setMainWidget(frame);
	frame->show();
	app->processEvents(1);
}


int appExec()
{
	return app->exec();
}


Tile::Tile(int ax, int ay, int aw, int ah)
{
	Widget *rw = new Widget(aw, ah, app);

	x = ax; y = ay; w = aw; h = ah;
	widget = (void *) rw;

	frame->addChild(rw, ax, ay);
	rw->show();
	app->processEvents(1);
}


void Tile::newRow(int row, unsigned int *v)
{
	((Widget *)widget)->newRow(row, v);
}
