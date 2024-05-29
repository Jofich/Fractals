#include "burningship.h"

BurningShip::BurningShip(QSize res,std::vector<QColor> pal) {
    palette = pal;
    maxIter = 256;
    resolution = res;
    positions.reserve(20);
    positions.push_back(cor(res.width() / 2,res.height() / 2,res.width(),res.height()));
    image = QImage(res,QImage::Format_RGB32);
}


void BurningShip::Image(){

    ldouble posX = positions.back().centerX, posY = positions.back().centerY;
    ldouble sizeX = positions.back().sizeX, sizeY = positions.back().sizeY;

    ldouble minX = posX - sizeX / 2.0,maxX = minX + sizeX;
    ldouble minY = posY - sizeY / 2.0,maxY = minY + sizeY;

    ldouble width = resolution.width();
    ldouble height = resolution.height();

    ldouble stepX = sizeX / width,stepY = sizeY / height;

    ldouble x{},y{},zx{},zy{};
    ldouble xtemp{};
    int iter{};
    for (ldouble Px = minX, XImage = 0; Px < maxX && XImage < width; Px += stepX, XImage += 1) {
        x = min_re + (max_re - min_re) * Px / width;
        for (ldouble Py = minY, YImage = 0; Py < maxY && YImage < height; Py += stepY, YImage += 1) {
            y = min_im + (max_im - min_im) * Py / height;

            zx = x,zy = y;
            iter = 0;
            while(zx * zx + zy * zy < 4 && iter < maxIter){
                xtemp = zx * zx - zy * zy + x;
                zy = abs(2 * zx * zy) + y;
                zx = xtemp;
                iter++;
            }
            image.setPixel(XImage,YImage,coloring(iter,maxIter));
        }
    }
    emit ImageRendered(image);
}


