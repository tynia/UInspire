#ifndef _UI_INSPIRE_LIB_DEFINITION_H_
#define _UI_INSPIRE_LIB_DEFINITION_H_

// Windows
#include <tchar.h>
#include <Windows.h>

// C RUNTIME
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>
#include <time.h>
#include <fstream>

// STL
#include <vector>
#include <list>
#include <map>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

#pragma warning( disable : 4250 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4244 )

#ifdef INSPIRE_DLL_BUILD
#define INSPIRE_EXPORT_API __declspec( dllexport )
#else
#define INSPIRE_EXPORT_API __declspec( dllimport )
#endif

typedef unsigned int uint;
typedef long long int64;
typedef unsigned long long uint64;

#ifdef INTERNAL_UNICODE
typedef std::wstring      _tstring;
typedef wchar_t           _tchar;
#else
typedef std::string       _tstring;
typedef char              _tchar;
#endif // INTERNAL_UNICODE

#endif
