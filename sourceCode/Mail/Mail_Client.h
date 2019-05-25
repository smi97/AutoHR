#ifndef INCLUDE_MAIL_CLIENT_H_
#define INCLUDE_MAIL_CLIENT_H_


#include <algorithm>
#include <cstddef>         // std::size_t
#include <cstdio>          // snprintf
#include <cstdlib>
#include <cstring>         // strerror, strlen, memcpy, strcpy
#include <ctime>
#include <curl/curl.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <mutex>
#include <stdarg.h>        // va_start, etc...
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <memory>          // std::unique_ptr


class CMailClient
{
public:
    struct ProgressFnStruct
    {
        ProgressFnStruct() : dLastRunTime(0), pCurl(nullptr), pOwner(nullptr) {}
        double dLastRunTime;
        CURL*  pCurl;

        void*  pOwner;
    };

    enum SettingsFlag
    {
        NO_FLAGS    = 0x00,
        ENABLE_LOG  = 0x01,
        VERIFY_PEER = 0x02,
        VERIFY_HOST = 0x04,
        ALL_FLAGS   = 0xFF
    };

    enum SslTlsFlag
    {
        NO_SSLTLS  = 0x00,
        ENABLE_TLS = 0x01,
        ENABLE_SSL = 0x02
    };

    explicit CMailClient();
    virtual ~CMailClient();

    CMailClient(const CMailClient& Copy) = delete; // копирующий конструктор
    CMailClient& operator=(const CMailClient& Copy) = delete; // оператор присваивания

    void SetProxy(const std::string& strProxy);
    inline void SetTimeout(const int& iTimeout) { m_iCurlTimeout = iTimeout; }
    inline void SetNoSignal(const bool& bNoSignal) { m_bNoSignal = bNoSignal; }

    inline const std::string& GetProxy() const { return m_strProxy; }
    inline const int GetTimeout() const { return m_iCurlTimeout; }
    inline const bool GetNoSignal() const { return m_bNoSignal; }
    inline const std::string& GetURL()      const { return m_strURL; }
    inline const std::string& GetUsername() const { return m_strUserName; }
    inline const std::string& GetPassword() const { return m_strPassword; }
    inline const unsigned char GetFlags() const { return m_eSettingsFlags; }
    inline const SslTlsFlag GetSslTlsFlags() const { return m_eSslTlsFlags; }

    const bool InitSession(const std::string& strHost, // сессия
                           const std::string& strLogin,
                           const std::string& strPassword,
                           const SettingsFlag& SettingsFlags = ALL_FLAGS,
                           const SslTlsFlag& SslTlsFlags = NO_SSLTLS);
    virtual const bool CleanupSession();
    static int GetCurlSessionCount() { return s_iCurlSession; }
    const CURL* GetCurlPointer() const { return m_pCurlSession; }

    static const std::string& GetCertificateFile() { return s_strCertificationAuthorityFile; }
    static void SetCertificateFile(const std::string& strPath) { s_strCertificationAuthorityFile = strPath; }

    void SetSSLCertFile(const std::string& strPath) { m_strSSLCertFile = strPath; }
    const std::string& GetSSLCertFile() const { return m_strSSLCertFile; }

    void SetSSLKeyFile(const std::string& strPath) { m_strSSLKeyFile = strPath; }
    const std::string& GetSSLKeyFile() const { return m_strSSLKeyFile; }

    void SetSSLKeyPassword(const std::string& strPwd) { m_strSSLKeyPwd = strPwd; }
    const std::string& GetSSLKeyPwd() const { return m_strSSLKeyPwd; }

protected:
    virtual const bool PrePerform() { return true; }
    const bool Perform();
    virtual const bool PostPerform(CURLcode ePerformCode) {  return true; }
    virtual inline void ParseURL(std::string& strURL) { }

    // Curl callbacks
    static size_t WriteInStringCallback(void* ptr, size_t size, size_t nmemb, void* data);
    static size_t WriteToFileCallback(void* ptr, size_t size, size_t nmemb, void* data);
    static size_t ReadLineFromFileStreamCallback(void* ptr, size_t size, size_t nmemb, void* stream);
    static size_t ReadLineFromStringStreamCallback(void* ptr, size_t size, size_t nmemb, void* userp);
    static size_t ReadFromFileCallback(void* ptr, size_t size, size_t nmemb, void* stream);


#ifdef DEBUG_CURL
    static int DebugCallback(CURL* curl, curl_infotype curl_info_type, char* strace, size_t nSize, void* pFile);
   inline void StartCurlDebug();
   inline void EndCurlDebug();
#endif

    std::string          m_strUserName;
    std::string          m_strPassword;
    std::string          m_strURL;
    std::string          m_strProxy;

    bool                 m_bNoSignal;

    std::string          m_strLocalFile;
    std::fstream         m_fLocalFile;
    std::istringstream   m_ssString;

    static std::string   s_strCertificationAuthorityFile; // SSL
    std::string          m_strSSLCertFile;
    std::string          m_strSSLKeyFile;
    std::string          m_strSSLKeyPwd;

    static std::mutex     s_mtxCurlSession; // mutex
    volatile static int   s_iCurlSession;   // перемещение по актуальым сессиям

    mutable CURL*         m_pCurlSession;
    struct curl_slist*    m_pRecipientslist;
    int                   m_iCurlTimeout;
    SettingsFlag          m_eSettingsFlags;
    SslTlsFlag            m_eSslTlsFlags;

};

#endif