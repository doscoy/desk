
#ifndef LINE_DRAW_HPP
#define LINE_DRAW_HPP

#include "img_bitmap.hpp"

//  ‚Æ‚è‚ ‚¦‚¸ƒvƒŒƒ[ƒ“ƒnƒ€
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


//  ‰ü—Ç”ÅƒvƒŒƒ[ƒ“ƒnƒ€
void drawLine2(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    //  •ûŒüŒvZ
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;

    //  ·•ªŒvZ
    int delta_x = std::abs(x1 - x0);
    int delta_y = std::abs(y1 - y0);

    //  xy‚ÌŒë·‚ğ“¯‚ÉŒvZ
    int error_xy = delta_x - delta_y;

    int x = x0;
    int y = y0;
    while(x != x1 || y != y1) {
        image->plot(x, y, color);

        int error2 = error_xy << 1;  // Œë·‚Ì”{ = error_xy * 2

        //  x²
        if (error2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y²
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

//  ƒAƒ“ƒ`ƒGƒCƒŠƒAƒX•t‚¯‚é
void drawLineAA(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    float ep = 0.25f;

    //  •ûŒüŒvZ
    float sign_x = x0 < x1 ? ep : -ep;
    float sign_y = y0 < y1 ? ep : -ep;

    //  ·•ªŒvZ
    float delta_x = std::abs(x1 - x0);
    float delta_y = std::abs(y1 - y0);

    //  xy‚ÌŒë·‚ğ“¯‚ÉŒvZ
    int error_xy = delta_x - delta_y;

    float x = x0;
    float y = y0;
    Color line_color = color * ep;

    while(!isEndOfLine(x, x1, y, y1, ep)) {
        image->addPixelColor(x, y, line_color);

        int error_xy2 = error_xy << 1;  // Œë·‚Ì”{ = error_xy * 2

        //  x²
        if (error_xy2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y²
        if (error_xy2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}

//  ”jü•`‰æ
void drawBrokenLine(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){
    int broken_pixel = 3;   //  ”jü‚ÌƒsƒNƒZƒ‹
    bool draw = true;
    int draw_count = broken_pixel;


    //  •ûŒüŒvZ
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;

    //  ·•ªŒvZ
    int delta_x = std::abs(x1 - x0);
    int delta_y = std::abs(y1 - y0);

    //  xy‚ÌŒë·‚ğ“¯‚ÉŒvZ
    int error_xy = delta_x - delta_y;
    int x = x0;
    int y = y0;
    while(x != x1 || y != y1) {
        if (draw) {
            image->plot(x, y, color);
        }

        //  ”jü—pƒJƒEƒ“ƒg
        draw_count -= 1;
        if (draw_count <= 0) {
            draw_count = broken_pixel;
            draw = !draw;
        }

        int error2 = error_xy << 1;  // Œë·‚Ì”{ = error_xy * 2

        //  x²
        if (error2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y²
        if (error2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}






#endif // LINE_DRAW_HPP