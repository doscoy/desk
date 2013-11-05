/* -------------------------------------------------------------------------------
	オプション変数カプセル化テンプレート
	値の有効判定に使うオプション情報が付加されたデータ型を作ることができます
---------------------------------------------------------------------------------*/

#ifndef HPP_OPTIONAL_INCLUDED
#define HPP_OPTIONAL_INCLUDED


// -----------------------------------------------------------------
//	インクルード
#include <cassert>	// for assert


namespace nd {


// =================================================================
//	optional
template <class T>
class optional
{
// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
public:
	// *************************************************************************
	//	コンストラクタ
	optional() 
		: valid_( false )
		{
		// none
	}

	// *************************************************************************
	//	引数付きコンストラクタ
	optional(
		const T& t	// I : 保持するデータ値 
		)
		: content_( t )
		, valid_( true )
		{
		// none
	}

	// *************************************************************************
	//	コピーコンストラクタ optional<>を受けた場合
	optional(
		const optional& other	// I : コピー先
		)
		: valid_( false )
		{
		if ( other.isValid() ){
			content_ = other.content_;
			valid_ = true;
		}
	}
	
	// *************************************************************************
	//	デストラクタ
	~optional()
	{
		// none
	}

// -----------------------------------------------------------------
//	オペレータ
public:

	// *************************************************************************
	//	代入演算子
	optional& operator =(
		const T& t	// I : 代入値
		){

		content_ = t;
		valid_ = true;

		return ( *this );
	}

	// *************************************************************************
	//	optional<>との代入演算子
	optional& operator =( 
		const optional& other	// I : コピー元 optional
		){
		
		if ( this != &other ){	//	自己代入防止
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
	//	前置インクリメント演算子
	optional& operator ++() {
		assert( valid_ );
		++content_;
		return ( *this );
	}

	// *************************************************************************
	//	後置インクリメント演算子
	optional& operator ++(int) {
		assert( valid_ );
		content_++;
		return ( *this );
	}

	// *************************************************************************
	//	前置デクリメント演算子
	optional& operator --() {
		assert( valid_ );
		--content_;
		return ( *this );
	}

	// *************************************************************************
	//	後置デクリメント演算子
	optional& operator --(int) {
		assert( valid_ );
		content_--;
		return ( *this );
	}

	// *************************************************************************
	//	+= 演算子
	const optional& operator +=(
		const optional& rhs
		){
		assert( valid_ );
		content_ += rhs.content_;

		return ( *this );
	}

	// *************************************************************************
	//	元の型に対する += 演算子
	const optional& operator +=(
		const T& rhs
		){
		assert( valid_ );
		content_ += rhs;

		return ( *this );
	}
	
	// *************************************************************************
	//	-= 演算子
	const optional& operator -=(
		const optional& rhs
		){
		assert( valid_ );
		content_ -= rhs.content_;

		return ( *this );
	}

	
	// *************************************************************************
	//	元の型に対する -= 演算子
	const optional& operator -=(
		const T& rhs
		){
		
		assert( valid_ );
		content_ -= rhs;

		return ( *this );
	}

	// *************************************************************************
	//	*= 演算子
	const optional& operator *=(
		const optional& rhs
		){
		assert( valid_ );
		content_ *= rhs.content_;

		return ( *this );
	}

	// *************************************************************************
	//	元の型に対する *= 演算子
	const optional& operator *=(
		const T& rhs
		){
		assert( valid_ );
		content_ *= rhs;

		return ( *this );
	}

	// *************************************************************************
	//	/= 演算子
	const optional& operator /=(
		const optional& rhs
		){
		assert( valid_ );
		content_ /= *rhs.getContent();

		return ( *this );
	}

	// *************************************************************************
	//	元の型に対する /= 演算子
	const optional& operator /=(
		const T& rhs
		){
		assert( valid_ );
		content_ /= rhs;

		return ( *this );
	}
	
	// *************************************************************************
	//	%= 演算子
	const optional& operator %=(
		const optional& rhs
		){
		assert( valid_ );
		content_ %= rhs.content_;

		return ( *this );
	}

	// *************************************************************************
	//	元の型に対する %= 演算子
	const optional& operator %=(
		const T& rhs
		){
		assert( valid_ );
		content_ %= rhs;

		return ( *this );
	}

/*	
	比較演算は cast演算子によって解決された型T同士のオペレータに任せる。
	optional<>同士の判定は用意しない。
	元の型Tへのcast演算子を有効にしているので曖昧さが解決できない為。

	// *************************************************************************
	//	比較演算子
	const bool operator == ( 
		const optional& other
		) const {
		//	両方、有効値
		if ( other.isValid() && isValid() ){
			return ( *other.getContent() == *getContent() );
		}
		return ( false );
	}
	const bool operator < ( 
		const optional& other 
		) const {
		//	両方、有効値
		if ( other.isValid() && isValid() ){
			return ( *other.getContent() < *getContent() );
		}
		return ( false );
	}
*/	
	// *************************************************************************
	//	const参照演算子
	const T& operator *() const {
		assert( valid_ );
		return ( content_ );
	}
	
	// *************************************************************************
	//	参照演算子
	T& operator *() {
		assert( valid_ );
		return ( content_ );
	}
	
	// *************************************************************************
	//	constポインタ演算子
	const T* const operator ->() const {
		assert( valid_ );
		return ( &content_ );
	}
	
	// *************************************************************************
	//	ポインタ演算子
	T* const operator ->() {
		assert( valid_ );
		return ( &content_ );
	}
	
	// *************************************************************************
	//	キャスト演算子
	operator T(){
		assert( valid_ );
		return ( content_ );
	}

// -----------------------------------------------------------------
//	公開メソッド
public:
	// *************************************************************************
	//	有効判定
	bool isValid() const {
		return ( valid_ );
	}
	
	// *************************************************************************
	//	無効化
	void clear() {
		valid_ = false;
	}


// -----------------------------------------------------------------
//	非公開メソッド
private:
	// none


// -----------------------------------------------------------------
//	メンバ変数
private:
	T content_;
	bool valid_;
	
	
};



} // namespace nd

#endif // HPP_OPTIONAL_INCLUDED
