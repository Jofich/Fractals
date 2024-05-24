#ifndef BURNINGSHIP_H
#define BURNINGSHIP_H

#include "Fractal.h"

class BurningShip: public Fractal
{
    Q_OBJECT
public:
    BurningShip(){maxIter = 256;}
    BurningShip(QSize res,std::vector<QColor> pal);
    void Image() override;
protected:
    QColor getColor(int maxIter,int iter);
    ldouble min_re = -2.5, max_re = 2.0;
    ldouble min_im = -2.5, max_im = 1;
};

#endif // BURNINGSHIP_H
