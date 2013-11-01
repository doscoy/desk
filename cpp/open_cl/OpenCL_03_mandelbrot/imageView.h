//
//  imageView.h
//  OpenCL_03_mandelbrot
//
//  Created by 哲郎 可児 on 12/04/01.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "mandelblot.hpp"
@interface imageView : NSView{
    CGContextRef off_screen_context_;
    Mandelblot* mandel_;
}
    
@end
