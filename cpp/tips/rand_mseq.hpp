/* -------------------------------------------------------------------------------
	乱数 M系列乱数
	周期は 31 bitです。
---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_MSEQ_INCLUDED
#define HPP_RAND_MSEQ_INCLUDED

namespace nd {

class RandMseq {
// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
public:
	//	コンストラクタ
	explicit RandMseq(
		const unsigned long seed		// I : 乱数の種
	);
	//	デストラクタ
	~RandMseq();

// -----------------------------------------------------------------
//	公開メソッド
public:
	unsigned long getU32();


// -----------------------------------------------------------------
//	メンバ変数
private:
	unsigned long seed_;
};



} // namespace nd


#endif // HPP_RAND_MSEQ_INCLUDED
