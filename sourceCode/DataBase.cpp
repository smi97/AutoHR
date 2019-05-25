//
// Created by Maxim on 2019-05-19.
//

#include "DataBase.h"

#include <string>
#include "iostream"


pg_result * DataBase::runQuery(std::string query){
	PGresult * res = nullptr;
	auto conn = this->connection();
	res = PQexec(conn->connection().get(), query.c_str());
	int s = PQntuples(res);
	freeConnection (conn);
	return res;
}

DataBase::DataBase(std::string host_, std::string name_, std::string login_, std::string password_, int port_) :
		host(host_), login(login_), password(password_), name(name_)
{

	createPool();

}

void DataBase::createPool()
{
	std::lock_guard<std::mutex> locker_( db_mutex );

	for ( auto i = 0; i < POOL; ++i ){
		connection_pool.emplace ( std::make_shared<DataBaseConnection>(host, name, login, password) );
	}
}

std::shared_ptr<DataBaseConnection> DataBase::connection()
{

	std::unique_lock<std::mutex> lock_( db_mutex );

	while ( connection_pool.empty() ){
		db_condition.wait( lock_ );
	}

	auto conn_ = connection_pool.front();
	connection_pool.pop();

	return  conn_;
}


void DataBase::freeConnection(std::shared_ptr<DataBaseConnection> conn_)
{
	std::unique_lock<std::mutex> lock_( db_mutex );
	connection_pool.push( conn_ );
	lock_.unlock();
	db_condition.notify_one();
}