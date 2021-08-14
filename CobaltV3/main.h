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
_________     ______        _____________    _______
__  ____ / ________ / _______ ___ / _ / __ |  / /_ | __ \
_ / _  __ \_  __ \  __ `/_ / _  __ / _ | / /____/ /
/ /___  / /_/ /  /_/ / /_/ /_  / / /_ __ |/ / _  __ /
\____ / \____//_.___/\__,_/ /_/  \__/ _____/  /____/ 
)");
    Log(ascii);
    Log("\nLaunching CobaltV2!"); //(" + ver);
    Log(std::string("Redirecting to ") + FNhost, true, true);
}
