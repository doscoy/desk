

#ifndef TRI_PARALLEL_SYSTEM_HPP
#define TRI_PARALLEL_SYSTEM_HPP

#include <vector>
#include <OpenCL/OpenCL.h>

namespace t3 {
    
class ParallelSystem{
    
    static const int MAX_DEVICE_NUM = 10;
    
public:
    // *********************************************
    //  コンストラクタ
    ParallelSystem();
    
    // *********************************************
    //  デストラクタ
    ~ParallelSystem();
    
public:
    // *********************************************
    //  並列処理システムの初期化
    bool initialize( 
        cl_device_type type // I : 対象となるデバイスの種類
    );
    
    // *********************************************
    //  OpenCLプログラムのビルド
    int build( 
        const char* const source    // I : ビルドするソース
    );
    
    // *********************************************
    //  カーネルの生成
    int createKernel(                   // R : 生成したカーネルのハンドル
        const char* const kernel_name   // I : カーネル関数名
    );

    // *********************************************
    //  カーネルの実行リクエスト
    void requestKernelExecute(
        int queue_handle,
        int kernel_handle,
        unsigned int work_dim,
        const size_t* work_size
    );

    // *********************************************
    //  OpenCLコンテキスト取得
    cl_context getContext() const {
        return context_;
    }
    
    // *********************************************
    //  デバイスID取得
    cl_device_id getDeviceID(
        int device_idx
    ){
        return devices_[device_idx];
    }
    
    // *********************************************
    //  コマンドキュー取得
    cl_command_queue getQueue( int device_idx ) const {
        return queue_[device_idx];
    }
    
    // *********************************************
    //  デバイス数取得
    int getDeviceNum() const {
        return device_num_;
    }
    
    // *********************************************
    //  プラットフォーム情報をダンプ
    static void dumpPlatformInfo();
    
    
    // *********************************************
    //  ビルド済プログラムを取得 const
    const std::vector<cl_program>& getBuildedPrograms() const {
        return builded_programs_;
    }
    
    // *********************************************
    //  ビルド済プログラムを取得
    std::vector<cl_program>& getBuildedPrograms() {
        return builded_programs_;
    }
    
    // *********************************************
    //  ビルド済プログラムを取得 const
    const cl_program& getBuildedProgram( int index ) const {
        return builded_programs_.at( index );
    }
    
    // *********************************************
    //  ビルド済プログラムを取得
    cl_program& getBuildedProgram( int index ) {
        return builded_programs_.at( index );
    }
    
    // *********************************************
    //  カーネルを取得
    const cl_kernel& getKernel( const int kernel_handle ) const {
        return kernels_.at( kernel_handle );
    }

    // *********************************************
    //  カーネルを取得
    cl_kernel& getKernel( const int kernel_handle ){
        return kernels_.at( kernel_handle );
    }
    
    // *********************************************
    //  メモリバッファ作成
    cl_mem createBuffer(
        cl_mem_flags flags, 
        size_t size,
        void* host_ptr 
    );

    // *********************************************
    //  カーネルに引数をセットする
    void setKernelArgument( 
        int kernel_handle,
        unsigned int arg_index,
        size_t arg_size,
        const void* arg_value
    );

    
    // *********************************************
    //  演算結果の取得
    void readBuffer(
        int queue_handle,
        cl_mem result_buffer,
        bool is_wait,
        size_t offset,
        size_t read_data_size,
        void* buffer
    );
    
    char* loadProgramSource(const char *filename);
    
    
private:
    cl_context context_;
    int device_num_;
    cl_device_id devices_[MAX_DEVICE_NUM];
    cl_command_queue queue_[MAX_DEVICE_NUM];
    std::vector<cl_program> builded_programs_;
    std::vector<cl_kernel> kernels_;
    
};
    
    
}   // namespace t3




#endif // TRI_PARALLEL_SYSTEM_HPP
