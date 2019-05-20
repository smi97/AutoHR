#include <curl/curl.h>
#include <iostream>
#include <string.h>
#include <string>
#include <queue>

using namespace std;

//Порты SMTP
//Порт 25 – порт без шифрования
//Порт 465 – порт SSL/TLS, также известный как SMTPS
#define SERVER_PORT_SEND 465

class MailSend {
public:
    MailSend (std::string mServer, unsigned int mPort, std::string mUser, std::string mPassword)
    : Server(mServer), Port(mPort), User(mUser), Password(mPassword), curl(), recipients(NULL)
    {}

    ~MailSend () { // Закрытие соединения
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    bool Send (std::string From,std::string To,std::string Subject,std::string Message) {
        CURLcode res;

        if ( connect() ) {
            queue<string> msg = init_message(To, From, Subject, Message); // create message

            curl_easy_setopt(curl, CURLOPT_MAIL_FROM, From.c_str() );
            recipients = curl_slist_append(recipients, To.c_str() );
            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

            curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
            curl_easy_setopt(curl, CURLOPT_READDATA, &msg );

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res) );
                return false;
            }
            return true;
        }
        return false;
    }
private:
    bool connect() {
        struct curl_slist *recipients = NULL;

        curl = curl_easy_init();
        if ( curl ) {
            curl_easy_setopt(curl, CURLOPT_URL, Server + ":" + Port);
            curl_easy_setopt(curl, CURLOPT_USERNAME, User);
            curl_easy_setopt(curl, CURLOPT_PASSWORD, Password);
            return true;
        }
        return false;
    }

    queue <string> init_message(string to, string from, string subj, string message) {
        queue <string> msg;
        string s = "To: " + to + "\n";
        msg.push(s);
        s = "From: " + from + "\n";
        msg.push(s);
        s = "Subject: " + subj + "\n";
        msg.push(s);
        s = "\n";
        msg.push(s);
        msg.push(message);
        return msg;
    }

    static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {

        queue <string> *msg = (queue <string> *) userp;
        string s;
        if (msg->empty()) {
            return 0;
        }
        else {
            s = msg->front();
            msg->pop();
        }

        memcpy(ptr, s.c_str(), s.size());
        return s.size();
    }

    //variables
    std::string Server;
    unsigned int Port;
    std::string User;
    std::string Password;
    CURL *curl;
    struct curl_slist *recipients;
};

int main() {
    MailSend mailc("smtp://smtp.gmail.com", SERVER_PORT_SEND, "<from_mail>", "<password>");
    mailc.Send("<from_mail>", "<to_mail>", "subject", "Hello from C++ SMTP Client!");

    return 0;
}

