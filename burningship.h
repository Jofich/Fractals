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
    ldouble min_re = -2.5000000000, max_re = 1.000000000;
    ldouble min_im = -1.000000000, max_im = 1.000000000;
};

#endif // BURNINGSHIP_H
