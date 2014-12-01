#include <QImage>
#include <QWidget>
#include <QtWidgets/QApplication>
#include <QEvent>
#include <QGridLayout>
#include <QThread>
#include <QPainter>
#include <QPaintEvent>


#include "tile.h"
#include "widget.h"



Widget::Widget(int w, int h, QApplication *a)
    // : QWidget(0, 0, Qt::WA_StaticContents) {
    : QWidget(),
    image(w, h, QImage::Format_RGB32)
    {
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(w, h);
    image.fill(qRgba(0, 0, 0, 0));
    app = a;
}


void Widget::newRow(int row, unsigned int v[]) {
    int i;

    for(i=0; i<width(); i++) {
        image.setPixel(i, row, v[i]);
    }
    app->postEvent(this, new QPaintEvent(QRect(0, row, width(),1)));
}


void Widget::paintEvent(QPaintEvent *ev) {
    QPainter painter(this);
    painter.drawImage(ev->rect().topLeft(), image, ev->rect());
}
