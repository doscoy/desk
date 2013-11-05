/* -------------------------------------------------------------------------------
	�Q�ƃJ�E���g�t���X�}�[�g�|�C���^�ł��B
	�ێ����Ă���|�C���^�̎Q�Ɛ����O�ɂȂ������Ɏ����I�ɉ�����܂��B
---------------------------------------------------------------------------------*/


#ifndef HPP_SHARED_PTR_INCLUDED
#define HPP_SHARED_PTR_INCLUDED

// -----------------------------------------------------------------
//	�C���N���[�h
#include <algorithm>	// for std::swap
#include <cassert>		// for assert
#include <new>			// for new/delete

namespace nd {

// -----------------------------------------------------------------
//	�N���X�O���錾
template <class T> class weak_ptr;



// =================================================================
//	�Q�ƃJ�E���g�X�}�[�g�|�C���^
template <class T>
class shared_ptr
{
// -----------------------------------------------------------------
//	�N���X���^��`
private:
	typedef shared_ptr<T> this_type;

// -----------------------------------------------------------------
//	���J�^��`
public:
	typedef T element_type;
	typedef T value_type;
	typedef T* pointer;


// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	// *************************************************************************
	//	�f�t�H���g�R���X�g���N�^
	shared_ptr() 
		: px_( NULL )
		, pn_( NULL )
		{}

	// *************************************************************************
	//	�R���X�g���N�^	ptr( p ) �`���ł������������Ă͂����܂���
	explicit shared_ptr(
		T* p		// I : �����A�h���X
		)
		: px_( NULL )
		, pn_( NULL ) {
		
		//	p �ɗL���A�h���X���w�肳��Ă���ꍇ�ɏ�����
		if ( p ) {
			px_ = p;			// �A�h���X�R�s�[
			pn_ = new int(1);	// �Q�ƃJ�E���^����
		}
	}

	// *************************************************************************
	//	�R�s�[�R���X�g���N�^  ptr = r �`���̏�������OK
	shared_ptr( 
		const shared_ptr<T>& r	// �V�F�A����|�C���^
		)
		: px_( r.px_ )
		, pn_( r.pn_ ) 
		{
		
		if ( pn_ ){
			++(*pn_);
		}
	}
	
	// *************************************************************************
	//	�R���X�g���N�^ weak_ptr����쐬
	explicit shared_ptr( 
		const weak_ptr<T>& r
		)
		: px_(r.px_)
		, pn_(r.pn_) 
		{}

	// *************************************************************************
	//	�f�X�g���N�^
	~shared_ptr()
	{
		if ( pn_ ) {
			if (--(*pn_) <= 0) {
				//	�Ō�̎Q�Ƃ��؂ꂽ�̂ŉ��
				delete px_;
				px_ = NULL;
				
				delete pn_;
				pn_ = NULL;
				
	//			printf("����I");
			}
		}
	}


// -----------------------------------------------------------------
//	�I�y���[�^
public:
	// *************************************************************************
	//	�R�s�[
	shared_ptr& operator =(
		const shared_ptr& r
		) {
	
		this_type( r ).swap( *this );
	
		return ( *this );
	}

	// *************************************************************************
	//	�Q�Ɖ��Z�q
	T& operator *() const { 
		assert( px_ ); 
		return *px_; 
	}

	// *************************************************************************
	//	�|�C���^���Z�q
	T* operator ->() const { 
		assert( px_ ); 
		return px_;
	}

	// *************************************************************************
	//	bool ���Z�q
	operator bool() const {
		return ( px_ != NULL );
	}
	bool operator !() const	{
		return ( px_ == NULL );
	}


// -----------------------------------------------------------------
//	���J���\�b�h
public:
	// *************************************************************************
	//	���|�C���^�擾
	T* get() const {		// R : ���|�C���^
		return ( px_ );
	}
	
	// *************************************************************************
	//	���Z�b�g
	void reset( 
		T* p = NULL			// I : ����
		) {
		if ( !p || ( p != px_ ) ){
			this_type( p ).swap( *this );
		}
	}

	// *************************************************************************
	//	�Q�ƃJ�E���g�擾
	int useCount() const {	// R : �Q�Ƃ���Ă��鐔
		return pn_ ? *pn_ : NULL;
	}
		
	// *************************************************************************
	//	���L�������L���Ă��� shared_ptr �����邩����
	bool isUnique() const {	// R : true = �����ȊO�ɓ��e�����L���Ă���shared_ptr������
		return ( useCount() == 1 );
	}
	
	// *************************************************************************
	//	����
	void swap( 
		shared_ptr<T>& other	// I : ��������
		) {
		std::swap( px_, other.px_ );
		std::swap( pn_, other.pn_ );
	}
	
	// *************************************************************************
	//	< ����֐�
	//		�֐�����boost����
	bool _internal_less( shared_ptr<T> const & rhs ) const {
		return ( pn_ < rhs.pn_ );
	}

// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	template<class Y> friend class weak_ptr;
    template<class Y> friend class shared_ptr;

	T* px_;
	int* pn_;
};


// *************************************************************************
//	��r�I�y���[�^
template <class T> 
inline bool operator ==(
	const shared_ptr<T>& a,	// I : ��r�Ώ�1
	const shared_ptr<T>& b	// I : ��r�Ώ�2
	){
	//	����A�h���X���ǂ���
	return ( a.get() == b.get() );
}
template <class T> 
inline bool operator !=(
	const shared_ptr<T>& a,	// I : ��r�Ώ�1
	const shared_ptr<T>& b	// I : ��r�Ώ�2
	){
	return ( a.get() != b.get() );
}



} // namespace nd

#endif // HPP_SHARED_PTR_INCLUDED
