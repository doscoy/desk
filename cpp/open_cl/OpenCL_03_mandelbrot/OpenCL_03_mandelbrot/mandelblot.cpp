//
//  mandelblot.cpp
//  OpenCL_03_mandelbrot
//
//  Created by 哲郎 可児 on 12/04/02.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "mandelblot.hpp"
#include "tri_parallel_system.hpp"


namespace {

t3::ParallelSystem ps_;


}   // unname namespace







Mandelblot::Mandelblot(
    const int width,
    const int height,
    const int max_calc
)   : width_(width)
    , height_(height)
    , pixel_count_(width * height)
    , max_calc_num_(max_calc)
    , mapper_( width, height )
{
    data_ = new int[pixel_count_];
    for ( int i = 0; i < pixel_count_; ++i ){
        data_[i] = -1;
    }
    
    initialize(width, height, max_calc);
    ps_.initialize(CL_DEVICE_TYPE_GPU);
}

void Mandelblot::initialize(
    const int width,
    const int height,
    const int max_calc
){
    width_ = width;
    height_ = height;
    max_calc_num_ = max_calc;
    
    mapper_.init(width, height);
    mapper_.setMaxY(1.2f);
}


void Mandelblot::calculateCL(){
    cl_context context = ps_.getContext();
    cl_command_queue q = ps_.getQueue(0);
    const char* source = ps_.loadProgramSource( "/Users/doscoy_t/project/OpenCL_Projects/OpenCL_03_mandelbrot/calc.cl" );
    int program_id = ps_.build( source );
    int kernel_id = ps_.createKernel( "calcMandelBrot" );
    cl_mem out = ps_.createBuffer(CL_MEM_WRITE_ONLY, sizeof(cl_int) * pixel_count_, 0 );
    
    // カーネルに渡すパラメータ
    const cl_int max_calc = max_calc_num_;
    float startX = (float)mapper_.getVcX0();
    float startY = (float)mapper_.getVcY0();
    float step = (float)mapper_.getStep();
    ps_.setKernelArgument(kernel_id, 0, sizeof(cl_int), (void*)&max_calc);
    ps_.setKernelArgument(kernel_id, 1, sizeof(cl_float), (void*)&startX);
    ps_.setKernelArgument(kernel_id, 2, sizeof(cl_float), (void*)&startY);
    ps_.setKernelArgument(kernel_id, 3, sizeof(cl_float), (void*)&step);
    ps_.setKernelArgument(kernel_id, 4, sizeof(out), (void*)&out);

    //　実行リクエスト
    cl_uint work_dim = 2; // x, y
    size_t global_work_size[] = {width_, height_};

    ps_.requestKernelExecute(0, kernel_id, work_dim, global_work_size);

    ps_.readBuffer(0, out, CL_TRUE, 0, sizeof(cl_int) * pixel_count_, data_);
}


int Mandelblot::getCalc0Num(
    const double x,
    const double y,
    const int max_calc_num
) const {
    int count = 0;
    double prev_x = 0;
    double prev_y = 0;
    
    for ( int i = 0; i < max_calc_num + 1; ++i ){
        count = i + 1;
        double new_x = (prev_x * prev_x) - (prev_y * prev_y) + x;
        double new_y = 2.0f * prev_x * prev_y + y;
        
        if ((new_x * new_x) + (new_y * new_y) > 4.0f){
            break;
        }
        else {
            prev_x = new_x;
            prev_y = new_y;
        }
    }
    
    return count;
}

Mandelblot::~Mandelblot()
{
    delete[] data_;
}



void Mandelblot::calculate()
{
    
    double start_x = mapper_.getVcX0();
    double start_y = mapper_.getVcY0();
    double step = mapper_.getStep();
    unsigned int width = mapper_.getDcWidth();
    unsigned int height = mapper_.getDcHeight();
    
    int index = 0;
    for ( int y = 0; y < height; ++y ){
        double fy = start_y + (step * (double)y);
        for ( int x = 0; x < width; ++x ){
            double fx = start_x + (step * (double)x);
            data_[index] = getCalc0Num( fx, fy, max_calc_num_ );
            ++index;
        }
    }
    
}


