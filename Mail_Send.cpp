#include "Mail_Send.h"

Mail_Send::Mail_Send() :
        m_eOperationType(SMTP_SEND_STRING)
{}

const bool Mail_Send::SendString(const std::string& strFrom, const std::string& strTo,
                                   const std::string& strCc, const std::string& strMail)
{
    m_strFrom = strFrom;
    m_strTo = strTo;
    m_strCc = strCc;
    m_strMail = strMail;
    m_eOperationType = SMTP_SEND_STRING;

    return Perform();
}

const bool Mail_Send::SendFile(const std::string& strFrom, const std::string& strTo,
                                 const std::string& strCc, const std::string& strPath)
{
    m_strFrom = strFrom;
    m_strTo = strTo;
    m_strCc = strCc;
    m_strLocalFile = strPath;
    m_eOperationType = SMTP_SEND_FILE;

    return Perform();
}

const bool Mail_Send::VerifyAddress(const std::string& strAddress)
{
    m_strTo = strAddress;
    m_eOperationType = SMTP_VRFY;

    return Perform();
}

const bool Mail_Send::ExpandMailList(const std::string& strListName)
{
    m_strMail = strListName;
    m_eOperationType = SMTP_EXPN;

    return Perform();
}

void Mail_Send::ParseURL(std::string& strURL)
{
    std::string strTmp = strURL;
    std::transform(strTmp.begin(), strTmp.end(), strTmp.begin(), ::toupper);

    if (strTmp.compare(0, 8, "SMTPS://") == 0 || strTmp.compare(0, 7, "SMTP://") == 0)
    {
        if (m_eSslTlsFlags != SslTlsFlag::ENABLE_SSL)
            m_eSslTlsFlags = SslTlsFlag::ENABLE_SSL;
    }
    else if (m_eSslTlsFlags == SslTlsFlag::ENABLE_SSL)
    {
        strURL.insert(0, "smtps://");
    }
    else
        strURL.insert(0, "smtp://");
}

const bool Mail_Send::PrePerform()
{
    m_ssString.clear();

    switch (m_eOperationType)
    {
        case SMTP_SEND_STRING:
            if (!m_strFrom.empty() && !m_strTo.empty())
            {
                m_ssString.str(m_strMail);
                curl_easy_setopt(m_pCurlSession, CURLOPT_MAIL_FROM, m_strFrom.c_str());

                m_pRecipientslist = curl_slist_append(m_pRecipientslist, m_strTo.c_str());

                if (!m_strCc.empty())
                    m_pRecipientslist = curl_slist_append(m_pRecipientslist, m_strCc.c_str());

                curl_easy_setopt(m_pCurlSession, CURLOPT_MAIL_RCPT, m_pRecipientslist);

                curl_easy_setopt(m_pCurlSession, CURLOPT_READFUNCTION, ReadLineFromStringStreamCallback);
                curl_easy_setopt(m_pCurlSession, CURLOPT_READDATA, &m_ssString);
                curl_easy_setopt(m_pCurlSession, CURLOPT_UPLOAD, 1L);
            }
            else
                return false;
            break;

        case SMTP_SEND_FILE:
            if (!m_strLocalFile.empty() && !m_strFrom.empty() && !m_strTo.empty())
            {
                m_fLocalFile.open(m_strLocalFile, std::fstream::in);

                if (m_fLocalFile)
                {
                    m_fLocalFile.seekg(0);

                    curl_easy_setopt(m_pCurlSession, CURLOPT_READFUNCTION, CMailClient::ReadLineFromFileStreamCallback);
                    curl_easy_setopt(m_pCurlSession, CURLOPT_READDATA, &m_fLocalFile);
                    curl_easy_setopt(m_pCurlSession, CURLOPT_UPLOAD, 1L);
                }
                curl_easy_setopt(m_pCurlSession, CURLOPT_MAIL_FROM, m_strFrom.c_str());
                m_pRecipientslist = curl_slist_append(m_pRecipientslist, m_strTo.c_str());

                if (!m_strCc.empty())
                    m_pRecipientslist = curl_slist_append(m_pRecipientslist, m_strCc.c_str());

                curl_easy_setopt(m_pCurlSession, CURLOPT_MAIL_RCPT, m_pRecipientslist);
            }
            else
                return false;

            break;

        case SMTP_VRFY:
            if (!m_strTo.empty())
            {
                if (m_strTo.at(0) != '<')
                    m_strTo.insert(0, "<");

                if (m_strTo.at(m_strTo.length() - 1) != '>')
                    m_strTo += '>';

                m_pRecipientslist = curl_slist_append(m_pRecipientslist, m_strTo.c_str());
                curl_easy_setopt(m_pCurlSession, CURLOPT_MAIL_RCPT, m_pRecipientslist);
            }
            else
                return false;

            break;

        case SMTP_EXPN:
            m_pRecipientslist = curl_slist_append(m_pRecipientslist, m_strMail.c_str());
            curl_easy_setopt(m_pCurlSession, CURLOPT_MAIL_RCPT, m_pRecipientslist);
            curl_easy_setopt(m_pCurlSession, CURLOPT_CUSTOMREQUEST, "EXPN");
            break;

    }

    curl_easy_setopt(m_pCurlSession, CURLOPT_URL, m_strURL.c_str());

    return true;
}

const bool Mail_Send::PostPerform(CURLcode ePerformCode)
{
    if (m_eOperationType == SMTP_SEND_FILE)
        if (m_fLocalFile.is_open())
            m_fLocalFile.close();

    return true;
}
