
#ifndef IMG_BITMAP_HPP
#define IMG_BITMAP_HPP

#include <cstdlib>
#include <iostream>
#include <cstdint>



//------------------------------------------------------------------------------------------
//  ビットマップファイルヘッダ
#pragma pack(1)

struct BitmapFileHeader {
    uint16_t type_;
    uint32_t size_;
    uint16_t reserved1_;
    uint16_t reserved2_;
    uint32_t offbits_;
};

struct BitmapInfoHeader{
  uint32_t size_;
  int32_t width_;
  int32_t heigth_;
  uint16_t planes_;
  uint16_t bit_count_;
  uint32_t compression_;
  uint32_t size_image_;
  int32_t pels_per_meter_x_;
  int32_t pels_per_meter_y_;
  uint32_t clr_used_;
  uint32_t clr_important_;
};

struct RgbQuad{
  uint8_t blue_;
  uint8_t green_;
  uint8_t red_;
  uint8_t reserved_;
};

#pragma pack()

//------------------------------------------------------------------------------------------
//  カラー値
struct Color
{
    Color()
        : r_(0)
        , g_(0)
        , b_(0)
    {
    }

    Color(
        const int r,
        const int g,
        const int b
    )   : r_(r)
        , g_(g)
        , b_(b)
    {
    }

    static Color black() {
        return Color(0, 0, 0);
    }

    static Color white() {
        return Color(255, 255, 255);
    }

    static Color red() {
        return Color(255, 0, 0);
    }

    static Color green() {
        return Color(0, 255, 0);
    }

    static Color blue() {
        return Color(0, 0, 255);
    }

    //  Color * s
    Color operator *( const float s ) const {
        return Color(r_ * s, g_ * s, b_ * s);
    }


    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
};


//------------------------------------------------------------------------------------------
//  ピクチャ
class Image
{
    typedef Image   self_t;

private:
    //  ctor.
    Image()
        : width_(0)
        , height_(0)
        , r_(nullptr)
        , g_(nullptr)
        , b_(nullptr)
        , a_(nullptr)
    {
    }

    //  dtor.
    ~Image() 
    {
        delete[] r_;
        delete[] g_;
        delete[] b_;
        delete[] a_;
    }

public:

    int width_;
    int height_;
    uint8_t* r_;
    uint8_t* g_;
    uint8_t* b_;
    uint8_t* a_;

public:
    /**
     *  インスタンス生成.
     */
    static self_t* createImage() {
        self_t* image = new self_t;
        return image;
    }

    /**
     *  インスタンス生成.
     */
    static self_t* createImage(
        const size_t width,   //  幅
        const size_t height   //  高さ
    ){
        self_t* image = new self_t;
        image->setupImage(
            width,
            height
        );
          
        return image;          
    }

    /**
     *  破棄.
     */
    void destroy() {
        delete this;
    }

    /**
     *  情報の出力.
     */
    void dump() {
        ::std::cout << "x:" << width_ << std::endl;
        ::std::cout << "y:" << height_ << std::endl;
    }

    /**
     *  ピクセル値取得.
     */
    void getPixel(
        Color* out,
        const int x,
        const int y
    ) {
        int pixel_index = x + (y * width_);
        out->r_ = r_[pixel_index];
        out->g_ = g_[pixel_index];
        out->b_ = b_[pixel_index];
    }


    /**
     *  ピクセル値加算.
     */
    void addPixelColor(
        const int x,
        const int y,
        const Color& color
    ){
        //  イメージの範囲外へのプロットは無視
        if (x < 0 || x >= width_){
            return;
        }
        if (y < 0 || y >= height_){
            return;
        }

        int pixel_index = x + (y * width_);

        if (r_[pixel_index] + color.r_ < 256) {
            r_[pixel_index] += color.r_;
        }
        else {
            r_[pixel_index] = 255;
        }

        if (g_[pixel_index] + color.g_ < 256) {
            g_[pixel_index] += color.g_;
        }
        else {
            g_[pixel_index] = 255;
        }

        if (b_[pixel_index] + color.b_ < 256) {
            b_[pixel_index] += color.b_;
        }
        else {
            b_[pixel_index] = 255;
        }
    }

    /**
     *  ピクセル値指定.
     */
    void plot(
        const int x,
        const int y,
        const Color& color
    ) {
        plot(x, y, color.r_, color.g_, color.b_);
    }

