#ifndef INCLUDE_MAIL_SEND_H_
#define INCLUDE_MAIL_SEND_H_

#include "Mail_Client.h"

class Mail_Send : public CMailClient
{
public:
    explicit Mail_Send();

    Mail_Send(const Mail_Send& Copy) = delete;
    Mail_Send& operator=(const Mail_Send& Copy) = delete;

    const bool SendString(const std::string& strFrom, const std::string& strTo,
                          const std::string& strCc, const std::string& strMail);

    const bool SendFile(const std::string& strFrom, const std::string& strTo,
                        const std::string& strCc, const std::string& strPath);

    const bool VerifyAddress(const std::string& strAddress);

    const bool ExpandMailList(const std::string& strListName);

protected:
    enum MailOperation
    {
        SMTP_SEND_STRING,
        SMTP_SEND_FILE,
        SMTP_VRFY,
        SMTP_EXPN
    };

    const bool PrePerform() override;
    const bool PostPerform(CURLcode ePerformCode) override;
    inline void ParseURL(std::string& strURL) override final;

    MailOperation        m_eOperationType;

    std::string          m_strFrom;
    std::string          m_strTo;
    std::string          m_strCc;
    std::string          m_strMail;

};

#endif