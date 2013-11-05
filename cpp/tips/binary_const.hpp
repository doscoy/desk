/* -------------------------------------------------------------------------------
	2�i���萔�T�|�[�g
---------------------------------------------------------------------------------*/

#ifndef HPP_BINARY_CONST_INCLUDED
#define HPP_BINARY_CONST_INCLUDED

namespace nd {

// =================================================================
//	�Q�i���萔�W�F�l���[�^
//	��@30��2�i��(11110)�ő��
//		int a = BinaryConst<11110>::value
//
template<int n>
struct BinaryConst{
	enum{
		value = n % 8 + ( BinaryConst<n/8>::value << 1 )
	};
};
template<>
struct BinaryConst<0>{
	enum{
		value = 0
	};
};


} // namespace nd


// -----------------------------------------------------------------
//	�}�N���� ���ۂɃ��[�U�[���g���̂͂�����
//
//	�R���p�C�����ɒl�����肳��萔������܂��̂Ŏ��s���R�X�g�͂���܂���B
//	2�i���Ɍ�����l�����ۂɂ͂�����10�i�����l�Ȃ̂�int�ő�l(10��)
//	�𒴂��邱�Ƃ͂ł��܂���B
//	�ł��̂ő傫�Ȓl���`�������Ƃ���8bit��؂�Ŏw�肵�܂�
#define _0b8(n1)				((int)nd::BinaryConst<0##n1>::value)
#define _0b16(n2,n1)			((_0b8(n2)<<8  | _0b8(n1)))
#define _0b24(n3,n2,n1)			((_0b8(n3)<<16 | _0b16(n2,n1)))
#define _0b32(n4,n3,n2,n1)		((_0b8(n4)<<24 | _0b24(n3,n2,n1)))


#endif // HPP_BINARY_CONST_INCLUDED
