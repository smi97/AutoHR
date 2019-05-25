//
// Created by Maxim on 2019-04-08.
//

#include <string>
#include "libpq-fe.h"
#include "iostream"
#include <mutex>
#include <queue>
#include "DataBaseController.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include "../Selector/User.cpp"
#include "../Selector/Vacancy.cpp"


class HRDataBaseController
{
	DataBaseController * dataBase;

public:
	HRDataBaseController() {
		dataBase = new DataBaseController("192.168.56.222",  "resume", "hrmanager", "P@ssw0rd");
	}

	bool addSkill(std::string skill)
	{
		std::vector<std::pair<std::string, std::string>> values;
		std::pair<std::string, std::string> date, name, python;

		name.first = "name";
		name.second = skill;

		values.push_back (name);

		dataBase->insertRow ("skills", values);
		dataBase->insertBoolColumn ("vacancies", skill);
		dataBase->insertBoolColumn ("resume", skill);

	}

	User getFirstUnseenUser(){
		PGresult * res = dataBase->getRows ("resume");
		std::vector<int> skills;
		int ncols = PQnfields(res);
		for(int i = 6; i < ncols - 1; i++)
		{
			const char *name = PQfname(res, i);

			if(strcmp (name, "true") == 0)
				skills.push_back (i-7);
		}
		time_t data;

		User user(PQgetvalue(res, 0, 2), PQgetvalue(res, 0, 3), PQgetvalue(res, 0, 4), data, PQgetvalue(res, 0, 1), skills);
		return user;
	}
//	User * getNewUsers(){
//		PGresult * res = dataBase->getRows ("resume", "seen", "false");
//
//		int nrows = PQntuples(res);
//
//		for(int i = 0; i < nrows; i++)
//		{
//			char* id = PQgetvalue(res, i, 0);
//			char* name = PQgetvalue(res, i, 1);
//			char* phone = PQgetvalue(res, i, 2);
//			char* last_changed = PQgetvalue(res, i, 3);
//			printf("Id: %s, Name: %s, Phone: %s, Last changed: %s\n",
//			       id, name, phone, last_changed);
//		}
//
//
//		User * user;
//		return user;
//	}
	std::vector<Vacancy> getVacancies(){
		PGresult * res = dataBase->getRows ("vacancies");
		std::vector<Vacancy> vacancies;
		int nrows = PQntuples(res);
		int ncols = PQnfields(res);

		for(int i = 0; i < nrows; i++)
		{
			std::vector<int> skills;
			for(int i = 2; i < ncols; i++)
			{
				const char *name = PQfname(res, i);

				if(strcmp (name, "true") == 0)
					skills.push_back (i - 2);
			}

			Vacancy vacancy(i, PQgetvalue(res, i, 1), skills);
			vacancies.push_back (vacancy);
		}


		return vacancies;

	}
	bool addVacancy(Vacancy){
		std::vector<std::pair<std::string, std::string>> values;
		std::pair<std::string, std::string> date, name, python;


		std::time_t t = std::time(0);   // get time now
		std::tm* now = std::localtime(&t);

		name.first = "name";
		name.second = "name";

		python.first = "python";
		python.second = "TRUE";

		values.push_back (name);
		values.push_back (python);

		dataBase->insertRow ("vacancies", values);

	}
	bool addCriteriaToVacancy(std::string, Vacancy){

	}
	bool addUser(User resume){


		std::vector<std::pair<std::string, std::string>> values;
		std::pair<std::string, std::string> date, name, surname, phone, email, seen;

		std::time_t t = std::time(0);   // get time now
		std::tm* now = std::localtime(&t);

		name.first = "name";
		name.second = resume.getFIO ();

		surname.first = "surname";
		surname.second = resume.getFIO ();

		date.first = "date";
		date.second +=  std::to_string(now->tm_year + 1900) + '-' + std::to_string(now->tm_mon + 1) + '-' + std::to_string(now->tm_mday);

		phone.first = "phone";
		phone.second = resume.getNomber ();

		email.first = "email";
		email.second = resume.getEmail ();

		seen.first = "seen";
		seen.second = "false";

		std::vector<int> skills_id = resume.getSkills ();
		std::vector<std::string> skills_names = this->getAllSkills ();

		values.push_back (name);
		values.push_back (surname);
		values.push_back (phone);
		values.push_back (date);
		values.push_back (email);

		int i = 0;
		for(auto it = skills_names.begin (); it != skills_names.end (); ++it)
		{
			std::pair<std::string, std::string> skill;
			skill.first = *it;
			if(std::find(skills_id.begin (), skills_id.end (), i) != skills_id.end ())
				skill.second = "true";
			else skill.second = "false";
			++i;
			values.push_back (skill);
		}

		values.push_back (seen);


		return dataBase->insertRow ("resume", values);
	}

	std::vector<std::string> getAllSkills()
	{
		std::vector<std::string> skills;
		PGresult * res = dataBase->getRows ("skills");
		int nrows = PQntuples(res);

		for(int i = 0; i < nrows; i++)
		{
			skills.push_back(PQgetvalue(res, i, 1));
		}
		return skills;
	}

	~HRDataBaseController() = default;
};
