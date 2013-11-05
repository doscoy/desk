/* -------------------------------------------------------------------------------
	数値文字列の相互変換キャスト
		対象オブジェクトが << >> (ストリーム演算子) をサポートしていれば
		基本型以外でも使うことができます
		書式は boost::lexical_cast と同様です
	
		int a = lexical_cast<int>( "123" );
		std::string b = lexical_cast<std::string>( 50 );
---------------------------------------------------------------------------------*/

#ifndef HPP_LEXICAL_CAST_INCLUDED
#define HPP_LEXICAL_CAST_INCLUDED

// -----------------------------------------------------------------
//	インクルード
#include <sstream>


// *************************************************************************
//	レキシカルキャスト
template < class To, class From >
inline To lexical_cast(		// R : 変換後
	From from				// I : 変換前
	){
	
	To result;
	
	std::stringstream ss;
	ss << from;
	ss >> result;
	
	return ( result );
}


#endif // HPP_LEXICAL_CAST_INCLUDED
