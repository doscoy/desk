/* -------------------------------------------------------------------------------
	2進数定数サポート
---------------------------------------------------------------------------------*/

#ifndef HPP_BINARY_CONST_INCLUDED
#define HPP_BINARY_CONST_INCLUDED

namespace nd {

// =================================================================
//	２進数定数ジェネレータ
//	例　30を2進数(11110)で代入
//		int a = BinaryConst<11110>::value
//
template<int n>
struct BinaryConst{
	enum{
		value = n % 8 + ( BinaryConst<n/8>::value << 1 )
	};
};
template<>
struct BinaryConst<0>{
	enum{
		value = 0
	};
};


} // namespace nd


// -----------------------------------------------------------------
//	マクロ化 実際にユーザーが使うのはこちら
//
//	コンパイル時に値が決定され定数化されますので実行時コストはありません。
//	2進数に見える値も実際にはただの10進整数値なのでint最大値(10桁)
//	を超えることはできません。
//	ですので大きな値を定義したいときは8bit区切りで指定します
#define _0b8(n1)				((int)nd::BinaryConst<0##n1>::value)
#define _0b16(n2,n1)			((_0b8(n2)<<8  | _0b8(n1)))
#define _0b24(n3,n2,n1)			((_0b8(n3)<<16 | _0b16(n2,n1)))
#define _0b32(n4,n3,n2,n1)		((_0b8(n4)<<24 | _0b24(n3,n2,n1)))


#endif // HPP_BINARY_CONST_INCLUDED
