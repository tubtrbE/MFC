#include "pch.h"
#include "CMysqlHandler.h"
using namespace std;

CMysqlHandler::CMysqlHandler() {

}
CMysqlHandler::~CMysqlHandler() {

}
bool CMysqlHandler::SelectQuery(char* sql, vector<AdcValue*>& vMyValue) {
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS,
		DB_NAME, 3306, (char*)NULL, 0);
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if (connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}
	query_stat = mysql_query(connection, sql);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}
	sql_result = mysql_store_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		CString yymmdd;
		CString hhmmss;
		CString value;

		yymmdd.Format(_T("%s"), (LPSTR)(sql_row[0]));
		hhmmss.Format(_T("%s"), (LPSTR)(sql_row[1]));
		value.Format(_T("%s"), (LPSTR)(sql_row[2]));

		AdcValue* temp = new AdcValue((string)CT2CA(yymmdd), (string)CT2CA(hhmmss), (string)CT2CA(value));
		vMyValue.push_back(temp);

	}
	vValue = vMyValue;
	mysql_free_result(sql_result);
	mysql_close(connection);
	return true;
}


bool CMysqlHandler::InsertQuery(char* sql) {
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_query(connection, "set session character_set_connection = euckr; ");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if (connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}


	/////////////////////////////
	query_stat = mysql_query(connection, sql);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}
	////////////////////////////////


	mysql_close(connection);

	return true;
}

bool CMysqlHandler::InsertQuerys(vector<string>& vMyQuery) {

	//===================================================================================================
	// MYSQL �� �����ϴ� �κ��̴�.
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat = 0;
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	mysql_query(connection, "set session character_set_connection = euckr; ");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	if (connect == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return false;
	}
	//===================================================================================================

	//===================================================================================================
	// �������Ŀ� ������ ������ �κ��̴�.
	for (int i = 0; i < (int)vMyQuery.size(); i++) {
		
		query_stat = mysql_query(connection, (char*)vMyQuery.at(i).c_str());
	}

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}
	//===================================================================================================


	// mysql �� ������ �������ν� ������ ������ ������ ���̳���.
	mysql_close(connection);
	//Query ���� uart �κ��� ���� ADC ���� ������ �����̹Ƿ� clear �ؼ��� �ȵȴ�.
	//���� ���纻�� �޾Ƽ� ������ ������ ���纻�� .size()��ŭ�� ó���� �־�� �Ѵ�.
	//vMyQuery.clear();
	//vector<CString>().swap(vMyQuery);
	return true;
}



