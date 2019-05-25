//
// Created by Maxim on 2019-05-19.
//

#include "DataBaseConnection.h"


DataBaseConnection::DataBaseConnection(std::string host, std::string name, std::string user, std::string password, int port) :
		db_host(host), db_name(name), db_user(user), db_pass(password), db_port(port)
{
	db_connection.reset( PQsetdbLogin(db_host.c_str(), std::to_string(db_port).c_str(), nullptr, nullptr, db_name.c_str(), db_user.c_str(), db_pass.c_str()), &PQfinish );

	if (PQstatus( db_connection.get() ) != CONNECTION_OK && PQsetnonblocking(db_connection.get(), 1) != 0 )
	{
		throw std::runtime_error( PQerrorMessage( db_connection.get() ) );
	}

}


std::shared_ptr<PGconn> DataBaseConnection::connection() const
{
	return db_connection;
}


