//
//  imageView.m
//  OpenCL_03_mandelbrot
//
//  Created by 哲郎 可児 on 12/04/01.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "imageView.h"
#include <iostream>
#include "color_table.hpp"

#define MAX_CALC 255
#define CANVAS_WIDTH 430
#define CANVAS_HEIGHT 320
MandColorTable ct(MAX_CALC);

@implementation imageView
NSTimer* timer;        
- (id)initWithFrame:(NSRect)frame
{
    
    self = [super initWithFrame:frame];
    if (self) {
        off_screen_context_ = newImageBuffer(CANVAS_WIDTH, CANVAS_HEIGHT);
    }
    
    
    timer     = [NSTimer scheduledTimerWithTimeInterval:0.025
                    target:self
                    selector:@selector(onTimer)
                    userInfo:nil
                    repeats:NO];
    
    
    // マンデルブロ計算
    mandel_ = new Mandelblot( CANVAS_WIDTH, CANVAS_HEIGHT, MAX_CALC );
    mandel_->setCenterVcX(-0.56159);
    mandel_->setCenterVcY(-0.6419);
    mandel_->setMaxY(0.001);
    mandel_->calculateCL();
        
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
    CGImageRef image = CGBitmapContextCreateImage( off_screen_context_ );
    CGContextDrawImage( context, self.bounds, image );
    CGImageRelease( image );
}


-(void)dealloc {
    delete mandel_;
    disposeImageBuffer( off_screen_context_ );
    [super dealloc];
}


-(void) onTimer{
    static float md_x = -1;
    md_x += 0.1;


    
    render( off_screen_context_, mandel_->getData() );
    [self setNeedsDisplay:YES];
    /*
    mandel_->initialize(CANVAS_WIDTH, CANVAS_HEIGHT, MAX_CALC);
    mandel_->setCenterWithDcXY(1.76, md_x);
    mandel_->setMaxY(1.3);
    mandel_->calculate();
*/
}

static void render( CGContextRef context, int* calcnum ){

    int width = CGBitmapContextGetWidth( context );
	int height = CGBitmapContextGetHeight( context );
	unsigned char* baseAddress = (unsigned char*) CGBitmapContextGetData( context );
	size_t bytesPerRow = CGBitmapContextGetBytesPerRow( context );


	for (int v = 0; v < height; v++) {
		for (int h = 0; h < width; h++) {

            unsigned char* p = baseAddress + (v * bytesPerRow) + h * 4;
            int index = (v * CANVAS_WIDTH) + h;
            std::cout << calcnum[index] << std::endl;
            int num = calcnum[index];
            if (num > MAX_CALC) {
                num = 0;
            }
            *p++ = ct.getR( num ) * 255;
            *p++ = ct.getG( num ) * 255;
            *p++ = ct.getB( num ) * 255;
            *p++ = 255;
		}
	}
    
}

static CGContextRef newImageBuffer(int width, int height )
{
#define COMPONENT_COUNT 4
    
    size_t bitsPerComponent = 8;
    size_t bytesPerRow = width * COMPONENT_COUNT;
    unsigned char* baseAddress = (unsigned char*)malloc( bytesPerRow * height * sizeof(unsigned char));
    
    for (int v = 0; v < height; ++v ){
        for ( int h = 0; h < width; ++h ){
            unsigned char* p = baseAddress + (v * bytesPerRow) + h * 4;
            *p++ = 0;
            *p++ = v%255;
            *p++ = 0;
            *p++ = 255;
        }
    }
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    CGContextRef context = CGBitmapContextCreate(
        baseAddress,
        width, 
        height, 
        bitsPerComponent, 
        bytesPerRow, 
        colorSpace, 
        kCGImageAlphaPremultipliedLast 
    );
    
    CGColorSpaceRelease( colorSpace );
        
    return context;
}


static void disposeImageBuffer(
    CGContextRef context
){
    [timer release];
    unsigned char* baseAddress = (unsigned char*)CGBitmapContextGetData( context );
    CGContextRelease( context );
    free( baseAddress );
}


@end
