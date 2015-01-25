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
#ifndef _INSPIRE_INVOKER_MANAGER_H_
#define _INSPIRE_INVOKER_MANAGER_H_

#include "platform.h"

class IInvoker;

class InvokerManager
{
public:
   ~InvokerManager();
   static InvokerManager* Instance();

   template<class TObj, class TFunc>
   IInvoker* MakeInvoker( TObj* obj, TFunc func );

private:
   InvokerManager();
   /**
    @brief 防止窗口频繁切换回调的时候，不断的new新的invoker而造成内存泄漏，需要找到已经存在的invoker返回就OK。
    */
   template<class TObj, class TFunc>
   IInvoker* FindInvoker(TObj* obj, TFunc func);

   void AddInvoker( IInvoker* oper );

private:
   std::vector<IInvoker*> _invokerVec;
};

//////////////////////////////////////////////////////////////////////////
template<class TObj, class TFunc>
IInvoker* InvokerManager::FindInvoker(TObj* obj, TFunc func)
{
   std::vector<IInvoker*>::iterator it = _invokerVec.begin();
   for (; it != _invokerVec.end(); ++it)
   {
      Invoker<TObj>* invoker = ( *it );
      if ( invoker )
      {
         if ( invoker->Equel( obj, func ) )
         {
            return ( *it );
         }
      }
   }
   return NULL;
}

template<class TObj, class TFunc>
IInvoker* InvokerManager::MakeInvoker( TObj* obj, TFunc func )
{
   IInvoker* oper = NULL;
   // find if it ever made before..
   oper = FindInvoker( obj, func );
   if ( oper )
   {
      return oper;
   }
   // if no then do next.
   void* memory = _memory_pool->alloc( sizeof( Invoker<TObj> ) );
   if ( memory )
   {
      oper = new( memory ) Invoker<TObj>( obj, func );
      // push in a invoker manager...
      AddInvoker(oper);
      return oper;
   }

   // can't process to here.
   return oper;
}

#endif