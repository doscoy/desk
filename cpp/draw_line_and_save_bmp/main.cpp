
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#include "img_bitmap.hpp"
#include "line_draw.hpp"



//  -o �o�̓t�@�C��
//  -p ���W
//  -w �L�����p�X��
//  -h �L�����p�X����
//  -a �A���`�G�C���A�X
//  -b �j��
//  �g�p���@
//      -o c:\xxx.bmp -p 10 8 76 200 -w 200 -h 300
int main(int argc,char* argv[])
{   
    char* OUTPUT_PATH_OPTION = "-o";    //  �o�̓t�@�C��
    char* POINT_OPTION = "-p";          //  �|�C���g�w��
    char* AA_OPTION = "-a";             //  �A���`�G�C���A�X
    char* BL_OPTION = "-b";             //  �j��
    char* WIDTH_OPTION = "-w";          //  �L�����p�X��
    char* HEIGHT_OPTION = "-h";         //  �L�����p�X����
    

    bool output_option = false;
    bool point_option = false;
    bool width_option = false;
    bool height_option = false;

    bool line_aa = false;
    bool line_bl = false;

    int point[4] = {4, 8, 60, 30};
    int width = 200;
    int height = 200;


    //  �o�̓p�X
    const int MAX_PATH_LEN = 80;
    char out_path[MAX_PATH_LEN];
    //  �f�t�H���g�p�X�̐ݒ�
    char* DEFAULT_OUTPUT_PATH = "./default.bmp";
    strcpy_s(out_path, MAX_PATH_LEN, DEFAULT_OUTPUT_PATH);

    while (*argv) {
        if (output_option) {
            output_option = false;
            strcpy_s(out_path, MAX_PATH_LEN, *argv);
        }
        else if (point_option) {
            point_option = false;
            point[0] = std::atoi(*argv);
            ++argv;
            point[1] = std::atoi(*argv);
            ++argv;
            point[2] = std::atoi(*argv);
            ++argv;
            point[3] = std::atoi(*argv);

            printf("%d %d %d %d\n", point[0], point[1], point[2], point[3]);

        }
        else if (width_option) {
            //  �L�����p�X�̉����擾
            width_option = false;
            printf("width %d -> %d\n", width, std::atoi(*argv));
            width = std::atoi(*argv);
        }
        else if (height_option) {
            //  �L�����p�X�̍����擾
            height_option = false;
            printf("height %d -> %d\n", height, std::atoi(*argv));
            height = std::atoi(*argv);
        }


        if (!strcmp(*argv, OUTPUT_PATH_OPTION)) {
            //  �A�E�g�v�b�g�I�v�V����
            output_option = true;
        }
        else if (!strcmp(*argv, POINT_OPTION)) {
            //  �|�C���g�I�v�V����
            point_option = true;
        }
        else if (!strcmp(*argv, WIDTH_OPTION)) {
            //  �L�����p�X��
            width_option = true;
        }
        else if (!strcmp(*argv, HEIGHT_OPTION)) {
            //  �L�����p�X��
            height_option = true;
        }
        else if (!strcmp(*argv, AA_OPTION)) {
            //  �A���`�G�C���A�X�t��
            line_aa = true;
        }
        else if (!strcmp(*argv, BL_OPTION)) {
            //  �j��
            line_bl = true;
        }

        ++argv;
    }

    // --------------------------------------------------
    //  ��������

    //  �L�����p�X�쐬
    Image* image = Image::createImage(width, height);

    //  �h��Ԃ�
    image->fill(Color::black());

    //  ��������
    if (line_bl) {
        //  �j��
        drawBrokenLine(image, point[0], point[1], point[2], point[3], Color::red());
    }
    else if (line_aa) {
        //  �A���`�G�C���A�X�t��
        drawLineAA(image, point[0], point[1], point[2], point[3], Color::red());
    }
    else {
        //  �ʏ�
        drawLine2(image, point[0], point[1], point[2], point[3], Color::red());
    }


    //  -----------------------------------------------
    //  bmp�ۑ�

    //  �t�@�C���X�g���[���J��
    std::ofstream ofs(out_path, std::ios::out | std::ios::binary);

    //  �ۑ�
    serializeBmp(&ofs, image);


    //  �L�����p�X�j��
    image->destroy();


    return 0;
}