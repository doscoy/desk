//
//  color_table.hpp
//  OpenCL_03_mandelbrot
//
//  Created by 哲郎 可児 on 12/04/03.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#include <math.h>

#ifndef OpenCL_03_mandelbrot_color_table_hpp
#define OpenCL_03_mandelbrot_color_table_hpp

class MandColorTable{
public:
    MandColorTable( const int color_index = 1000 ){
        num_color_index_ = color_index;
        r_ = new float [color_index];
        g_ = new float [color_index];
        b_ = new float [color_index];
        
        fillColorTable();
        
    }
    
    ~MandColorTable(){
        delete[] r_;
        delete[] g_;
        delete[] b_;
        
    }
    
    float getR( const int index ) const {
        return r_[index];
    }
    float getG( const int index ) const {
        return g_[index];
    }
    float getB( const int index ) const {
        return b_[index];
    }
    
    
    void fillColorTable(){
        
        const float step = 100.0f;
        
        for ( int i = 0; i < num_color_index_; ++i ){
            r_[i] = float((sin(((M_PI * 2.0f * (float)i) / step + M_2_PI)) + 1.0f) / 2.0f);
            g_[i] = float((sin(((M_PI * 2.0f * (float)i) / step + M_2_PI)) + 1.0f) / 2.0f);
            b_[i] = float((sin(((M_PI * 2.0f * (float)i) / step + M_2_PI)) + 1.0f) / 2.0f);
        }
    }
    
    int num_color_index_;
    
    float* r_;
    float* g_;
    float* b_;
    
};

#endif
