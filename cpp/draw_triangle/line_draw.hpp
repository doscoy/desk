
#ifndef LINE_DRAW_HPP
#define LINE_DRAW_HPP

#include "img_bitmap.hpp"

//  とりあえずプレゼンハム
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


//  改良版プレゼンハム
void drawLine2(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    //  方向計算
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;

    //  差分計算
    int delta_x = std::abs(x1 - x0);
    int delta_y = std::abs(y1 - y0);

    //  xyの誤差を同時に計算
    int error_xy = delta_x - delta_y;

    int x = x0;
    int y = y0;
    while(x != x1 || y != y1) {
        image->plot(x, y, color);

        int error2 = error_xy << 1;  // 誤差の倍 = error_xy * 2

        //  x軸
        if (error2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y軸
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

//  アンチエイリアス付ける
void drawLineAA(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    float ep = 0.25f;

    //  方向計算
    float sign_x = x0 < x1 ? ep : -ep;
    float sign_y = y0 < y1 ? ep : -ep;

    //  差分計算
    float delta_x = std::abs(x1 - x0);
    float delta_y = std::abs(y1 - y0);

    //  xyの誤差を同時に計算
    int error_xy = delta_x - delta_y;

    float x = x0;
    float y = y0;
    Color line_color = color * ep;

    while(!isEndOfLine(x, x1, y, y1, ep)) {
        image->addPixelColor(x, y, line_color);

        int error_xy2 = error_xy << 1;  // 誤差の倍 = error_xy * 2

        //  x軸
        if (error_xy2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y軸
        if (error_xy2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}

//  アンチエイリアス改造版
void drawLineAA2(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){

    float ep = 0.25f;

    //  プロット移動量計算
    float dx = x1 - x0;
    float dy = y1 - y0;

    if (dx == 0 && dy == 0) {
        //  長さが無い直線だったら点打って終了
        image->plot(x0, y0, color);
        return;
    }

    float length = std::sqrtf((dx * dx) + (dy * dy));
    float scale = ep / length;
    
    float dir_x = dx * scale;
    float dir_y = dy * scale;
    
    //  始点
    float x = x0;
    float y = y0;

    //  線の色
    Color line_color = color * ep;

    //  プロット回数
    int plot_count = length / ep;

    //  描画
    for (int i = 0; i < plot_count; ++i) {
        image->addPixelColor(x, y, line_color);
        //  プロット点移動
        x += dir_x;
        y += dir_y;
    }

}

float calcCoverag(
    const float x,
    const float y
){
    int ix = x;
    int iy = y;

    float fx = ix + 0.5f;
    float fy = iy + 0.5f;

    float dx = std::abs(fx - x);
    float dy = std::abs(fy - y);

    float coverage = 1.0f - (dx + dy);

    return coverage;
}

//  アンチエイリアスを新たなアイディアに乗せて
void drawLineAA3(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){
    //  プロット移動量計算
    float dx = x1 - x0;
    float dy = y1 - y0;

    if (dx == 0 && dy == 0) {
        //  長さが無い直線だったら点打って終了
        image->plot(x0, y0, color);
        return;
    }

    float length = std::sqrtf((dx * dx) + (dy * dy));
    float scale = 1.0f / length;
    
    float dir_x = dx * scale;
    float dir_y = dy * scale;
    
    //  始点
    float x = x0;
    float y = y0;

    //  プロット回数
    int plot_count = length;

    //  描画
    for (int i = 0; i < plot_count; ++i) {
        float coverage = calcCoverag(x, y);
        image->plot(x, y, color * coverage);
        //  プロット点移動
        x += dir_x;
        y += dir_y;
    }
}



//  破線描画
void drawBrokenLine(
    Image* const image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const Color& color
){
    int broken_pixel = 3;   //  破線のピクセル
    bool draw = true;
    int draw_count = broken_pixel;


    //  方向計算
    int sign_x = x0 < x1 ? 1 : -1;
    int sign_y = y0 < y1 ? 1 : -1;

    //  差分計算
    int delta_x = std::abs(x1 - x0);
    int delta_y = std::abs(y1 - y0);

    //  xyの誤差を同時に計算
    int error_xy = delta_x - delta_y;
    int x = x0;
    int y = y0;
    while(x != x1 || y != y1) {
        if (draw) {
            image->plot(x, y, color);
        }

        //  破線用カウント
        draw_count -= 1;
        if (draw_count <= 0) {
            draw_count = broken_pixel;
            draw = !draw;
        }

        int error2 = error_xy << 1;  // 誤差の倍 = error_xy * 2

        //  x軸
        if (error2 > -delta_y) {
            error_xy -= delta_y;
            x += sign_x;
        }
        //  y軸
        if (error2 < delta_x) {
            error_xy += delta_x;
            y += sign_y;
        }
    }

}






#endif // LINE_DRAW_HPP