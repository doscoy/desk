/* -------------------------------------------------------------------------------
	== != 比較演算子自動生成 CRTP

---------------------------------------------------------------------------------*/

#ifndef HPP_EQUAL_COMPARABLE_INCLUDED
#define HPP_EQUAL_COMPARABLE_INCLUDED

namespace nd {

// =================================================================
//	== != 比較演算子生成
template <class T>
class EqualComparable {

	
	//	継承先では isEqualCompare()関数を実装する必要があります
	// virtual bool isEqualCompare( const T& ) = 0;
	
	
	// *************************************************************************
	// T 同士の == 比較
	friend bool operator == ( 
		const T& lhs,
		const T& rhs
		){
		
		return ( lhs.isEqualCompare( rhs ) );
	}

	// *************************************************************************
	// T 同士の != 比較
	friend bool operator != (
		const T& lhs,
		const T& rhs
		){
		
		return ( !lhs.isEqualCompare( rhs ) );	
	}
};


} // namespace nd

#endif // HPP_EQUAL_COMPARABLE_INCLUDED
