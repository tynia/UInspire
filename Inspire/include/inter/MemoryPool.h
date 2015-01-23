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
#ifndef _INSPIRE_MEMORY_POOL_H_
#define _INSPIRE_MEMORY_POOL_H_

#include "InspireInternal.h"

class MemoryPool
{
public:
   MemoryPool();
   ~MemoryPool();

   static MemoryPool* getPool();

   void* alloc( std::size_t size );
   void release();

   void setMemoryFunc( inspire::alloc* af, inspire::free* ff )
   {
      _alloc = af;
      _free  = ff ;
   }

private:
   void init();
   char* align( char* ptr );
   char* addMemory( std::size_t size );

private:
   static const int BLOCK_SIZE = 64 * 1024;
   static const int OBJECT_ALIGNMENT = sizeof( void* );
   struct MBHeader
   {
      char* prevHeader;
   };

   inspire::alloc*  _alloc;
   inspire::free*   _free;

   char   _original[BLOCK_SIZE];
   char*  _ptrBegin;
   char*  _ptrEnd;
   char*  _curPtr;
};
#endif