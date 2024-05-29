#ifndef TRICORN_H
#define TRICORN_H


#include "Fractal.h"
class Tricorn: public Fractal
{
public:
    Tricorn(){maxIter = 256;}
    Tricorn(QSize res,std::vector<QColor> pal);
    void Image() override;
protected:
    ldouble min_re = -2 , max_re = 1.5 ;
    ldouble min_im = -1.25, max_im = 1.25;
};

#endif // TRICORN_H
