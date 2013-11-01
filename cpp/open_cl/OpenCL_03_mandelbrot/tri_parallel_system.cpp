
#include "tri_parallel_system.hpp"
#include <iostream>
#include <sys/stat.h>

#define PS_ASSERT(exp)  (void)( (exp) || (std::cout << #exp << __FILE__ << __LINE__ << "assert" << std::endl ),0)

namespace {

const int MAX_PLATFORM_ID = 10;
const int MAX_DEVICE_ID = 10;

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
        std::cout << "  " << header << "failed..." << std::endl;
    }
}

void printDeviceInfoWorkItem( cl_device_id id, const char* const header )
{
    cl_uint value;
    cl_int status = clGetDeviceInfo( id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &value, nullptr );
    if ( status == CL_SUCCESS ) {
        size_t work[10];
        clGetDeviceInfo( id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(size_t) * value, &work, nullptr );
    
        std::cout << "   " << header << value;
        std::cout << "(";
        for ( int i = 0; i < value; ++i ){
            std::cout << " " << work[i];
        }
        std::cout << " )" << std::endl;
    }
    else {
        std::cout << "   " << header << "failed..." << std::endl;
    }
    
    
}

void printDeviceInfoString( cl_device_id id, int type, const char* const header )
{
    char buffer[1024];
    size_t actual_size;
    cl_int status = clGetDeviceInfo( id, type, sizeof(buffer) -1, buffer, &actual_size );
    if ( status == CL_SUCCESS ){
        buffer[actual_size] = 0;
        std::cout << "   " << header << buffer << std::endl;        
    } 
    else {
        std::cout << "   " << header << "failed..." << std::endl;
    }
}
    
void printDeviceInfoUInt( cl_device_id id, int type, const char* const header )
{
    cl_uint value;
    cl_int status = clGetDeviceInfo( id, type, sizeof(cl_uint), &value, nullptr );
    if ( status == CL_SUCCESS ) {
        std::cout << "   " << header << value << std::endl;
    }
    else {
        std::cout << "   " << header << "failed..." << std::endl;
    }
}

void printDeviceInfoBool( cl_device_id id, int type, const char* const header )
{
    cl_bool value;
    cl_int status = clGetDeviceInfo( id, type, sizeof(value), &value, nullptr );
    if ( status == CL_SUCCESS ) {
        if ( value ) {
            std::cout << "   " << header << "true" << std::endl;
        }
        else {
            std::cout << "   " << header << "false" << std::endl;
        }    
    }
    else {
        std::cout << "   " << header << "failed..." << std::endl;
    }
}
void printOpenCLInfo()
{
    cl_platform_id platform_id[MAX_PLATFORM_ID];
    cl_uint num_platforms;
    cl_int status;
    
    //  OpenCLのPlatform情報を取得
    status = clGetPlatformIDs( 
        MAX_PLATFORM_ID,
        platform_id,
        &num_platforms
    );
    
    for ( int i = 0; i < num_platforms; ++i ){
        cl_platform_id current_id = platform_id[i];
        std::cout << "platform " << i << " ID:" << current_id << std::endl;
        printPlatformInfo( current_id, CL_PLATFORM_PROFILE,     "profile :");
        printPlatformInfo( current_id, CL_PLATFORM_VERSION,     "version :");
        printPlatformInfo( current_id, CL_PLATFORM_NAME,        "name    :");
        printPlatformInfo( current_id, CL_PLATFORM_VENDOR,      "vendor  :");
//        printPlatformInfo( current_id, CL_PLATFORM_EXTENSIONS,  "extensions :");
        
        //  platformに含まれているデバイス情報を取得
        cl_device_id device_id[MAX_DEVICE_ID];
        cl_uint num_devices;
        clGetDeviceIDs( current_id, CL_DEVICE_TYPE_ALL, MAX_DEVICE_ID, device_id, &num_devices );
        for ( int device_idx = 0; device_idx < num_devices; ++device_idx ){
            std::cout << std::endl << " device[" << device_idx << "]" << std::endl;
            cl_device_id current_device_id = device_id[device_idx];
            printDeviceInfoUInt( current_device_id, CL_DEVICE_VENDOR_ID,                "vender id         :" ); 
            printDeviceInfoUInt( current_device_id, CL_DEVICE_MAX_COMPUTE_UNITS,        "core              :" ); 
            printDeviceInfoWorkItem( current_device_id,                                 "work dimensions   :" ); 
            printDeviceInfoUInt( current_device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY,      "clock frequency   :" ); 
            printDeviceInfoUInt( current_device_id, CL_DEVICE_ADDRESS_BITS,             "address bits      :" ); 
            printDeviceInfoBool( current_device_id, CL_DEVICE_ENDIAN_LITTLE,            "little endian     :" );
            printDeviceInfoBool( current_device_id, CL_DEVICE_AVAILABLE,                "device available  :" );
            printDeviceInfoBool( current_device_id, CL_DEVICE_COMPILER_AVAILABLE,       "compiler available:" );
            printDeviceInfoString( current_device_id, CL_DEVICE_NAME,                   "device name       :" );
            printDeviceInfoString( current_device_id, CL_DEVICE_VENDOR,                 "device vendor     :" );
            printDeviceInfoString( current_device_id, CL_DEVICE_PROFILE,                "device profile    :" );
            printDeviceInfoString( current_device_id, CL_DEVICE_VERSION,                "device version    :" );
//            printDeviceInfoString( current_device_id, CL_DEVICE_EXTENSIONS,             "device extensions :" );
        }
    }

}

} // unname namespace



