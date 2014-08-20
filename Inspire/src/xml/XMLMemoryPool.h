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
#ifndef _INSPIRE_XML_MEMORY_POOL_H_
#define _INSPIRE_XML_MEMORY_POOL_H_

#include "XMLBase.h"

XML_BEGIN

class IXMLNode;
class IXMLAttribute;
enum XMLNodeType;

class XMLMemoryPool
{
public:
   XMLMemoryPool();
   ~XMLMemoryPool();

   void* alloc( std::size_t size );

   IXMLNode* allocNode( XMLNodeType nt, const char* name = NULL,
                                        const char* value = NULL );

   IXMLAttribute* allocAttribute( const char* name = NULL,
                                 const char* value = NULL );

   char* allocString( const char* str );

   void setMemoryFunc( XML::alloc* af, XML::free * ff )
   {
      _alloc = af;
      _free  = ff;
   }

   void  release();

private:
   static const int BLOCK_SIZE = 64 * 1024;
   static const int XML_ALIGNMENT = sizeof( void* );

   char     _begin[BLOCK_SIZE];
   char*    _ptrBegin;
   char*    _ptrEnd;
   char*    _curPtr;

   XML::alloc*  _alloc;
   XML::free*   _free;

private:
   // MB : Memory block
   struct MBHeader
   {
      char* prevHeader;
   };

   void  initMemoryPool();
   char* addMemory( std::size_t size );

   // 内存对齐，使偏移为sizeof( void* )的整数倍
   char* align( char* ptr );
};

XML_END
#endif