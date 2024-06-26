#ifndef ABSTRACTFRACTAL_H
#define ABSTRACTFRACTAL_H


#include <QObject>
#include <QImage>
#include <qRgb>
#include <QPixmap>
#include <QSize>
#include <vector>
#include "coordinates.h"

class AbstractFractal:public QObject
{
    Q_OBJECT
public:
    virtual void Image() = 0;
    virtual void Zoom(QPoint MousePosition,ldouble scaleFactor) = 0;
    virtual void unZoom() = 0;
    virtual void setResolution(QSize res) = 0;
    virtual void increaseMaxIter() = 0;
    virtual void decreaseMaxIter() = 0;
    virtual void setPalette(std::vector<QColor> pal) = 0;
    virtual void Reset() = 0;
    virtual int getMaxIter() = 0;
    virtual QRgb coloring(int iter,int maxIter) = 0;
    virtual QImage getImg() = 0;
    virtual QColor linearInterpolation(QColor &v, QColor &u, double a) = 0;


public:
signals:
    void ImageRendered(QImage image);
protected:

    int maxIter;

    QImage image;
    QSize resolution;

    std::vector<cor> positions;
    std::vector<QColor> palette;
};

#endif // ABSTRACTFRACTAL_H
