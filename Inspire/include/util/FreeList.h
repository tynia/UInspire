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
#ifndef _INSPIRE_FREE_LIST_H_
#define _INSPIRE_FREE_LIST_H_

#include "platform.h"
#include "InspireLock.h"

namespace inspire {

template<class TEntity>
class FreeList
{
public:
   FreeList() : _count( 0 ), _freeHead( NULL )
   {
      _size = sizeof( TEntity ) > sizeof( TEntity* ) ? sizeof( TEntity ) : sizeof( TEntity* );
   }

   ~FreeList()
   {
      while ( _freeHead )
      {
         TEntity* toFree = _freeHead;
         _freeHead = *( reinterpret_cast<TEntity**>( _freeHead ) );
         ::free( toFree );
      }
   }

   int count()
   {
      return _count;
   }

   TEntity* alloc()
   {
      LockCondition lock( &_variable );
      ++_count;
      if ( _freeHead == NULL )
      {
         return new( malloc( _size ) )TEntity;
      }

      TEntity* memory = _freeHead;
      _freeHead = *( reinterpret_cast<TEntity**>( _freeHead ) );
      return new( memory )TEntity;
   }

   TEntity* alloc( const TEntity* entity )
   {
      LockCondition lock( &_variable );
      ++_count;
      if ( _freeHead == NULL )
      {
         return new( malloc( _size ) )TEntity( entity );
      }

      TEntity* memory = _freeHead;
      _freeHead = *( reinterpret_cast<TEntity**>( _freeHead ) );
      return new( memory )TEntity( entity );
   }

   void dealloc( TEntity* entity )
   {
      entity->~TEntity();
      if ( true )
      {
         LockCondition lock( &_variable );
         memset( entity, 0xfe, _size );
         --_count;
         assert( _count > 0 );
         *( reinterpret_cast<TEntity**>( entity ) ) = _freeHead;
         _freeHead = entity;
      }
   }

private:
   int                 _count;
   int                 _size;
   TEntity*            _freeHead;
   LockVariable _variable;
};

}
#endif