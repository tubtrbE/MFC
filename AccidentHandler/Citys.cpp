#include "pch.h"
#include "Citys.h"

Citys::Citys(string myCity, string myDistrict, int myData[]) {

	city = myCity;
	district = myDistrict;
	for (int i = 0; i < 11; i++) {
		death[i] = myData[i];
	}
}
Citys::~Citys() {
}

string Citys::GetCity() const {
	return city;
}
string Citys::GetDistrict() const {
	return district;
}
const int* Citys::GetDeath() const {
	return death;
}
