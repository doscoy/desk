
#include <fstream>
#include <cstdio>
#include "img_bitmap.hpp"
#include <algorithm>

//  ‚Æ‚è‚ ‚¦‚¸ƒvƒŒƒ[ƒ“ƒnƒ€
void
bresenhamLine(
    Image* image,
    int x0,
    int y0,
    int x1,
    int y1
){
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int deltax = x1 - x0;
    int deltay = std::abs(y1 - y0);
    int error = deltax / 2;
    int ystep;
    int y = y0;
    if (y0 < y1) {
        ystep = 1;
    }
    else {
        ystep = -1;
    }

    for (int x = x0; x < x1; ++x){
        if (steep) {
            image->setPixelColor(y,x, 255, 0, 0);
        }
        else {
            image->setPixelColor(x,y, 255, 0, 0);
        }
        error = error - deltay;
        if (error < 0) {
            y = y + ystep;
            error = error + deltax;
        }

    }

}



void
test1()
{
    std::ifstream ifs("d:\\sandbox\\ajisai.bmp", std::ios::in | std::ios::binary);

    Image* pic = loadBmp(&ifs);

    pic->setPixelColor(0, 0, 255, 0, 0);
    pic->setPixelColor(1, 0, 255, 0, 0);
    pic->setPixelColor(2, 0, 255, 0, 0);

    pic->setPixelColor(4, 0, 255, 0, 0);
    pic->setPixelColor(5, 0, 255, 0, 0);
    pic->setPixelColor(6, 0, 255, 0, 0);

    pic->setPixelColor(10, 0, 0, 0, 255);
    pic->setPixelColor(10, 1, 0, 0, 255);
    pic->setPixelColor(10, 2, 0, 0, 255);

    pic->setPixelColor(29, 29, 255, 222, 222);

    std::ofstream ofs("d:\\sandbox\\p30x30_.bmp", std::ios::out | std::ios::binary);
    saveBmp(&ofs, pic);


    pic->dump();
    pic->destroy();

}


void
test2()
{
    Image* image = Image::createImage(100, 100);
    std::ofstream ofs("d:\\sandbox\\test2.bmp", std::ios::out | std::ios::binary);

    image->fill(0, 0 , 0);

    bresenhamLine(image, 10, 5, 30, 130);

    saveBmp(&ofs, image);



    image->dump();
    image->destroy();

}


int main()
{   
    test2(); 
    getchar();
    return 0;
}