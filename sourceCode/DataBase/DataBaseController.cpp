//
// Created by Maxim on 2019-05-20.
//


#include "DataBaseController.h"

DataBaseController::DataBaseController(std::string host_, std::string name_, std::string login_, std::string password_, int port_)
{
	base = new DataBase(host_, name_, login_, password_);
}

void DataBaseController::dataBaseSettings(std::string host_, std::string name_, std::string login_, std::string password_, int port_)
{
	base = new DataBase(host_, name_, login_, password_);
}

PGresult * DataBaseController::getRows(std::string schema, std::string field, std::string filter) {
	std::string query = "select * from " + schema + " where " + field + " = '" + filter + "'";
	PGresult * res = nullptr;
	res = base->runQuery (query);

	return res;
}

PGresult * DataBaseController::getRows(std::string schema) {
	std::string query = "select * from " + schema;
	PGresult * res = nullptr;
	res = base->runQuery (query);

	return res;
}

bool DataBaseController::insertRow(std::string schema, std::vector<std::pair<std::string, std::string>> values){
	PGresult * res = nullptr;

	std::string query = "insert into " + schema + "(";

	for(const auto it : values)
	{
		query += it.first;
		if(it != *(values.end() - 1))
			query += ", ";
	}
	query += ") values (";
	for(const auto it : values)
	{
		query += "'" + it.second + "'";
		if(it != *(values.end() - 1))
			query += ", ";
	}
	query += ");";
	res = base->runQuery (query);


	return PQresultStatus(res) == PGRES_COMMAND_OK;
}
bool DataBaseController::insertBoolColumn(std::string schema, std::string column_name){
	PGresult * res = nullptr;

	std::string query = "alter table " + schema + " add column \"" + column_name + "\" BOOLEAN DEFAULT FALSE;";

	res = base->runQuery (query);

	return PQresultStatus(res) == PGRES_COMMAND_OK;
}