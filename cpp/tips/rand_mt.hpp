/* -------------------------------------------------------------------------------
	�����@�����Z���k�E�c�C�X�^
	mt19937ar-cok.c�Ƃ��Ēm���Ă�������̈ڐA�ł��B
	���̎������V���v���ɂ��Ă���A32bit�ȏ�̏������q��^���镔����
	����Ă���܂��B
	BSD���C�Z���X�ł��i http://www.opensource.org/licenses/bsd-license.php �j
	
---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_MT_INCLUDED
#define HPP_RAND_MT_INCLUDED

namespace nd {

// =================================================================
//	�����Z���k�E�c�C�X�^�ɂ�闐���W�F�l���[�^
class RandMT {

// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	//	�R���X�g���N�^
	explicit RandMT( 
		const unsigned long seed	// I : �����̎�
	);
	
	//	�f�X�g���N�^
	~RandMT();
	
// -----------------------------------------------------------------
//	���J���\�b�h
public:
	//	32bit �������������̗������擾
	unsigned long getU32();	// R : �擾�l
	
// -----------------------------------------------------------------
//	����J���\�b�h
private:
	void nextState();


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	enum {
		MAX_WORK = 624,
	};
	unsigned long state_[MAX_WORK];
	int left_;
	unsigned long* next_;

};

} // namespace nd


#endif // HPP_RAND_MT_INCLUDED
