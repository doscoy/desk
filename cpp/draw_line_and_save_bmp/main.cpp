
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

#include "img_bitmap.hpp"
#include "line_draw.hpp"



//  -o 出力ファイル
//  -p 座標
//  -w キャンパス幅
//  -h キャンパス高さ
//  -a アンチエイリアス
//  -b 破線
//  使用方法
//      -o c:\xxx.bmp -p 10 8 76 200 -w 200 -h 300
int main(int argc,char* argv[])
{   
    char* OUTPUT_PATH_OPTION = "-o";    //  出力ファイル
    char* POINT_OPTION = "-p";          //  ポイント指定
    char* AA_OPTION = "-a";             //  アンチエイリアス
    char* BL_OPTION = "-b";             //  破線
    char* WIDTH_OPTION = "-w";          //  キャンパス幅
    char* HEIGHT_OPTION = "-h";         //  キャンパス高さ
    

    bool output_option = false;
    bool point_option = false;
    bool width_option = false;
    bool height_option = false;

    bool line_aa = false;
    bool line_bl = false;

    int point[4] = {4, 8, 60, 30};
    int width = 200;
    int height = 200;


    //  出力パス
    const int MAX_PATH_LEN = 80;
    char out_path[MAX_PATH_LEN];
    //  デフォルトパスの設定
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
            //  キャンパスの横幅取得
            width_option = false;
            printf("width %d -> %d\n", width, std::atoi(*argv));
            width = std::atoi(*argv);
        }
        else if (height_option) {
            //  キャンパスの高さ取得
            height_option = false;
            printf("height %d -> %d\n", height, std::atoi(*argv));
            height = std::atoi(*argv);
        }


        if (!strcmp(*argv, OUTPUT_PATH_OPTION)) {
            //  アウトプットオプション
            output_option = true;
        }
        else if (!strcmp(*argv, POINT_OPTION)) {
            //  ポイントオプション
            point_option = true;
        }
        else if (!strcmp(*argv, WIDTH_OPTION)) {
            //  キャンパス幅
            width_option = true;
        }
        else if (!strcmp(*argv, HEIGHT_OPTION)) {
            //  キャンパス幅
            height_option = true;
        }
        else if (!strcmp(*argv, AA_OPTION)) {
            //  アンチエイリアス付き
            line_aa = true;
        }
        else if (!strcmp(*argv, BL_OPTION)) {
            //  破線
            line_bl = true;
        }

        ++argv;
    }

    // --------------------------------------------------
    //  線を引く

    //  キャンパス作成
    Image* image = Image::createImage(width, height);

    //  塗りつぶし
    image->fill(Color::black());

    //  線を書く
    if (line_bl) {
        //  破線
        drawBrokenLine(image, point[0], point[1], point[2], point[3], Color::red());
    }
    else if (line_aa) {
        //  アンチエイリアス付き
        drawLineAA(image, point[0], point[1], point[2], point[3], Color::red());
    }
    else {
        //  通常
        drawLine2(image, point[0], point[1], point[2], point[3], Color::red());
    }


    //  -----------------------------------------------
    //  bmp保存

    //  ファイルストリーム開く
    std::ofstream ofs(out_path, std::ios::out | std::ios::binary);

    //  保存
    serializeBmp(&ofs, image);


    //  キャンパス破棄
    image->destroy();


    return 0;
}