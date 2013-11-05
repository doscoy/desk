/* -------------------------------------------------------------------------------
	侵入型参照カウント方式のスマートポインタ
	オブジェクト側の参照カウント機能を利用して管理を行ないます
---------------------------------------------------------------------------------*/

#ifndef HPP_INTRUSIVE_PTR_INCLUDED
#define HPP_INTRUSIVE_PTR_INCLUDED

// -----------------------------------------------------------------
//	インクルード
#include <algorithm>	// for std::swap
#include <cassert>		// for assert

namespace nd {



// =================================================================
//	侵入型参照カウントスマートポインタ
template <typename T>
class intrusive_ptr
{
// -----------------------------------------------------------------
//	公開型定義
public:
	typedef T element_type;
	
// -----------------------------------------------------------------
//	クラス内型定義
private:
	typedef intrusive_ptr this_type;


// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
public:
	// *************************************************************************
	//	デフォルトコンストラクタ
	intrusive_ptr()
		: px_( NULL )
		{}
	
	// *************************************************************************
	//	コンストラクタ
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
	//	コピーコンストラクタ
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
	//	デストラクタ
	~intrusive_ptr()
	{
		if ( px_ != 0 ){
			px_->releaseReference();
		}
	}
	
	
// -----------------------------------------------------------------
//	オペレータ
public:
	
	// *************************************************************************
	//	intrusive_ptr同士の代入演算子
	intrusive_ptr& operator =(
		const intrusive_ptr& rhs
		){
		//	代入処理の実装はコピーコンストラクタに任せる
        this_type( rhs ).swap( *this );
        return ( *this );
    }

	// *************************************************************************
	//	T* との代入演算子
    intrusive_ptr & operator =( T* rhs )
    {
		//	代入処理の実装はコピーコンストラクタに任せる
        this_type( rhs ).swap( *this );
        return ( *this );
    }


	// *************************************************************************
	//	参照演算子
    T& operator *() const
    {
        assert( px_ != 0 );
        return ( *px_ );
    }
	
	// *************************************************************************
	//	アロー演算子
    T* operator ->() const
    {
        assert( px_ != 0 );
        return ( px_ );
    }


// -----------------------------------------------------------------
//	公開メソッド
public:

	// *************************************************************************
	//	生ポインタ取得
    T* get() const
    {
        return ( px_ );
    }

	// *************************************************************************
	//	リセット
	void reset( T * rhs )
    {
        this_type( rhs ).swap( *this );
    }

	// *************************************************************************
	//	スワップ
    void swap(
		intrusive_ptr& rhs
		){
		std::swap( rhs.px_, px_ );
    }


// -----------------------------------------------------------------
//	メンバ変数
private:
	T*	px_;

};


// *************************************************************************
//	グローバル比較オペレータ

//	intrusive_ptr同士 ==
template<class T, class U> 
inline bool operator ==(
	const intrusive_ptr<T>& a,		// I : 比較対象 a
	const intrusive_ptr<U>& b		// I : 比較対象 b
	){
    return ( a.get() == b.get() );
}

//	intrusive_ptr同士 !=
template<class T, class U> 
inline bool operator !=( 
	const intrusive_ptr<T>& a,		// I : 比較対象 a
	const intrusive_ptr<U>& b		// I : 比較対象 b
	){
    return ( a.get() != b.get() );
}

//	intrusive_ptr と生ポインタ ==
template<class T, class U> 
inline bool operator ==(
	const intrusive_ptr<T>& a,		// I : 比較対象 a
	const U* const b				// I : 比較対象 b
	){
    return ( a.get() == b );
}

//	intrusive_ptr と生ポインタ !=
template<class T, class U> 
inline bool operator !=(
	const intrusive_ptr<T>& a,		// I : 比較対象 a
	const U* const b				// I : 比較対象 b
	){
    return ( a.get() != b );
}

//	生ポインタとintrusive_ptr  ==
template<class T, class U> 
inline bool operator ==(
	const T* const a,				// I : 比較対象 a
	const intrusive_ptr<U>& b		// I : 比較対象 b
	){
    return a == b.get();
}

//	生ポインタとintrusive_ptr  !=
template<class T, class U> 
inline bool operator !=(
	const T* const a,				// I : 比較対象 a			
	const intrusive_ptr<U>& b		// I : 比較対象 b
	){
    return ( a != b.get() );
}



} // namespace nd

#endif // HPP_INTRUSIVE_PTR_INCLUDED
