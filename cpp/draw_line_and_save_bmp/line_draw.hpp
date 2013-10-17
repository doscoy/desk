
#ifndef LINE_DRAW_HPP
#define LINE_DRAW_HPP

#include "img_bitmap.hpp"

//  �Ƃ肠�����v���[���n��
void drawLine(
    Image* image,
    int x0,
    int y0,
    int x1,
    int y1,
    const Color& color
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
            image->plot(y,x, color);
        }
        else {
            image->plot(x,y, color);
        }
        error = error - deltay;
        if (error < 0) {
            y = y + ystep;
            error = error + deltax;
        }

    }

}


//  ���ǔŃv���[���n��
void drawLine2(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    //  �����v�Z
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;

    //  �����v�Z
    int delta_x = std::abs(x1 - x0);
    int delta_y = std::abs(y1 - y0);

    //  xy�̌덷�𓯎��Ɍv�Z
    int error_xy = delta_x - delta_y;

    int x = x0;
    int y = y0;
    while(x != x1 || y != y1) {
        image->plot(x, y, color);

        int error2 = error_xy << 1;  // �덷�̔{ = error_xy * 2

        //  x��
        if (error2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y��
        if (error2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}


bool isEndOfLine(
    const float x, 
    const float x1, 
    const float y, 
    const float y1,
    const float ep
) {

    if (x < x1 - ep){
        return false;
    }
    else if (x > x1 + ep) {
        return false;
    }

    if (y < y1 - ep){
        return false;
    }
    else if (y > y1 + ep) {
        return false;
    }

    return true;
}

//  �A���`�G�C���A�X�t����
void drawLineAA(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    float ep = 0.25f;

    //  �����v�Z
    float sign_x = x0 < x1 ? ep : -ep;
    float sign_y = y0 < y1 ? ep : -ep;

    //  �����v�Z
    float delta_x = std::abs(x1 - x0);
    float delta_y = std::abs(y1 - y0);

    //  xy�̌덷�𓯎��Ɍv�Z
    int error_xy = delta_x - delta_y;

    float x = x0;
    float y = y0;
    Color line_color = color * ep;

    while(!isEndOfLine(x, x1, y, y1, ep)) {
        image->addPixelColor(x, y, line_color);

        int error_xy2 = error_xy << 1;  // �덷�̔{ = error_xy * 2

        //  x��
        if (error_xy2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y��
        if (error_xy2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}

//  �j���`��
void drawBrokenLine(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){
    int broken_pixel = 3;   //  �j���̃s�N�Z��
    bool draw = true;
    int draw_count = broken_pixel;


    //  �����v�Z
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;

    //  �����v�Z
    int delta_x = std::abs(x1 - x0);
    int delta_y = std::abs(y1 - y0);

    //  xy�̌덷�𓯎��Ɍv�Z
    int error_xy = delta_x - delta_y;
    int x = x0;
    int y = y0;
    while(x != x1 || y != y1) {
        if (draw) {
            image->plot(x, y, color);
        }

        //  �j���p�J�E���g
        draw_count -= 1;
        if (draw_count <= 0) {
            draw_count = broken_pixel;
            draw = !draw;
        }

        int error2 = error_xy << 1;  // �덷�̔{ = error_xy * 2

        //  x��
        if (error2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y��
        if (error2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}






#endif // LINE_DRAW_HPP