#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <iostream>
#include <string>

class dbexception
{
public:
	dbexception(const int &ErrorNo,const char *Format,...);
    virtual ~dbexception();

    virtual int     GetErrorNo()const;
    virtual std::string  GetErrorMessage()const;
    virtual std::string  GetErrorNoAndMessage()const;

    virtual int     GetLine()const;
    virtual std::string  GetFile()const;
    
protected:

private:
    int     ErrorNo;
    std::string  ErrorMessage;
    
    std::string  File;
    int     Line;

    
};

#endif


