#pragma once
#include <string>

using namespace std;

class AdcValue
{
private:
	string adcValue;
	string YyMmDd;
	string HhMmSs;

public:
	AdcValue(string myYyMmDd, string myHhMmSs, string myValue);
	string GetValue();
	string GetYyMmDd();
	string GetHhMmSs();

};

