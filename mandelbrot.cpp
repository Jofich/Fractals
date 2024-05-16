#include "mandelbrot.h"
#include <QDebug>


Mandelbrot::Mandelbrot(QSize res):Mandelbrot()
{
    image = QImage(res,QImage::Format_RGB32);
    resolution = res;
    positions.reserve(10);
    positions.push_back(cor(res.width() / 2,res.height() / 2,res.width(),res.height()));
    makePalette();
    maxIter = 256;
}

// void Mandelbrot::setResolution(QSize res)
// {
//     image = new QImage(res,QImage::Format_RGB32);
//     resolution = res;
//     positions.push_back(cor(res.width() / 2,res.height() / 2,res.width(),res.height()));
// }

void Mandelbrot::Image()
{
    ldouble posX = positions.back().centerX, posY = positions.back().centerY;
    ldouble sizeX = positions.back().sizeX, sizeY = positions.back().sizeY;

    ldouble minX = posX - sizeX / 2,maxX = minX + sizeX;
    ldouble minY = posY - sizeY / 2,maxY = minY + sizeY;

    ldouble width = resolution.width();
    ldouble height = resolution.height();

    ldouble x0{},x{};
    ldouble y0{},y{};

    ldouble buf;

    int iter{};

    QColor color{};

    ldouble x2 = 0,y2 = 0;

    ldouble stepX = sizeX / width,stepY = sizeY / height;

    for (ldouble Px = minX, XImage = 0; Px < maxX && XImage < width; Px += stepX, XImage += 1) {
        x0 = min_re + (max_re - min_re) * Px / width;
        for (ldouble Py = minY, YImage = 0; Py < maxY && YImage < height; Py += stepY, YImage += 1) {
            y0 = min_im + (max_im - min_im) * Py / height;

            x = 0,y = 0;
            x2 = 0,y2 = 0;
            iter = 0;
            while(x2 + y2 <= 4 && iter < maxIter){
                y = 2 * x * y + y0;
                x = x2 - y2 + x0;
                x2 = x * x;
                y2 = y * y;
                iter++;
            }

            color = 255 - (255 * iter/maxIter);
            image.setPixel(XImage,YImage,coloring(iter,maxIter));
        }
    }
}



