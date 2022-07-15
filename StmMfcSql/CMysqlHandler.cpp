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
	// MYSQL 에 접속하는 부분이다.
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
	// 접속이후에 쿼리를 보내는 부분이다.
	for (int i = 0; i < (int)vMyQuery.size(); i++) {
		
		query_stat = mysql_query(connection, (char*)vMyQuery.at(i).c_str());
	}

	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return false;
	}
	//===================================================================================================


	// mysql 에 연결을 끊음으로써 쿼리를 보내는 과정이 끝이난다.
	mysql_close(connection);
	//Query 값이 uart 로부터 받은 ADC 값을 정제한 문장이므로 clear 해서는 안된다.
	//따라서 복사본을 받아서 쿼리를 보낸후 복사본의 .size()만큼을 처리해 주어야 한다.
	//vMyQuery.clear();
	//vector<CString>().swap(vMyQuery);
	return true;
}



