#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{

    readPalettes();
    ui->setupUi(this);

    scales.push(scale);
    fractal = new Mandelbrot(LabelResolution,palettes[curPalette]);
    bool success =  connect(fractal,SIGNAL(ImageRendered(QImage)),this,SLOT(updateLabel(QImage)));
    Q_ASSERT(success);

    boxLayout = new QVBoxLayout(this);
    boxLayout->setContentsMargins(0,0,0,0);

    menuBar = new QMenuBar();
    fractalMenu = new QMenu("Fractals");
    coloring = new QMenu("Color");

    menuBar->addMenu(fractalMenu);
    menuBar->addMenu(coloring);
    QAction *action1;
    for(QString fractalName : fractals){


        action1 = new QAction(fractalName);
        action1->setObjectName(fractalName);
        fractalMenu->addAction(action1);
        connect(fractalMenu->actions().back(), SIGNAL(triggered()), this,SLOT(changeFractal()));

    }
    for(QString color: namePalettes){

        action1 = new QAction(color);
        action1->setObjectName(color);
        coloring->addAction(action1);
        connect(coloring->actions().back(), SIGNAL(triggered()), this,SLOT(changePalette()));
    }

    this->layout()->setMenuBar(menuBar);

    fractalLabel = new QLabel(this);
    boxLayout->addWidget(fractalLabel);


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

        fractal->Zoom(m_mousePos,scaleFactor);
        scales.push(scales.top() / scaleFactor);
    }
    if(event->button() == Qt::RightButton){
        if(scales.size() > 1){
            fractal->unZoom();
            scales.pop();
        }
    }
    qDebug() << scales.top();
}

void Widget::wheelEvent(QWheelEvent *event)
{   if(drawZoomBox){
        if(QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier)) {
            if(event->angleDelta().y() > 0){

                increaseScaleFactor();

            }if(event->angleDelta().y() < 0){

                decreaseScaleFactor();

            }
            return;
        }
    }
    if(event->angleDelta().y() > 0){

        fractal->increaseMaxIter();

    }if(event->angleDelta().y() < 0){

        fractal->decreaseMaxIter();
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
    palettes["White"] = {};
    namePalettes.insert(namePalettes.begin(),"White");
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

void Widget::changePalette()
{

    fractal->setPalette(palettes[QObject::sender()->objectName()]);

}

void Widget::changeFractal()
{
    QString FractalName = QObject::sender()->objectName();
    if(FractalName != curFractal){ // Mandelbrot
        if(FractalName == fractals[0]){
            fractal = new Mandelbrot(LabelResolution,palettes[curPalette]);
            fractal->Image();
            curFractal = FractalName;

        }
        else if(FractalName == fractals[1]){ // Burning ship
            fractal = new BurningShip(LabelResolution,palettes[curPalette]);
            fractal->Image();
            curFractal = FractalName;
        }
    }
}


void Widget::on_zoomBox_toggled(bool checked)
{
    drawZoomBox =  checked;
    updateLabel(fractal->getImg());
}



