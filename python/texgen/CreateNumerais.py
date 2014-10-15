#!/usr/bin/python
# coding: UTF-8


#import
import codecs
import cairo
import os
from PIL import Image



#各種定義
png_filename = "font_texture.png"
header_filename = "font_texture.hpp"
font_name = "Osaka"
font_size = 32


#cairoの画像サーフェスを作成
imagesize = (2048, 2048)
surface = cairo.ImageSurface(cairo.FORMAT_ARGB32, *imagesize)
cr = cairo.Context(surface)
padding = 3


#フォントを選択
cr.select_font_face(font_name, cairo.FONT_SLANT_NORMAL, cairo.FONT_WEIGHT_BOLD)
cr.set_font_size(font_size)
cr.set_source_rgb(1,1,1)

#テクスチャファイルにメトリックスを不可するための文字列
glyphs = '''
#include <cstdint>

struct GlyphPosition {
	int16_t x_;
	int16_t y_;
};
struct GlyphMetrics {
	int8_t x_bearing_;
	int8_t y_bearing_;
	int8_t width_;
	int8_t height_;
	int8_t x_advance_;
	int8_t y_advance_;
};
struct Glyph {
	GlyphPosition position_;
	GlyphMetrics metrics_;
	const char* char_;
};
static const Glyph GLYPHS[] = {
'''

# charsetのグリフを描画しメトリックスを書き出す
# 使う文字セットは外部ファイルから読み込み
charset_file = codecs.open('charset.txt', 'r', 'utf-8')
charset_line = charset_file.readline()

x, y = 0, 0
while charset_line:
	#改行コード除去
	charset_line = charset_line.replace('\n','')
	charset_line = charset_line.replace('\r','')
	charset_line = charset_line.replace('\t','')
	charset_line = charset_line.replace(u' ','')
	charset_line = charset_line.replace(u'　','')
	for character in charset_line:
		extents = cr.text_extents(character)
		x_bearing, y_bearing, width, height, x_advance, y_advance = extents
		#描画位置計算
		if x + width > imagesize[0]:
			x = 0
			y += font_size + padding	

		# GlyphPosition書き出し
		glyphs += '   {{ %4d, %4d }, ' % (x,y)

		# GlyphMetrics書き出し
		glyphs += '{%2d, %3d, %2d, %2d, %2d, %2d},' % extents

		# char_idx書き出し
		glyphs += ' u8\"%s\"},\n' %character
		
		# 閉じる
		cr.save()
		cr.translate(x, y-y_bearing)
		cr.show_text(character)
		cr.fill()
		cr.restore()
		x += width + padding
	charset_line = charset_file.readline()
glyphs += '};'

#アルファチャンネルを抽出しプレビュー画像を作成
surface.write_to_png(png_filename)
image = Image.open(png_filename)
image.load();
image.split()[3].save(png_filename)
os.system("open " + png_filename);


#画像データをヘッダ形式に変換
os.system('PVRTexTool -h -yflip1 -fOGL8 -i' + png_filename)


#ヘッダファイルとして書き出す
headerFile = codecs.open(header_filename, 'w', 'utf-8');
headerFile.write(glyphs)
headerFile.close()
