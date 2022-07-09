#include "pch.h"
#include "VendingMachine.h"

void VendingMachine::BeverageAdd(Beverage temp) {
	beverageList.push_back(temp);
}
void VendingMachine::BeverageDelete(int index) {
	beverageList.erase(beverageList.begin() + index);
}
Beverage* VendingMachine::BeverageGet(int index) {
	beverageList.begin() + index;

	if (beverageList.size() != 0) {
		return &beverageList.at(index);
	}
	else {
		return nullptr;
	}
}
