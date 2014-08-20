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
#ifndef _INSPIRE_SIMPLE_MEMORY_POOL_H_
#define _INSPIRE_SIMPLE_MEMORY_POOL_H_

#include "UIStaticText.h"
#include "UIButton.h"
#include "UICheckBox.h"
#include "UIComboBox.h"
#include "UICustomWnd.h"
#include "UIEditBox.h"
#include "UIRichEditBox.h"
#include "UIImage.h"
#include "UIItem.h"
#include "UIList.h"
#include "UIMenu.h"
#include "UITree.h"
#include "UIScrollBar.h"
#include "UISlider.h"
#include "UIProgressBar.h"
#include <windows.h>

INSPIRE_CLIENT_BENGIN
class simple_lock
{
public:
   simple_lock()
   {
      ::InitializeCriticalSection( &cs );
   }
   ~simple_lock()
   {
      ::DeleteCriticalSection( &cs );
   }

   void lock()
   {
      ::EnterCriticalSection( &cs );
   }

   void unlock()
   {
      ::LeaveCriticalSection( &cs );
   }

private:
   CRITICAL_SECTION cs;
};

class lock_proxy
{
public:
   lock_proxy( simple_lock* lock ) : _lock( lock )
   {
      _lock->lock();
   }
   ~lock_proxy()
   {
      _lock->unlock();
   }
private:
   simple_lock* _lock;
};

template<class TWnd>
class simple_pool
{
public:
   simple_pool() : _allocatedCount( 0 ), _freelistHead( NULL )
   {
      _elementSize = sizeof( TWnd ) > sizeof( TWnd* ) ? sizeof( TWnd ) : sizeof( TWnd* );
   }

   ~simple_pool()
   {
      while ( _freelistHead )
      {
         TWnd* toFree = _freelistHead;
         _freelistHead = *( reinterpret_cast<TWnd**>( _freelistHead ) );
         ::free( toFree );
      }
   }

   int count()
   {
      return _allocatedCount;
   }

   TWnd* alloc()
   {
      lock_proxy lock( &_lock );
      ++_allocatedCount;
      if ( _freelistHead == NULL )
      {
         return new( malloc( _elementSize ) )TWnd;
      }

      TWnd* memory = _freelistHead;
      _freelistHead = *( reinterpret_cast<TWnd**>( _freelistHead ) );
      return new( memory )TWnd;
   }

   TWnd* alloc( const TWnd* wnd )
   {
      lock_proxy lock( &_lock );
      ++_allocatedCount;
      if ( _freelistHead == NULL )
      {
         return new( malloc( _elementSize ) )TWnd;
      }

      TWnd* memory = _freelistHead;
      _freelistHead = *( reinterpret_cast<TWnd**>( _freelistHead ) );
      return new( memory )TWnd( wnd );
   }

   void dealloc( TWnd* wnd )
   {
      wnd->~TWnd();
      if ( true )
      {
         lock_proxy lock( &_lock );
         memset( wnd, 0xfe, _elementSize );
         --_allocatedCount;
         assert( _allocatedCount > 0 );
         *( reinterpret_cast<TWnd**>( wnd ) ) = _freelistHead;
         _freelistHead = wnd;
      }
   }

private:
   int         _allocatedCount;
   int         _elementSize;
   TWnd*       _freelistHead;
   simple_lock _lock;
};

INSPIRE_CLIENT_END
#endif