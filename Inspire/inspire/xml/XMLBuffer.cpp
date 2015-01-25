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
#include <new>
#include "XMLHelper.h"
#include "XMLBuffer.h"
#include "XMLAttribute.h"
#include "XMLNode.h"

namespace inspire {
class XMLNode;

XMLBuffer::XMLBuffer() : _ptrBegin( NULL ), _ptrEnd( NULL ), _curPtr( NULL )
{
   InitBuffer();
}

XMLBuffer::~XMLBuffer()
{
   Release();
}

void XMLBuffer::InitBuffer()
{
   _ptrBegin = _begin;
   _curPtr = Align( _ptrBegin );
   _ptrEnd = _begin + sizeof( _begin );
}

void XMLBuffer::Release()
{
   while( _ptrBegin != _begin )
   {
      char* prevBlock = reinterpret_cast<MBHeader*>( Align( _ptrBegin ) )->prevHeader;
      delete [] _ptrBegin;
      _ptrBegin = prevBlock;
   }
   InitBuffer();
}

char* XMLBuffer::Align( char* ptr )
{
   std::size_t offset = ( ( XML_ALIGNMENT - ( std::size_t( ptr ) & ( XML_ALIGNMENT - 1 ) ) ) & ( XML_ALIGNMENT - 1 ) );
   return ptr + offset;
}

char* XMLBuffer::AddMemory( std::size_t size )
{
   void* pMemory = new char[size];
   if ( pMemory == NULL )
   {
      // 内存分配不成功，打log
   }
   return static_cast<char*>( pMemory );
}

void* XMLBuffer::Alloc( std::size_t size )
{
   char* pReturn = Align( _curPtr );

   if ( pReturn + size > _ptrEnd )
   {
      std::size_t blockSize = BLOCK_SIZE;
      if ( blockSize < size )
      {
         blockSize = size;
      }

      std::size_t allocSize = sizeof( MBHeader ) + 2 * ( XML_ALIGNMENT - 1 ) + blockSize;
      char* newMemory = AddMemory( allocSize );

      char* begin = Align( newMemory );
      MBHeader* memHeader = reinterpret_cast<MBHeader*>( begin );
      memHeader->prevHeader = _begin;
      _ptrBegin = newMemory;
      _curPtr = begin + sizeof( MBHeader );
      _ptrEnd = newMemory + allocSize;

      pReturn = Align( _curPtr );
   }

   _curPtr = pReturn + size;
   return pReturn;
}

IXMLNode* XMLBuffer::AllocNode( XMLNodeType nt, const char* name, const char* value )
{
   void* memory = Alloc( sizeof( XMLNode ) );
   XMLNode* node = new( memory ) XMLNode( nt );
   if ( name )
   {
      node->SetName( name, Length( name ) );
   }

   if ( value )
   {
      node->SetValue( value, Length( value ) );
   }

   return node;
}

IXMLAttribute* XMLBuffer::AllocAttribute( const char* name, const char* value )
{
   void* memory = Alloc( sizeof( XMLAttribute ) );
   IXMLAttribute* attri = new( memory ) XMLAttribute();
   if ( name )
   {
      attri->SetName( name, Length( name ) );
   }

   if ( value )
   {
      attri->SetValue( value, Length( value ) );
   }

   return attri;
}

char* XMLBuffer::AllocString( const char* str )
{
   if ( str == NULL )
   {
      return NULL;
   }

   std::size_t length = Length( str );
   char* memory = static_cast<char*>( Alloc( length ) );
   memcpy( memory, str, length );

   return memory;
}

}
