/* -------------------------------------------------------------------------------
	���� M�n�񗐐�
	������ 31 bit�ł��B
---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_MSEQ_INCLUDED
#define HPP_RAND_MSEQ_INCLUDED

namespace nd {

class RandMseq {
// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	//	�R���X�g���N�^
	explicit RandMseq(
		const unsigned long seed		// I : �����̎�
	);
	//	�f�X�g���N�^
	~RandMseq();

// -----------------------------------------------------------------
//	���J���\�b�h
public:
	unsigned long getU32();


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	unsigned long seed_;
};



} // namespace nd


#endif // HPP_RAND_MSEQ_INCLUDED
