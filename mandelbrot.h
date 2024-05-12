#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Fractal.h"

class Mandelbrot: public Fractal
{
public:
    Mandelbrot(){};
    Mandelbrot(QSize res);

    void Image();
    void Zoom(QSize MousePosition,double scaleFactor);

    QImage *getImgPtr();
    void setResolution(QSize res);
private:
    QImage* image;
    QSize resolution;
    double min_re = -2.5, max_re = 1;
    double min_im = -1, max_im = 1;
    const int maxIter = 250;
    std::vector<cor> positions;
};

#endif // MANDELBROT_H
