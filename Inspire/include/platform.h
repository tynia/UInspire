/*******************************************************************************
   Copyright (C) 2015 tynia.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.
   
   Any problem, please ping xduilib@gmail.com, free service may be supported.
*******************************************************************************/
#ifndef _INSPIRE_PLATFORM_H_
#define _INSPIRE_PLATFORM_H_

#if defined( _WIN32 ) || defined( _WINDOWS ) || defined( WIN32 )

#include <tchar.h>
#include <windows.h>
// windows
#define INSPIRE_IN_WINDOWS_32_PLATFORM
// unicode
#define INTERNAL_UNICODE

#endif

#ifdef _WIN32
#  define _IN_WINDOWS_32_PLATFORM_
#elif  _WIN64
#  define _IN_WINDOWS_64_PLATFORM_
#endif // _WIN32

#ifdef WIN32
typedef __int64 int64;
#else
typedef long long int64;
#endif

#define NULL 0

///< disable 4250 warning on diamond inheritance 
///< 消除菱形继承的警告
#pragma warning( disable : 4250 )
// 消除sprintf警告
#pragma warning( disable : 4996 )
// 消除双通道：：streamoff --> int警告
#pragma warning( disable : 4244 )

#include <stdlib.h>
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

//默认Unicode字符
#ifdef INTERNAL_UNICODE
typedef std::wstring      _tstring;
typedef wchar_t           _tchar;
#else
typedef std::string       _tstring;
typedef char              _tchar;
#endif // INTERNAL_UNICODE

#ifdef INSPIRE_DLL_BUILD
#define INSPIRE_EXPORT_API __declspec( dllexport )
#else
#define INSPIRE_EXPORT_API __declspec( dllimport )
#endif // ifdef INSPIRE_DLL_BUILD

#if defined(_WIN32) || defined(WIN32)
#define NEWLINE "\r\n"
#else
#define NEWLINE "\n"
#endif

#endif // _INSPIRE_PLATFORM_H_