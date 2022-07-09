#pragma once
#include <CString>
using namespace std;

class Beverage
{
private:
public:
	CString name;
	CString stock;
	CString price;
	Beverage(CString myName, CString myPrice, CString myStock);
	CString GetName();
	CString GetStock();
	CString GetPrice();
	void Beverage::SetStock(CString myStock);

};

