#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSize>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QString>
#include "mandelbrot.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void increaseScaleFactor();
    void decreaseScaleFactor();
public slots:
    void updateLabel(QImage image);
protected:
    QSize resolution = {600,400};
    Ui::Widget *ui;

    ldouble scaleFactor = 0.2;
    ldouble scale = 1;

    Mandelbrot fractal{resolution};
    QLabel *label;
    QPixmap pixmap{resolution};
    QPainter painter;

    QPoint m_mousePos;

    QString title = "Fractals";

    bool drawZoomBox{true};

};
#endif // WIDGET_H
