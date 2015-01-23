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
#include "MemoryPool.h"

MemoryPool::MemoryPool() : _ptrBegin( _original ), _ptrEnd( NULL ), _curPtr( NULL )
{
   init();
}

MemoryPool::~MemoryPool()
{
   release();
}

MemoryPool* MemoryPool::getPool()
{
   static MemoryPool _pool;
   return &_pool;
}

void MemoryPool::init()
{
   _ptrBegin = _original;
   _curPtr = align( _ptrBegin );
   _ptrEnd = _original + sizeof( _original );
}

char* MemoryPool::align( char* ptr )
{
   std::size_t offset = ( ( OBJECT_ALIGNMENT - ( std::size_t( ptr ) & ( OBJECT_ALIGNMENT - 1 ) ) ) & ( OBJECT_ALIGNMENT - 1 ) );
   return ptr + offset;
}

void* MemoryPool::alloc( std::size_t size )
{
   char* pReturn = align( _curPtr );

   if ( pReturn + size > _ptrEnd )
   {
      std::size_t block_size = BLOCK_SIZE;
      if ( block_size < size )
      {
         block_size = size;
      }

      std::size_t allocSize = sizeof( MBHeader ) + 2 * ( OBJECT_ALIGNMENT - 1 ) + block_size;
      char* newMemory = addMemory( allocSize );

      char* begin = align( newMemory );
      MBHeader* memHeader = reinterpret_cast<MBHeader*>( begin );
      memHeader->prevHeader = _original;
      _ptrBegin = newMemory;
      _curPtr = begin + sizeof( MBHeader );
      _ptrEnd = newMemory + allocSize;

      pReturn = align( _curPtr );
   }

   _curPtr = pReturn + size;
   return pReturn;
}

char* MemoryPool::addMemory( std::size_t size )
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

void MemoryPool::release()
{
   while( _ptrBegin != _original )
   {
      char* prev_block = reinterpret_cast<MBHeader*>( align( _ptrBegin ) )->prevHeader;
      if ( _free )
      {
         _free( _ptrBegin );
      }
      else
      {
         delete [] _ptrBegin;
      }
      _ptrBegin = prev_block;
   }
   init();
}