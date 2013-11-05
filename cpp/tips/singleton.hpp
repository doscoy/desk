/* -------------------------------------------------------------------------------
	シングルトン化CRTP
---------------------------------------------------------------------------------*/

#ifndef HPP_SINGLETON_INCLUDED
#define HPP_SINGLETON_INCLUDED

// -----------------------------------------------------------------
//	インクルード
#include <new>		// for new/delete
#include <cassert>	// for assert


namespace nd {

//
//	new/delete と malloc/free のポリシーはデフォルトで用意
//	

namespace SingletonPolicy {

// =================================================================
//	シングルトンインスタンスクリエイトポリシー new/delete
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
//	シングルトンインスタンスクリエイトポリシー malloc/free
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
//	シングルトンホルダー
template <
	class T,
	template <class> class CreationPolicy = SingletonPolicy::UseNew
>
class Singleton
{
// -----------------------------------------------------------------
//	静的公開メソッド
public:
	// *************************************************************************
	//	インスタンスへの参照取得
	//		インスタンスが存在しない場合は実行時エラーになります。
	static T& getInstance() {
		assert( instance_ );
		return ( *instance_ );
	}

	// *************************************************************************
	//	インスタンスへのポインタ取得
	static T* getInstancePtr() {
		assert( instance_ );
		return ( instance_ );
	}

	// *************************************************************************
	//	インスタンス生成
	static void createInstance(){
		assert( instance_ == NULL );	// インスタンスがあるのに生成するのはおかしい
		instance_ = CreationPolicy<T>::createInstance();
	}
	
	// *************************************************************************
	//	インスタンス破棄
	static void destroyInstance(){
		if ( instance_ ){
			CreationPolicy<T>::destroyInstance( instance_ );
			instance_ = NULL;
		}
	}
	
	// *************************************************************************
	//	インスタンスが生成済みか判定
	static bool isCreateInstance(){
		return ( instance_ != NULL );
	}


// -----------------------------------------------------------------
//	コピー禁止
private:
	Singleton( const Singleton& );
	Singleton& operator =( Singleton& );
	
	
// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
protected:
	Singleton() {
	}
	
	~Singleton() {
	}


// -----------------------------------------------------------------
//	メンバ変数
private:
	static T* instance_;		// インスタンス
	
	
};

//	静的メンバの初期化
template 
<
	class T,
	template <class> class CreationPolicy
>
T* Singleton<T,CreationPolicy>::instance_( NULL );


} // namespace nd


#endif // HPP_SINGLETON_INCLUDED
