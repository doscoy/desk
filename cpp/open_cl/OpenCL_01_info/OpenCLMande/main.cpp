//
//  main.cpp
//  OpenCLMande
//
//  Created by 哲郎 可児 on 12/03/12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <OpenCL/OpenCL.h>



void printPlatformInfo( cl_platform_id id, int type, const char* const header )
{
    char buffer[1024];
    size_t actual_size;
    cl_int status = clGetPlatformInfo( id, type, sizeof(buffer) -1, buffer, &actual_size );
    if ( status == CL_SUCCESS ){
        buffer[actual_size] = 0;
        std::cout << "  " << header << buffer << std::endl;        
    } 
    else {
        std::cout << "info failed..." << std::endl;
    }
    
    
}


// *********************************************
//  OpenCL情報のダンプ
void dumpOpenCLInfo()
{
    cl_platform_id platform_id[10];
    cl_uint num_platforms;
    cl_int status;
    
    //  OpenCLの構成情報を取得
    status = clGetPlatformIDs( sizeof(platform_id) / sizeof(*platform_id),
                              platform_id,
                              &num_platforms
    );

    for ( int i = 0; i < num_platforms; ++i ){
        cl_platform_id current_id = platform_id[i];
        std::cout << "platform " << current_id << std::endl;
        printPlatformInfo( current_id, CL_PLATFORM_PROFILE,     "platform profile:");
        printPlatformInfo( current_id, CL_PLATFORM_VERSION,     "platform version:");
        printPlatformInfo( current_id, CL_PLATFORM_NAME,        "platform name   :");
        printPlatformInfo( current_id, CL_PLATFORM_VENDOR,      "platform vendor :");
        printPlatformInfo( current_id, CL_PLATFORM_EXTENSIONS,  "platform ext    :");
    }
    
    //  platform infomation
    
}


int main (int argc, const char * argv[])
{

    dumpOpenCLInfo();
   
    return 0;
}

