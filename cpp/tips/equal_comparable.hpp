/* -------------------------------------------------------------------------------
	== != ”äŠr‰‰Zq©“®¶¬ CRTP

---------------------------------------------------------------------------------*/

#ifndef HPP_EQUAL_COMPARABLE_INCLUDED
#define HPP_EQUAL_COMPARABLE_INCLUDED

namespace nd {

// =================================================================
//	== != ”äŠr‰‰Zq¶¬
template <class T>
class EqualComparable {

	
	//	Œp³æ‚Å‚Í isEqualCompare()ŠÖ”‚ğÀ‘•‚·‚é•K—v‚ª‚ ‚è‚Ü‚·
	// virtual bool isEqualCompare( const T& ) = 0;
	
	
	// *************************************************************************
	// T “¯m‚Ì == ”äŠr
	friend bool operator == ( 
		const T& lhs,
		const T& rhs
		){
		
		return ( lhs.isEqualCompare( rhs ) );
	}

	// *************************************************************************
	// T “¯m‚Ì != ”äŠr
	friend bool operator != (
		const T& lhs,
		const T& rhs
		){
		
		return ( !lhs.isEqualCompare( rhs ) );	
	}
};


} // namespace nd

#endif // HPP_EQUAL_COMPARABLE_INCLUDED
