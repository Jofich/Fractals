#include "Fractal.h"
#include <QDebug>
#include <algorithm>


void Fractal::Zoom(QPoint MousePosition, ldouble scaleFactor)
{
    {
        ldouble posX = positions.back().centerX - positions.back().sizeX / 2.0 + MousePosition.x() / float(resolution.width()) * float(positions.back().sizeX);
        ldouble posY = positions.back().centerY - positions.back().sizeY / 2.0 + MousePosition.y() / float(resolution.height()) * float(positions.back().sizeY);
        ldouble sizeX = positions.back().sizeX * scaleFactor;
        ldouble sizeY = positions.back().sizeY * scaleFactor;
        positions.push_back(cor(posX,posY,sizeX,sizeY));
        Image();

    }
}

void Fractal::unZoom()
{
    if(positions.size() > 1)
    {
        positions.pop_back();
        Image();
    }
}

QImage Fractal::getImg()
{
    return image;
}

QColor Fractal::linearInterpolation(QColor &v, QColor &u, double a)
{
    auto b = 1 - a;

    return QColor(b*v.red() + a * u.red(), b*v.green() + a * u.green(), b*v.blue() + a * u.blue());
}

void Fractal::setResolution(QSize res)
{
    image = QImage(res,QImage::Format_RGBA64);
    resolution = res;
    positions.push_back(cor(res.width() / 2,res.height() / 2,res.width(),res.height()));
    qDebug() << "Fractal setResolution" << positions.size();
}

void Fractal::increaseMaxIter()
{
    maxIter = maxIter * 2;
    Image();
}

void Fractal::decreaseMaxIter()
{
    if(maxIter >= 64){
        maxIter /= 2;
        Image();
    }
}



void Fractal::setPalette(std::vector<QColor> pal)
{
    if(palette != pal){
        palette = pal;
        Image();
    }
}

QRgb Fractal::coloring(int iter, int maxIter)
{
    QColor c{};
    if(palette.size() != 0){
        int max_color = palette.size() - 1;
        if (iter == maxIter)iter = 0;
        double mu = 1.0*iter / maxIter;
        mu *= max_color;
        int i_mu = static_cast<size_t>(mu);
        QColor color1 = palette[i_mu];
        QColor color2 = palette[std::min(i_mu + 1, max_color)];
        c = linearInterpolation(color1, color2, mu - i_mu);
    }else{
        double color = 1.0 * (maxIter - iter) / maxIter *  0xff;
        c = QColor(color,color,color);
    }
    return c.rgb();

    // QColor mapping(Qt::white);
    // if (iter <= maxIter){
    //     double quotient = (double) iter / (double) maxIter;
    //     double color = std::clamp(0.0, 1.0, quotient);
    //     if (quotient > 0.5) {
    //         // Close to the mandelbrot set the color changes from green to white
    //         mapping.setRgbF(color, 1.f, color);
    //     }
    //     else {
    //         // Far away it changes from black to green
    //         mapping.setRgbF(0.f, color, 0.f);
    //     }
    // }
    // return mapping.rgb();
}

int Fractal::getMaxIter()
{
    return maxIter;
}
