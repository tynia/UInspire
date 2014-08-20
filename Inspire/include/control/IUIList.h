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
#ifndef _INSPIRE_IUI_LIST_H_
#define _INSPIRE_IUI_LIST_H_

#include "IUIWnd.h"

INSPIRE_CLIENT_BENGIN
struct ItemData;

class INSPIRE_LIB_API IUIList : virtual public IUIWnd
{
public:
   virtual ~IUIList() {};

   virtual void AddItem( ItemData& item, int index ) = 0;

   virtual void RemoveItem( int index ) = 0;

   virtual void Clear() = 0;

   virtual void ShowScrollBar( bool show ) = 0;
};
INSPIRE_CLIENT_END
#endif