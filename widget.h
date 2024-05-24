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
#include <map>
#include <QDir>
#include <fstream>
#include <QCheckBox>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAction>
#include <stack>

#include "burningship.h"
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
    void readPalettes();

public slots:
    void updateLabel(QImage image);
    void changePalette();
    void changeFractal();
protected:
    //GUI
    QVBoxLayout *boxLayout;
    QMenuBar* menuBar;
    QMenu *fractalMenu;
    QMenu *coloring;

    Ui::Widget *ui;


    QSize resolution = {800,600};
    QSize toolBarRes = {resolution.width(),resolution.height() / 20};
    QSize LabelResolution = resolution;

    //scale
    ldouble scaleFactor = 0.2;
    double scale = 1;

    Fractal* fractal;
    QLabel *fractalLabel;
    QPixmap pixmap{resolution};
    QPainter painter;

    QPoint m_mousePos;


    std::stack<double> scales;
    std::vector<QString> fractals{"Mandelbrot","Burning Ship"};
    QString title = "Fractals";
    std::vector<QString> namePalettes{"Dragon blaze","Sea foam","Thunderstorm","Venomous"};
    QString curPalette = "Sea foam",curFractal = fractals[0];
    std::map<QString,std::vector<QColor>> palettes;

    //flags
    bool drawZoomBox{true};

private slots:
    void on_zoomBox_toggled(bool checked);
};
#endif // WIDGET_H
