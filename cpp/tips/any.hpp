/* -------------------------------------------------------------------------------
	������^���󂯎��^
	boost::any�̈ڐA
	RTTI�i���s���^���j���L���ɂȂ��Ă���K�v������܂��B

	������^���󂯎�邱�Ƃ��ł��܂����A�����ɂ̓R�s�[�\��
	������Z�q���T�|�[�g���Ă�����̂Ɍ����܂��B
---------------------------------------------------------------------------------*/

#ifndef HPP_ANY_INCLUDED
#define HPP_ANY_INCLUDED


// -----------------------------------------------------------------
//	�C���N���[�h
#include <typeinfo>


namespace nd {


// =================================================================
//	������^���i�[�ł���^
class any {

// -----------------------------------------------------------------
//	�N���X���^��`
private:
	// =================================================================
	//	�z���_�[�x�[�X
	struct holder_base{
		virtual ~holder_base() {}
		virtual holder_base* clone() const = 0;
		virtual const std::type_info& type() const = 0;
	};
	
	// =================================================================
	//	�z���_�[
	template <class T>
	struct holder : public holder_base{
		//	�l�ێ�
		T value_;
		
		//	�R���X�g���N�^
		holder( const T& value )
			:value_(value)
			{}
		
		//	�R�s�[����
		virtual holder_base* clone() const {
			return ( new holder( value_ ) );
		}
		
		//	�^���擾
		virtual const std::type_info& type() const{
			return ( typeid( T ) );
		}
	};
	


	// =================================================================
	//	any�̎����͈ȉ�
public:
// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
	// *************************************************************************
	//	�R���X�g���N�^
	template <class T>
	any( const T& value )
		: content_( new holder<T>(value) )
		{}

	// *************************************************************************
	//	�R���X�g���N�^
	any( const any& other )
		: content_( other.content_ ? other.content_->clone() : NULL )
		{}
		
	// *************************************************************************
	//	�f�X�g���N�^
	~any(){
		if( content_ ){
			delete content_;
			content_ = NULL;
		}
	}


// -----------------------------------------------------------------
//	�I�y���[�^
public:
	// *************************************************************************
	// �����A�ʂ̌^��any�ɑ��
	template <class T>
	any& operator =( const T& value )
	{
		if( content_ ){
			delete content_;
			content_ = NULL;
		}
		content_ = new holder<T>(value);
		return ( *this );
	}
	
	// *************************************************************************
	//	any���m�̑��
	any& operator =( const any& other )
	{
		if( content_ ){
			delete content_;
			content_ = NULL;
		}
		content_ = other.content_ ? other.content_->clone() : NULL;
		return ( *this );
	}


// -----------------------------------------------------------------
//	���J���\�b�h
public:
	// *************************************************************************
	//	�l�����o��
	template <class T>
	const T& cast() const
	{
		return ( dynamic_cast< holder<T>& >(*content_).value_ );
	}

	// *************************************************************************
	//	�^���擾
	const std::type_info& type() const
	{
		return content_ ? content_->type() : typeid( void );
	}


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	holder_base* content_;
	

};

} // namespace nd



// -----------------------------------------------------------------
//	�T�[�r�X�֐� any_cast�p��
template < class To >
inline To any_cast(	// R : �ϊ���
	nd::any& from	// I : �ϊ��O
	){
	
	return from.cast<To>();
}


#endif // HPP_ANY_INCLUDED


