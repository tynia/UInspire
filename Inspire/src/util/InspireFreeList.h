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

#include "Inspire.h"
#include "InspireLock.h"

INSPIRE_CLIENT_BENGIN
template<class TEntity>
class InspireFreeList
{
public:
   InspireFreeList() : _allocatedCount( 0 ), _freelistHead( NULL )
   {
      _elementSize = sizeof( TEntity ) > sizeof( TEntity* ) ? sizeof( TEntity ) : sizeof( TEntity* );
   }

   ~InspireFreeList()
   {
      while ( _freelistHead )
      {
         TEntity* toFree = _freelistHead;
         _freelistHead = *( reinterpret_cast<TEntity**>( _freelistHead ) );
         ::free( toFree );
      }
   }

   int count()
   {
      return _allocatedCount;
   }

   TEntity* alloc()
   {
      InspireLock lock( &_variable );
      ++_allocatedCount;
      if ( _freelistHead == NULL )
      {
         return new( malloc( _elementSize ) )TEntity;
      }

      TEntity* memory = _freelistHead;
      _freelistHead = *( reinterpret_cast<TEntity**>( _freelistHead ) );
      return new( memory )TEntity;
   }

   TEntity* alloc( const TEntity* entity )
   {
      InspireLock lock( &_variable );
      ++_allocatedCount;
      if ( _freelistHead == NULL )
      {
         return new( malloc( _elementSize ) )TEntity( entity );
      }

      TEntity* memory = _freelistHead;
      _freelistHead = *( reinterpret_cast<TEntity**>( _freelistHead ) );
      return new( memory )TEntity( entity );
   }

   void dealloc( TEntity* entity )
   {
      entity->~TEntity();
      if ( true )
      {
         InspireLock lock( &_variable );
         memset( entity, 0xfe, _elementSize );
         --_allocatedCount;
         assert( _allocatedCount > 0 );
         *( reinterpret_cast<TEntity**>( entity ) ) = _freelistHead;
         _freelistHead = entity;
      }
   }

private:
   int                 _allocatedCount;
   int                 _elementSize;
   TEntity*            _freelistHead;
   InspireLockVariable _variable;
};

INSPIRE_CLIENT_END
#endif