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
#ifndef _INSPIRE_CHAR_CONVERTER_H_
#define _INSPIRE_CHAR_CONVERTER_H_

#include "platform.h"

namespace inspire {

class INSPIRE_EXPORT_API CharConverter
{
public:
   CharConverter( const char* str );
   CharConverter( const wchar_t* wstr );
   ~CharConverter();

   const char* GetUTF8() const
   {
      return _UTF8String;
   }

   const wchar_t* GetUnicode() const
   {
      return _UnicodeString;
   }

private:
   bool     _IsUTF8;
   char*    _UTF8String;
   wchar_t* _UnicodeString;
};
}
#endif