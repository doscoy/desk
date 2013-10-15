
#ifndef IMG_BITMAP_HPP
#define IMG_BITMAP_HPP

#include <cstdlib>
#include <iostream>


typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef long            LONG;



//------------------------------------------------------------------------------------------
//  �r�b�g�}�b�v�t�@�C���w�b�_
#pragma pack(1)

struct BitmapFileHeader {
    WORD type_;
    DWORD size_;
    WORD reserved1_;
    WORD reserved2_;
    DWORD offbits_;
};

struct BitmapInfoHeader{
  DWORD size_;
  LONG width_;
  LONG heigth_;
  WORD planes_;
  WORD bit_count_;
  DWORD compression_;
  DWORD size_image_;
  LONG pels_per_meter_x_;
  LONG pels_per_meter_y_;
  DWORD clr_used_;
  DWORD clr_important_;
};

struct RgbQuad{
  BYTE blue_;
  BYTE green_;
  BYTE red_;
  BYTE reserved_;
};

#pragma pack()


//------------------------------------------------------------------------------------------
//  �s�N�`��
class Image
{
    typedef Image   self_t;

private:
    Image()
        : width_(0)
        , height_(0)
        , r_(nullptr)
        , g_(nullptr)
        , b_(nullptr)
        , a_(nullptr)
    {
    }

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
    BYTE* r_;
    BYTE* g_;
    BYTE* b_;
    BYTE* a_;

public:
    static self_t* createImage() {
        Image* image = new Image;
        return image;
    }

    static self_t* createImage(
        size_t width,
        size_t height
    ){
        Image* image = new Image;
        image->setupImage(
            width,
            height
        );
          
        return image;          
    }

    void destroy() {
        delete this;
    }

    void dump() {
        ::std::cout << "x:" << width_ << std::endl;
        ::std::cout << "y:" << height_ << std::endl;
    }


    void setPixelColor(
        int x,
        int y,
        BYTE r,
        BYTE g,
        BYTE b
    ) {

        //  �C���[�W�͈̔͊O�ւ̃v���b�g�͖���
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

    void fill(
        BYTE r,
        BYTE g,
        BYTE b
    ) {
        size_t pixel_num = width_ * height_;
        for (int i = 0; i < pixel_num; ++i) {
            r_[i] = r;
            g_[i] = g;
            b_[i] = b;            
        }
    }

private:

    void setupImage(size_t width, size_t height) {

        width_ = width;
        height_ = height;
        size_t pixel_num = height_ * width_;
        r_ = new unsigned char[pixel_num];
        g_ = new unsigned char[pixel_num];
        b_ = new unsigned char[pixel_num];

    }

};


//------------------------------------------------------------------------------------------
Image*
saveBmp(FILE* file, Image* image)
{
    if(file == nullptr || image == nullptr) {
        return nullptr;
    }

    //  �w�b�_�쐬
    int x = image->width_;
    int y = image->height_;
    int padding = (x * 3 + 3) / 4 * 4 - x * 3;  // 32bit���E�����ɂ��p�f�B���O
    int img_size = (x * 3 + padding) * y;        // �o�͂����ꑝ�f�[�^�T�C�Y

    //  �t�@�C���w�b�_
    BitmapFileHeader file_header;
    file_header.type_ = *(WORD*)"BM";
    file_header.size_ = img_size + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    file_header.reserved1_ = 0;
    file_header.reserved2_ = 0;
    file_header.offbits_ = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    //  �t�@�C���w�b�_
    BitmapInfoHeader info_header;
    info_header.size_ = sizeof(BitmapInfoHeader);
    info_header.width_ = x;
    info_header.heigth_ = y;
    info_header.planes_ = 1;
    info_header.bit_count_ = 24;
    info_header.compression_ = 0;
    info_header.size_image_ = img_size;
    info_header.pels_per_meter_x_ = 0;
    info_header.pels_per_meter_y_ = 0;
    info_header.clr_used_ = 0;
    info_header.clr_important_ = 0;

    //  �w�b�_�o��
    if (fwrite((void*)&file_header,sizeof(BitmapFileHeader),1,file) != 1) {
        //  �������ݎ��s
        return nullptr;
    }
    if (fwrite((void*)&info_header,sizeof(BitmapInfoHeader),1,file) != 1) {
        //  �������ݎ��s
        return nullptr;
    }

    //  �o�̓o�b�t�@�m��
    unsigned char* buf = (unsigned char*)malloc(img_size);
    unsigned char* buf_top = buf;     // �摜�f�[�^�Ƃ��̐擪�|�C���^

    if(buf_top == nullptr) {
        return nullptr; // �������m�ێ��s
    }
    //  �f�[�^����
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
        return nullptr;
    }


