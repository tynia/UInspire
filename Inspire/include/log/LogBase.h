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
#ifndef _INPSIRE_LOG_DEFINITION_H_
#define _INPSIRE_LOG_DEFINITION_H_

#define INSPIRE_LOG_BENGIN namespace INSPIRE_LOG {
#define INSPIRE_LOG_END }
#define USE_INSPIRE_LOG using namespace INSPIRE_LOG;

#include <vector>
#include <cstring>
#include <fstream>

#ifdef _WIN32
#  define OSS_NEWLINE "\r\n"
#else
#  define OSS_NEWLINE "\n"
#endif

#endif // _INPSIRE_LOG_DEFINITION_H_
