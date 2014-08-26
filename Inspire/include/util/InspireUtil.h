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
#ifndef _INSPIRE_UTIL_H_
#define _INSPIRE_UTIL_H_

#include "Inspire.h"
#include "CharConverter.h"
#include "LogHelper.h"

inline void AssertFail( const char* file, const int line, const char* exp )
{
   FILE* fp = fopen( "assert.log", "a" );
   if( fp )
   {
      long cur_size = ftell( fp );
      if( cur_size > ( 1 << 30 ) )
      {
         fclose( fp );
         fp = fopen( "assert.log","w" );
      }
      if( fp )
      {
         printf( "Assertion Failed: File: %s, line: %d\nexpression: %s\n", file, line, exp );
         fprintf( fp, "Assertion Failed: File: %s, line: %d\nexpression: %s\n", file, line, exp );
         fclose( fp );
      }
   }

   __asm int 3;
}

#ifndef LIB_ASSERT
#  ifdef _DEBUG
#define LIB_ASSERT( exp ) ( int )( ( exp ) || ( AssertFail( __FILE__, __LINE__, #exp ), 0 ) )
#  else
#define LIB_ASSERT( exp ) ( ( int ) 1 )
#  endif
#endif

/// assert always even though project under Release!!
#define SYSTEM_ASSERT( exp ) ( int )( ( exp ) || ( AssertFail( __FILE__, __LINE__, #exp ), 0 ) )

DEFINE_LOG_WRAPPER( LogEmerg,    "emerg",     INSPIRE_LOG::PRIO_EMERG )
DEFINE_LOG_WRAPPER( LogFatal,    "fatal",     INSPIRE_LOG::PRIO_FATAL )
DEFINE_LOG_WRAPPER( LogCritical, "ctritical", INSPIRE_LOG::PRIO_CRITICAL )
DEFINE_LOG_WRAPPER( LogError,    "error",     INSPIRE_LOG::PRIO_ERROR )
DEFINE_LOG_WRAPPER( LogWarning,  "warning",   INSPIRE_LOG::PRIO_WARNING )
DEFINE_LOG_WRAPPER( LogDebug,    "debug",     INSPIRE_LOG::PRIO_DEBUG )
DEFINE_LOG_WRAPPER( LogNotice,   "notice",    INSPIRE_LOG::PRIO_NOTICE )
DEFINE_LOG_WRAPPER( LogInfo,     "info",      INSPIRE_LOG::PRIO_INFO )

inline std::string ItoA( int i )
{
   char buff[32];
   sprintf( buff, "%d", i );
   return buff;
}

typedef long long int64;
typedef unsigned long long uint64;

inline std::string ItoA( int64 i )
{
   char buf[64] = { 0 };

#ifndef _IN_WINDOWS_32_PLATFORM_
   sprintf( buf, "%I64d", i );
#else
   sprintf( buf, "%lld", i );
#endif

   return buf;
}

#endif