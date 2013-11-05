/* -------------------------------------------------------------------------------
	乱数 x or shift 128bit周期

---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_XORSHIFT_INCLUDED
#define HPP_RAND_XORSHIFT_INCLUDED

namespace nd {

// =================================================================
//	x or shift による乱数ジェネレータ
class RandXorShift {

// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
public:
	//	コンストラクタ
	RandXorShift( const unsigned long seed );
	
	//	デストラクタ
	~RandXorShift();


// -----------------------------------------------------------------
//	公開メソッド
public:
	//	32bit 符号なし整数の乱数を取得
	unsigned long getU32();		// R : 取得値

	
// -----------------------------------------------------------------
//	メンバ変数
private:
	unsigned long x_;
	unsigned long y_;
	unsigned long z_;
	unsigned long w_;
};


} // namespace nd

#endif // HPP_RAND_XORSHIFT_INCLUDED
