/* -------------------------------------------------------------------------------
	���l������̑��ݕϊ��L���X�g
		�ΏۃI�u�W�F�N�g�� << >> (�X�g���[�����Z�q) ���T�|�[�g���Ă����
		��{�^�ȊO�ł��g�����Ƃ��ł��܂�
		������ boost::lexical_cast �Ɠ��l�ł�
	
		int a = lexical_cast<int>( "123" );
		std::string b = lexical_cast<std::string>( 50 );
---------------------------------------------------------------------------------*/

#ifndef HPP_LEXICAL_CAST_INCLUDED
#define HPP_LEXICAL_CAST_INCLUDED

// -----------------------------------------------------------------
//	�C���N���[�h
#include <sstream>


// *************************************************************************
//	���L�V�J���L���X�g
template < class To, class From >
inline To lexical_cast(		// R : �ϊ���
	From from				// I : �ϊ��O
	){
	
	To result;
	
	std::stringstream ss;
	ss << from;
	ss >> result;
	
	return ( result );
}


#endif // HPP_LEXICAL_CAST_INCLUDED
