//
// Created by mario on 3/5/2019.
//
#ifdef _WIN32

#include "proxysetting.h"
#define UNICODE

#include <iostream>
#include <Windows.h>
#include <WinInet.h>
#pragma comment(lib, "wininet.lib")
#include <codecvt>
#include <string>


void SetGlobalProxy(std::string ip, std::string port)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring global_proxy_setting = converter.from_bytes(ip + ":" + port);

    LPCTSTR local_proxy_setting = L"<local>";

    INTERNET_PER_CONN_OPTION_LIST OptionList;
    INTERNET_PER_CONN_OPTION Option[3];
    unsigned long listSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);


    Option[0].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
    Option[0].Value.pszValue = (LPWSTR)global_proxy_setting.c_str();

    Option[1].dwOption = INTERNET_PER_CONN_FLAGS;
    Option[1].Value.dwValue = PROXY_TYPE_PROXY;

    Option[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
    Option[2].Value.pszValue = (LPWSTR)local_proxy_setting;


    OptionList.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    OptionList.pszConnection = NULL;
    OptionList.dwOptionCount = 3;
    OptionList.dwOptionError = 0;
    OptionList.pOptions = Option;

    if (!InternetSetOption(0, INTERNET_OPTION_PER_CONNECTION_OPTION, &OptionList, listSize)) {
        printf("err\n");

    }

    InternetSetOption(0, INTERNET_OPTION_REFRESH, NULL, NULL);

}

void SetPacProxy(std::string pac_url)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring pac_proxy_setting = converter.from_bytes(pac_url);

    INTERNET_PER_CONN_OPTION_LIST OptionList;
    INTERNET_PER_CONN_OPTION Option[2];
    unsigned long listSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

    Option[0].dwOption = INTERNET_PER_CONN_AUTOCONFIG_URL;
    Option[0].Value.pszValue = (LPWSTR)pac_proxy_setting.c_str();

    Option[1].dwOption = INTERNET_PER_CONN_FLAGS;
    Option[1].Value.dwValue = PROXY_TYPE_AUTO_PROXY_URL;


    OptionList.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    OptionList.pszConnection = NULL;
    OptionList.dwOptionCount = 2;
    OptionList.dwOptionError = 0;
    OptionList.pOptions = Option;

    if (!InternetSetOption(0, INTERNET_OPTION_PER_CONNECTION_OPTION, &OptionList, listSize)) {
        printf("err\n");
    }

    InternetSetOption(0, INTERNET_OPTION_REFRESH, NULL, NULL);

}

void SetNoProxy()
{

    INTERNET_PER_CONN_OPTION_LIST OptionList;
    INTERNET_PER_CONN_OPTION Option[1];
    unsigned long listSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

    Option[0].dwOption = INTERNET_PER_CONN_FLAGS;
    Option[0].Value.dwValue = PROXY_TYPE_DIRECT;


    OptionList.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    OptionList.pszConnection = NULL;
    OptionList.dwOptionCount = 1;
    OptionList.dwOptionError = 0;
    OptionList.pOptions = Option;

    if (!InternetSetOption(0, INTERNET_OPTION_PER_CONNECTION_OPTION, &OptionList, listSize)) {
        printf("err\n");
    }

    InternetSetOption(0, INTERNET_OPTION_REFRESH, NULL, NULL);

}

#endif
