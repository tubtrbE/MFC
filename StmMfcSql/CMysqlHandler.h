#pragma once
#include <mysql.h>
#include <vector>
#include "AdcValue.h"

using namespace std;


#define DB_HOST "127.0.0.1"//���� ������
#define DB_USER "root"//DB ���� ����
#define DB_PASS "1234"//DB ���� ��ȣ
#define DB_NAME "adcdb"//DB �̸�

class CMysqlHandler
{
public:


	vector<AdcValue*> vValue;
	CMysqlHandler();
	~CMysqlHandler();
	bool SelectQuery(char* sql, vector<AdcValue*>& vMyValue);
	bool InsertQuery(char* sql);
	bool InsertQuerys(vector<string>& vMyQuery);


};

