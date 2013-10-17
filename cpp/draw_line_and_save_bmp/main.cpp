
#include <fstream>
#include <cstdio>
#include <algorithm>

#include "img_bitmap.hpp"
#include "line_draw.hpp"


void
test1()
{
    std::ifstream ifs("d:\\sandbox\\ajisai.bmp", std::ios::in | std::ios::binary);

    Image* pic = deserializeBmp(&ifs);
    if (pic == nullptr) {
        return;
    }
    
    pic->plot(0, 0, Color::red());
    pic->plot(1, 0, Color::red());
    pic->plot(2, 0, Color::red());

    pic->plot(4, 0, Color::blue());
    pic->plot(5, 0, Color::blue());
    pic->plot(6, 0, Color::blue());

    pic->plot(10, 0, Color::white());
    pic->plot(10, 1, Color::white());
    pic->plot(10, 2, 0, 0, 255);

    pic->plot(29, 29, 255, 222, 222);

    std::ofstream ofs("d:\\sandbox\\test1.bmp", std::ios::out | std::ios::binary);
    serializeBmp(&ofs, pic);


    pic->dump();
    pic->destroy();

}


void
test2()
{
    Image* image = Image::createImage(100, 100);
    std::ofstream ofs("d:\\sandbox\\test2.bmp", std::ios::out | std::ios::binary);

    Image* image_aa = Image::createImage(100, 100);
    std::ofstream ofsaa("d:\\sandbox\\test2aa.bmp", std::ios::out | std::ios::binary);
    
    Image* image_bl = Image::createImage(100, 100);
    std::ofstream ofsbl("d:\\sandbox\\test2bl.bmp", std::ios::out | std::ios::binary);
    


    image->fill(Color::black());
    image_aa->fill(Color::black());
    image_bl->fill(Color::black());

    int point[5][4] = {
        {10, 10, 40, 40},
        {15, 10, 90, 40},
        {90, 10, 15, 40},
        {55, 80, 11, 8},
        {30, 30, 30, 40},
    };

    for (int i = 0; i < 5; ++i) {
        drawLine(image, point[i][0], point[i][1], point[i][2], point[i][3], Color::red());
        drawLineAA(image_aa, point[i][0], point[i][1], point[i][2], point[i][3], Color::red());
        drawBrokenLine(image_bl, point[i][0], point[i][1], point[i][2], point[i][3], Color::red());
    }

    serializeBmp(&ofs, image);
    serializeBmp(&ofsaa, image_aa);
    serializeBmp(&ofsbl, image_bl);



    image->destroy();
    image_aa->destroy();
    image_bl->destroy();

}


int main()
{   
    test2();
    return 0;
}