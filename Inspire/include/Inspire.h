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

#include "platform.h"
#include "log\Log.h"

#define __LOG_WRAPPER( LEVEL, fmt, ... )                       \
do                                                             \
{                                                              \
   inspire::Log( LEVEL, __FUNCTION__,                          \
                 __FILE__, __LINE__, fmt, __VA_ARGS__ ) ;      \
} while ( false )

#ifdef _DEBUG
#define INSPIRE_ASSERT( condition, fmt, ... )                  \
do                                                             \
{                                                              \
   if ( !condition )                                           \
   {                                                           \
      inspire::Log( inspire::PRIO_ERROR, __FUNCTION__,         \
                    __FILE__, __LINE__, fmt, __VA_ARGS__ ) ;   \
      inspire::Panic() ;                                       \
   }                                                           \
} while ( false )
#else
#define INSPIRE_ASSERT( condition, fmt, ... )                  \
do                                                             \
{                                                              \
   if ( !condition )                                           \
   {}                                                          \
} while ( false )
#endif

//////////////////////////////////////////////////////////////////////////
// useful function
namespace inspire {

inline std::string ItoA( int i )
{
   char buff[32];
   sprintf( buff, "%d", i );
   return buff;
}

inline std::string ItoA( int64 i )
{
   char buf[64] = { 0 };

#ifndef _IN_WINDOWS_32_PLATFORM_
   sprintf_s( buf, "%I64d", i );
#else
   sprintf_s( buf, "%lld", i );
#endif
   return buf;
}

inline void GetLocalTime( struct tm *t )
{
   INSPIRE_ASSERT( NULL != t, "ptr should be NULL" ) ;
   time_t tt = time( NULL ) ;
   localtime_s( t, &tt) ;
}

inline int64 GetProcessID()
{
#ifdef WIN32
   return ::GetCurrentProcessId() ;
#else
   return 0 ;
#endif
}

inline int64 GetThreadID()
{
#ifdef WIN32
   return ::GetCurrentThreadId() ;
#else
   return 0 ;
#endif
}

}
#endif // _INSPIRE_H_

