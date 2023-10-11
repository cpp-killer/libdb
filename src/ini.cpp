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
// Version      : 2.0 sad   ftgf cc    32        0
// Author       : lxmy
// Accomplished date : March 20, 2013
//
// Replaced version  :  1.0 
// Original Author   : lxmy
// Accomplished date : March 20, 2013
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#include "ini.h"

CIni::CIni(const string & IniFile)
{
    this->IniFile = IniFile;
    IniMap.clear();
    Load();
}

CIni::~ CIni()
{
   Clear();
}

int CIni::Update()
{
    return Flush() ? 0 : -1;
}

void CIni::Clear()
{
    list<string> listAllSection;
    list<string>::iterator itAllSectionList;

    ReadSections(listAllSection);
    for(itAllSectionList = listAllSection.begin();itAllSectionList != listAllSection.end();++itAllSectionList)
    {
        TruncateSection(*itAllSectionList);
    }

    IniMap.clear();
}

string CIni::ReadString(const string & Section, const string & Key, const string & defaultValue /* = "" */)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;

    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return defaultValue;
    }

    itKeyMap = FindKey(itSectionMap, Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        return defaultValue;
    }

    return itKeyMap->second.second;
}


void CIni::WriteString(const string & Section, const string & Key, const string & Value)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;
    keymap tmpKeyMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        tmpKeyMap.insert(keymap::value_type(Key,pair<string,string>("",Value)));
        IniMap.insert(inimap::value_type(Section,pair<string,keymap>("",tmpKeyMap)));

        return;
    }

    itKeyMap = FindKey(itSectionMap, Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        itSectionMap->second.second.insert(keymap::value_type(Key,pair<string,string>("",Value)));

        return;
    }

    itKeyMap->second.second = Value;
}

int CIni::ModifyString(const string & Section, const string & Key, const string & Value)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return -1;
    }

    itKeyMap = FindKey(itSectionMap, Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        return -2;
    }

    itKeyMap->second.second = Value;
    
    return 0;
}

int CIni::ReadInteger(const string & Section, const string & Key, int defaultValue /* = 0 */)
{
    string sValue = ReadString(Section,Key,"");
    if(sValue == "")
    {
        return defaultValue;
    }

    return atoi(sValue.c_str());
}

void CIni::WriteInteger(const string & Section, const string & Key, int Value)
{
    stringstream streamValue;
    string sValue;

    streamValue << Value;
    streamValue >> sValue;
    
    return WriteString(Section,Key,sValue);
}

int CIni::ModifyInteger(const string & Section, const string & Key, int Value)
{
    stringstream streamValue;
    string sValue;

    streamValue << Value;
    streamValue >> sValue;

    return ModifyString(Section,Key,sValue);
}

double CIni::ReadDouble(const string & Section, const string & Key, double defaultValue /* = 0.0 */)
{
    string sValue = ReadString(Section,Key,"");

    if(sValue == "")
    {
        return defaultValue;
    }

    return atof(sValue.c_str());
}

void CIni::WriteDouble(const string & Section, const string & Key, double Value)
{
    stringstream streamValue;
    string sValue;

    streamValue << Value;
    streamValue >> sValue;
    
    return WriteString(Section,Key,sValue);
}

int CIni::ModifyDouble(const string & Section, const string & Key, double Value)
{
    stringstream streamValue;
    string sValue;

    streamValue << Value;
    streamValue >> sValue;

    return ModifyString(Section,Key,sValue);    
}

bool CIni::ReadBool(const string & Section, const string & Key, bool defaultValue /* = false */)
{
    string sValue = ReadString(Section,Key,"");

    if(sValue == "")
    {
        return defaultValue;
    }

    return (sValue == "true" || sValue == "TRUE") ? true : false;
}

void CIni::WriteBool(const string & Section, const string & Key, bool Value)
{
    string sValue;

    sValue = (Value ? "true" : "false");

    return WriteString(Section,Key,sValue);    
}

int CIni::ModifyBool(const string & Section, const string & Key, bool Value)
{
    string sValue;
    
    sValue = (Value ? "true" : "false");

    return ModifyString(Section,Key,sValue);
}

void CIni::WriteSection(const string & Section)
{
    inimap::iterator itSectionMap;
    keymap tmpKeyMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        IniMap.insert(inimap::value_type(Section,pair<string,keymap>("",tmpKeyMap)));
    }
}

string CIni::ReadKeyDescription(const string & Section, const string & Key)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return "";
    }

    itKeyMap = FindKey(itSectionMap, Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        return "";
    }

    return itKeyMap->second.first;
}

string CIni::ReadSectionDescription(const string & Section)
{
    inimap::iterator itSectionMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return "";
    }

    return itSectionMap->second.first;
}

int CIni::WriteKeyDescription(const string & Section, const string & Key,const string &Description)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return -1;
    }

    itKeyMap = FindKey(itSectionMap, Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        return -2;
    }

    itKeyMap->second.first = Description;

    return 0;
}

int CIni::WriteSectionDescription(const string & Section, const string & Description)
{
    inimap::iterator itSectionMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return -1;
    }

    itSectionMap->second.first = Description;

    return 0;
}

int CIni::ModifyKeyDescription(const string & Section, const string & Key, const string & Description = "")
{
    return WriteKeyDescription(Section,Key,Description);
}

int CIni::ModifySectionDescription(const string & Section, const string & Description)
{
    return WriteSectionDescription(Section,Description);
}

void CIni::DeleteKey(const string &Section, const string & Key)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;
    
    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return;
    }

    itKeyMap = FindKey(itSectionMap,Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        return;
    }

    itSectionMap->second.second.erase(itKeyMap);
}

