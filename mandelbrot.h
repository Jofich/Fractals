#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Fractal.h"

class Mandelbrot: public Fractal
{
    Q_OBJECT
public:
    Mandelbrot(){maxIter = 256;};
    Mandelbrot(QSize res);
    void Image() override;   
signals:
    void ImageRendered(QImage image);
protected:
    ldouble min_re = -2.5000000000, max_re = 1.000000000;
    ldouble min_im = -1.000000000, max_im = 1.000000000;
};

#endif // MANDELBROT_H
