//
// Created by mario on 3/5/2019.
//
/*
 *
 * we only modify pac and socks5 proxy setting
 * if other proxy method is set, we just ignore it
 *
 */
#ifdef __APPLE__

#include "proxysetting.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string getdefault_if()
{
    auto default_if = exec("networksetup -listnetworkserviceorder | awk -F'\\\\) ' '/\\(1\\)/ {print $2}'");
    return default_if.substr(0, default_if.length() - 1);
}

void SetGlobalProxy(std::string ip, std::string port)
{
    SetNoProxy();
    std::string globalproxy_str = "networksetup -setsocksfirewallproxy \""+ getdefault_if() +"\" \""+ ip + "\"" + " \""+ port + "\"";
    exec(globalproxy_str.c_str());
    return;
}

void SetPacProxy(std::string pac_url)
{
    SetNoProxy();
    std::string pac_str = "networksetup -setautoproxyurl \""+ getdefault_if() +"\" \""+ pac_url + "\"";
    exec(pac_str.c_str());
}

void SetNoProxy()
{
    std::string disable_socks5_str = "networksetup -setsocksfirewallproxystate \""+ getdefault_if() + "\" off";
    std::string disable_pac_str = "networksetup -setautoproxystate \""+ getdefault_if() + "\" off";

    exec(disable_socks5_str.c_str());
    exec(disable_pac_str.c_str());
}

#endif
