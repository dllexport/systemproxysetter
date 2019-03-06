//
// Created by mario on 3/5/2019.
//
#pragma once

#include <string>

void SetGlobalProxy(std::string ip, std::string port);
void SetPacProxy(std::string pac_url);
void SetNoProxy();

