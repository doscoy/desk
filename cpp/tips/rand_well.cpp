/* -------------------------------------------------------------------------------
	�����@WELL�A���S���Y��
---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	�C���N���[�h
#include "rand_well.hpp"

namespace nd {

// *************************************************************************
//	�R���X�g���N�^
RandWell::RandWell(
	const unsigned long seed	// I : �����̎�
	)
	: index_( 0 )
	{

	//	�����l�͉��ł��ǂ��B
	//	�A���S�� 0 �ł̓_���B�o����ΑS�Ĉ�����l���]�܂���
	state_[0] = seed;
	state_[1] = 1;
	state_[2] = 2;
	state_[3] = 3;
	state_[4] = 4;
	state_[5] = 5;
	state_[6] = 6;
	state_[7] = 7;
	state_[8] = 8;
	state_[9] = 9;
	state_[10] = 10;
	state_[11] = 11;
	state_[12] = 12;
	state_[13] = 13;
	state_[14] = 14;
	state_[15] = 15;
}

// *************************************************************************
//	�f�X�g���N�^
RandWell::~RandWell()
{
}

// *************************************************************************
//	32bit �������������擾
unsigned long RandWell::getU32()
{
	//	index_�ɂ͂悭�A�N�Z�X����̂ŃX�^�b�N�Ɏ���
	unsigned int idx = index_;

	// -----------------------------------------------------------------
	//	WELL�̃L���@�����z�񐶐�
	unsigned long a = state_[idx];
	unsigned long c = state_[(idx+13) & 15];
	unsigned long b = a ^ c ^ (a<<16) ^ (c<<15);
	c = state_[( idx + 9 ) & 15];
	c ^= ( c >> 11 );
	a = state_[idx] = b ^ c;
	unsigned long d = a ^ ( (a << 5 ) & 0xDA442D20UL );
	idx = ( idx + 15 ) & 15;
	a = state_[idx];
	state_[idx] = a ^ b ^ d ^ ( a << 2 ) ^ ( b << 18 ) ^ ( c << 28 );

	
	
	//	index�X�V
	index_ = idx;
	
	//	����
	return ( state_[index_] );
		
}


} // namespace nd

