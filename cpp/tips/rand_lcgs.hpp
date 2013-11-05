/* -------------------------------------------------------------------------------
	乱数　線形合同法

---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_LCGS_INCLUDED
#define HPP_RAND_LCGS_INCLUDED


namespace nd {

// =================================================================
//	線形合同法による乱数ジェネレータ
//	Linear congruential generators
class RandLcgs {

// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
public:
	//	コンストラクタ
	explicit RandLcgs(
		const unsigned long seed	// I : 乱数の種
	);
	
	//	デストラクタ
	~RandLcgs();


// -----------------------------------------------------------------
//	公開メソッド
public:
	//	32bit 符号なし整数の乱数を取得
	unsigned long getU32();		// R : 取得値

	//	16bit 符号なし整数の乱数を取得
	unsigned short getU16();	// R : 取得値
	
	
// -----------------------------------------------------------------
//	非公開メソッド
private:
	unsigned long seed_;
};


} // namespace nd


#endif // HPP_RAND_LCGS_INCLUDED
