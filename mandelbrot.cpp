#include "mandelbrot.h"
#include <QDebug>

Mandelbrot::Mandelbrot(QSize res) {
    image = new QImage(res,QImage::Format_RGB32);
    resolution = res;
    positions.reserve(10);
    positions[0] = cor(res.width() / 2,res.height() / 2,res.width(),res.height());
}

void Mandelbrot::Image()
{
    double posX = positions.back().centerX, posY = positions.back().centerY;
    double sizeX = positions.back().sizeX, sizeY = positions.back().sizeY;

    double minX = posX - sizeX / 2,maxX = posX + sizeX / 2;
    double minY = posY - sizeY / 2,maxY = posY + sizeY / 2;

    int width = resolution.width();
    int height = resolution.height();

    double cr{},ci{};
    double re{},im{};

    double buf;

    int iter{};

    int color{};

    double stepX = sizeX / width,stepY = sizeY / height;

    for (double x = minX, XImage = 0; x < maxX && XImage < width; x += stepX, XImage += 1) {
        for (double y = minY, YImage = 0; y < maxY && YImage < height; y += stepY, YImage += 1) {
            cr = min_re + (max_re - min_re) * x / width;
            ci = min_im + (max_im - min_im) * y / height;

            re = 0,im = 0;
            for(iter = 0;iter < maxIter;iter++){
                buf = re * re - im * im + cr;
                im = 2 * re * im + ci;
                re = buf;
                if(re * re + im * im > 2 * 2) break;
            }
            color = float(maxIter - iter) / maxIter * 0xff;
            image->setPixel(XImage,YImage,qRgb(color,color,color));
        }
    }
}

void Mandelbrot::Zoom(QSize MousePosition, double scaleFactor)
{
    double posX = positions.back().centerX - positions.back().sizeX / 2.0 + MousePosition.width() / float(resolution.width()) * float(positions.back().sizeX);
    double posY = positions.back().centerY - positions.back().sizeY / 2.0 + MousePosition.height() / float(resolution.height()) * float(positions.back().sizeY);
    double sizeX = positions.back().sizeX * scaleFactor;
    double sizeY = positions.back().sizeY * scaleFactor;
    positions.push_back(cor(posX,posY,sizeX,sizeY));
    this->Image();
}

QImage *Mandelbrot::getImgPtr()
{
    return image;
}

void Mandelbrot::setResolution(QSize res)
{
    image = new QImage(res,QImage::Format_RGB32);
    resolution = res;
    positions.push_back(cor(res.width() / 2,res.height() / 2,res.width(),res.height()));
}

