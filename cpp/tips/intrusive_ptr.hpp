/* -------------------------------------------------------------------------------
	�N���^�Q�ƃJ�E���g�����̃X�}�[�g�|�C���^
	�I�u�W�F�N�g���̎Q�ƃJ�E���g�@�\�𗘗p���ĊǗ����s�Ȃ��܂�
---------------------------------------------------------------------------------*/

#ifndef HPP_INTRUSIVE_PTR_INCLUDED
#define HPP_INTRUSIVE_PTR_INCLUDED

// -----------------------------------------------------------------
//	�C���N���[�h
#include <algorithm>	// for std::swap
#include <cassert>		// for assert

namespace nd {



// =================================================================
//	�N���^�Q�ƃJ�E���g�X�}�[�g�|�C���^
template <typename T>
class intrusive_ptr
{
// -----------------------------------------------------------------
//	���J�^��`
public:
	typedef T element_type;
	
// -----------------------------------------------------------------
//	�N���X���^��`
private:
	typedef intrusive_ptr this_type;


// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	// *************************************************************************
	//	�f�t�H���g�R���X�g���N�^
	intrusive_ptr()
		: px_( NULL )
		{}
	
	// *************************************************************************
	//	�R���X�g���N�^
	intrusive_ptr(
		T* p,
		bool add_ref = true
		) 
		: px_( p )
		{
		
		if ( px_ != NULL && add_ref ){
			px_->addReference();
		}
	}
	
	// *************************************************************************
	//	�R�s�[�R���X�g���N�^
	intrusive_ptr(
		const intrusive_ptr& rhs
		)
		: px_( rhs.px_ )
		{
		if ( px_ != 0 ){
			px_->addReference();
		} 
	}

	// *************************************************************************
	//	�f�X�g���N�^
	~intrusive_ptr()
	{
		if ( px_ != 0 ){
			px_->releaseReference();
		}
	}
	
	
// -----------------------------------------------------------------
//	�I�y���[�^
public:
	
	// *************************************************************************
	//	intrusive_ptr���m�̑�����Z�q
	intrusive_ptr& operator =(
		const intrusive_ptr& rhs
		){
		//	��������̎����̓R�s�[�R���X�g���N�^�ɔC����
        this_type( rhs ).swap( *this );
        return ( *this );
    }

	// *************************************************************************
	//	T* �Ƃ̑�����Z�q
    intrusive_ptr & operator =( T* rhs )
    {
		//	��������̎����̓R�s�[�R���X�g���N�^�ɔC����
        this_type( rhs ).swap( *this );
        return ( *this );
    }


	// *************************************************************************
	//	�Q�Ɖ��Z�q
    T& operator *() const
    {
        assert( px_ != 0 );
        return ( *px_ );
    }
	
	// *************************************************************************
	//	�A���[���Z�q
    T* operator ->() const
    {
        assert( px_ != 0 );
        return ( px_ );
    }


// -----------------------------------------------------------------
//	���J���\�b�h
public:

	// *************************************************************************
	//	���|�C���^�擾
    T* get() const
    {
        return ( px_ );
    }

	// *************************************************************************
	//	���Z�b�g
	void reset( T * rhs )
    {
        this_type( rhs ).swap( *this );
    }

	// *************************************************************************
	//	�X���b�v
    void swap(
		intrusive_ptr& rhs
		){
		std::swap( rhs.px_, px_ );
    }


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	T*	px_;

};


// *************************************************************************
//	�O���[�o����r�I�y���[�^

//	intrusive_ptr���m ==
template<class T, class U> 
inline bool operator ==(
	const intrusive_ptr<T>& a,		// I : ��r�Ώ� a
	const intrusive_ptr<U>& b		// I : ��r�Ώ� b
	){
    return ( a.get() == b.get() );
}

//	intrusive_ptr���m !=
template<class T, class U> 
inline bool operator !=( 
	const intrusive_ptr<T>& a,		// I : ��r�Ώ� a
	const intrusive_ptr<U>& b		// I : ��r�Ώ� b
	){
    return ( a.get() != b.get() );
}

//	intrusive_ptr �Ɛ��|�C���^ ==
template<class T, class U> 
inline bool operator ==(
	const intrusive_ptr<T>& a,		// I : ��r�Ώ� a
	const U* const b				// I : ��r�Ώ� b
	){
    return ( a.get() == b );
}

//	intrusive_ptr �Ɛ��|�C���^ !=
template<class T, class U> 
inline bool operator !=(
	const intrusive_ptr<T>& a,		// I : ��r�Ώ� a
	const U* const b				// I : ��r�Ώ� b
	){
    return ( a.get() != b );
}

//	���|�C���^��intrusive_ptr  ==
template<class T, class U> 
inline bool operator ==(
	const T* const a,				// I : ��r�Ώ� a
	const intrusive_ptr<U>& b		// I : ��r�Ώ� b
	){
    return a == b.get();
}

//	���|�C���^��intrusive_ptr  !=
template<class T, class U> 
inline bool operator !=(
	const T* const a,				// I : ��r�Ώ� a			
	const intrusive_ptr<U>& b		// I : ��r�Ώ� b
	){
    return ( a != b.get() );
}



} // namespace nd

#endif // HPP_INTRUSIVE_PTR_INCLUDED
