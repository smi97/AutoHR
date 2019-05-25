#include "Mail_Recv.h"

Mail_Recv::Mail_Recv() :
        m_pstrText(nullptr),
        m_eOperationType(POP3_NOOP)
{}

const bool Mail_Recv::CleanupSession()
{
    m_pstrText = nullptr;
    return CMailClient::CleanupSession();
}

const bool Mail_Recv::List(std::string& strList)
{
    m_pstrText = &strList;
    m_eOperationType = POP3_LIST;
    return Perform();
}

const bool Mail_Recv::ListUIDL(std::string& strList)
{
    m_pstrText = &strList;
    m_eOperationType = POP3_UIDL;
    return Perform();
}

const bool Mail_Recv::GetString(const std::string& strMsgNumber, std::string& strOutput)
{
    m_pstrText = &strOutput;
    m_strMsgNumber = strMsgNumber;
    m_eOperationType = POP3_RETR_STRING;
    return Perform();
}

const bool Mail_Recv::GetFile(const std::string& strMsgNumber, const std::string& strFilePath)
{
    m_strLocalFile = strFilePath;
    m_strMsgNumber = strMsgNumber;
    m_eOperationType = POP3_RETR_FILE;
    return Perform();
}

const bool Mail_Recv::GetHeaders(const std::string& strMsgNumber, std::string& strOutput)
{
    m_pstrText = &strOutput;
    m_strMsgNumber = strMsgNumber;
    m_eOperationType = POP3_TOP;
    return Perform();
}

const bool Mail_Recv::Delete(const std::string& strMsgNumber)
{
    m_strMsgNumber = strMsgNumber;
    m_eOperationType = POP3_DELE;
    return Perform();
}

const bool Mail_Recv::Noop()
{
    m_eOperationType = POP3_NOOP;
    return Perform();
}

const bool Mail_Recv::Stat(std::string& strStat)
{
    m_pstrText = &strStat;
    m_eOperationType = POP3_STAT;
    return Perform();
}

void Mail_Recv::ParseURL(std::string& strURL)
{
    std::string strTmp = strURL;
    std::transform(strTmp.begin(), strTmp.end(), strTmp.begin(), ::toupper);

    if (strTmp.compare(0, 8, "POP3S://") == 0 || strTmp.compare(0, 7, "POP3://") == 0)
    {
        if (m_eSslTlsFlags != SslTlsFlag::ENABLE_SSL)
            m_eSslTlsFlags = SslTlsFlag::ENABLE_SSL;
    }
    else if (m_eSslTlsFlags == SslTlsFlag::ENABLE_SSL)
    {
        strURL.insert(0, "pop3s://");
    }
    else
        strURL.insert(0, "pop3://");

    if (strURL.at(strURL.length() - 1) != '/')
        strURL += '/'; // дописывание к URL /

}

const bool Mail_Recv::PrePerform()
{
    std::string strRequestURL(m_strURL);

    switch (m_eOperationType)
    {
        case POP3_TOP:
            if (m_pstrText != nullptr)
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEFUNCTION, &CMailClient::WriteInStringCallback);
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEDATA, m_pstrText);
            }
            else
                return false;

            if (!m_strMsgNumber.empty())
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_CUSTOMREQUEST,
                                 ("TOP " + m_strMsgNumber + " 0").c_str());
            }
            else
                return false;

            break;

        case POP3_NOOP:
            curl_easy_setopt(m_pCurlSession, CURLOPT_CUSTOMREQUEST, "NOOP");
            curl_easy_setopt(m_pCurlSession, CURLOPT_NOBODY, 1L);

            break;

        case POP3_UIDL:
            curl_easy_setopt(m_pCurlSession, CURLOPT_CUSTOMREQUEST, "UIDL");
        case POP3_LIST:
            if (m_pstrText != nullptr)
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEFUNCTION, &CMailClient::WriteInStringCallback);
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEDATA, m_pstrText);
            }
            else
                return false;

            break;

        case POP3_DELE:
            if (!m_strMsgNumber.empty())
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_CUSTOMREQUEST, ("DELE " + m_strMsgNumber).c_str());
                curl_easy_setopt(m_pCurlSession, CURLOPT_NOBODY, 1L);
            }
            else
                return false;

            break;

        case POP3_RETR_STRING:
            if (!m_strMsgNumber.empty())
            {
                strRequestURL += m_strMsgNumber;
            }
            else
                return false;

            if (m_pstrText != nullptr)
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEFUNCTION, &CMailClient::WriteInStringCallback);
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEDATA, m_pstrText);
            }
            else
                return false;
            break;

        case POP3_RETR_FILE:
            if (!m_strMsgNumber.empty())
            {
                strRequestURL += m_strMsgNumber;
            }
            else
                return false;

            m_fLocalFile.open(m_strLocalFile, std::fstream::out | std::fstream::binary | std::fstream::trunc);
            if (m_fLocalFile)
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEFUNCTION, &CMailClient::WriteToFileCallback);
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEDATA, &m_fLocalFile);
            }
            break;

        case POP3_STAT:
            if (m_pstrText != nullptr)
            {
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEFUNCTION, &CMailClient::WriteInStringCallback);
                curl_easy_setopt(m_pCurlSession, CURLOPT_WRITEDATA, m_pstrText);
            }
            else
                return false;

            curl_easy_setopt(m_pCurlSession, CURLOPT_CUSTOMREQUEST, "STAT");
            curl_easy_setopt(m_pCurlSession, CURLOPT_NOBODY, 1L);
            break;
    }

    curl_easy_setopt(m_pCurlSession, CURLOPT_URL, strRequestURL.c_str());

    return true;
}

const bool Mail_Recv::PostPerform()
{
    if (m_eOperationType == POP3_RETR_FILE)
        if (m_fLocalFile.is_open())
            m_fLocalFile.close();

    return true;
}