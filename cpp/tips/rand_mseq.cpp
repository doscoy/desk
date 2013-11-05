/* -------------------------------------------------------------------------------
	�����@M�n�񗐐�
	31bit ����
---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	�C���N���[�h
#include "rand_mseq.hpp"
#include <stdio.h>


namespace {

//	M�n�񐶐��ׂ̈̑������T���v�� (p,q) 
//	(2,1) (3,1) (4,1) (7,1) (17,3) (23,5) (31,3) (35,2) (41,20) (63,5) (65,32) (127,63) (255,82) (524,167) (756,19)

//
const unsigned long FIX_P = 31;
const unsigned long FIX_Q = 3;
const unsigned long FIX_MASK = 0x7fffffff;	// p = 31 �ȊO�̎��� ((1 << FIX_P ) - 1);

}	// unname namespace




namespace nd {

// *************************************************************************
//	�R���X�g���N�^
RandMseq::RandMseq(
	const unsigned long seed		// I : �����̎�
	)
	: seed_( seed )
	{
	// none
}

// *************************************************************************
//	�f�X�g���N�^
RandMseq::~RandMseq()
{
	// none
}

// *************************************************************************
//	�����擾
unsigned long RandMseq::getU32()
{
	unsigned long s = seed_;
	unsigned long bit = ( ( s >> ( FIX_P -1) )  ^  ( s >> ( FIX_Q -1) ) ) & 1;
	seed_ = ( (s << 1) | bit ) & FIX_MASK;

	return ( seed_ );
}


} // namespace nd




