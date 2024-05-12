#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{
    ui->setupUi(this);
    label = new QLabel(this);

    fractal.setResolution(resolution);
    fractal.Image();
    image = fractal.getImgPtr();
    updateLabel();

    this->setWindowTitle("Fractals");
    this->setFixedSize(resolution);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        qDebug() << event->pos().x()<< event->pos().y();

        fractal.Zoom(QSize(event->pos().x(), event->pos().y()),scaleFactor);
        updateLabel();
    }
}

void Widget::updateLabel()
{
    label->setPixmap(QPixmap::fromImage(*image));
}

