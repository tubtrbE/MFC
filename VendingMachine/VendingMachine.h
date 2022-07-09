#pragma once
#include "Beverage.h"
#include <vector>

using namespace std;

class VendingMachine
{
private:
	vector<Beverage> beverageList;
public:

	void BeverageAdd(Beverage temp);
	void BeverageDelete(int index);
	Beverage* BeverageGet(int index);
};

