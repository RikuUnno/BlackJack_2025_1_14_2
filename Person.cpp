#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "Person.h"
#include "Shoe.h"

using namespace std;

Person::Person(const char* name)
{
	_name = new(nothrow) char[strlen(name) + 1];
	if (_name != nullptr)
	{
		strcpy(_name, name);
	}

	fill_n(_hand, HAND_SIZE, -1);
	_cardNum = 0;
	_calcUpdate = false;
	_score = 0;
}

Person::~Person()
{
	if (_name != nullptr)
	{
		delete[] _name;
		_name = nullptr;
	}
}

char* Person::getName() const
{
	return _name;
}

//スコアの計算
int Person::getScore()
{
	if (_calcUpdate == true)
	{// 再計算フラグが立っていたら再計算する
		int* data = NULL; //スコア計算用配列用ポインタ

		data = new(nothrow) int[_cardNum]; //手札枚数確保
		if (data == NULL)
		{
			// メモリ不足は今回はバーストとして終了する。
			cout << "メモリの確保に失敗しました。再起動してください。" << endl;
			return 0;
		}

		//手札配列からデータを取得,1-10の値として格納
		for (int i = 0; i < _cardNum; i++) {
			if (_hand[i] % 13 < 10) {
				//配列の値が10以下(0-9)であれば1を加えて格納
				*(data + i) = _hand[i] % 13 + 1;
			}
			else {
				//ここで10を格納しているのは,11-13のカードのこと
				*(data + i) = 10;
			}
		}

		//ソート（Aをあぶりだすため）
		sort(data, data + _cardNum);

		//返り値用変数(計算結果)
		_score = 0;
		//2番目から順にスコアを足していく
		//1番目が0の場合(つまりAである。2枚続く可能性はあるが2枚目のAは必ず1としてカウントする
		//ので先頭だけ調べればよい
		for (int i = 1; i < _cardNum; i++) {
			//スコアにデータを加える
			_score = _score + (*(data + i));
		}

		//先頭が1(A)であるか判定し状況によって1 or 11として計算
		if (*data == 1) {
			if (_score + 11 < 22) { //11として扱ってもバーストしない場合
				//11を加える
				_score += 11;
			}
			else {
				//11として扱うとバーストする場合
				//スコアに1を加える
				_score += 1;
			}
		}
		else {
			//先頭が1でないなら,スコアにデータをそのまま加える
			_score += data[0];
		}

		//バーストである場合は0を返す
		if (_score > 21) {
			_score = 0;
		}

		// 解放
		if (data != NULL)
		{
			delete[] data;
			data = NULL;
		}
	}

	return _score;
}

//手持ちにカードの追加
void Person::hit(Shoe* shoe) {
	int card = shoe->takeCard();
	if (card >= 0) {
		_hand[_cardNum] = card;
		_cardNum++;
		_calcUpdate = true;
	}
	else
	{
		cout << "カードが引けませんでした。" << endl;
	}
}

//手札を表示
void Person::showHand() {
	//標準出力
	cout << "hand: ";
	//配列の最初から最後までを順に表示
	for (int i = 0; i < _cardNum; i++) {
		//カードの種類(スペード,ハート,ダイヤ,クラブ)を探索
		int type = (_hand[i] % 52) / 13; //デッキごとに分けた後,13で割った数(0-3)で4種類を分割

		//標準出力
		const char* strType[] = { "s", "h", "d", "c" };
		cout << strType[type];
		cout << _hand[i] % 13 + 1 << ' ';
	}
	//改行
	cout << endl;
	cout << "score: " << getScore() << endl; //スコアの表示
}

// ターン処理
bool Person::play(Shoe* shoe)
{
	playBase(shoe);

	if (getScore() <= 0) return false;
	return true;
}

// ターンメイン処理
void Person::playBase(Shoe* shoe)
{
	// なんもせずでよいか。
}