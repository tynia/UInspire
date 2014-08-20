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
#ifndef _INSPIRE_XML_UTIL_H_
#define _INSPIRE_XML_UTIL_H_

#if defined( _WIN32 ) || defined( _WINDOWS ) || defined( WIN32 )
#include <tchar.h>
#include <cstdlib>   // std::size_t
#include <cstring>
#include <assert.h>
using namespace std;
#define XML_IN_WINDOWS_PLATFORM
#define XML_INTERNAL_UNICODE
#define XML_LIB_BUILD
#endif // if define( _WIN32 ) end

///< disable 4250 warning on diamond inheritance 
///< 消除菱形继承的警告
#pragma warning( disable : 4250 )

#ifdef XML_LIB_BUILD
#define XML_LIB_API __declspec( dllexport )
#else
#define XML_LIB_API __declspec( dllimport )
#endif // ifdef XML_LIB_BUILD

#define XML_BEGIN namespace XML {
#define XML_END }
#define USE_XML using namespace XML;

#include <ostream>
#include <iterator>

#endif