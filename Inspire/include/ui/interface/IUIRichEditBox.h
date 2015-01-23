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
#ifndef _INSPIRE_IUI_RICHEDIT_H_
#define _INSPIRE_IUI_RICHEDIT_H_

#include "IUIWnd.h"

namespace inspire {
class INSPIRE_EXPORT_API IUIRichEditBox : virtual public IUIWnd
{
public:
   virtual ~IUIRichEditBox() {};

   virtual void SetText( const _tchar* text ) = 0;

   virtual void Enable() = 0;

   virtual void Disable() = 0;

   virtual bool IsEnable() const = 0;

   virtual void SetSingleLine( bool single_line ) = 0;

   virtual void SetHorizonCenter( bool h_center ) = 0;

   virtual void SetVerticeCenter( bool v_center ) = 0;

   virtual IOperation* SetTextChangeFunc( IOperation* oper ) = 0;
};
}
#endif