namespace t3 {



// *********************************************
//  コンストラクタ
ParallelSystem::ParallelSystem()
{
    
    
}

// *********************************************
//  デストラクタ
ParallelSystem::~ParallelSystem()
{
    
}

// *********************************************
//  初期化
bool ParallelSystem::initialize(
    const cl_device_type type
){
    cl_int status;
    
    //  コンテキスト生成
    context_ = clCreateContextFromType(
        nullptr,
        type,
        nullptr,
        nullptr,
        &status
    );
    PS_ASSERT(status == CL_SUCCESS);
    if ( status != CL_SUCCESS ){
        return false;
    }
    
    //  デバイス取得
    size_t return_size;
    status = clGetContextInfo(
        context_,
        CL_CONTEXT_DEVICES,
        sizeof(devices_),
        devices_,
        &return_size
    );
    if ( status != CL_SUCCESS ){
        return false;
    }

    //  デバイスの個数所持
    device_num_ = return_size / sizeof(size_t);
    
    for ( int i = 0; i < device_num_; ++i ){
        std::cout << devices_[i] << std::endl;
    }
    
    for ( int device_idx = 0; device_idx < device_num_; ++device_idx ){
        queue_[device_idx] = clCreateCommandQueue(
            context_,
            devices_[device_idx],
            0,
            &status
        );
        
        if ( status != CL_SUCCESS ){
            std::cout << "queue create fail. " << device_idx << std::endl;
            return false;
        }
    }


    return true;
}


// *********************************************
//  プログラムのビルド
int ParallelSystem::build(
    const char* const source
){
    //  プログラムのビルド
    cl_int status;
    cl_program program = clCreateProgramWithSource( context_, 1, (const char**)&source, nullptr, &status );
    PS_ASSERT( status == CL_SUCCESS );
    if ( status != CL_SUCCESS ){
        std::cout << "error." << std::endl;
        return -1;
    }
    
    status = clBuildProgram( program, device_num_, devices_, nullptr, nullptr, nullptr );
    PS_ASSERT( status == CL_SUCCESS );
    
    if ( status != CL_SUCCESS ){
        //  ビルド失敗
        const int LOG_BUFFER_SIZE = 1024;
        char log_buffer[LOG_BUFFER_SIZE];
        clGetProgramBuildInfo(
            program,
            devices_[0],
            CL_PROGRAM_BUILD_LOG,
            LOG_BUFFER_SIZE,
            log_buffer,
            nullptr
        );
        std::cout << log_buffer << std::endl;
        //## panic
        return -1;
    }
    
    builded_programs_.push_back( program );
    
    clUnloadCompiler();
    return builded_programs_.size()-1;
}




// *********************************************
//  カーネル作成
int ParallelSystem::createKernel(
    const char* const kernel_name
){
    cl_kernel kernel;
    bool kernel_found = false;
    cl_int status;
    for ( auto program: builded_programs_ ){
        kernel = clCreateKernel( program, kernel_name, &status );
        if ( status == CL_SUCCESS ){
            kernel_found = true;
            break;
        }
    }
    if ( !kernel_found ){
        return -1;
    }
    
    kernels_.push_back( kernel );
    return kernels_.size()-1;
}
    
// *********************************************
//  メモリバッファ作成
cl_mem ParallelSystem::createBuffer(
    const cl_mem_flags flags,     
    const size_t size,
    void* host_ptr 
){
    cl_int status;
    cl_mem mem = clCreateBuffer( context_, flags, size, host_ptr, &status );
    PS_ASSERT( status == CL_SUCCESS );
    if ( status != CL_SUCCESS ){
        return nullptr;
    }
    return mem;
}

// *********************************************
//  カーネルに引数をセットする
void ParallelSystem::setKernelArgument( 
    const int kernel_handle,
    const unsigned int arg_index,
    const size_t arg_size,
    const void* arg_value
){
    cl_int status = clSetKernelArg( getKernel( kernel_handle ), arg_index, arg_size, arg_value );

    std::cout << "index " << arg_index << std::endl;
    PS_ASSERT( status == CL_SUCCESS );

}


// *********************************************
//  演算結果の取得
void ParallelSystem::readBuffer(
    const int queue_handle,
    const cl_mem result_buffer,
    const bool is_wait,
    const size_t offset,
    const size_t read_data_size,
    void* buffer
){
    clEnqueueReadBuffer( getQueue( queue_handle ), result_buffer, is_wait, offset, read_data_size, buffer, 0, nullptr, nullptr );
}

char* ParallelSystem::loadProgramSource(const char *filename)
{
    struct stat statbuf;
    char *source;
    
    FILE* fp = fopen( filename, "rb" );
    if ( fp == nullptr ) {
        return nullptr;
    }
    if ( stat(filename, &statbuf) != 0 ) {
        return nullptr;
    }
    
    source = new char[statbuf.st_size + 1];
    fread(source, statbuf.st_size, 1, fp);
    source[statbuf.st_size] = '\0';
    fclose(fp);
    
    return source;
}



// *********************************************
//  カーネルの実行リクエスト
void ParallelSystem::requestKernelExecute(
    const int queue_handle,
    const int kernel_handle,
    const unsigned int work_dim,
    const size_t* work_size
){
    clEnqueueNDRangeKernel(
        getQueue( queue_handle ),
        getKernel( kernel_handle ),
        work_dim,
        nullptr,
        work_size,
        0,
        0,
        nullptr,
        nullptr
    );
}

// *********************************************
//  プラットホーム情報表示
void ParallelSystem::dumpPlatformInfo()
{
    printOpenCLInfo();
}

}   // namespace t3


