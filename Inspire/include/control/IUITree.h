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
#ifndef _INSPIRE_IUI_TREE_H_
#define _INSPIRE_IUI_TREE_H_

#include "IUIWnd.h"

INSPIRE_CLIENT_BENGIN
class INSPIRE_LIB_API IUITree : virtual public IUIWnd
{
public:
   virtual ~IUITree() {};

   virtual void AddChild( ItemData child ) = 0;

   virtual void RemoveChild( const _tchar* child_id ) = 0;

   virtual void RemoveChild( const int index ) = 0;

   virtual void SetMultiChildNodeCheck( bool multi_check ) = 0;

   virtual void Check( bool check ) = 0;

   virtual bool IsCheck() = 0;

   virtual IOperation*   SetDoubleClickFunc( IOperation* oper ) = 0;

   virtual IOperation* SetPressFunc( IOperation* oper ) = 0;
};
INSPIRE_CLIENT_END
#endif