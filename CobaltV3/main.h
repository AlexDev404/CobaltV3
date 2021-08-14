#pragma once

#include <Windows.h>
#include "hooks.h"
#include "Utils/hook.h"
#include "Utils/logs.h"

using namespace Logs;
using namespace File;

void Main()
{
    fdelete(std::string(GetCobaltPath() + "\\logs.txt"));
    fcreate(std::string(GetCobaltPath() + "\\logs.txt"));
    Curl::Curl();
    Hooking::Hook((void*)CurlEasyOptP, Curl::CurlHook, (void**)&_curl_easy_setopt, HookMethod);
    //if (bIsS13 && PROCESSEVENTHOOK) Hooking::Hook((void*)S13PEP, ProcessEvent::S13PE, S13PEOG, HookMethod);
    //if (bIsProd && PROCESSEVENTHOOK) Hooking::Hook((void*)PRODPEP, ProcessEvent::PRODPE, PRODPEOG, HookMethod);
    const char* ascii = ENC(R"(
   ___         _             _  _            _____ 
  / __\  ___  | |__    __ _ | || |_ /\   /\ |___ / 
 / /    / _ \ | '_ \  / _` || || __|\ \ / /   |_ \ 
/ /___ | (_) || |_) || (_| || || |_  \ V /   ___) |
\____/  \___/ |_.__/  \__,_||_| \__|  \_/   |____/ 
)");
    Log(ascii);
    Log("\nLaunching CobaltV2!"); //(" + ver);
    Log(std::string("Redirecting to ") + FNhost, true, true);
}
