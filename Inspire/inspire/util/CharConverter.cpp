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
#include "CharConverter.h"

namespace inspire {
CharConverter::CharConverter( const char* str ) : _UnicodeString( NULL ), _UTF8String( NULL )
{
   if ( str == NULL )
   {
      _UTF8String = NULL;
      return;
   }

   int len = ::MultiByteToWideChar( CP_ACP, 0, str, strlen( str ) + 1, NULL, 0 );

   _UnicodeString = new wchar_t[len];

   ::MultiByteToWideChar( CP_ACP, 0, str, strlen( str ) + 1, _UnicodeString, len );

   _UTF8String = const_cast<char*>( str );
}

CharConverter::CharConverter( const wchar_t* wstr ) : _UnicodeString( NULL ), _UTF8String( NULL )
{
   if ( wstr == NULL )
   {
      _UTF8String = NULL;
      return;
   }

   int len = ::WideCharToMultiByte( CP_ACP, 0, wstr, wcslen( wstr ) + 1, NULL, 0, NULL, NULL );

   _UTF8String = new char[len];

   ::WideCharToMultiByte( CP_ACP, 0, wstr, wcslen( wstr ) + 1, _UTF8String, len, NULL, NULL );

   _UnicodeString = const_cast<wchar_t*>( wstr );
}

CharConverter::~CharConverter()
{
   if ( _IsUTF8 )
   {
      if ( _UnicodeString != NULL )
      {
         delete [] _UnicodeString;
         _UnicodeString = NULL;
      }
   }
   else
   {
      if ( _UTF8String != NULL )
      {
         delete [] _UTF8String;
         _UTF8String = NULL;
      }
   }
}
}
