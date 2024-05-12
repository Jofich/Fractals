#include <QImage>
#include <QPixmap>
#include <QSize>
#include <vector>

struct cor{
    double centerX;
    double centerY;
    double sizeX;
    double sizeY;
    cor(double centerx,double centery,double sizex,double sizey){
        centerX = centerx;
        centerY = centery;
        sizeY = sizey;
        sizeX = sizex;
    }
};

class Fractal{
public:
    void Image(double posX,double posY,double sizeX,double sizeY);
    void Zoom(QSize MousePosition,double scaleFactor);
    QImage* getImgPtr();
private:
    QImage *image;
    QSize resolution;
    QRgb coloring(int maxIter,int iter);
    int maxIter;
    double min_re, max_re;
    double min_im, max_im;
    std::vector<cor> positions;
};
