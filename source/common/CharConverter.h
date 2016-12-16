#ifndef _INSPIRE_CHAR_CONVERTOR_H_
#define _INSPIRE_CHAR_CONVERTOR_H_

#include "interface/definition.h"

class CharConvertor
{
#ifdef _WINDOWS
public:
    CharConvertor(const char* pstr) : _wstr(NULL)
    {
        int uLen = ::MultiByteToWideChar(CP_ACP, 0, pstr, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[uLen + 1];
        if (NULL == wstr)
        {
            //Panic();
        }
        memset(wstr, 0, (uLen + 1) * sizeof(wchar_t));
        ::MultiByteToWideChar(CP_ACP, 0, pstr, -1, (LPWSTR)wstr, uLen);
        _wstr = wstr;
    }

    ~CharConvertor()
    {
        if (_wstr)
        {
            delete[] _wstr;
            _wstr = NULL;
        }
    }

    const wchar_t* toString() const
    {
        return _wstr;
    }

    const unsigned length() const
    {
        return wcslen(_wstr);
    }

private:
    wchar_t* _wstr;
#else
    CharConvertor(const char* pstr) : _str(NULL)
    {
        unsigned len = strlen(pstr);
        _str = new char[len + 1];
        if (NULL != _str)
        {
            memset(_str, 0, len + 1);
            memcpy(_str, pstr, len);
        }
    }

    ~CharConvertor()
    {
        if (_str)
        {
            delete[] _str;
            _str = NULL;
        }
    }

    const char* toString() const
    {
        return _str;
    }

    const uint length() const
    {
        return strlen(_str);
    }

private:
    char* _str;
#endif
};
#endif
