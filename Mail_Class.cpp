#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fstream.h>
#include <iostream.h>
#include <windows.h>
#include <winsock2.h>
//Winsock v1.1

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 4096
#define CLIENT_PORT 1234 // после 1024 - незарезервированный

// Получение писем

//Порты IMAP
//Порт 143 – порт без шифрования
//Порт 993 – порт SSL/TLS, также известный как IMAPS

//Порты протокола POP3
//Порт 110 – порт без шифрования
//Порт 995 – порт SSL/TLS, также известный как POP3S
#define SERVER_PORT_RECV 110

//Отправка писем

//Порты SMTP
//Порт 25 – порт без шифрования
//Порт 465 – порт SSL/TLS, также известный как SMTPS
#define SERVER_PORT_SEND 25

#define CRLF "\r\n"                 // carriage-return/line feed pair


class Mail() {
public:
    Mail(): server_imap(), timeout(0), errors_count(0) {};
    ~Mail() {};
    bool save_file(char* directory_resume, int message_id) {

    }
    int* get_new_messages() {

    }
private:
    void connect(int* s, char* host, char* login, char* password){
        int rez;
        char buf[BUF_SIZE];

        struct hostent *hp;
        struct sockaddr_in clnt_sin;
        struct sockaddr_in srv_sin;

        //создание сокета
        *s = socket (AF_INET, SOCK_STREAM, 0);
        memset ((char *)&clnt_sin, '\0', sizeof(clnt_sin));
        //установка sockaddr структуры
        clnt_sin.sin_family = AF_INET;
        clnt_sin.sin_addr.s_addr = INADDR_ANY;
        clnt_sin.sin_port = CLIENT_PORT;
        //связываем сокет с адресом
        bind (*s, (struct sockaddr *)&clnt_sin, sizeof(clnt_sin));
        memset ((char *)&srv_sin, '\0', sizeof(srv_sin));
        srv_sin.sin_family = AF_INET;
        hp = gethostbyname (host);     //адрес узла по имени
        memcpy ((char *)&srv_sin.sin_addr, hp->h_addr, hp->h_length); //копирование адреса удаленного узла в структуру srv_sin
        srv_sin.sin_port = htons(SERVER_PORT_RECV);  //заполнения адреса порта сервера с сетевым порядком расположения байтов

        fprintf (stderr, "Connecting to \'%s\'\n", host);
        rez = connect (*s, (struct sockaddr *)&srv_sin, sizeof(srv_sin));
        //fprintf (stderr, "%d: %s\n", rez, strerror(errno));

        rez = recv (*s, buf, BUF_SIZE, 0);
        buf[rez] = '\0';
        //fprintf (stderr, "< %s", buf);

        sprintf (buf, "USER %s\n", user);
        transaction (*s, buf);          //отправка команды USER логин
        sprintf (buf, "PASS %s\n", password);
        transaction (*s, buf);          //отправка команды PASS пароль
    }

    // Здесь используется протокол POP3 для получения все письма
    // Протокол IMAP получает только заголовки писем
    int transaction (int s, char* message)    //Функция отправки запросов POP3-серверу
    {
        int recv_len;
        char buf[BUF_SIZE];
        strcpy (buf, message);

        send (s, buf, strlen(buf), 0);          //Отправить запрос
        recv_len = recv (s, buf, BUF_SIZE, 0);  //Получить ответ
        buf[recv_len] = '\0';
        fprintf (stderr, "< %s", buf);

        if (!strncmp (buf, "+OK", 3))
            return 0;
        else
            return 1;
    }

    std::string server_pop3;
    int timeout;
    int errors_count;
}

