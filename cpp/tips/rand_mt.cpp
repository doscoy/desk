/* -------------------------------------------------------------------------------
	乱数　メルセンヌ・ツイスタ
	mt19937ar-cok.cとして知られている実装の移植です。
	BSDライセンスです（ http://www.opensource.org/licenses/bsd-license.php ）

---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	インクルード
#include "rand_mt.hpp"

namespace {

static const int FIX_M = 397;
static const int MATRIX_A = 0x9908b0dfUL;
static const int UMASK = 0x80000000UL;
static const int LMASK = 0x7fffffffUL;

// *************************************************************************
//	ビットミックス
inline unsigned long mixBits( 
	const unsigned long u,
	const unsigned long v
	){
	
	return ( ( u & UMASK ) | ( v & LMASK ));
}

// *************************************************************************
//	ツイスト
inline unsigned long twistBits(
	const unsigned long u,
	const unsigned long v
	){
	return ( ( mixBits( u, v ) >> 1 )  ^ ( v & 1 ? MATRIX_A : 0) );
}


} // unnname namespace




namespace nd {


// *************************************************************************
//	コンストラクタ
RandMT::RandMT(
	const unsigned long seed	// I : 乱数の種
	)
	: left_( 1 )
	, next_( 0 )
	{
	
	
	state_[0] = seed & 0xffffffffUL;
	for ( int i = 1; i < MAX_WORK; ++i ){
		state_[i] = (1812433253UL * (state_[i-1] ^ (state_[i-1] >> 30)) + i); 
	}
}

// *************************************************************************
//	デストラクタ
RandMT::~RandMT()
{
}

// *************************************************************************
//	次の状態に遷移
void RandMT::nextState()
{
	left_ = MAX_WORK;
	next_ = state_;
	
	unsigned long* p = state_;
	for ( int i = MAX_WORK - FIX_M + 1; --i; p++ ){
		*p = p[FIX_M] ^ twistBits( p[0], p[1] );
	}
	
	for ( int i = FIX_M; --i; p++ ){
		*p = p[ MAX_WORK - FIX_M ] ^ twistBits( p[0], p[1] );
	}
	
	*p = p[FIX_M - MAX_WORK] ^ twistBits( p[0], state_[0] );
}




// *************************************************************************
//	32bit符号なし整数の乱数を取得
unsigned long RandMT::getU32()
{
	if ( --left_ == 0 ){
		nextState();
	}
	
	unsigned long rand_num = *next_;
	next_++;
	
	rand_num ^= ( rand_num >> 11 );
    rand_num ^= ( rand_num << 7  ) & 0x9d2c5680UL;
    rand_num ^= ( rand_num << 15 ) & 0xefc60000UL;
    rand_num ^= ( rand_num >> 18 );


	return ( rand_num );	
}





} // namespace nd