    //  ����
    free(buf_top);
    return image;

}


//------------------------------------------------------------------------------------------
Image*
saveBmp(std::ofstream* file, Image* image)
{
    if(file == nullptr || image == nullptr) {
        return nullptr;
    }

    //  �w�b�_�쐬
    int x = image->width_;
    int y = image->height_;
    int padding = (x * 3 + 3) / 4 * 4 - x * 3;  // 32bit���E�����ɂ��p�f�B���O
    int img_size = (x * 3 + padding) * y;        // �o�͂����ꑝ�f�[�^�T�C�Y

    //  �t�@�C���w�b�_
    BitmapFileHeader file_header;
    file_header.type_ = *(WORD*)"BM";
    file_header.size_ = img_size + sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    file_header.reserved1_ = 0;
    file_header.reserved2_ = 0;
    file_header.offbits_ = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    //  �t�@�C���w�b�_
    BitmapInfoHeader info_header;
    info_header.size_ = sizeof(BitmapInfoHeader);
    info_header.width_ = x;
    info_header.heigth_ = y;
    info_header.planes_ = 1;
    info_header.bit_count_ = 24;
    info_header.compression_ = 0;
    info_header.size_image_ = img_size;
    info_header.pels_per_meter_x_ = 0;
    info_header.pels_per_meter_y_ = 0;
    info_header.clr_used_ = 0;
    info_header.clr_important_ = 0;

    //  �w�b�_�o��
    file->write((char*)&file_header, sizeof(BitmapFileHeader));
    file->write((char*)&info_header, sizeof(BitmapInfoHeader));

    //  �o�̓o�b�t�@�m��

    unsigned char* buf = (unsigned char*)malloc(img_size);
    unsigned char* buf_top = buf;     // �摜�f�[�^�Ƃ��̐擪�|�C���^

    if(buf_top == nullptr) {
        return nullptr; // �������m�ێ��s
    }
    //  �f�[�^����
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



    //  ����
    free(buf_top);
    return image;

}


