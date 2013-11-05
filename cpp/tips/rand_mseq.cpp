/* -------------------------------------------------------------------------------
	乱数　M系列乱数
	31bit 周期
---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	インクルード
#include "rand_mseq.hpp"
#include <stdio.h>


namespace {

//	M系列生成の為の多項式サンプル (p,q) 
//	(2,1) (3,1) (4,1) (7,1) (17,3) (23,5) (31,3) (35,2) (41,20) (63,5) (65,32) (127,63) (255,82) (524,167) (756,19)

//
const unsigned long FIX_P = 31;
const unsigned long FIX_Q = 3;
const unsigned long FIX_MASK = 0x7fffffff;	// p = 31 以外の時は ((1 << FIX_P ) - 1);

}	// unname namespace




namespace nd {

// *************************************************************************
//	コンストラクタ
RandMseq::RandMseq(
	const unsigned long seed		// I : 乱数の種
	)
	: seed_( seed )
	{
	// none
}

// *************************************************************************
//	デストラクタ
RandMseq::~RandMseq()
{
	// none
}

// *************************************************************************
//	乱数取得
unsigned long RandMseq::getU32()
{
	unsigned long s = seed_;
	unsigned long bit = ( ( s >> ( FIX_P -1) )  ^  ( s >> ( FIX_Q -1) ) ) & 1;
	seed_ = ( (s << 1) | bit ) & FIX_MASK;

	return ( seed_ );
}


} // namespace nd




