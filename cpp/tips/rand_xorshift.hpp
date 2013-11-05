/* -------------------------------------------------------------------------------
	���� x or shift 128bit����

---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_XORSHIFT_INCLUDED
#define HPP_RAND_XORSHIFT_INCLUDED

namespace nd {

// =================================================================
//	x or shift �ɂ�闐���W�F�l���[�^
class RandXorShift {

// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	//	�R���X�g���N�^
	RandXorShift( const unsigned long seed );
	
	//	�f�X�g���N�^
	~RandXorShift();


// -----------------------------------------------------------------
//	���J���\�b�h
public:
	//	32bit �����Ȃ������̗������擾
	unsigned long getU32();		// R : �擾�l

	
// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	unsigned long x_;
	unsigned long y_;
	unsigned long z_;
	unsigned long w_;
};


} // namespace nd

#endif // HPP_RAND_XORSHIFT_INCLUDED
