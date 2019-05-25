//
// Created by Maxim on 2019-05-19.
//

#ifndef AUTOHR_DATABASE_H
#define AUTOHR_DATABASE_H

#include <memory>
#include <mutex>
#include <libpq-fe.h>
#include <string>
#include "iostream"
#include <queue>
#include "DataBaseConnection.h"


class DataBase
{
	std::string host, login, password, name;
	int port;
	void createPool();

	std::mutex db_mutex;
	std::condition_variable db_condition;
	std::queue<std::shared_ptr<DataBaseConnection>> connection_pool;

	const int POOL = 10;

	std::shared_ptr<DataBaseConnection> connection();
	void freeConnection(std::shared_ptr<DataBaseConnection>);

public:
	//DataBase();
	DataBase (std::string host_, std::string name_, std::string login_, std::string password_, int port_ = 5432);

//	std::string buildQuery(std::string method, std::string schema,  std::map<std::string, std::string> arguments = std::map<std::string, std::string>()){
//		std::string result;
//		if(method == "insert")
//			result = method+"into"+schema;
//		if(method == "select")
//
//		return result;
//	}

	pg_result * runQuery(std::string query);

	~DataBase() = default;
};

#endif //AUTOHR_DATABASE_H
