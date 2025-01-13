#pragma once

#include "Person.h"

//ディーラークラス
class Dealer : public Person 
{
public:
	Dealer(const char* name);

protected:
	//ゲーム実行
	void playBase(Shoe* shoe) override;

};