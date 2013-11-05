/* -------------------------------------------------------------------------------
	参照カウント計測基底クラス
---------------------------------------------------------------------------------*/

#ifndef HPP_REF_COUNTABLE_INCLUDED
#define HPP_REF_COUNTABLE_INCLUDED



namespace nd {


// =================================================================
//	参照カウントを注入するクラス
class RefCountable
{
// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
protected:
	// *************************************************************************
	//	デフォルトコンストラクタ
	RefCountable()
		: ref_count_( 0 )
		{
	}
	
	// *************************************************************************
	//	デストラクタ
    virtual ~RefCountable()
    {
    }


// -----------------------------------------------------------------
//	コピー禁止
private:
	// *************************************************************************
	//	コピーコンストラクタ
	RefCountable( const RefCountable& );
	
	// *************************************************************************
	//	代入演算子オペレータ
	RefCountable& operator =( const RefCountable& );


// -----------------------------------------------------------------
//	公開メソッド
public:
	// *************************************************************************
	//	参照カウント加算
	void addReference()
	{
		ref_count_ += 1;
	}
	
	// *************************************************************************
	//	参照カウント減算
	void releaseReference()
	{
		ref_count_ -= 1;
		
		if ( ref_count_ == 0 ){
			withoutReference();
		}
	}
	
	// *************************************************************************
	//	参照が無くなった時の処理
	virtual void withoutReference()
	{
		delete this;
	}


// -----------------------------------------------------------------
//	メンバ変数
private:
	int ref_count_;

};

} // namespace nd

#endif // HPP_REF_COUNTABLE_INCLUDED
