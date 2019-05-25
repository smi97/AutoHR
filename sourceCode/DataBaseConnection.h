//
// Created by Maxim on 2019-05-19.
//

#ifndef AUTOHR_DBCONNECTION_H
#define AUTOHR_DBCONNECTION_H

#include <libpq-fe.h>
#include "string"

class DataBaseConnection
{
public:
	//DataBaseConnection(); default
	DataBaseConnection(std::string host, std::string name, std::string user, std::string password, int port = 5432);
	std::shared_ptr<PGconn> connection() const;

private:

	std::string db_host;
	int         db_port;
	std::string db_name;
	std::string db_user;
	std::string db_pass;

	std::shared_ptr<PGconn>  db_connection;

};

#endif //AUTOHR_DBCONNECTION_H
