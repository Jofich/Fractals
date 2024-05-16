#ifndef RENDERTREAD_H
#define RENDERTREAD_H

#include <QObject>
#include "Fractal.h"

class RenderTread : public QObject
{
    Q_OBJECT
public:
    explicit RenderTread(QObject *parent = nullptr);
signals:
    // void ImageRendered();
    // Fractal fractal;
};

#endif // RENDERTREAD_H
