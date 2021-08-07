#pragma once

#include "../options.h"
#include <Windows.h>
#include <iostream>
#include <xorstr.hpp>

class Utils
{
	Utils() {}
public:
	static void ConstructUEConsole()
	{
	
	}
	static void EnableConsole()
	{
		AllocConsole();

		FILE* a;
		freopen_s(&a, ENC("CONIN$"), "w", stdin);
		if (SendLogsToConsole)
		{
			freopen_s(&a, ENC("CONOUT$"), "w", stdout);
			freopen_s(&a, ENC("CONOUT$"), "w", stderr);
		}
		if(WritePEToLogs) freopen_s(&a, ENC("logs.txt"), "w", stdout);
	}
};