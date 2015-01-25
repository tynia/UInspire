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
#ifndef _INSPIRE_UI_CHECKBOX_H_
#define _INSPIRE_UI_CHECKBOX_H_

#include "IUICheckBox.h"
#include "UIWnd.h"

namespace inspire {

class CUICheckBox : public CUIWnd, public IUICheckBox
{
public:
   CUICheckBox();
   virtual ~CUICheckBox();

   virtual void Draw();

   virtual bool ProcessEvent( CKeyboardEvent* kb_event );
   virtual bool ProcessEvent( CMouseEvent* ms_event );

   virtual void Check( bool check );

   virtual bool IsCheck() const;

   virtual void Enable();

   virtual void Disable();

   virtual bool IsEnable() const;

   virtual void Flash( bool flash );

   virtual bool IsFlash() const;

   ///< 窗口回调函数
   virtual IInvoker* SetPressFunc( IInvoker* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( inspire::IXMLNode* node );

protected:
   bool      _Check;
   bool      _Enable;
   bool      _Flash;
   int         _xOffset;
   int         _yOffset;

   IInvoker*   _PressDownOper;
};
}
#endif