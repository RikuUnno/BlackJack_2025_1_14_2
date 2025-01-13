#include <iostream>
#include "Player.h"
#include "Shoe.h"

using namespace std;

Player::Player(const char* name) : Person(name) {}

//ゲーム実行
void Player::playBase(Shoe* shoe) {
	//バーストするまでループ処理
	while (getScore()) {
		cout<< "hit or stand >> ";

		//入力
		char str[16]; //文字列型
		cin >> str; //文字列を入力
		//hitが入力された場合
		if (strcmp(str, "hit") == 0) {
			//カードの配布
			hit(shoe);

			//手札の表示
			cout << "====================" << endl;
			cout << "player" << endl;
			showHand();
			cout << "====================" << endl;
		}
		else if (strcmp(str, "stand") == 0) {
			//終了処理
			break;
		}
	}
}
