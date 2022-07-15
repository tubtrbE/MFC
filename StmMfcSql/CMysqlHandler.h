#pragma once
#include <mysql.h>
#include <vector>
#include "AdcValue.h"

using namespace std;


#define DB_HOST "127.0.0.1"//서버 아이피
#define DB_USER "root"//DB 접속 계정
#define DB_PASS "1234"//DB 계정 암호
#define DB_NAME "adcdb"//DB 이름

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

