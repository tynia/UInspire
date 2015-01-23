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
#ifndef _INSPIRE_IUI_SCROLLBAR_H_
#define _INSPIRE_IUI_SCROLLBAR_H_

#include "IUIWnd.h"

namespace inspire {

class INSPIRE_EXPORT_API IUIScrollBar : virtual public IUIWnd
{
public:
   virtual ~IUIScrollBar() {};

   virtual void Enable() = 0;

   virtual void Disable() = 0;

   virtual bool IsEnable() = 0;

   virtual void SetScrollRange( int max_range ) = 0;
//    void SetScrollPosition( int pos );
//    const int GetScrollPosition() const;
};
}
#endif