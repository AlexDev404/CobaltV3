#include <iostream>
#include <fstream>
//#include <shlobj_core.h>
#include <Windows.h>
#include <sstream>
#include <filesystem>
#include "errors.h"
#include "../options.h"

namespace Colors
{
    inline int cyan = 3;
    inline int lightRed = 12;
    inline int green = 10;
    inline int defaultGray = 7;
}

namespace fs = std::filesystem;

const char* CharPtrToConst(char* c) { return c; }
std::string FloatToStr(float f) { return std::to_string(f); }
std::string IntToStr(int i) { return std::to_string(i); }
//const char* StrToConst(std::string s) { return s.c_str(); }
std::string PathToStr(fs::path p)
{
    std::string pstr = p.u8string();
    return pstr;
}
std::string BoolToStr(bool b)
{
    if (b) return "true";
    else if (!b) return "false";
    return IntToStr(BOOL_TO_STR_FAILED);
}

void WriteToLog(const char* msg)
{
    std::ofstream myfile;
    myfile.open("example.txt", std::ios::app);
    myfile << msg << std::endl;
    myfile.close();
}


void Log(int msg, int color = Colors::defaultGray, bool bNl = true, bool err = false)
{
    if (err)
    {
        Log(std::string("Error Code: #") + IntToStr(msg), Colors::lightRed, true, false, false);
        WriteToLog(std::string("Error Code: #") + IntToStr(msg));
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << msg;
    if (bNl) nl();
}

void Log(std::string msg, int color = Colors::defaultGray, bool bNl = true, bool debug = false, bool rainbowLog = false)
{
    if (debug)
    {
        if (Version == vProd) return;
    }
    if (rainbowLog)
    {
        std::string msgStr = msg;
        bool t = RainbowLog(msgStr);
        if (t)
        {
            if (bNl) nl();
        }
        return;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << msg;
    if (bNl) nl();
}

void Log(const char* msg, int color = Colors::defaultGray, bool bNl = true, bool debug = false, bool rainbowLog = false)
{
    if (debug)
    {
        if (Version == vProd) return;
    }
    if (rainbowLog)
    {
        std::string msgStr = msg;
        bool t = RainbowLog(msgStr);
        if (t)
        {
            if (bNl) nl();
        }
        return;
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    std::cout << msg;
    if (bNl) nl();
}

void nl() { std::cout << std::endl; }

//template <typename T>
bool RainbowLog(std::string msg) // TODO: Add support for const char etc.
{
    /*if (!checkType(msg, "string"))
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, Colors::lightRed);
        std::cout << "[ERROR] ";
        SetConsoleTextAttribute(hConsole, Colors::defaultGray);
        std::cout << "Type was not string!";
        return false;
    } */
    int msgIndex = 0;
    for (int k = 1; k < msg.length() + 1; k++)
    {
        if (msgIndex == msg.length() + 1)
        {
            nl();
            return true;
        }
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
        std::cout << msg[msgIndex];
        msgIndex++;
        if (k == 15) k = 1;
    }
    return true;
}

bool fexists(const fs::path& p)
{
    if (exists(p)) return true;
    else return false;
}

bool fdelete(const fs::path& p)
{
    if (!fexists(p)) return false;
    remove(p);
    WriteToLog(std::string("Deleted ") + PathToStr(p));
}

void fcreate(const fs::path& p)
{
    if (fexists(p)) return;
    fs::create_directory(p);
    WriteToLog(std::string("Created ") + PathToStr(p));
}

const char* GetEnv(const char* envname)
{
    // SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path_tmp);
    char* pValue;
    size_t len;
    errno_t err = _dupenv_s(&pValue, &len, envname);
    return CharPtrToConst(pValue);
}

std::string CobaltPath = GetEnv("APPDATA") + std::string("\\United Backend\\CobaltV2");

std::string GetCobaltPath() { return CobaltPath; }

void InitAD()
{
    if (fexists(CobaltPath)) return;
    fcreate(CobaltPath);
    WriteToLog("Running InitAD..");
    return;
}

template <typename T>
void WriteToLog(T msg)
{
    std::ofstream outfile;
    outfile.open(CobaltPath + "\\logs.txt", std::ios::app); // TODO(Milxnor): name the files the time and date so the logs dont reset every time idk.
    if (!outfile.is_open()) Log(FSTREAM_NOT_OPEN, Colors::defaultGray, true, true);
    outfile << msg << std::endl;
    outfile.close();
}