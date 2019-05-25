#ifndef INCLUDE_MAIL_RECV_H_
#define INCLUDE_MAIL_RECV_H_

#include "Mail_Client.h"

class Mail_Recv : public CMailClient
{
public:
    explicit Mail_Recv();

    Mail_Recv(const Mail_Recv& Copy) = delete;
    Mail_Recv& operator=(const Mail_Recv& Copy) = delete;

    const bool CleanupSession() override;

    const bool List(std::string& strList);

    const bool ListUIDL(std::string& strList);

    const bool GetString(const std::string& strMsgNumber, std::string& strOutput);
    const bool GetFile(const std::string& strMsgNumber, const std::string& strFilePath);

    const bool GetHeaders(const std::string& strMsgNumber, std::string& strOutput);

    const bool Delete(const std::string& strMsgNumber);

    const bool Noop();

    const bool Stat(std::string& strStat);

protected:
    enum MailOperation
    {
        POP3_LIST,
        POP3_RETR_STRING,
        POP3_RETR_FILE,
        POP3_DELE,
        POP3_UIDL,
        POP3_TOP,
        POP3_STAT,
        POP3_NOOP
    };

    const bool PrePerform() override;
    const bool PostPerform();
    inline void ParseURL(std::string& strURL) override final;

    MailOperation        m_eOperationType;

    std::string          m_strMsgNumber;
    std::string*         m_pstrText;

};

#endif