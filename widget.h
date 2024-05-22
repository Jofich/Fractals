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
#include "mandelbrot.h"
#include "qcheckbox.h"




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
protected:
    QSize resolution = {800,600};
    QSize toolBarRes = {resolution.width(),resolution.height() / 20};
    QSize LabelResolution = {resolution.width(),resolution.height()-toolBarRes.height()};
    Ui::Widget *ui;

    QCheckBox *ZoomBox;

    ldouble scaleFactor = 0.2;
    double scale = 1;

    Fractal* fractal;
    QLabel *fractalLabel;
    QPixmap pixmap{resolution};
    QPainter painter;

    QPoint m_mousePos;

    QString title = "Fractals";
    std::vector<QString> namePalettes{"dragon_blaze","sea_foam","thunderstorm","venomous"};
    QString curPalette = namePalettes[0];
    std::map<QString,std::vector<QColor>> palettes;
    bool drawZoomBox{true};

private slots:
    void on_zoomBox_stateChanged(int arg1);
    void on_ZoomBox_toggled(bool checked);
    void on_zoomBox_toggled(bool checked);
    void on_zoomBox_clicked();
    void on_zoomBox_clicked(bool checked);
};
#endif // WIDGET_H
