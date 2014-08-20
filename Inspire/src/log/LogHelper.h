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
#ifndef _INSPIRE_LOG_HELPER_H_
#define _INSPIRE_LOG_HELPER_H_

#include "InspireLog.h"

#define WRITE_LOG( category, priority, str )                              \
   INSPIRE_LOG::InspireLogManager::Instance()->getLogCategory( category ) \
   ->writeLog( priority, str );

#define LOG_BUFFER_SIZE 4096

#define DEFINE_LOG_WRAPPER( FuncName, category, priority )     \
inline void FuncName( const char* fmt, ... )                   \
{                                                              \
   char userLog[ LOG_BUFFER_SIZE ] = { 0 };                    \
   va_list ap;                                                 \
                                                               \
   va_start( ap, fmt );                                        \
   vsnprintf( userLog, LOG_BUFFER_SIZE, fmt, ap );             \
   va_end( ap );                                               \
                                                               \
   WRITE_LOG( category, priority, userLog );                   \
}

#endif