    /**
     *  ピクセル値指定.
     */
    void plot(
        const int x,
        const int y,
        const int r,
        const int g,
        const int b
    ) {
        //  イメージの範囲外へのプロットは無視
        if (x < 0 || x >= width_){
            return;
        }
        if (y < 0 || y >= height_){
            return;
        }

        int pixel_index = x + (y * width_);
        r_[pixel_index] = r;
        g_[pixel_index] = g;
        b_[pixel_index] = b;
    }


    /**
     *  塗りつぶし.
     */
    void fill(
        const Color& color
    ) {
        fill(color.r_, color.g_, color.b_);
    }

    /**
     *  塗りつぶし.
     */
    void fill(
        const int r,
        const int g,
        const int b
    ) {
        size_t pixel_num = width_ * height_;
        for (size_t i = 0; i < pixel_num; ++i) {
            r_[i] = r;
            g_[i] = g;
            b_[i] = b;            
        }
    }


private:
    /**
     *  サイズ設定.
     */
    void setupImage(
        const size_t width, 
        const size_t height
    ) {

        //  サイズ設定
        width_ = width;
        height_ = height;

        //  領域確保
        size_t pixel_num = height_ * width_;
        delete[] r_;
        r_ = new unsigned char[pixel_num];

        delete[] g_;
        g_ = new unsigned char[pixel_num];
        
        delete[] b_;
        b_ = new unsigned char[pixel_num];

    }

};

/**
 *  ビットマップファイルヘッダ構築.
 */
void setupBitmapFileHeader(
    BitmapFileHeader* const file_header,
    const int img_size
){
    file_header->type_ = *(uint16_t*)"BM";  // TODO 定数アクセスする
    file_header->size_ = img_size + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    file_header->reserved1_ = 0;
    file_header->reserved2_ = 0;
    file_header->offbits_ = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
}

/**
 *  ビットマップインフォヘッダ構築.
 */
void setupBitmapInfoHeader(
    BitmapInfoHeader* const info_header,
    const int x,
    const int y,
    const int img_size
){
    info_header->size_ = sizeof(BitmapInfoHeader);
    info_header->width_ = x;
    info_header->heigth_ = y;
    info_header->planes_ = 1;
    info_header->bit_count_ = 24;
    info_header->compression_ = 0;
    info_header->size_image_ = img_size;
    info_header->pels_per_meter_x_ = 0;
    info_header->pels_per_meter_y_ = 0;
    info_header->clr_used_ = 0;
    info_header->clr_important_ = 0;
}


//------------------------------------------------------------------------------------------
//  ビットマップ書き出し. FILE* ver.
bool serializeBmp(
    FILE* file,
    const Image* const image
){
    if(file == nullptr || image == nullptr) {
        return false;
    }

    //  ----------------------------------
    //  ヘッダ作成
    int x = image->width_;
    int y = image->height_;
    int padding = (x * 3 + 3) / 4 * 4 - (x * 3);      // 32bit境界条件によるパディング
    int img_size = (x * 3 + padding) * y;           // 出力される場増データサイズ

    //  ファイルヘッダ
    BitmapFileHeader file_header;
    setupBitmapFileHeader(&file_header, img_size);

    //  インフォヘッダ
    BitmapInfoHeader info_header;
    setupBitmapInfoHeader(
        &info_header,
        x,
        y,
        img_size
    );


    //  ----------------------------------
    //  ヘッダ出力
    if (fwrite((void*)&file_header,sizeof(BitmapFileHeader),1,file) != 1) {
        //  書き込み失敗
        return false;
    }
    if (fwrite((void*)&info_header,sizeof(BitmapInfoHeader),1,file) != 1) {
        //  書き込み失敗
        return false;
    }

    //  出力バッファ確保
    unsigned char* buf = (unsigned char*)malloc(img_size);
    unsigned char* buf_top = buf;     // 画像データとその先頭ポインタ

    if(buf_top == nullptr) {
        return false; // メモリ確保失敗
    }
    //  データ整列
    for(int i = y - 1 ; i >= 0 ; i--){
        for(int j = 0 ; j < x ; j++){
            *(buf++) = image->b_[j + i * x];
            *(buf++) = image->g_[j + i * x];
            *(buf++) = image->r_[j + i * x];
        }
        for(int j = 0;j < padding;j++) {
            *(buf++) = 0;
        }
    }
  
    if (fwrite((void*)buf_top,1,img_size,file) != img_size) {
        free(buf_top);
        return false;
    }


    //  成功
    free(buf_top);
    return true;

}


