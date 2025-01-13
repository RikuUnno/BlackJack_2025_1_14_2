#pragma once

#include "common.h"

class Shoe;

class Person
{
private:
	
	int _hand[HAND_SIZE];	// 理論上これくらい持てばOK...に今回はしちゃう
	bool _calcUpdate;
	int _cardNum;
	int _score;

public:
	// コンストラクタ
	Person(const char* name);

	virtual ~Person();

	//スコアの取得(hitされた時のみ再計算される)
	int getScore();

	//カードの追加
	void hit(Shoe* shoe);

	//手札を表示
	void showHand();

	//ターン処理
	bool play(Shoe* shoe);

	char* getName() const;

protected:
	virtual void playBase(Shoe* shoe) = 0;	//ターン処理本体
	char* _name;

};