void CIni::DeleteSection(const string & Section)
{
    inimap::iterator itSectionMap;

    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return;
    }

    if(itSectionMap->second.second.empty())
    {
        IniMap.erase(itSectionMap);
    }
}

void CIni::TruncateSection(const string & Section)
{
    inimap::iterator itSectionMap;
    list<string> listAllKey;
    list<string>::iterator itAllKeyList;

    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return;
    }

    ReadKeys(itSectionMap->first,listAllKey);
    for(itAllKeyList = listAllKey.begin();itAllKeyList != listAllKey.end();++itAllKeyList)
    {
        DeleteKey(Section,*itAllKeyList);
    }
    
    DeleteSection(Section);
}

void CIni::DeleteKeyDescription(const string & Section, const string & Key)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;

    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return;
    }

    itKeyMap = FindKey(itSectionMap,Key);
    if(itKeyMap == itSectionMap->second.second.end())
    {
        return;
    }

    itKeyMap->second.first = "";
}

void CIni::DeleteSectionDescription(const string & Section)
{
    inimap::iterator itSectionMap;

    itSectionMap = FindSection(Section);
    if(itSectionMap == IniMap.end())
    {
        return;
    }

    itSectionMap->second.first = "";
}

void CIni::ReadKeys(const string & Section, list < string > & listAllKey)
{
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;

    for(itSectionMap = IniMap.begin();itSectionMap != IniMap.end();++itSectionMap)
    {
        if(itSectionMap->first != Section)
        {
            continue;
        }
        for(itKeyMap = itSectionMap->second.second.begin();itKeyMap != itSectionMap->second.second.end();++itKeyMap)
        {
            listAllKey.push_back(itKeyMap->first);
        }
        
        break;
    }
}

void CIni::ReadSections(list < string > & listAllSection)
{
    inimap::iterator itSectionMap;
    
    for(itSectionMap = IniMap.begin();itSectionMap != IniMap.end();++itSectionMap)
    {
        listAllSection.push_back(itSectionMap->first);
    }
}

void CIni::ReadHeads(list < string > & listIniHead)
{
    listIniHead = this->listIniHead;
}

keymap::iterator CIni::FindKey(const  inimap::iterator & itSectionMap, const string & Key)
{
    return itSectionMap->second.second.find(Key);
}

inimap::iterator CIni::FindSection(const string & Section)
{
    return IniMap.find(Section);
}

bool CIni::Load()
{
    vector<string> IniVector;
    vector<string>::iterator itIniVector;
    string Line;

    string strtmp = "";
    string strtmp_description = "";
    string strtmp_section = "";
    string strtmp_key = "";
    string strtmp_value = "";
    
    ifstream fin(IniFile.c_str());
    if(!fin.is_open())
    {
        return false;
    }
    
    while(!fin.eof())
    {
        getline(fin,Line,'\n');
        IniVector.push_back(Line);
    }

    fin.close();

    if(IniVector.empty())
    {
        return false;
    }

    for(itIniVector = IniVector.begin();itIniVector != IniVector.end();++itIniVector)
    {
        int first;
        int last;
        
        if(itIniVector->empty())
        {
            continue;
        }

        switch(itIniVector->at(0))
        {
        case ' ':
            continue;
            break;
        case '\n':
            continue;
            break;
        case '\t':
            continue;
            break;
        case '\r':
            break;
        case '/':
            first = 3;
            last  = (int)string::npos;
            strtmp = itIniVector->substr(first,last-1);
            listIniHead.push_back(strtmp);
            break;
        case '#':
            first = 2;
            last  = (int)string::npos;
            strtmp_description = itIniVector->substr(first,last-1);            
            break;
        case '[':
            first = 1;
            last = itIniVector->find_last_of("]");
            if(last == (int)string::npos)
            {
                return false;
            }
            
            strtmp_section = itIniVector->substr(first,last-1);
            WriteSection(strtmp_section);                                   // Write section
            WriteSectionDescription(strtmp_section,strtmp_description);     // Write description
            strtmp_description = "";
            break;
        default:
            if(strtmp_section == "")
            {
                return false;
            }

            first = 0;
            last  = itIniVector->find_first_of(" =\t");
            strtmp_key = itIniVector->substr(first,last);
            first = itIniVector->find_last_of(" =\t");
            last = (int)string::npos;
            strtmp_value = itIniVector->substr(first+1,last-1);
            WriteString(strtmp_section,strtmp_key,strtmp_value);
            WriteKeyDescription(strtmp_section,strtmp_key,strtmp_description);
            strtmp_description = "";
            break;
        }
    }
    return true;
}


bool CIni::Flush()
{
    list<string>::iterator itIniHeadList;
    inimap::iterator itSectionMap;
    keymap::iterator itKeyMap;

    ofstream fout(IniFile.c_str());
    if(!fout.is_open())
    {
        return false;
    }

    for(itIniHeadList = listIniHead.begin();itIniHeadList != listIniHead.end();++itIniHeadList)
    {
        fout << "// " << *itIniHeadList << endl;
    }

    fout << endl;

    for(itSectionMap = IniMap.begin();itSectionMap != IniMap.end();++itSectionMap)
    {
        fout << "# " << itSectionMap->second.first <<endl;      // put description
        fout << "[" << itSectionMap->first << "]" <<endl;       // put section
        fout << endl;        
        for(itKeyMap = itSectionMap->second.second.begin();itKeyMap != itSectionMap->second.second.end();++itKeyMap)
        {
            fout << "# " << itKeyMap->second.first << endl;     // put description
            fout << itKeyMap->first << " = " << itKeyMap->second.second << endl;
            fout << endl;
        }
        
        fout << endl;
    }

    return true;
}

// g++ -g -shared -fPIC -o ../../../lib/libini.so.2.0 Ini.cpp -I../../../include -I../../../include/lib -Wall


