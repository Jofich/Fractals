#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{

    ui->setupUi(this);
    label = new QLabel(this);
    // QObject::connect(&fractal,SIGNAL(AbstractFractal::ImageRendered()),this,SLOT(Widget::updateLabel()));
    label->setMouseTracking(true);
    this->setMouseTracking(true);
    fractal.Image();
    updateLabel(fractal.getImg());
    this->setWindowTitle(title);
    this->setFixedSize(resolution);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        fractal.Zoom(QSize(event->pos().x(), event->pos().y()),scaleFactor);
        updateLabel(fractal.getImg());
    }
    if(event->button() == Qt::RightButton){
        fractal.unZoom();
        updateLabel(fractal.getImg());
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if(QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
        if(event->angleDelta().y() > 0){

            increaseScaleFactor();

        }if(event->angleDelta().y() < 0){

            decreaseScaleFactor();

        }
    }
    else{
        if(event->angleDelta().y() > 0){

            fractal.increaseMaxIter();
            updateLabel(fractal.getImg());

        }if(event->angleDelta().y() < 0){

            fractal.decreaseMaxIter();
            updateLabel(fractal.getImg());
        }
    }

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
    update();
}

void Widget::increaseScaleFactor()
{
    if(scaleFactor < 0.9){
        scaleFactor += 0.05;
    }
}

void Widget::decreaseScaleFactor()
{
    if(scaleFactor > 0.1){
        scaleFactor -= 0.05;
    }
}


void Widget::paintEvent(QPaintEvent *)
{
    if(drawZoomBox){
        updateLabel(fractal.getImg());
        QPainter painter(&pixmap);
        painter.setPen(Qt::gray);
        QRect rectangle = QRect{QPoint(0, 0), QSize(resolution.width() * scaleFactor, resolution.height() * scaleFactor)};
        rectangle.moveCenter(m_mousePos);
        painter.drawRect(rectangle);
        label->setPixmap(pixmap);
    }
}


void Widget::updateLabel(QImage image)
{
    pixmap = QPixmap::fromImage(image);
    label->setPixmap(pixmap);

}

