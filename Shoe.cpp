#include "Shoe.h"
#include <iostream>
#include <random> //乱数生成

using namespace std;

//シャッフル（フィッシャーイェーツ）
void Shoe::_shuffle()
{
	for (int i = _cardNum; i > 1; --i) {
		int a = i - 1;
		int b = rand() % i;
		swap(_cardShoe[a], _cardShoe[b]);
	}
}

//コンストラクタ
Shoe::Shoe() {

	_initCardShoe();
}

//コンストラクタ
void Shoe::_initCardShoe() {

	//カードを入れてく0.... /52でデッキ、さらに/13でカード種類とする
	_cardNum = CARD_NUM; //カード枚数の設定
	for (int i = 0; i < _cardNum; i++) {
		_cardShoe[i] = i;
	}

	//シャッフル
	_shuffle();
}

//カードシューを表示(デバッグ用)
void Shoe::showShoe(SHOW_TYPE type) const
{
	int roopCnt = CARD_NUM;
	if (type == CARD_ONLY) {	//カード枚数分表示
		//カードのみ表示にする。
		roopCnt = _cardNum;
	}

	for (int i = 0; i < roopCnt; i++) {
		cout << _cardShoe[i] << ' ';
	}
	cout << endl;
}

//カードを1枚取り出す
int Shoe::takeCard() {
	// うしろから引いていく方がロジック的に楽
	_cardNum--;
	int card = _cardShoe[_cardNum];
	_cardShoe[_cardNum] = -1;	//んー-1を入れとくか。

	if (_cardNum <= 0) {
		//カードが無くなったら次のカードを準備
		_initCardShoe();
	}

	//要素を返り値とする
	return card;

}
