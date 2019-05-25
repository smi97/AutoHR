
#include <ctime>
#include "HRDataBaseController.cpp"

//#include "catch.hpp"

//#define CATCH_CONFIG_MAIN

//CATCH_CONFIG_MAIN
//#include "DBChecker.cpp"


int main()
		{
		/*	DataBaseController db("192.168.56.222",  "resume", "hrmanager", "P@ssw0rd");
			std::vector<std::pair<std::string, std::string>> values;
			std::pair<std::string, std::string> id, date, name, python;

			id.first = "id";
			id.second = "3";

			std::time_t t = std::time(0);   // get time now
			std::tm* now = std::localtime(&t);
			date.first = "date";
			date.second +=  std::to_string(now->tm_year + 1900) + '-' + std::to_string(now->tm_mon + 1) + '-' + std::to_string(now->tm_mday);

			name.first = "name";
			name.second = "name";

			python.first = "python";
			python.second = "TRUE";

			//values.push_back (id);
			values.push_back (date);
			values.push_back (name);
			values.push_back (python);

			//std::cout << "result: " << db.insertRow ("resume", values) << std::endl;

			//std::cout << "result: " << db.insertBoolColumn ("resume", "c++") << std::endl;
*/
			HRDataBaseController hr;
			std::vector<Vacancy> a = hr.getVacancies ();
			time_t data;
			std::vector<int> vec;
			vec.push_back (2);

			User user("name", "no", "rverv", data, "fvrt", vec);
			std::cout << hr.addUser (user);
//			User us = hr.getUser ();
//			std::cout << us.getFIO ();
//			std::vector<std::string> vec = hr.getAllSkills ();



		}