//------------------------------------------------------------------------------------------
Image* 
loadBmp(FILE* file)
{

    if(file == nullptr) {
        return nullptr;
    }

    //  �w�b�_�擾
    BitmapFileHeader file_header;
    size_t bmpfileheader_size = fread((void*)&file_header,sizeof(BitmapFileHeader),1,file);
    printf("bmp file header size %d == %d\n", bmpfileheader_size, sizeof(BitmapFileHeader));
    if(bmpfileheader_size != 1){
        //  �ǂݍ��ݎ��s
        return nullptr;
    }

    //  �t�@�C���w�b�_
    BitmapInfoHeader info_header;
    size_t bmp_info_header_size = fread((void*)&info_header,sizeof(BitmapInfoHeader),1,file);
    printf("bmp info header size %d == %d\n", bmp_info_header_size, sizeof(BitmapInfoHeader));
    if (bmp_info_header_size != 1) {
        //  �ǂݍ��ݎ��s
        return nullptr;
    }
    if (file_header.type_ != *(WORD*)"BM") {
        return nullptr;
    }
    if (info_header.size_ != sizeof(BitmapInfoHeader)) {
        return nullptr;
    }
    if (info_header.compression_ != 0) {
        return nullptr;
    }


    int pallet_size = file_header.offbits_ - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);
    int img_size = info_header.size_image_;     // �C���[�W�T�C�Y
    int x = info_header.width_;                 //  �C���[�W�̕�
    int y = info_header.heigth_;                // �C���[�W�̍���
    int color_bit = info_header.bit_count_;     // �P�F������̃r�b�g��



    // y�̐����ɂ���đ���������ݒ�
    int start_y;
    int stop_y;
    int sign_y;

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

    int padding = (x * color_bit + 31) / 32 * 4 - (x * color_bit + 7 ) / 8;
    int mask = (1 << color_bit) - 1;   // �w��r�b�g���̃}�X�N

    //  �w�b�_�̖������m�F
    if (color_bit  != 24 
        && pallet_size != sizeof(RgbQuad) * (1 << color_bit)) {
        return nullptr;
    }

    if (color_bit  == 0) {
        return nullptr;
    }

    if (x <= 0 || y <= 0) {
        return nullptr;
    }

    if (img_size != file_header.size_ - file_header.offbits_) {
        return nullptr;
    }

    if (img_size != (x * color_bit + 31) / 32 * 4 * y) {
        return nullptr;
    }

    //  �J���[�p���b�g�擾
    RgbQuad* rgbq;
    
    if (color_bit  == 24) {
        rgbq = nullptr;
    }
    else {
        rgbq = (RgbQuad*)malloc(pallet_size);
        if (rgbq == nullptr) {
            return nullptr;
        }
        size_t color_pallet_size = fread((void*)rgbq,1,pallet_size,file);
        printf("plt %d == %d\n", color_pallet_size, pallet_size);
        if (color_pallet_size != pallet_size) {
            free(rgbq);
            return nullptr;
        }
    }

    //  �C���[�W�f�[�^�擾
    unsigned char* buf = (unsigned char*)malloc(img_size);
    unsigned char* buf_top = buf;

    if (buf == nullptr) {
        free(rgbq);
        //  �ǂݍ��ݎ��s
        return nullptr;
    }

    size_t read_size = fread((void*)buf,1,img_size,file);
    printf("%d == %d\n", read_size, img_size);
    if (read_size != img_size) {
        free(rgbq   );
        free(buf_top);
        //  �ǂݍ��ݎ��s
        return nullptr;
    }

    //  �߂�l�̃������m��
    Image* image = Image::createImage(x, y);

    if (image->r_ == nullptr || image->b_ == nullptr || image->g_ == nullptr) {
        image->destroy();
        image = nullptr;
        free(rgbq);
        free(buf_top);
        return nullptr;
    }

    //  �f�[�^�ϊ�
    if(color_bit  == 24){                 
        // �J���[�p���b�g���g�p���Ȃ��ꍇ
        for(int i = start_y ; i < stop_y ; i++){
            for(int j = 0 ; j < x ; j++){
                image->b_[j + i * x * sign_y] = *(buf++);
                image->g_[j + i * x * sign_y] = *(buf++);
                image->r_[j + i * x * sign_y] = *(buf++);
            }
            //  �p�f�B���O��ǂݔ�΂�
            buf += padding;
        }
    }
    else {                             
        //  �J���[�p���b�g���g�p����ꍇ
        for (int i = start_y ; i < stop_y ; i++) {
            int shift = 8;
            for(int j = 0 ; j < x ; j++){
                shift -= color_bit;
                int p = *buf >> shift & mask;
                if (shift <= 0) {
                    shift = 8;
                    buf++;
                }
                image->b_[j + i * x * sign_y] = rgbq[p].blue_;
                image->g_[j + i * x * sign_y] = rgbq[p].green_;
                image->r_[j + i * x * sign_y] = rgbq[p].red_;
            }
            if(shift != 8){
                buf++;
            }
            buf += padding;
        }
    }

    /* ------------------------- ���ׂĐ��� ---------------------------- */
    free(rgbq   );
    free(buf_top);
    printf("read success.\n");
    return image;
}



