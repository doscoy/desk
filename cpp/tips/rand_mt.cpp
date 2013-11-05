/* -------------------------------------------------------------------------------
	�����@�����Z���k�E�c�C�X�^
	mt19937ar-cok.c�Ƃ��Ēm���Ă�������̈ڐA�ł��B
	BSD���C�Z���X�ł��i http://www.opensource.org/licenses/bsd-license.php �j

---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	�C���N���[�h
#include "rand_mt.hpp"

namespace {

static const int FIX_M = 397;
static const int MATRIX_A = 0x9908b0dfUL;
static const int UMASK = 0x80000000UL;
static const int LMASK = 0x7fffffffUL;

// *************************************************************************
//	�r�b�g�~�b�N�X
inline unsigned long mixBits( 
	const unsigned long u,
	const unsigned long v
	){
	
	return ( ( u & UMASK ) | ( v & LMASK ));
}

// *************************************************************************
//	�c�C�X�g
inline unsigned long twistBits(
	const unsigned long u,
	const unsigned long v
	){
	return ( ( mixBits( u, v ) >> 1 )  ^ ( v & 1 ? MATRIX_A : 0) );
}


} // unnname namespace




namespace nd {


// *************************************************************************
//	�R���X�g���N�^
RandMT::RandMT(
	const unsigned long seed	// I : �����̎�
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
//	�f�X�g���N�^
RandMT::~RandMT()
{
}

// *************************************************************************
//	���̏�ԂɑJ��
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
//	32bit�����Ȃ������̗������擾
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



