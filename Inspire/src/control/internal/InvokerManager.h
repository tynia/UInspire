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
#ifndef _INSPIRE_INVOKER_MANAGER_H_
#define _INSPIRE_INVOKER_MANAGER_H_

#include "Inspire.h"
#include "MemoryPool.h"

class IOperation;
class MemoryPool;

class InvokerManager
{
public:
   InvokerManager();
   ~InvokerManager();

   static InvokerManager* GetInvokerManager();
   /**
    @brief 该函数并不是一直new，如果一个回调已经注册过并生成了invoker，函数就只会找到该invoker，并返回它。这样，用户（程序员）就可以放心大胆地使用MakeInvoker。
    *      这可是我的得意之作啊！！
    */
   template<class TObj, class TFunc>
   IOperation* MakeInvoker( TObj* obj, TFunc func );

private:
   /**
    @brief 防止窗口频繁切换回调的时候，不断的new新的invoker而造成内存泄漏，需要找到已经存在的invoker返回就OK。
    */
   template<class TObj, class TFunc>
   IOperation* FindOperation( TObj* obj, TFunc func );

   void AddOperation( IOperation* oper );

private:
   MemoryPool* _memory_pool;
   std::vector<IOperation*> _oper_vector;
};

//////////////////////////////////////////////////////////////////////////
template<class TObj, class TFunc>
IOperation* InvokerManager::FindOperation( TObj* obj, TFunc func )
{
   std::vector<IOperation*>::const_iterator cit = _oper_vector.begin();
   for ( ; cit != _oper_vector.end(); ++cit )
   {
      Invoker<TObj>* invoker = dynamic_cast<Invoker<TObj>*>( *cit );
      if ( invoker )
      {
         if ( invoker->Equel( obj, func ) )
         {
            return ( *cit );
         }
      }
   }
   return NULL;
}

template<class TObj, class TFunc>
IOperation* InvokerManager::MakeInvoker( TObj* obj, TFunc func )
{
   IOperation* oper = NULL;
   // find if it ever made before..
   oper = FindOperation( obj, func );
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
      AddOperation( oper );
      return oper;
   }

   // can't process to here.
   return oper;
}

#endif