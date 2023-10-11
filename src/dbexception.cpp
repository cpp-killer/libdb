#include "dbexception.h"
#include <stdio.h>
#include <stdarg.h>
#include <sstream>

dbexception::dbexception(const int & ErrorNo, const char *Format,...)
{
    va_list arg;
    va_start(arg,Format);
	char va_buffer[512] = {0};
    vsprintf(va_buffer,Format,arg);
    va_end(arg);
    
    this->ErrorNo = static_cast<int>(ErrorNo);
    this->ErrorMessage = static_cast<std::string>(va_buffer);

    this->File = static_cast<std::string>(__FILE__);
    this->Line = static_cast<int>(__LINE__);
}

dbexception::~dbexception()
{

}

int dbexception::GetErrorNo()const
{
    return ErrorNo;
}

std::string dbexception::GetErrorMessage()const
{
    return ErrorMessage;
}

/* Get string format is "ErrorNo,ErrorMessage */
std::string dbexception::GetErrorNoAndMessage()const
{
	std::stringstream  streamValue;
	std::string        sValue;

    streamValue << ErrorNo;
    streamValue << ",";
    streamValue >> sValue;

    sValue += ErrorMessage;

    return sValue;
}

std::string dbexception::GetFile()const
{
    return File;
}

int dbexception::GetLine()const
{
    return Line;
}

// g++ -g -shared -fPIC -o ../../../lib/libexception.so.1.0 Exception.cpp -I../../../include -I../../../include/lib -Wall



