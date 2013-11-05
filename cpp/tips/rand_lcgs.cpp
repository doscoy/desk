/* -------------------------------------------------------------------------------
	乱数　線形合同法
---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	インクルード
#include "rand_lcgs.hpp"

namespace {

const unsigned long FIX_A = 214013L;
const unsigned long FIX_B = 2531011L;

// *************************************************************************
//	乱数の種を混ぜる
inline unsigned long mixSeed(	// R : 混ざった種値
	const unsigned long seed	// I : 元の種値
	){
	//	Xn+1 = A x Xn + B
	return ( FIX_A * seed + FIX_B );
}

} // unname namespace








namespace nd {

// *************************************************************************
//	コンストラクタ
RandLcgs::RandLcgs(
	const unsigned long seed	// I : 乱数の種
	)
	: seed_( seed )
	{
	// none
}

// *************************************************************************
//	デストラクタ
RandLcgs::~RandLcgs()
{
	// none
}

// *************************************************************************
//	u32 乱数取得
unsigned long RandLcgs::getU32()		// R : 取得値
{
	unsigned long uval = getU16() << 16;
	unsigned long lval = getU16();
	return ( uval | lval );
}

// *************************************************************************
//	u16 乱数取得
//		線形合同法は下位ビットの分布が荒いので上位ビットを使用します
unsigned short RandLcgs::getU16()
{
	seed_ = mixSeed( seed_ );
	return ( static_cast<unsigned short>( (seed_ >> 16) & 0xffff ) );
}


} // namespace nd





