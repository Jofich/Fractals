#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSize>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
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
    void mousePressEvent(QMouseEvent *event) override;
private:
    void updateLabel();

    QSize resolution = {960,540};
    Ui::Widget *ui;

    double scaleFactor = 0.2;
    double scale = 1;

    Mandelbrot fractal;
    QImage *image;


    QLabel *label;
};
#endif // WIDGET_H
