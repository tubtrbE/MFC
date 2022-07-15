#include "pch.h"
#include "AdcValue.h"

AdcValue::AdcValue(string myYyMmDd, string myHhMmSs, string myValue)
	:adcValue(myValue), YyMmDd(myYyMmDd), HhMmSs(myHhMmSs)
{
}
string AdcValue::GetValue() {
	return adcValue;
}
string AdcValue::GetYyMmDd() {
	return YyMmDd;
}
string AdcValue::GetHhMmSs() {
	return HhMmSs;
}