#include "widget.h"
#include "mandelbrot.h"
#include "ui_widget.h"
#include "burningship.h"


Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{

    readPalettes();
    ui->setupUi(this);
    fractalLabel = new QLabel(this);
    QCheckBox *ZoomBox = new QCheckBox("C&ase sensitive", this);
    fractal = new BurningShip(LabelResolution,palettes[curPalette]);
    bool success =  connect(fractal,SIGNAL(ImageRendered(QImage)),this,SLOT(updateLabel(QImage)));
    Q_ASSERT(success);

    fractalLabel->move(0,toolBarRes.height());

    ui->fractalLabel = fractalLabel;
    ui->zoomBox = ZoomBox;

    fractal->Image();

    fractalLabel->setMouseTracking(true);
    this->setMouseTracking(true);
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
    m_mousePos = QPoint(m_mousePos.x() / float(resolution.width()) * LabelResolution.width(),m_mousePos.y() / float(resolution.height()) * LabelResolution.height());
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
        palettes[t].reserve(lines);
        for(int i =0;i < lines;i++){
            in >> R >> G >> B;
            palettes[t].push_back(QColor(R,G,B));
        }
        in.close();
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    if(drawZoomBox){
        updateLabel(fractal->getImg());
        QPainter painter(&pixmap);
        painter.setPen(Qt::gray);
        QRect rectangle = QRect{QPoint(0, 0), QSize(LabelResolution.width() * scaleFactor, LabelResolution.height() * scaleFactor)};
        rectangle.moveCenter(m_mousePos);
        painter.drawRect(rectangle);
        fractalLabel->setPixmap(pixmap);
    }
}


void Widget::updateLabel(QImage image)
{
    pixmap = QPixmap::fromImage(image);
    fractalLabel->setPixmap(pixmap);

}

void Widget::on_zoomBox_clicked()
{
    qDebug("Clicked");
}


void Widget::on_zoomBox_clicked(bool checked)
{
    qDebug() << checked;
}

