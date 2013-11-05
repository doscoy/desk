/* -------------------------------------------------------------------------------
	�I�v�V�����ϐ��J�v�Z�����e���v���[�g
	�l�̗L������Ɏg���I�v�V������񂪕t�����ꂽ�f�[�^�^����邱�Ƃ��ł��܂�
---------------------------------------------------------------------------------*/

#ifndef HPP_OPTIONAL_INCLUDED
#define HPP_OPTIONAL_INCLUDED


// -----------------------------------------------------------------
//	�C���N���[�h
#include <cassert>	// for assert


namespace nd {


// =================================================================
//	optional
template <class T>
class optional
{
// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
public:
	// *************************************************************************
	//	�R���X�g���N�^
	optional() 
		: valid_( false )
		{
		// none
	}

	// *************************************************************************
	//	�����t���R���X�g���N�^
	optional(
		const T& t	// I : �ێ�����f�[�^�l 
		)
		: content_( t )
		, valid_( true )
		{
		// none
	}

	// *************************************************************************
	//	�R�s�[�R���X�g���N�^ optional<>���󂯂��ꍇ
	optional(
		const optional& other	// I : �R�s�[��
		)
		: valid_( false )
		{
		if ( other.isValid() ){
			content_ = other.content_;
			valid_ = true;
		}
	}
	
	// *************************************************************************
	//	�f�X�g���N�^
	~optional()
	{
		// none
	}

// -----------------------------------------------------------------
//	�I�y���[�^
public:

	// *************************************************************************
	//	������Z�q
	optional& operator =(
		const T& t	// I : ����l
		){

		content_ = t;
		valid_ = true;

		return ( *this );
	}

	// *************************************************************************
	//	optional<>�Ƃ̑�����Z�q
	optional& operator =( 
		const optional& other	// I : �R�s�[�� optional
		){
		
		if ( this != &other ){	//	���ȑ���h�~
			if ( other.isValid() ){
				content_ = other.content_;
				valid_ = true;
			}
			else {
				valid_ = false;
			}
		}
		return ( *this );
	}


	// *************************************************************************
	//	�O�u�C���N�������g���Z�q
	optional& operator ++() {
		assert( valid_ );
		++content_;
		return ( *this );
	}

	// *************************************************************************
	//	��u�C���N�������g���Z�q
	optional& operator ++(int) {
		assert( valid_ );
		content_++;
		return ( *this );
	}

	// *************************************************************************
	//	�O�u�f�N�������g���Z�q
	optional& operator --() {
		assert( valid_ );
		--content_;
		return ( *this );
	}

	// *************************************************************************
	//	��u�f�N�������g���Z�q
	optional& operator --(int) {
		assert( valid_ );
		content_--;
		return ( *this );
	}

	// *************************************************************************
	//	+= ���Z�q
	const optional& operator +=(
		const optional& rhs
		){
		assert( valid_ );
		content_ += rhs.content_;

		return ( *this );
	}

	// *************************************************************************
	//	���̌^�ɑ΂��� += ���Z�q
	const optional& operator +=(
		const T& rhs
		){
		assert( valid_ );
		content_ += rhs;

		return ( *this );
	}
	
	// *************************************************************************
	//	-= ���Z�q
	const optional& operator -=(
		const optional& rhs
		){
		assert( valid_ );
		content_ -= rhs.content_;

		return ( *this );
	}

	
	// *************************************************************************
	//	���̌^�ɑ΂��� -= ���Z�q
	const optional& operator -=(
		const T& rhs
		){
		
		assert( valid_ );
		content_ -= rhs;

		return ( *this );
	}

	// *************************************************************************
	//	*= ���Z�q
	const optional& operator *=(
		const optional& rhs
		){
		assert( valid_ );
		content_ *= rhs.content_;

		return ( *this );
	}

	// *************************************************************************
	//	���̌^�ɑ΂��� *= ���Z�q
	const optional& operator *=(
		const T& rhs
		){
		assert( valid_ );
		content_ *= rhs;

		return ( *this );
	}

	// *************************************************************************
	//	/= ���Z�q
	const optional& operator /=(
		const optional& rhs
		){
		assert( valid_ );
		content_ /= *rhs.getContent();

		return ( *this );
	}

	// *************************************************************************
	//	���̌^�ɑ΂��� /= ���Z�q
	const optional& operator /=(
		const T& rhs
		){
		assert( valid_ );
		content_ /= rhs;

		return ( *this );
	}
	
	// *************************************************************************
	//	%= ���Z�q
	const optional& operator %=(
		const optional& rhs
		){
		assert( valid_ );
		content_ %= rhs.content_;

		return ( *this );
	}

	// *************************************************************************
	//	���̌^�ɑ΂��� %= ���Z�q
	const optional& operator %=(
		const T& rhs
		){
		assert( valid_ );
		content_ %= rhs;

		return ( *this );
	}

/*	
	��r���Z�� cast���Z�q�ɂ���ĉ������ꂽ�^T���m�̃I�y���[�^�ɔC����B
	optional<>���m�̔���͗p�ӂ��Ȃ��B
	���̌^T�ւ�cast���Z�q��L���ɂ��Ă���̂ŞB�����������ł��Ȃ��ׁB

	// *************************************************************************
	//	��r���Z�q
	const bool operator == ( 
		const optional& other
		) const {
		//	�����A�L���l
		if ( other.isValid() && isValid() ){
			return ( *other.getContent() == *getContent() );
		}
		return ( false );
	}
	const bool operator < ( 
		const optional& other 
		) const {
		//	�����A�L���l
		if ( other.isValid() && isValid() ){
			return ( *other.getContent() < *getContent() );
		}
		return ( false );
	}
*/	
	// *************************************************************************
	//	const�Q�Ɖ��Z�q
	const T& operator *() const {
		assert( valid_ );
		return ( content_ );
	}
	
	// *************************************************************************
	//	�Q�Ɖ��Z�q
	T& operator *() {
		assert( valid_ );
		return ( content_ );
	}
	
	// *************************************************************************
	//	const�|�C���^���Z�q
	const T* const operator ->() const {
		assert( valid_ );
		return ( &content_ );
	}
	
	// *************************************************************************
	//	�|�C���^���Z�q
	T* const operator ->() {
		assert( valid_ );
		return ( &content_ );
	}
	
	// *************************************************************************
	//	�L���X�g���Z�q
	operator T(){
		assert( valid_ );
		return ( content_ );
	}

// -----------------------------------------------------------------
//	���J���\�b�h
public:
	// *************************************************************************
	//	�L������
	bool isValid() const {
		return ( valid_ );
	}
	
	// *************************************************************************
	//	������
	void clear() {
		valid_ = false;
	}


// -----------------------------------------------------------------
//	����J���\�b�h
private:
	// none


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	T content_;
	bool valid_;
	
	
};



} // namespace nd

#endif // HPP_OPTIONAL_INCLUDED
