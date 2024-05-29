#ifndef COORDINATES_H
#define COORDINATES_H

typedef long double ldouble;


struct cor{
    ldouble centerX;
    ldouble centerY;
    ldouble sizeX;
    ldouble sizeY;
    cor(ldouble centerx,ldouble centery,ldouble sizex,ldouble sizey){
        centerX = centerx;
        centerY = centery;
        sizeY = sizey;
        sizeX = sizex;
    }
    cor(){}
};
#endif // COORDINATES_H
