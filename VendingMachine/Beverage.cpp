#include "pch.h"
#include "Beverage.h"

Beverage::Beverage(CString myName, CString myPrice, CString myStock)
	:name(myName), stock(myStock), price(myPrice)
{

}

CString Beverage::GetName() {
	return name;
}
CString Beverage::GetStock() {
	return stock;
}
void Beverage::SetStock(CString myStock) {
	stock = myStock;
}

CString Beverage::GetPrice() {
	return price;
}


