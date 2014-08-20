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
#include "InvokerManager.h"
#include "MemoryPool.h"

InvokerManager::InvokerManager()
{
   _memory_pool = new MemoryPool();
}

InvokerManager::~InvokerManager()
{
   delete _memory_pool;
   _memory_pool = NULL;
}

InvokerManager* InvokerManager::GetInvokerManager()
{
   static InvokerManager invoker_mng;
   return &invoker_mng;
}

void InvokerManager::AddOperation( IOperation* oper )
{
   _oper_vector.push_back( oper );
}