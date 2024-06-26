#ifndef FRACTAL_H
#define FRACTAL_H

#include "AbstractFractal.h"


class Fractal: public AbstractFractal{
    Q_OBJECT
public:
    Fractal(){}
    void Zoom(QPoint MousePosition,ldouble scaleFactor) override;
    void unZoom() override;
    void setResolution(QSize res) override;
    void increaseMaxIter() override;
    void decreaseMaxIter() override;
    void setPalette(std::vector<QColor> pal) override;
    void Reset() override;
    int getMaxIter() override;
    QRgb coloring(int iter,int maxIter) override;
    QImage getImg() override;
    QColor linearInterpolation(QColor &v, QColor &u, double a) override;
};
#endif //FRACTAL_H
