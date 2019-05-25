//
// Created by Maxim on 2019-05-20.
//

#ifndef AUTOHR_DATABASECONTROLLER_H
#define AUTOHR_DATABASECONTROLLER_H

#include "DataBase.h"

class DataBaseController
{
	DataBase * base;
public:
	DataBaseController() = default;
	DataBaseController(std::string host_, std::string name_, std::string login_, std::string password_, int port_ = 5432);
	void dataBaseSettings(std::string host_, std::string name_, std::string login_, std::string password_, int port_ = 5432);
	PGresult * getRows(std::string schema, std::string field, std::string filter);
	PGresult * getRows(std::string schema);
	bool insertRow(std::string schema, std::vector<std::pair<std::string, std::string>> values);
	bool insertBoolColumn(std::string schema, std::string column_name);
	~DataBaseController() = default;
};



#endif //AUTOHR_DATABASECONTROLLER_H
