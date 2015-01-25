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
#include "InvokerManager.h"

InvokerManager::InvokerManager()
{
}

InvokerManager::~InvokerManager()
{
}

InvokerManager* InvokerManager::Instance()
{
   static InvokerManager mng;
   return &mng;
}

void InvokerManager::AddInvoker(IInvoker* oper)
{
   _invokerVec.push_back(oper);
}