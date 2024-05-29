#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "Fractal.h"

class Mandelbrot: public Fractal
{
    Q_OBJECT
public:
    Mandelbrot(){maxIter = 256;};
    Mandelbrot(QSize res,std::vector<QColor> pal);
    void Image() override;
protected:
    ldouble min_re = -2.5, max_re = 1.0;
    ldouble min_im = -1.0, max_im = 1.0;
};

#endif // MANDELBROT_H
