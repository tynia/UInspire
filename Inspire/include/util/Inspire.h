/*******************************************************************************
   Copyright (C) 2014 tynia.

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
#ifndef _INSPIRE_H_
#define _INSPIRE_H_

#if defined( _WIN32 ) || defined( _WINDOWS ) || defined( WIN32 )
#include <tchar.h>
#include <Windows.h>
//Windows 下使用
#define INSPIRE_IN_WINDOWS_32_PLATFORM
//默认Unicode字符
#define INTERNAL_UNICODE
#endif
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
#define INSPIRE_LIB_API __declspec( dllexport )
#else
#define INSPIRE_LIB_API __declspec( dllimport )
#endif // ifdef INSPIRE_DLL_BUILD

#ifdef _WIN32
#  define _IN_WINDOWS_32_PLATFORM_
#elif  _WIN64
#  define _IN_WINDOWS_64_PLATFORM_
#endif // _WIN32


#define INSPIRE_CLIENT_BENGIN namespace INSPIRE_CLIENT {
#define INSPIRE_CLIENT_END }
#define USE_INSPIRE_CLIENT using namespace INSPIRE_CLIENT;

#define INSPIRE_INTERNAL_BEGIN namespace INSPIRE_INTERNAL {
#define INSPIRE_INTERNAL_END }
#define USE_INSPIRE_INTERNAL using namespace INSPIRE_INTERNAL;

#endif // _INSPIRE_H_

