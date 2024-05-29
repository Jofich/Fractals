#include "mandelbrot.h"
#include <QDebug>


Mandelbrot::Mandelbrot(QSize res,std::vector<QColor> pal):Mandelbrot()
{
    palette = pal;
    maxIter = 256;
    resolution = res;
    positions.reserve(20);
    positions.push_back(cor(res.width() / 2,res.height() / 2,res.width(),res.height()));
    image = QImage(res,QImage::Format_RGB32);

}
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

    int iter{};

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
            image.setPixel(XImage,YImage,coloring(iter,maxIter));
        }
    }
    emit ImageRendered(image);
}



