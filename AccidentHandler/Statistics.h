#pragma once
#include <vector>
#include "Citys.h"
class Statistics
{
private:
	vector<Citys*> vCity;
	vector<string> vFile;
	bool fileFlag;

public:
	Statistics();
	~Statistics();
	void InputCity(Citys* city);
	void ShowCity();
	void Search();
	void Sum();
	void MakeFile();


	string PlaceString(int place);
	int PlaceInt(string place);
};

