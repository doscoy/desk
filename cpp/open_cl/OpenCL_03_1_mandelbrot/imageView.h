//
//  imageView.h
//  OpenCL_03_mandelbrot
//
//  Created by 哲郎 可児 on 12/04/01.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "tri_parallel_system.hpp"
#include "Mandelbrot.h"
@interface imageView : NSView{
    CGContextRef off_screen_context_;
    t3::ParallelSystem ps_;
    Mandelbrot* mandel_;
}
    
@end
