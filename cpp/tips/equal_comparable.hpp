/* -------------------------------------------------------------------------------
	== != ��r���Z�q�������� CRTP

---------------------------------------------------------------------------------*/

#ifndef HPP_EQUAL_COMPARABLE_INCLUDED
#define HPP_EQUAL_COMPARABLE_INCLUDED

namespace nd {

// =================================================================
//	== != ��r���Z�q����
template <class T>
class EqualComparable {

	
	//	�p����ł� isEqualCompare()�֐�����������K�v������܂�
	// virtual bool isEqualCompare( const T& ) = 0;
	
	
	// *************************************************************************
	// T ���m�� == ��r
	friend bool operator == ( 
		const T& lhs,
		const T& rhs
		){
		
		return ( lhs.isEqualCompare( rhs ) );
	}

	// *************************************************************************
	// T ���m�� != ��r
	friend bool operator != (
		const T& lhs,
		const T& rhs
		){
		
		return ( !lhs.isEqualCompare( rhs ) );	
	}
};


} // namespace nd

#endif // HPP_EQUAL_COMPARABLE_INCLUDED
