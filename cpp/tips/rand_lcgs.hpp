/* -------------------------------------------------------------------------------
	�����@���`�����@

---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_LCGS_INCLUDED
#define HPP_RAND_LCGS_INCLUDED


namespace nd {

// =================================================================
//	���`�����@�ɂ�闐���W�F�l���[�^
//	Linear congruential generators
class RandLcgs {

// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	//	�R���X�g���N�^
	explicit RandLcgs(
		const unsigned long seed	// I : �����̎�
	);
	
	//	�f�X�g���N�^
	~RandLcgs();


// -----------------------------------------------------------------
//	���J���\�b�h
public:
	//	32bit �����Ȃ������̗������擾
	unsigned long getU32();		// R : �擾�l

	//	16bit �����Ȃ������̗������擾
	unsigned short getU16();	// R : �擾�l
	
	
// -----------------------------------------------------------------
//	����J���\�b�h
private:
	unsigned long seed_;
};


} // namespace nd


#endif // HPP_RAND_LCGS_INCLUDED
