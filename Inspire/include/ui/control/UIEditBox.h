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
#ifndef _INSPIRE_UI_EDITBOX_H_
#define _INSPIRE_UI_EDITBOX_H_

#include "IUIEditBox.h"
#include "UIWnd.h"

namespace inspire {

class CUIEditBox : public CUIWnd, public IUIEditBox
{
public:
   CUIEditBox();
   virtual ~CUIEditBox();

   virtual void Draw();
   virtual void Clear();
   virtual void SetText( const _tchar* text );
   virtual const _tchar* GetText() const;
   virtual void SetMaxInputLength( int len );
   virtual void Enable();
   virtual void Disable();
   virtual bool IsEnable() const;
   virtual void ShowCurser( bool show = true );
   virtual void SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical );
   virtual IOperation* SetTextChangeFunc( IOperation* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( XML::IXMLNode* node );

protected:
   bool      _Enable;
   bool      _ShowCurser;
   int         _MaxInputLength;
   int         _xOffset;
   int         _yOffset;
   IOperation*   _TextChangeOper;
};
}
#endif