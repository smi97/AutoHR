#include "parser.h"

parser::parser()
{
    criteria = { "c++", "python"};
    FileName = "text";
}
parser::parser(const char* file_name, std::vector<std::string> &criterias) : criteria(criterias) {
    FileName = file_name;
}

int parser::parse() {
    std::ifstream stream(FileName);
    std::string buf;
    std::regex reg_n(".*(N|n)ame.? (.*)\\.");
    std::regex reg_number("\\x2B{0,1}[0-9]\\x28{0,1}[0-9]{3}\\x29{0,1}[0-9]{3}\\x2D{0,1}[0-9]{2}\\x2D{0,1}[0-9]{2}");
    if (stream.is_open()) {
           while (getline(stream, buf)) {
               std::smatch match;
               for (size_t i = 0; i < criteria.size(); i++) {
                   std::regex reg(criteria[i]);
                   if (std::regex_search(buf, match, reg)) {
                       rez_.AddSkill(i);
                       criteria[i] = match[0];
                   }
               }
               if (std::regex_search(buf, match, reg_number)) rez_.AddNumber(match[0]);
               if (std::regex_search(buf, match, reg_n)) {
                   if (!rez_.flag) {
                       rez_.AddFName(match[2]);
                       rez_.flag = true;
                   }
                   else rez_.AddSName(match[2]);
               }
           }
       }
    stream.close();
    return 0;
}

void parser::print_file(const char* file_name) {
    std::ofstream out(file_name);
    out << "Firstname: " << rez_.FName() << std::endl << "Secondname: " << rez_.SName() << std::endl;
    for (size_t i = 0; i < SKILLS_COUNT; i++) {
        if (rez_[i])
            out << criteria[i] << " - OK" << std::endl;
    }
    out << "Phone: " << rez_.Phone() << std::endl;

    out << std::endl<< std::ctime(rez_.GiveDate()) << std::endl;

    out.close();
}
void parser::print() {
    std::cout << "Firstname: " << rez_.FName() << std::endl << "Secondname: " << rez_.SName() << std::endl;
    for (size_t i = 0; i < SKILLS_COUNT; i++) {
        if (rez_[i])
            std::cout << criteria[i] << " - OK" << std::endl;
    }
    std::cout << "Phone: " << rez_.Phone() << std::endl;
    std::cout << std::endl << std::ctime(rez_.GiveDate()) << std::endl;
}
rezume parser::get_rez() {
    return rez_;
}
