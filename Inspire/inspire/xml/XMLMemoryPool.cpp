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
#include <new>
#include "XMLHelper.h"
#include "XMLMemoryPool.h"
#include "XMLAttribute.h"
#include "XMLNode.h"

XML_BEGIN
class XMLNode;

XMLMemoryPool::XMLMemoryPool() :
_alloc( NULL ),
_free( NULL ),
_ptrBegin( NULL ),
_ptrEnd( NULL ),
_curPtr( NULL )
{
   initMemoryPool();
}

XMLMemoryPool::~XMLMemoryPool()
{
   release();
}

void XMLMemoryPool::initMemoryPool()
{
   _ptrBegin = _begin;
   _curPtr = align( _ptrBegin );
   _ptrEnd = _begin + sizeof( _begin );
}

void XMLMemoryPool::release()
{
   while( _ptrBegin != _begin )
   {
      char* prevBlock = reinterpret_cast<MBHeader*>( align( _ptrBegin ) )->prevHeader;
      if ( _free )
      {
         _free( _ptrBegin );
      }
      else
      {
         delete [] _ptrBegin;
      }
      _ptrBegin = prevBlock;
   }
   initMemoryPool();
}

char* XMLMemoryPool::align( char* ptr )
{
   std::size_t offset = ( ( XML_ALIGNMENT - ( std::size_t( ptr ) & ( XML_ALIGNMENT - 1 ) ) ) & ( XML_ALIGNMENT - 1 ) );
   return ptr + offset;
}

char* XMLMemoryPool::addMemory( std::size_t size )
{
   void* pMemory = NULL;
   if ( _alloc )
   {
      pMemory = _alloc( size );
      if ( pMemory == NULL )
      {
         // 内存分配不成功，打log
      }
   }
   else
   {
      pMemory = new char[size];
      if ( pMemory == NULL )
      {
         // 内存分配不成功，打log
      }
   }
   return static_cast<char*>( pMemory );
}

void* XMLMemoryPool::alloc( std::size_t size )
{
   char* pReturn = align( _curPtr );

   if ( pReturn + size > _ptrEnd )
   {
      std::size_t blockSize = BLOCK_SIZE;
      if ( blockSize < size )
      {
         blockSize = size;
      }

      std::size_t allocSize = sizeof( MBHeader ) + 2 * ( XML_ALIGNMENT - 1 ) + blockSize;
      char* newMemory = addMemory( allocSize );

      char* begin = align( newMemory );
      MBHeader* memHeader = reinterpret_cast<MBHeader*>( begin );
      memHeader->prevHeader = _begin;
      _ptrBegin = newMemory;
      _curPtr = begin + sizeof( MBHeader );
      _ptrEnd = newMemory + allocSize;

      pReturn = align( _curPtr );
   }

   _curPtr = pReturn + size;
   return pReturn;
}

IXMLNode* XMLMemoryPool::allocNode( XMLNodeType nt, const char* name, const char* value )
{
   void* memory = alloc( sizeof( XMLNode ) );
   XMLNode* node = new( memory ) XMLNode( nt );
   if ( name )
   {
      node->setName( name, caculateLen( name ) );
   }

   if ( value )
   {
      node->setValue( value, caculateLen( value ) );
   }

   return node;
}

IXMLAttribute* XMLMemoryPool::allocAttribute( const char* name, const char* value )
{
   void* memory = alloc( sizeof( XMLAttribute ) );
   IXMLAttribute* attri = new( memory ) XMLAttribute();
   if ( name )
   {
      attri->setName( name, caculateLen( name ) );
   }

   if ( value )
   {
      attri->setValue( value, caculateLen( value ) );
   }

   return attri;
}

char* XMLMemoryPool::allocString( const char* str )
{
   if ( str == NULL )
   {
      return NULL;
   }

   std::size_t length = caculateLen( str );
   char* memory = static_cast<char*>( alloc( length ) );
   memcpy( memory, str, length );

   return memory;
}

XML_END