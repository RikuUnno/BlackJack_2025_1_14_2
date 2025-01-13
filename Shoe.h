#pragma once

#include "common.h"

//カードシュークラス
class Shoe {

private:
	//基本的にカードシューはprivate
	int _cardShoe[CARD_NUM]; //カード配列
	int _cardNum; //カード枚数

	void _shuffle();
	void _initCardShoe();

public:
	enum SHOW_TYPE
	{
		CARD_ONLY,
		ALL
	};

	//コンストラクタ
	Shoe();

	//カードを1枚取り出す
	int takeCard();

	//カードシューを表示(デバッグ用)
	void showShoe(SHOW_TYPE type = CARD_ONLY) const;
};

