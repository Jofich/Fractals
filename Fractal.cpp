#include "Fractal.h"
#include <QDebug>
#include <algorithm>

Fractal::Fractal()
{
    // makePalette(QColor(255,255,255),QColor(0,0,0));
}

void Fractal::Zoom(QSize MousePosition, ldouble scaleFactor)
{
    {
        ldouble posX = positions.back().centerX - positions.back().sizeX / 2.0 + MousePosition.width() / float(resolution.width()) * float(positions.back().sizeX);
        ldouble posY = positions.back().centerY - positions.back().sizeY / 2.0 + MousePosition.height() / float(resolution.height()) * float(positions.back().sizeY);
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
    if(maxIter > 64){
        maxIter /= 2;
        Image();
    }
}



void Fractal::makePalette()
{
    // palette = {QColor(0,0,0),
    //            QColor(213,67,31),
    //            QColor(251,255,121),
    //            QColor(62,223,89),
    //            QColor(43,30,218),
    //            QColor(0,255,247)};
    palette = {QColor(0,0,0),
               QColor(66 , 30 , 15),
               QColor(25 ,  7 , 26),
               QColor(9  , 1  ,47),
               QColor(4  , 4  ,73),
               QColor(0  , 7 ,100 ),
               QColor(12 , 44 ,138 ),
               QColor(24 , 82 ,177 ),
               QColor(57 ,125 ,209 ),
               QColor(134, 181, 229),
               QColor(211, 236, 248),
               QColor(241, 233, 191),
               QColor(248, 201,  95),
               QColor(255, 170,   0),
               QColor(204, 128,   0),
               QColor(153,  87,   0),
               QColor(106,  52,   3)};
    // palette = {QColor(0,7,100),
    //     QColor(32,107,203),
    //     QColor(237,255,255),
    //     QColor(255,170,0),
    //     QColor(0,2,0),
    //     QColor(0,0,0)
    // };
    // palette = {QColor(0,0,0),
    //          QColor(255,6,0),
    //          QColor(255,12,0),
    //          QColor(255,18,0),
    //          QColor(255,24,0),
    //          QColor(255,30,0),
    //          QColor(255,36,0),
    //          QColor(255,42,0),
    //          QColor(255,48,0),
    //          QColor(255,54,0),
    //          QColor(255,60,0),
    //          QColor(255,66,0),
    //          QColor(255,72,0),
    //          QColor(255,78,0),
    //          QColor(255,84,0),
    //          QColor(255,90,0),
    //          QColor(255,96,0),
    //          QColor(255,102,0),
    //          QColor(255,108,0),
    //          QColor(255,114,0),
    //          QColor(255,120,0),
    //          QColor(255,126,0),
    //          QColor(255,132,0),
    //          QColor(255,138,0),
    //          QColor(255,144,0),
    //          QColor(255,150,0),
    //          QColor(255,156,0),
    //          QColor(255,162,0),
    //          QColor(255,168,0),
    //          QColor(255,174,0),
    //          QColor(255,180,0),
    //          QColor(255,186,0),
    //          QColor(255,192,0),
    //          QColor(255,198,0),
    //          QColor(255,204,0),
    //          QColor(255,210,0),
    //          QColor(255,216,0),
    //          QColor(255,222,0),
    //          QColor(255,228,0),
    //          QColor(255,234,0),
    //          QColor(255,240,0),
    //          QColor(255,246,0),
    //          QColor(255,252,0),
    //          QColor(252,255,0),
    //          QColor(246,255,0),
    //          QColor(239,255,0),
    //          QColor(233,255,0),
    //          QColor(227,255,0),
    //          QColor(221,255,0),
    //          QColor(215,255,0),
    //          QColor(209,255,0),
    //          QColor(203,255,0),
    //          QColor(197,255,0),
    //          QColor(191,255,0),
    //          QColor(185,255,0),
    //          QColor(179,255,0),
    //          QColor(173,255,0),
    //          QColor(167,255,0),
    //          QColor(161,255,0),
    //          QColor(155,255,0),
    //          QColor(149,255,0),
    //          QColor(143,255,0),
    //          QColor(137,255,0),
    //          QColor(131,255,0),
    //          QColor(125,255,0),
    //          QColor(119,255,0),
    //          QColor(113,255,0),
    //          QColor(107,255,0),
    //          QColor(101,255,0),
    //          QColor(95,255,0),
    //          QColor(89,255,0),
    //          QColor(83,255,0),
    //          QColor(77,255,0),
    //          QColor(71,255,0),
    //          QColor(65,255,0),
    //          QColor(59,255,0),
    //          QColor(53,255,0),
    //          QColor(47,255,0),
    //          QColor(41,255,0),
    //          QColor(35,255,0),
    //          QColor(29,255,0),
    //          QColor(23,255,0),
    //          QColor(17,255,0),
    //          QColor(11,255,0),
    //          QColor(5,255,0),
    //          QColor(0,255,0),
    //          QColor(0,255,6),
    //          QColor(0,255,12),
    //          QColor(0,255,18),
    //          QColor(0,255,24),
    //          QColor(0,255,30),
    //          QColor(0,255,36),
    //          QColor(0,255,42),
    //          QColor(0,255,48),
    //          QColor(0,255,54),
    //          QColor(0,255,60),
    //          QColor(0,255,66),
    //          QColor(0,255,72),
    //          QColor(0,255,78),
    //          QColor(0,255,84),
    //          QColor(0,255,90),
    //          QColor(0,255,96),
    //          QColor(0,255,102),
    //          QColor(0,255,108),
    //          QColor(0,255,114),
    //          QColor(0,255,120),
    //          QColor(0,255,126),
    //          QColor(0,255,132),
    //          QColor(0,255,138),
    //          QColor(0,255,144),
    //          QColor(0,255,150),
    //          QColor(0,255,156),
    //          QColor(0,255,162),
    //          QColor(0,255,168),
    //          QColor(0,255,174),
    //          QColor(0,255,180),
    //          QColor(0,255,186),
    //          QColor(0,255,192),
    //          QColor(0,255,198),
    //          QColor(0,255,204),
    //          QColor(0,255,210),
    //          QColor(0,255,216),
    //          QColor(0,255,222),
    //          QColor(0,255,228),
    //          QColor(0,255,234),
    //          QColor(0,255,240),
    //          QColor(0,255,246),
    //          QColor(0,255,252),
    //          QColor(0,251,255),
    //          QColor(0,245,255),
    //          QColor(0,239,255),
    //          QColor(0,233,255),
    //          QColor(0,227,255),
    //          QColor(0,221,255),
    //          QColor(0,215,255),
    //          QColor(0,209,255),
    //          QColor(0,203,255),
    //          QColor(0,197,255),
    //          QColor(0,191,255),
    //          QColor(0,185,255),
    //          QColor(0,179,255),
    //          QColor(0,173,255),
    //          QColor(0,167,255),
    //          QColor(0,161,255),
    //          QColor(0,155,255),
    //          QColor(0,149,255),
    //          QColor(0,143,255),
    //          QColor(0,137,255),
    //          QColor(0,131,255),
    //          QColor(0,125,255),
    //          QColor(0,119,255),
    //          QColor(0,113,255),
    //          QColor(0,107,255),
    //          QColor(0,101,255),
    //          QColor(0,95,255),
    //          QColor(0,89,255),
    //          QColor(0,83,255),
    //          QColor(0,77,255),
    //          QColor(0,71,255),
    //          QColor(0,65,255),
    //          QColor(0,59,255),
    //          QColor(0,53,255),
    //          QColor(0,47,255),
    //          QColor(0,41,255),
    //          QColor(0,35,255),
    //          QColor(0,29,255),
    //          QColor(0,23,255),
    //          QColor(0,17,255),
    //          QColor(0,11,255),
    //          QColor(0,5,255),
    //          QColor(0,0,255),
    //          QColor(6,0,255),
    //          QColor(12,0,255),
    //          QColor(18,0,255),
    //          QColor(24,0,255),
    //          QColor(30,0,255),
    //          QColor(36,0,255),
    //          QColor(42,0,255),
    //          QColor(48,0,255),
    //          QColor(54,0,255),
    //          QColor(60,0,255),
    //          QColor(66,0,255),
    //          QColor(72,0,255),
    //          QColor(78,0,255),
    //          QColor(84,0,255),
    //          QColor(90,0,255),
    //          QColor(96,0,255),
    //          QColor(102,0,255),
    //          QColor(108,0,255),
    //          QColor(114,0,255),
    //          QColor(120,0,255),
    //          QColor(126,0,255),
    //          QColor(132,0,255),
    //          QColor(138,0,255),
    //          QColor(144,0,255),
    //          QColor(150,0,255),
    //          QColor(156,0,255),
    //          QColor(162,0,255),
    //          QColor(168,0,255),
    //          QColor(174,0,255),
    //          QColor(180,0,255),
    //          QColor(186,0,255),
    //          QColor(192,0,255),
    //          QColor(198,0,255),
    //          QColor(204,0,255),
    //          QColor(210,0,255),
    //          QColor(216,0,255),
    //          QColor(222,0,255),
    //          QColor(228,0,255),
    //          QColor(234,0,255),
    //          QColor(240,0,255),
    //          QColor(246,0,255),
    //          QColor(252,0,255),
    //          QColor(255,0,251),
    //          QColor(255,0,245),
    //          QColor(255,0,239),
    //          QColor(255,0,233),
    //          QColor(255,0,227),
    //          QColor(255,0,221),
    //          QColor(255,0,215),
    //          QColor(255,0,209),
    //          QColor(255,0,203),
    //          QColor(255,0,197),
    //          QColor(255,0,191),
    //          QColor(255,0,185),
    //          QColor(255,0,179),
    //          QColor(255,0,173),
    //          QColor(255,0,167),
    //          QColor(255,0,161),
    //          QColor(255,0,155),
    //          QColor(255,0,149),
    //          QColor(255,0,143),
    //          QColor(255,0,137),
    //          QColor(255,0,131),
    //          QColor(255,0,125),
    //          QColor(255,0,119),
    //          QColor(255,0,113),
    //          QColor(255,0,107),
    //          QColor(255,0,101),
    //          QColor(255,0,95),
    //          QColor(255,0,89),
    //          QColor(255,0,83),
    //          QColor(255,0,77),
    //          QColor(255,0,71),
    //          QColor(255,0,65),
    //          QColor(255,0,59),
    //          QColor(255,0,53),
    //          QColor(255,0,47),
    //          QColor(255,0,41),
    //          QColor(255,0,35),
    //          QColor(255,0,29),
    //          QColor(255,0,23),
    //          QColor(255,0,17),
    //          QColor(255,0,11),
    //          QColor(255,0,5),
    //          QColor(255,0,5)
    //         };

}

QRgb Fractal::coloring(int iter, int maxIter)
{
    int max_color = palette.size() - 1;
    if (iter == maxIter)iter = 0;
    double mu = 1.0*iter / maxIter;
    mu *= max_color;
    int i_mu = static_cast<size_t>(mu);
    QColor color1 = palette[i_mu];
    QColor color2 = palette[std::min(i_mu + 1, max_color)];
    QColor c = linearInterpolation(color1, color2, mu - i_mu);
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
