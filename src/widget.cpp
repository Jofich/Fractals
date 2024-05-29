#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent): QWidget(parent) , ui(new Ui::Widget)
{

    readPalettes();
    ui->setupUi(this);

    scales.push(1);
    fractal = new Mandelbrot(LabelResolution,palettes[curPalette]);
    bool success =  connect(fractal,SIGNAL(ImageRendered(QImage)),this,SLOT(updateLabel(QImage)));
    Q_ASSERT(success);

    boxLayout = new QVBoxLayout(this);
    boxLayout->setContentsMargins(0,0,0,0);

    menuBar = new QMenuBar();


    currentScale = new QLabel("Scale: ",this,Qt::WindowStaysOnTopHint);
    maxIter = new QLabel("MaxIter: ",this,Qt::WindowStaysOnTopHint);

    fractalMenu = new QMenu("Fractals");
    coloring = new QMenu("Color");
    settings = new QMenu("Settings");

    zoomBox = new QAction("ZoomBox", this);
    zoomBox->setCheckable(true);
    zoomBox->setChecked(true);
    connect(zoomBox, SIGNAL(triggered()), this, SLOT(changeDrawZoomBox()));

    menuBar->addMenu(fractalMenu);
    menuBar->addMenu(coloring);
    menuBar->addMenu(settings);

    settings->addAction(zoomBox);

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

    // currentScale = new QLabel("Zoom: " + QString::number(scales.top()),this);
    // maxIter = new QLabel(this);

    // currentScale->setStyleSheet("QLabel {border: 0px; background-color:rgba(0,0,0,0%);}");
    // currentScale->setFrameStyle(QFrame::NoFrame);
    // currentScale->setAutoFillBackground(false);
    // maxIter->setText("Max iter.: " + fractal->getMaxIter());

    this->layout()->setMenuBar(menuBar);

    fractalLabel = new QLabel();
    boxLayout->addWidget(fractalLabel);



    fractal->Image();

    fractalLabel->setMouseTracking(true);
    this->setMouseTracking(true);
    currentScale->setMouseTracking(true);
    this->setWindowTitle(title);
    this->setFixedSize(resolution);

    currentScale->raise();
    maxIter->raise();

    currentScale->move(0,menuBar->sizeHint().height());
    maxIter->move(0,currentScale->geometry().height() + currentScale->geometry().y());

    currentScale->setText("Scale: " + QString::number(scales.top()));
    maxIter->setText("MaxIter: " + QString::number(fractal->getMaxIter()));

    currentScale->setStyleSheet("QLabel {color: #FF5050;}");
    maxIter->setStyleSheet("QLabel {color: #FF5050;}");


    currentScale->show();
    maxIter->show();
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
    currentScale->setText("Scale: " + QString::number(scales.top()));
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
        maxIter->setText("MaxIter: " + QString::number(fractal->getMaxIter()));

    }if(event->angleDelta().y() < 0){

        fractal->decreaseMaxIter();
        maxIter->setText("MaxIter: " + QString::number(fractal->getMaxIter()));
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
    if(scaleFactor <= 0.85){
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
        if(!in.is_open()){
            qFatal("Could not open folder with palettes");
        }
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
    curPalette = QObject::sender()->objectName();
    fractal->setPalette(palettes[curPalette]);
    updateLabel(fractal->getImg());
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
        }else if(FractalName == fractals[2]){
            fractal = new Tricorn(LabelResolution,palettes[curPalette]);
            fractal->Image();
            curFractal = FractalName;
        }
    }
    updateLabel(fractal->getImg());
    maxIter->setText("MaxIter: " + QString::number(fractal->getMaxIter()));
}

void Widget::changeDrawZoomBox()
{
    drawZoomBox = not drawZoomBox;
    updateLabel(fractal->getImg());
}


void Widget::on_zoomBox_toggled(bool checked)
{
    drawZoomBox =  checked;
    updateLabel(fractal->getImg());
}



