/* -------------------------------------------------------------------------------
	乱数　メルセンヌ・ツイスタ
	mt19937ar-cok.cとして知られている実装の移植です。
	元の実装よりシンプルにしてあり、32bit以上の初期化子を与える部分を
	削ってあります。
	BSDライセンスです（ http://www.opensource.org/licenses/bsd-license.php ）
	
---------------------------------------------------------------------------------*/

#ifndef HPP_RAND_MT_INCLUDED
#define HPP_RAND_MT_INCLUDED

namespace nd {

// =================================================================
//	メルセンヌ・ツイスタによる乱数ジェネレータ
class RandMT {

// -----------------------------------------------------------------
//	コンストラクタ・デストラクタ
public:
	//	コンストラクタ
	explicit RandMT( 
		const unsigned long seed	// I : 乱数の種
	);
	
	//	デストラクタ
	~RandMT();
	
// -----------------------------------------------------------------
//	公開メソッド
public:
	//	32bit 符号無し整数の乱数を取得
	unsigned long getU32();	// R : 取得値
	
// -----------------------------------------------------------------
//	非公開メソッド
private:
	void nextState();


// -----------------------------------------------------------------
//	メンバ変数
private:
	enum {
		MAX_WORK = 624,
	};
	unsigned long state_[MAX_WORK];
	int left_;
	unsigned long* next_;

};

} // namespace nd


#endif // HPP_RAND_MT_INCLUDED
