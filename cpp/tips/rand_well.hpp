/* -------------------------------------------------------------------------------
	�����@WELL�A���S���Y��
---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_WELL_INCLUDED
#define HPP_RAND_WELL_INCLUDED

namespace nd {

// =================================================================
//	WELL�A���S���Y���ɂ��[������
class RandWell {
// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	//	�R���X�g���N�^
	explicit RandWell(
		const unsigned long seed	// I : �����̎�
	);
	//	�f�X�g���N�^
	~RandWell();

// -----------------------------------------------------------------
//	���J���\�b�h
public:
	//	32bit �����Ȃ������擾
	unsigned long getU32();

// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	unsigned long state_[16];
	unsigned int index_;

};

} // namespace nd

#endif // HPP_RAND_WELL_INCLUDED
