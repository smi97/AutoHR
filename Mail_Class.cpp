#include <iostream>
#include <string>

class Mail() {
public:
    Mail(): server_imap(), timeout(0), errors_count(0) {};
    ~Mail() {};
    bool save_file(std::string directory_resume, int message_id) {

    }
    int* get_new_messages() {

    }
private:
    void connect(std::string login, std::string password){

    }
    std::string server_imap;
    int timeout;
    int errors_count;
}

class MailSend() {
public:
    MailSend(): mail_to_send(""), response(""), server_smtp("") {}
    ~MailSend() {}
    bool send(int time_out) {

    }
    bool connect_to_smtp(std::string login, std::string password) {

    }
private:
    std::string mail_to_send;
    std::string response;
    std::string server_smtp;
};

class MailHR {
public:
    MailHR(): {

    }
    ~MailHR(): {

    }
    bool get_new_resumes() {

    }
    bool send_response(User user) {

    }
private:
    Mail mail;
    MailSend mail_send;
};