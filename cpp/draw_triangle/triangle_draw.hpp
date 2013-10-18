
#ifndef TRIANGLE_DRAW_HPP
#define TRIANGLE_DRAW_HPP

#include "img_bitmap.hpp"
#include "line_draw.hpp"
#include <stack>




struct Point
{
    Point()
        : x_(0)
        , y_(0)
    {
    }

    Point(
        const int x,
        const int y
    )   : x_(x)
        , y_(y)
    {
    }

    int x_;
    int y_;
};

std::stack<Point> seeds_;


/**
*  �h��Ԃ��\�s�N�Z��������.
*/
bool canFill(
    Image* image,
    const Point& seed,
    const Color& edge_color
) {
    if (seed.x_ >= image->getWidth()) {
        return false;
    }
    else if (seed.x_ < 0) {
        return false;
    }
    else if (seed.y_ < 0) {
        return false;
    }
    else if (seed.y_ >= image->getHeight()) {
        return false;
    }
    Color color;
    image->getPixel(&color, seed.x_, seed.y_);
    if (color == edge_color) {
        return false;
    }

    return true;
}


/**
 *  �O�p�`�̏d�S���擾.
 */
Point getTriangleCenterOfGravity(
    const Point& a,
    const Point& b,
    const Point& c
) {
    return Point(
        (a.x_ + b.x_ + c.x_) / 3,
        (a.y_ + b.y_ + c.y_) / 3
    );
}

/**
 *  �h��Ԃ�.
 */
void seedFill(
    Image* image,
    const Color& edge_color,
    const Point& seed
){
    seeds_.push(seed);

    while (!seeds_.empty()) {
        //  ������o��
        Point current_seed = seeds_.top();
        seeds_.pop();


        Point up(current_seed.x_, current_seed.y_ - 1);
        if (canFill(image, up, edge_color)) {
            image->plot(up.x_, up.y_, edge_color);
            seeds_.push(up);
        }
        Point down(current_seed.x_, current_seed.y_ + 1);
        if (canFill(image, down, edge_color)) {
            image->plot(down.x_, down.y_, edge_color);
            seeds_.push(down);
        }
        Point right(current_seed.x_ + 1, current_seed.y_);
        if (canFill(image, right, edge_color)) {
            image->plot(right.x_, right.y_, edge_color);
            seeds_.push(right);
        }
        Point left(current_seed.x_ - 1, current_seed.y_);
        if (canFill(image, left, edge_color)) {
            image->plot(left.x_, left.y_, edge_color);
            seeds_.push(left);
        }
        
    }
}

/**
 *  �O�p�`�`��.
 */
void drawTriangle(
    Image* image,
    const int x0,
    const int y0,
    const int x1,
    const int y1,
    const int x2,
    const int y2,
    const Color& color
){
    //  �t���[���`��
    drawLine2(image, x0, y0, x1, y1, color);
    drawLine2(image, x1, y1, x2, y2, color);
    drawLine2(image, x2, y2, x0, y0, color);

    //  ����h��Ԃ�
    Point center = getTriangleCenterOfGravity(
        Point(x0, y0),
        Point(x1, y1),
        Point(x2, y2)
    );
	seedFill(image, color, center);


}



#endif // TRIANGLE_DRAW_HPP
