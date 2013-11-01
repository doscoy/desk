//
//  main.cpp
//  OpenCL_02_calc
//
//  Created by 哲郎 可児 on 12/03/12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <OpenCL/OpenCL.h>
#include <boost/timer.hpp>
#include "tri_parallel_system.hpp"


const int ARRAY_SIZE = 30000000;
//////////////////////////////
float in1[ARRAY_SIZE];
float in2[ARRAY_SIZE];
float out[ARRAY_SIZE];

static const char sources[] = {
"__kernel void addVector(\n\
    __global const float* in1,\n\
    __global const float* in2,\n\
    __global float* out\n\
){\n\
    int index = get_global_id(0);\n\
    out[index] = in1[index] + in2[index];\n\
}\n"
};




int main (int argc, const char * argv[])
{
    cl_int status;
    
    t3::ParallelSystem ps;
    t3::ParallelSystem::dumpPlatformInfo();
  
    if ( !ps.initialize( CL_DEVICE_TYPE_GPU ) ){
        std::cout << "initialize fail." << std::endl;
    }
    
    // ソースのビルド
    int program_handle = ps.build( sources );
    
    //  カーネル作成
    int kernel_handle = ps.createKernel( "addVector" );
    if ( kernel_handle == -1 ){
        return 1;
    }
    

    //  ダミー値を設定
    for (int i = 0; i < ARRAY_SIZE; ++i ) {
        in1[i] = float(i) * 10.0f;
        in2[i] = float(i) / 10.0f;
        out[i] = 0;
    }

    cl_mem memIn1 = ps.createBuffer( CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * ARRAY_SIZE, in1 );
    cl_mem memIn2 = ps.createBuffer( CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_float) * ARRAY_SIZE, in2 );
    cl_mem memOut = ps.createBuffer( CL_MEM_WRITE_ONLY, sizeof(cl_float) * ARRAY_SIZE, nullptr );
    
    //  カーネル関数引数のセット
    ps.setKernelArgument( kernel_handle, 0, sizeof( cl_mem ), reinterpret_cast<void*>( &memIn1 ) );
    ps.setKernelArgument( kernel_handle, 1, sizeof( cl_mem ), reinterpret_cast<void*>( &memIn2 ) );
    ps.setKernelArgument( kernel_handle, 2, sizeof( cl_mem ), reinterpret_cast<void*>( memOut ) );

    boost::timer t;
    
#if 1
    //  カーネル実行のリクエスト
    size_t globalSize[] = {ARRAY_SIZE};
    ps.requestKernelExecute( 0, kernel_handle, 1, globalSize );
    
    //  結果の取得
    ps.readBuffer( 0, memOut, true, 0, sizeof(cl_float) * ARRAY_SIZE, out );
#else
    for (int i = 0; i < ARRAY_SIZE; ++i ){
        out[i] = in1[i] + in2[i];
    }
#endif
    
    std::cout << "\n\nTOTAL CALC TIME : " << t.elapsed() << std::endl;
   
    //  結果の一部を表示
    for (int i = 0; i < 10; ++i ){
        std::cout << "   " << i << " : "<< in1[i] << " + " << in2[i] << " = " << out[i] << std::endl;
    }
    

    return 0;
}

