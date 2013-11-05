/* -------------------------------------------------------------------------------
	�V���O���g����CRTP
---------------------------------------------------------------------------------*/

#ifndef HPP_SINGLETON_INCLUDED
#define HPP_SINGLETON_INCLUDED

// -----------------------------------------------------------------
//	�C���N���[�h
#include <new>		// for new/delete
#include <cassert>	// for assert


namespace nd {

//
//	new/delete �� malloc/free �̃|���V�[�̓f�t�H���g�ŗp��
//	

namespace SingletonPolicy {

// =================================================================
//	�V���O���g���C���X�^���X�N���G�C�g�|���V�[ new/delete
template <class T> 
class UseNew
{
public:
    static T* createInstance()
    {
		return ( new T );
	}
    
    static void destroyInstance( T* p )
    { 
		delete p; 
    }
};

// =================================================================
//	�V���O���g���C���X�^���X�N���G�C�g�|���V�[ malloc/free
template <class T>
class UseMalloc
{
public:
	static T* createInstance()
    {
        void* p = std::malloc( sizeof(T) );
        if ( !p ){
			return ( NULL );
        }
        return ( new(p) T );
    }
    
    static void destroyInstance( T* p )
    {
        p->~T();
        std::free( p );
    }
};

} // namespace SingletonPolicy







// =================================================================
//	�V���O���g���z���_�[
template <
	class T,
	template <class> class CreationPolicy = SingletonPolicy::UseNew
>
class Singleton
{
// -----------------------------------------------------------------
//	�ÓI���J���\�b�h
public:
	// *************************************************************************
	//	�C���X�^���X�ւ̎Q�Ǝ擾
	//		�C���X�^���X�����݂��Ȃ��ꍇ�͎��s���G���[�ɂȂ�܂��B
	static T& getInstance() {
		assert( instance_ );
		return ( *instance_ );
	}

	// *************************************************************************
	//	�C���X�^���X�ւ̃|�C���^�擾
	static T* getInstancePtr() {
		assert( instance_ );
		return ( instance_ );
	}

	// *************************************************************************
	//	�C���X�^���X����
	static void createInstance(){
		assert( instance_ == NULL );	// �C���X�^���X������̂ɐ�������̂͂�������
		instance_ = CreationPolicy<T>::createInstance();
	}
	
	// *************************************************************************
	//	�C���X�^���X�j��
	static void destroyInstance(){
		if ( instance_ ){
			CreationPolicy<T>::destroyInstance( instance_ );
			instance_ = NULL;
		}
	}
	
	// *************************************************************************
	//	�C���X�^���X�������ς݂�����
	static bool isCreateInstance(){
		return ( instance_ != NULL );
	}


// -----------------------------------------------------------------
//	�R�s�[�֎~
private:
	Singleton( const Singleton& );
	Singleton& operator =( Singleton& );
	
	
// -----------------------------------------------------------------
//	�R���X�g���N�^�E�f�X�g���N�^
protected:
	Singleton() {
	}
	
	~Singleton() {
	}


// -----------------------------------------------------------------
//	�����o�ϐ�
private:
	static T* instance_;		// �C���X�^���X
	
	
};

//	�ÓI�����o�̏�����
template 
<
	class T,
	template <class> class CreationPolicy
>
T* Singleton<T,CreationPolicy>::instance_( NULL );


} // namespace nd


#endif // HPP_SINGLETON_INCLUDED