//------------------------------------------------------------------------------------------
Image* 
loadBmp(std::ifstream* file)
{

    if(file == nullptr) {
        return nullptr;
    }

    //  �w�b�_�擾
    BitmapFileHeader file_header;
    file->read((char *)(&file_header), sizeof(BitmapFileHeader));
    if( file->bad() ) {
        //  �ǂݍ��ݎ��s
        return nullptr;
    }

    //  �t�@�C���w�b�_
    BitmapInfoHeader info_header;
    file->read((char *)(&info_header), sizeof(BitmapInfoHeader));
    if( file->bad() ) {
        //  �ǂݍ��ݎ��s
        return nullptr;
    }


    if (file_header.type_ != *(WORD*)"BM") {
        return nullptr;
    }
    if (info_header.size_ != sizeof(BitmapInfoHeader)) {
        return nullptr;
    }
    if (info_header.compression_ != 0) {
        return nullptr;
    }


    int pallet_size = file_header.offbits_ - sizeof(BitmapFileHeader) - sizeof(BitmapInfoHeader);
    int img_size = info_header.size_image_;     // �C���[�W�T�C�Y
    int x = info_header.width_;                 //  �C���[�W�̕�
    int y = info_header.heigth_;                // �C���[�W�̍���
    int color_bit = info_header.bit_count_;     // �P�F������̃r�b�g��



    // y�̐����ɂ���đ���������ݒ�
    int start_y;
    int stop_y;
    int sign_y;

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

    int padding = (x * color_bit + 31) / 32 * 4 - (x * color_bit + 7 ) / 8;
    int mask = (1 << color_bit) - 1;   // �w��r�b�g���̃}�X�N

    //  �w�b�_�̖������m�F
    if (color_bit  != 24 
        && pallet_size != sizeof(RgbQuad) * (1 << color_bit)) {
        return nullptr;
    }

    if (color_bit  == 0) {
        return nullptr;
    }

    if (x <= 0 || y <= 0) {
        return nullptr;
    }

    if (img_size != file_header.size_ - file_header.offbits_) {
        return nullptr;
    }

    if (img_size != (x * color_bit + 31) / 32 * 4 * y) {
        return nullptr;
    }

    //  �J���[�p���b�g�擾
    RgbQuad* rgbq;
    
    if (color_bit  == 24) {
        rgbq = nullptr;
    }
    else {
        rgbq = (RgbQuad*)malloc(pallet_size);
        if (rgbq == nullptr) {
            return nullptr;
        }


        file->read((char *)rgbq, pallet_size);
        if( file->bad() ) {
            //  �ǂݍ��ݎ��s
            return nullptr;
        }
    }

    //  �C���[�W�f�[�^�擾
    unsigned char* buf = (unsigned char*)malloc(img_size);
    unsigned char* buf_top = buf;

    if (buf == nullptr) {
        free(rgbq);
        //  �ǂݍ��ݎ��s
        return nullptr;
    }


    file->read((char *)buf, img_size);


    //  �߂�l�̃������m��
    Image* image = Image::createImage();
    if (image == nullptr) {
        free(rgbq);
        free(buf_top);
        return nullptr;
    }

    image->width_ = x;
    image->height_ = y;
    size_t pixel_num = x * y;
    image->r_ = new unsigned char[pixel_num];
    image->g_ = new unsigned char[pixel_num];
    image->b_ = new unsigned char[pixel_num];
    if (image->r_ == nullptr || image->b_ == nullptr || image->g_ == nullptr) {
        image->destroy();
        image = nullptr;
        free(rgbq);
        free(buf_top);
        return nullptr;
    }

    //  �f�[�^�ϊ�
    if(color_bit  == 24){                 
        // �J���[�p���b�g���g�p���Ȃ��ꍇ
        for(int i = start_y ; i < stop_y ; i++){
            for(int j = 0 ; j < x ; j++){
                image->b_[j + i * x * sign_y] = *(buf++);
                image->g_[j + i * x * sign_y] = *(buf++);
                image->r_[j + i * x * sign_y] = *(buf++);
            }
            //  �p�f�B���O��ǂݔ�΂�
            buf += padding;
        }
    }
    else {                             
        //  �J���[�p���b�g���g�p����ꍇ
        for (int i = start_y ; i < stop_y ; i++) {
            int shift = 8;
            for(int j = 0 ; j < x ; j++){
                shift -= color_bit;
                int p = *buf >> shift & mask;
                if (shift <= 0) {
                    shift = 8;
                    buf++;
                }
                image->b_[j + i * x * sign_y] = rgbq[p].blue_;
                image->g_[j + i * x * sign_y] = rgbq[p].green_;
                image->r_[j + i * x * sign_y] = rgbq[p].red_;
            }
            if(shift != 8){
                buf++;
            }
            buf += padding;
        }
    }

    /* ------------------------- ���ׂĐ��� ---------------------------- */
    free(rgbq   );
    free(buf_top);
    printf("read success.\n");
    return image;
}







#endif // IMG_BITMAP_HPP