//------------------------------------------------------------------------------------------
//  ビットマップ書き出し. fstream ver.
bool serializeBmp(
    std::ofstream* file, 
    const Image* const image
){
    if(file == nullptr || image == nullptr) {
        return false;
    }

    //  ----------------------------------
    //  ヘッダ作成
    int x = image->width_;
    int y = image->height_;
    int padding = (x * 3 + 3) / 4 * 4 - x * 3;      // 32bit境界条件によるパディング
    int img_size = (x * 3 + padding) * y;           // 出力される場増データサイズ

    //  ファイルヘッダ
    BitmapFileHeader file_header;
    setupBitmapFileHeader(&file_header, img_size);

    //  インフォヘッダ
    BitmapInfoHeader info_header;
    setupBitmapInfoHeader(
        &info_header,
        x,
        y,
        img_size
    );

    //  ----------------------------------
    //  ヘッダ出力
    file->write((char*)&file_header, sizeof(BitmapFileHeader));
    file->write((char*)&info_header, sizeof(BitmapInfoHeader));

    //  出力バッファ確保

    unsigned char* buf = (unsigned char*)malloc(img_size);
    unsigned char* buf_top = buf;     // 画像データとその先頭ポインタ

    if(buf_top == nullptr) {
        return false; // メモリ確保失敗
    }
    //  データ整列
    for(int i = y - 1 ; i >= 0 ; i--){
        for(int j = 0 ; j < x ; j++){
            *(buf++) = image->b_[j + i * x];
            *(buf++) = image->g_[j + i * x];
            *(buf++) = image->r_[j + i * x];
        }
        for(int j = 0;j < padding;j++) {
            *(buf++) = 0;
        }
    }
    file->write((char*)buf_top, img_size);



    //  成功
    free(buf_top);
    return true;

}


//------------------------------------------------------------------------------------------
/**
 *  ビットマップの整合性チェック.
 */
bool isVaildBmp(
    const BitmapFileHeader* const file_header,
    const BitmapInfoHeader* const info_header
){
    if (file_header->type_ != *(uint16_t*)"BM") { // TODO 定数判定に変える
        return false;
    }
    if (info_header->size_ != sizeof(BitmapInfoHeader)) {
        return false;
    }
    if (info_header->compression_ != 0) {
        return false;
    }

    int pallet_size = file_header->offbits_ - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);
    int img_size = info_header->size_image_;     // イメージサイズ
    int x = info_header->width_;                 //  イメージの幅
    int y = info_header->heigth_;                // イメージの高さ
    int color_bit = info_header->bit_count_;     // １色あたりのビット数


    //  ヘッダの矛盾を確認
    if (color_bit  != 24 
        && pallet_size != sizeof(RgbQuad) * (1 << color_bit)) {
        return false;
    }

    if (color_bit  == 0) {
        return false;
    }

    if (x <= 0 || y <= 0) {
        return false;
    }

    if (img_size != file_header->size_ - file_header->offbits_) {
        return false;
    }

    if (img_size != (x * color_bit + 31) / 32 * 4 * y) {
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------------------
/**
 *  ビットマップからイメージデータ生成.
 */
Image* createImageFromBmp(
    uint8_t* img_buffer,
    const int width,
    const int height,
    const int color_bit,
    const RgbQuad* const rgbq
){
    //  イメージ作成
    Image* image = Image::createImage(width, height);
    if (image == nullptr) {
        return nullptr;
    }

    // yの正負によって走査方向を設定
    int start_y;
    int stop_y;
    int sign_y;
    int y = height;
    int x = width;
    if (y < 0) {
        y = -y;
        start_y = 0;
        stop_y = y;
        sign_y = 1;
    }
    else {
        start_y = -y + 1;
        stop_y = 1;
        sign_y = -1;
    }


    //  データ変換
    int padding = (x * color_bit + 31) / 32 * 4 - (x * color_bit + 7 ) / 8;
    int mask = (1 << color_bit) - 1;   // 指定ビット数のマスク

    if(color_bit  == 24){                 
        // カラーパレットを使用しない場合
        for(int i = start_y ; i < stop_y ; i++){
            for(int j = 0 ; j < x ; j++){
                image->b_[j + i * x * sign_y] = *(img_buffer++);
                image->g_[j + i * x * sign_y] = *(img_buffer++);
                image->r_[j + i * x * sign_y] = *(img_buffer++);
            }
            //  パディングを読み飛ばす
            img_buffer += padding;
        }
    }
    else {                             
        //  カラーパレットを使用する場合
        for (int i = start_y ; i < stop_y ; i++) {
            int shift = 8;
            for(int j = 0 ; j < x ; j++){
                shift -= color_bit;
                int p = *img_buffer >> shift & mask;
                if (shift <= 0) {
                    shift = 8;
                    img_buffer++;
                }
                image->b_[j + i * x * sign_y] = rgbq[p].blue_;
                image->g_[j + i * x * sign_y] = rgbq[p].green_;
                image->r_[j + i * x * sign_y] = rgbq[p].red_;
            }
            if(shift != 8){
                img_buffer++;
            }
            img_buffer += padding;
        }
    }



    return image;
}



//------------------------------------------------------------------------------------------
//  ビットマップ読み込み. FILE* ver.
Image* deserializeBmp(
    FILE* file
){

    if(file == nullptr) {
        return nullptr;
    }

    //  ヘッダ取得
    BitmapFileHeader file_header;
    size_t bmpfileheader_size = fread((void*)&file_header,sizeof(BitmapFileHeader),1,file);
    if(bmpfileheader_size != 1){
        //  読み込み失敗
        return nullptr;
    }

    //  ファイルヘッダ
    BitmapInfoHeader info_header;
    size_t bmp_info_header_size = fread((void*)&info_header,sizeof(BitmapInfoHeader),1,file);
    if (bmp_info_header_size != 1) {
        //  読み込み失敗
        return nullptr;
    }

    if (!isVaildBmp(&file_header, &info_header)) {
        //  不正なデータ
        return nullptr;
    }

    //  カラーパレット取得
    RgbQuad* rgbq = nullptr;
    if (info_header.bit_count_  != 24) {
        int pallet_size = file_header.offbits_ - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);

        rgbq = (RgbQuad*)malloc(pallet_size);
        if (rgbq == nullptr) {
            return nullptr;
        }
        size_t color_pallet_size = fread((void*)rgbq,1,pallet_size,file);
        if (color_pallet_size != pallet_size) {
            free(rgbq);
            return nullptr;
        }
    }

    //  イメージデータ取得
    int img_size = info_header.size_image_;
    uint8_t* buf = (uint8_t*)malloc(img_size);
    uint8_t* buf_top = buf;

    if (buf == nullptr) {
        free(rgbq);
        //  読み込み失敗
        return nullptr;
    }

    size_t read_size = fread((void*)buf,1,img_size,file);
    if (read_size != img_size) {
        free(rgbq);
        free(buf_top);
        //  読み込み失敗
        return nullptr;
    }

    //  ビットマップからイメージデータ生成
    Image* image = createImageFromBmp(
        buf, 
        info_header.width_, 
        info_header.heigth_, 
        info_header.bit_count_,
        rgbq
    );

    free(rgbq);
    free(buf_top);

    return image;
}