class MailSend() {
public:
    MailSend(): mail_to_send(""), response(""), server_smtp("") {}
    ~MailSend() {}
    bool send_to_smtp(std::string login, std::string password) {
        int         iProtocolPort        = 0;
        char        szFromAddr[64]       = "";
        char        szBuffer[4096]       = "";
        char        szLine[255]          = "";
        SOCKET      hServer;
        WSADATA     WSData;
        LPHOSTENT   lpHostEntry;
        LPSERVENT   lpServEntry;
        SOCKADDR_IN SockAddr;
        // Lookup email server IP address.
        lpHostEntry = gethostbyname(server_smtp);
        if ( !lpHostEntry )
        {
            cout << "Cannot find SMTP mail server " << server_smtp << endl;
            return false;
        }

        // создание сокета
        hServer = socket(PF_INET, SOCK_STREAM, 0);
         if ( hServer == INVALID_SOCKET )
        {
            cout << "Cannot open mail server socket" << endl;
            return false;
        }

        // получение mail порта
        lpServEntry = getservbyname("mail", 0);

        if ( !lpServEntry )
            iProtocolPort = htons(IPPORT_SMTP);
        else
            iProtocolPort = lpServEntry->s_port;

        // установка sockaddr структуры
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_port   = iProtocolPort;
        SockAddr.sin_addr   = *((LPIN_ADDR)*lpHostEntry->h_addr_list);

        // подключаемся к сокету
        if (connect(hServer, (PSOCKADDR) &SockAddr, sizeof(SockAddr)))
        {
            cout << "Error connecting to Server socket" << endl;
            return false;
        }

        // Получение ответа инициализации от smtp сервера
        Check(recv(hServer, szBuffer, sizeof(szBuffer), 0), "recv() Reply");

        // Отправка HELO server.com
        sprintf( response, "HELO %s%s", SmtpServerName, CRLF );
        Check( send( hServer, response, strlen( response ), 0 ), "send() HELO" );
        Check( recv( hServer, szBuffer, sizeof( szBuffer ), 0 ), "recv() HELO" );

        // Отправка MAIL FROM: <sender@mydomain.com>
        sprintf( szMsgLine, "MAIL FROM:<%s>%s", mail_from_send, CRLF );
        Check( send( hServer, response, strlen( response ), 0), "send() MAIL FROM" );
        Check( recv( hServer, szBuffer, sizeof( szBuffer ), 0), "recv() MAIL FROM" );

        // Отправка RCPT TO: <receiver@domain.com>
        sprintf( szMsgLine, "RCPT TO:<%s>%s", mail_to_send, CRLF);
        Check( send( hServer, response, strlen(response), 0), "send() RCPT TO");
        Check( recv( hServer, szBuffer, sizeof(szBuffer), 0), "recv() RCPT TO");

        // Отправка DATA
        sprintf( szMsgLine, "DATA%s", CRLF);
        Check( send( hServer, response, strlen(response), 0), "send() DATA");
        Check( recv( hServer, szBuffer, sizeof(szBuffer), 0), "recv() DATA");

        // Отправка пустой стоки
        sprintf( szMsgLine, "%s.%s", CRLF, CRLF);
        Check( send( hServer, response, strlen(response), 0), "send() end-message");
        Check( recv( hServer, szBuffer, sizeof(szBuffer), 0), "recv() end-message");

        // Отправка QUIT
        sprintf (szMsgLine, "QUIT%s", CRLF);
        Check( send( hServer, response, strlen(response), 0), "send() QUIT");
        Check( recv( hServer, szBuffer, sizeof(szBuffer), 0), "recv() QUIT");

        // Report message has been sent
        cout << "Sent " << argv[4] << " as email message to " << mail_to_send << endl;

        // Закрываем соединение с сокетом
        closesocket( hServer );
        WSACleanup();

        return 0;
    }
private:
    void Check(int iStatus, char *szFunction)  // Проверка на ошибки send() и recv()
    {
        if((iStatus != SOCKET_ERROR) && (iStatus))
            return;

        cerr << "Error during call to " << szFunction << ": " << iStatus << " - " << GetLastError() << endl;
    }

    std::string mail_to_send;
    std::string response;
    std::string server_smtp;
};

class MailHR {
public:
    MailHR(): {

    }
    ~MailHR(): {}
    bool get_new_resumes() {

    }
    bool send_response(User user) {

    }
private:
    Mail mail;
    MailSend mail_send;
};

int main() {
    return 0;
}