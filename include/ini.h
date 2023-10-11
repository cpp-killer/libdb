////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013, eeechina
// All rights reserved.
//
// Filename     : Macro.h
// Project Code : The project code about this file
// Abstract     : Describe the content of this file summarily
// Reference    : ......
//
// Version      : 2.Asad   ftgf cc    32        0
// Author       : lxmy
// Accomplished date : March 20, 2013
//
// Replaced version  :  1.0 
// Original Author   : lxmy
// Accomplished date : March 20, 2013
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#ifndef INI_H
#define INI_H
#include "dbglobal.h"
#include <map>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

/* key,key's ,description,value */
typedef map<string,pair<string,string> > keymap;
/* section,section's description,key,key's description,value */
typedef map<string,pair<string,keymap> > inimap;

class CIni
{
public:
    CIni(const string &IniFile);
    ~CIni();

public:
     /* Update memory data to configure file */
     int     Update();
     /* Clear configure */
     void    Clear();
     /* Read string type data from configure file */
     string  ReadString(const string &Section,const string &Key,const string &defaultValue = "");
     /* Write string type data to configure file */
     void    WriteString(const string &Section,const string &Key,const string &Value);
     /* Modify string type data in the configure file */
     int     ModifyString(const string &Section,const string &Key,const string &Value);
     /* Read integer type data from configure file */
     int     ReadInteger(const string &Section,const string &Key, int defaultValue = 0);
     /* Write integer type data to configure file */
     void    WriteInteger(const string &Section,const string &Key,int Value);
     /* Modify integer type data in the configure file */
     int     ModifyInteger(const string &Section,const string &Key,int Value);
     /* Read double type data from configure file */
     double  ReadDouble(const string &Section,const string &Key,double defaultValue = 0.0);
     /* Write double type data to configure file */
     void    WriteDouble(const string &Section,const string &Key,double Value);
     /* Modifydouble type data in the configure file */
     int     ModifyDouble(const string &Section,const string &Key,double Value);
     /* Read bool type data from configure file */
     bool    ReadBool(const string &Section,const string &Key,bool defaultValue = false);
     /* Write bool type data to configure file */
     void    WriteBool(const string &Section,const string &Key,bool Value);
     /* Modify bool type data in the configure file */
     int     ModifyBool(const string &Section,const string &Key,bool Value);
     /* Write section */
     void    WriteSection(const string & Section);
     
     /* Read section description in the configure file */    
     string  ReadSectionDescription(const string &Section);
     /* Read key description in the configure file */
     string  ReadKeyDescription(const string &Section,const string &Key);
     /* Write section's description data to configure file */
     int     WriteSectionDescription(const string &Section,const string &Description);
     /* Write key's description data to configure file */
     int     WriteKeyDescription(const string &Section,const string &Key,const string &Description);
     /* Modify section description in the configure file */
     int     ModifySectionDescription(const string &Section,const string &Description);
     /* Modify Key description in the configure file */
     int     ModifyKeyDescription(const string &Section,const string &Key,const string &Description);
     
     /* Delete key in the configure file */
     void    DeleteKey(const string &Section,const string &Key);
     /* Delete section in the configure file when the section has not key */
     void    DeleteSection(const string &Section);
     /* Delete key description in the configure file */
     void    DeleteKeyDescription(const string &Section,const string &Key);
     /* Delete section description in the configure */
     void    DeleteSectionDescription(const string &Section);
     /* Delete section in the configure file any time */
     void    TruncateSection(const string &Section);
     
     /* Read all key in the section from configure file to list */
     void    ReadKeys(const string &Section,list<string>& listAllKey);
     /* Read all sections from configure file to list */
     void    ReadSections(list<string>& listAllSection);
     /* Read head string */
     void    ReadHeads(list<string> &listIniHead);
    
protected:

private:
    string              IniFile;       // File path
    inimap              IniMap;        // Configure map
    
    list<string>        listIniHead;   // Head description

    inimap::iterator    FindSection(const string& Section);
    keymap::iterator    FindKey(const inimap::iterator& itSectionMap,const string & Key);
    
    bool    Load();
    bool    Flush();
    
};

#endif //INI_H

