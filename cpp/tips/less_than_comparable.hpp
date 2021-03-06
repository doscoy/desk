/* -------------------------------------------------------------------------------
	< > <= >= 比較演算子自動作成 CRTP
---------------------------------------------------------------------------------*/

#ifndef HPP_LESS_THAN_COMPARABLE_INCLUDED
#define HPP_LESS_THAN_COMPARABLE_INCLUDED

namespace nd {

template <class T>
class LessThanComparable
{
	// 継承先では < を作成する必要があります。
	//	virtual bool isLessThanCompare( const T& lhs, const T& rhs ) = 0;

	// *************************************************************************
	//	<
	friend bool operator <( 
		const T& lhs,
		const T& rhs
		){
		
		return ( lhs.isLessThanCompare( rhs ) );	
	}

	// *************************************************************************
	//	> 
	friend bool operator >( 
		const T& lhs,
		const T& rhs
		){
		
		return ( rhs.isLessThanCompare( lhs ) );	
	}

	// *************************************************************************
	//	<=
	friend bool operator <=(
		const T& lhs,
		const T& rhs
		){
		
		return ( !rhs.isLessThanCompare( lhs ) );	
	}
	
	// *************************************************************************
	//	>=
	friend bool operator >=(
		const T& lhs,
		const T& rhs
		){
		
		return ( !lhs.isLessThanCompare( rhs ) );	
	}
	
};

} // namespace nd



#endif // HPP_LESS_THAN_COMARABLE_INCLUDED
