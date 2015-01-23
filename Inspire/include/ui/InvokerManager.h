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

#include "platform.h"
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
    @brief �ú���������һֱnew�����һ���ص��Ѿ�ע�����������invoker��������ֻ���ҵ���invoker�������������������û�������Ա���Ϳ��Է��Ĵ󵨵�ʹ��MakeInvoker��
    *      ������ҵĵ���֮��������
    */
   template<class TObj, class TFunc>
   IOperation* MakeInvoker( TObj* obj, TFunc func );

private:
   /**
    @brief ��ֹ����Ƶ���л��ص���ʱ�򣬲��ϵ�new�µ�invoker������ڴ�й©����Ҫ�ҵ��Ѿ����ڵ�invoker���ؾ�OK��
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