#ifndef WIDGET_H
#define WIDGET_H

#include <qimage.h>
#include <qwidget.h>
#include <qapplication.h>
#include <qevent.h>

class Widget : public QWidget
{
	Q_OBJECT

public:
	Widget(){}
	Widget(int w, int h, QApplication *a);
	void show(){QWidget::show();}
	void newRow(int row, unsigned int *v);

protected:
	void paintEvent(QPaintEvent *event);

private:
	QImage image;
	QApplication *app;
};

#endif
