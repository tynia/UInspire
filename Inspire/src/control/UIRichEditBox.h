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
#ifndef _INSPIRE_UI_RICHEDIT_H_
#define _INSPIRE_UI_RICHEDIT_H_

#include "../../interface/IUIRichEditBox.h"
#include "UIWnd.h"

INSPIRE_CLIENT_BENGIN

class CUIWnd;

class CUIRichEditBox : public CUIWnd, public IUIRichEditBox
{
public:
   CUIRichEditBox();
   virtual ~CUIRichEditBox();

   virtual void Draw();
   virtual void SetText( const _tchar* text );
   virtual void Enable();
   virtual void Disable();
   virtual bool IsEnable() const;
   virtual void SetSingleLine( bool single_line );
   virtual void SetHorizonCenter( bool h_center );
   virtual void SetVerticeCenter( bool v_center );

   virtual IOperation* SetTextChangeFunc( IOperation* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( XML::IXMLNode* node );

protected:
   IOperation*      _TextChangeOper;
   bool         _Enable;
   bool         _SingleLine;
   bool         _HorizonCenter;
   bool         _VerticeCenter;
};

INSPIRE_CLIENT_END
#endif