//------------------------------------------------------------------------------------------
//  ビットマップ読み込み. fstream ver.
Image* deserializeBmp(
    std::ifstream* file
){

    if(file == nullptr) {
        return nullptr;
    }

    //  ヘッダ取得
    BitmapFileHeader file_header;
    file->read((char *)(&file_header), sizeof(BitmapFileHeader));
    if( file->bad() ) {
        //  読み込み失敗
        return nullptr;
    }

    //  ファイルヘッダ
    BitmapInfoHeader info_header;
    file->read((char *)(&info_header), sizeof(BitmapInfoHeader));
    if( file->bad() ) {
        //  読み込み失敗
        return nullptr;
    }


    if (!isVaildBmp(&file_header, &info_header)) {
        //  不正なデータ
        return nullptr;
    }

    //  カラーパレット取得
    RgbQuad* rgbq = nullptr;
    if (info_header.bit_count_  != 24) {
        int pallet_size = file_header.offbits_ - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);

        rgbq = (RgbQuad*)malloc(pallet_size);
        if (rgbq == nullptr) {
            return nullptr;
        }


        file->read((char *)rgbq, pallet_size);
        if( file->bad() ) {
            //  読み込み失敗
            return nullptr;
        }
    }

    //  イメージデータ取得
    int img_size = info_header.size_image_;
    uint8_t* buf = (uint8_t*)malloc(img_size);
    uint8_t* buf_top = buf;

    if (buf == nullptr) {
        free(rgbq);
        //  読み込み失敗
        return nullptr;
    }


    file->read((char *)buf, img_size);

    //  ビットマップからイメージデータ生成
    Image* image = createImageFromBmp(
        buf, 
        info_header.width_, 
        info_header.heigth_, 
        info_header.bit_count_,
        rgbq
    );

    //   片付け
    free(rgbq);
    free(buf_top);
    return image;
}





#endif // IMG_BITMAP_HPP

