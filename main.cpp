#include "Mail_Send.cpp"
#include "Mail_Recv.cpp"
#include "Mail_Send.h"
#include "Mail_Recv.h"
#include <string>

int main() {
    // SMTP
    Mail_Send SMTPClient;
    std::string strMail = "Subject: Test SMTP Client\n\nThis email is sent via MailClient-C++ API.\n";
    SMTPClient.InitSession("smtp.gmail.com:465", "username@gmail.com", "password",
                           CMailClient::SettingsFlag::NO_FLAGS, CMailClient::SslTlsFlag::ENABLE_SSL);

    bool bResSendStr = SMTPClient.SendString("<foo@gmail.com>", "<toto@yahoo.com>", "", strMail);

    // POP3
    CPOPClient POPClient;
    POPClient.InitSession("pop.gmail.com:995", "username@gmail.com", "password",
                          CMailClient::SettingsFlag::ALL_FLAGS, CMailClient::SslTlsFlag::ENABLE_SSL);

    std::string strEmail;
    bool bResRcvStr = POPClient.GetString("1", strEmail);

    bool bResRcvStr = POPClient.GetFile("1", "email_1.txt");
    return 0;
}