//
// Created by Maxim on 2019-04-08.
//

#include <string>


struct User{
	int n;
};
struct Vacancy{
	int n;
};

class DataBase
{
	std::string IP, login, password, type;
	int port;
public:
	DataBase() {}
	DataBase (std::string IP_, std::string login_, std::string password_, std::string type_, int port_) {}
	bool connect(){}
	std::string buildQuery(std::string, std::string){}
	std::string runQuery(){}
	bool disconnect() {}
	~DataBase() = default;
};

class DataBaseController
{
	DataBase base;
public:
	DataBaseController() {}
	std::string * getRows(std::string){}
	bool insertRows(std::string, std::string *){}
	bool insertColumn(std::string, std::string){}
	~DataBaseController() = default;
};


class HRDataBaseController : DataBaseController
{
	DataBase base;
public:
	HRDataBaseController() {}
	User * getAllUsers(){
		User * users = nullptr;
		return users;
	}
	User * getNewUsers(){}
	Vacancy * getVacancies(){}
	bool addVacancy(Vacancy){}
	bool addCriteriaToVacancy(std::string, Vacancy){}
	bool addUser(User){}
	~HRDataBaseController() = default;
};
