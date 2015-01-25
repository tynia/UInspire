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
#ifndef _INSPIRE_IUI_STATICTEXT_H_
#define _INSPIRE_IUI_STATICTEXT_H_

#include "IUIWnd.h"

namespace inspire {
class INSPIRE_EXPORT_API IUIStaticText : virtual public IUIWnd
{
public:
   virtual ~IUIStaticText() {};

   virtual void SetText( _tchar* text ) = 0;
   virtual void SetSubText( _tchar* text ) = 0;
   virtual void SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical ) = 0;

   virtual IInvoker* SetPressFunc( IInvoker* oper ) = 0;
};
}
#endif