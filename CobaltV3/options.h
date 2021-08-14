#pragma once

#include "Utils/enums.h"

constexpr bool SendLogsToConsole = true;
constexpr bool WritePEToLogs = false;
constexpr bool INGAME = true;
const char* FNhost = "idk"; // TODO: Check if fnhost can be a string (No reason for it to error but idk) and check if encryption works with it.
constexpr int vProd = 17;
constexpr int vS13 = 13;
constexpr int Version = vProd;
constexpr bool bIsHybrid = true;
const char* ProxyHost = "";
int HookMethod = KIERO;