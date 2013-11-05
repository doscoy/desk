/* -------------------------------------------------------------------------------
	あらゆる型を受け取る型
	boost::anyの移植
	RTTI（実行時型情報）が有効になっている必要があります。

	あらゆる型を受け取ることができますが、厳密にはコピー可能で
	代入演算子をサポートしているものに限られます。
---------------------------------------------------------------------------------*/

#ifndef HPP_ANY_INCLUDED
#define HPP_ANY_INCLUDED


// -----------------------------------------------------------------
//	インクルード
#include <typeinfo>


namespace nd {


// =================================================================
//	あらゆる型を格納できる型
class any {

// -----------------------------------------------------------------
//	クラス内型定義
private:
	// =================================================================
	//	ホルダーベース
	struct holder_base{
		virtual ~holder_base() {}
		virtual holder_base* clone() const = 0;
		virtual const std::type_info& type() const = 0;
	};
	
	// =================================================================
	//	ホルダー
	template <class T>
	struct holder : public holder_base{
		//	値保持
		T value_;
		
		//	コンストラクタ
		holder( const T& value )
			:value_(value)
			{}
		
		//	コピー処理
		virtual holder_base* clone() const {
			return ( new holder( value_ ) );
		}
		
		//	型情報取得
		virtual const std::type_info& type() const{
			return ( typeid( T ) );
		}
	};
	


	// =================================================================
	//	anyの実装は以下
public:
// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
	// *************************************************************************
	//	コンストラクタ
	template <class T>
	any( const T& value )
		: content_( new holder<T>(value) )
		{}

	// *************************************************************************
	//	コンストラクタ
	any( const any& other )
		: content_( other.content_ ? other.content_->clone() : NULL )
		{}
		
	// *************************************************************************
	//	デストラクタ
	~any(){
		if( content_ ){
			delete content_;
			content_ = NULL;
		}
	}


// -----------------------------------------------------------------
//	オペレータ
public:
	// *************************************************************************
	// 何か、別の型をanyに代入
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
	//	any同士の代入
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
//	公開メソッド
public:
	// *************************************************************************
	//	値を取り出す
	template <class T>
	const T& cast() const
	{
		return ( dynamic_cast< holder<T>& >(*content_).value_ );
	}

	// *************************************************************************
	//	型情報取得
	const std::type_info& type() const
	{
		return content_ ? content_->type() : typeid( void );
	}


// -----------------------------------------------------------------
//	メンバ変数
private:
	holder_base* content_;
	

};

} // namespace nd



// -----------------------------------------------------------------
//	サービス関数 any_cast用意
template < class To >
inline To any_cast(	// R : 変換後
	nd::any& from	// I : 変換前
	){
	
	return from.cast<To>();
}


#endif // HPP_ANY_INCLUDED


