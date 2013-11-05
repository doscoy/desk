/* -------------------------------------------------------------------------------
	�����@���`�����@
---------------------------------------------------------------------------------*/

// -----------------------------------------------------------------
//	�C���N���[�h
#include "rand_lcgs.hpp"

namespace {

const unsigned long FIX_A = 214013L;
const unsigned long FIX_B = 2531011L;

// *************************************************************************
//	�����̎��������
inline unsigned long mixSeed(	// R : ����������l
	const unsigned long seed	// I : ���̎�l
	){
	//	Xn+1 = A x Xn + B
	return ( FIX_A * seed + FIX_B );
}

} // unname namespace








namespace nd {

// *************************************************************************
//	�R���X�g���N�^
RandLcgs::RandLcgs(
	const unsigned long seed	// I : �����̎�
	)
	: seed_( seed )
	{
	// none
}

// *************************************************************************
//	�f�X�g���N�^
RandLcgs::~RandLcgs()
{
	// none
}

// *************************************************************************
//	u32 �����擾
unsigned long RandLcgs::getU32()		// R : �擾�l
{
	unsigned long uval = getU16() << 16;
	unsigned long lval = getU16();
	return ( uval | lval );
}

// *************************************************************************
//	u16 �����擾
//		���`�����@�͉��ʃr�b�g�̕��z���r���̂ŏ�ʃr�b�g���g�p���܂�
unsigned short RandLcgs::getU16()
{
	seed_ = mixSeed( seed_ );
	return ( static_cast<unsigned short>( (seed_ >> 16) & 0xffff ) );
}


} // namespace nd





