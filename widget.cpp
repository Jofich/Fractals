#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{
    readPalettes();
    qRegisterMetaType<Mandelbrot>("Mandelbrot");
    ui->setupUi(this);
    label = new QLabel(this);
    fractal = new Mandelbrot(resolution,palettes[curPalette]);


    bool success =  connect(fractal,SIGNAL(ImageRendered(QImage)),this,SLOT(updateLabel(QImage)));
    Q_ASSERT(success);

    label->setMouseTracking(true);
    this->setMouseTracking(true);
    fractal->Image();
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
        fractal->Zoom(QSize(event->pos().x(), event->pos().y()),scaleFactor);
        scale /= scaleFactor;
        qDebug() << scale;
    }
    if(event->button() == Qt::RightButton){
        fractal->unZoom();
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

            fractal->increaseMaxIter();

        }if(event->angleDelta().y() < 0){

            fractal->decreaseMaxIter();
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

void Widget::readPalettes()
{
    int R{},G{},B{};
    int lines{};
    QDir::setCurrent("..//..//palettes//");
    QStringList line{};
    QString fileName{};
    for(QString t:namePalettes){
        fileName = t + ".txt";
        std::ifstream in(fileName.toStdString());
        in >> lines;
        qDebug() << lines;
        palettes[t].reserve(lines);
        for(int i =0;i < lines;i++){
            in >> R >> G >> B;
            qDebug() << R << G << B;
            palettes[t].push_back(QColor(R,G,B));
        }
        in.close();
        // palettes[t].reserve(lines);
        // while(in >> R >> G >>B){
        //     palettes[t].push_back(QColor(R,G,B));
        // }
        // in.close();
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    if(drawZoomBox){
        updateLabel(fractal->getImg());
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

