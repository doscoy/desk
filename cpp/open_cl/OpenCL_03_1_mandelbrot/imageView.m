//
//  imageView.m
//  OpenCL_03_mandelbrot
//
//  Created by 哲郎 可児 on 12/04/01.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "imageView.h"
#include <iostream>


#define MAX_CALC 1000
#define CANVAS_WIDTH 800
#define CANVAS_HEIGHT 600

@implementation imageView
NSTimer* timer;        
- (id)initWithFrame:(NSRect)frame
{
    ps_.initialize( CL_DEVICE_TYPE_GPU );
    ps_.dumpPlatformInfo();
    
    self = [super initWithFrame:frame];
    if (self) {
        off_screen_context_ = newImageBuffer(CANVAS_WIDTH, CANVAS_HEIGHT);
    }
    
    
    timer     = [NSTimer scheduledTimerWithTimeInterval:0.025
                    target:self
                    selector:@selector(onTimer)
                    userInfo:nil
                    repeats:YES];
    
/*    
    // マンデルブロ計算
    mandel_ = new Mandelbrot( CANVAS_WIDTH, CANVAS_HEIGHT );
    mandel_->setCenterVcX(-0.56159);
    mandel_->setCenterVcY(-0.6419);
    mandel_->setMaxY(0.001);
    mandel_->calculate();
   */     
    
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
    static float md_x = -0.56159;
    static float md_y = -0.6419;
    static float may = 0.01f;
    md_x -= 0.00001;
    md_y += 0.00001;
    may -= 0.00001f;

    mandel_ = new Mandelbrot( CANVAS_WIDTH, CANVAS_HEIGHT );
    mandel_->setCenterVcX(md_x);
    mandel_->setCenterVcY(md_y);
    mandel_->setMaxY(may);
    mandel_->calculate();
    
    render( off_screen_context_, mandel_->data() );
    [self setNeedsDisplay:YES];
    
    delete mandel_;
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
            int num = calcnum[index];
            if (num > MAX_CALC) {
                num = 0;
            }
            *p++ = ((float)num / (float)255) * 255;
            *p++ = ((float)num / (float)255) * 255;
            *p++ = ((float)num / (float)255) * 255;
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
