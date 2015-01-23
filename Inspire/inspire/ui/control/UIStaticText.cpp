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
#include "UIStaticText.h"

namespace inspire {
CUIStaticText::CUIStaticText() : CUIWnd( EWT_STATICTEXT )
, _PressDownOper( NULL )
, _SubTextFlag( false )
{

}

CUIStaticText::~CUIStaticText()
{
   _PressDownOper = NULL;
   _SubTextFlag = false;
}

void CUIStaticText::SetText( _tchar* text )
{
   _SubTextFlag = false;
   _Caption = text;
}

void CUIStaticText::SetSubText( _tchar* text )
{
   _SubTextFlag = true;
   _Caption = text;
}

void CUIStaticText::SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical )
{
   _Horizon = horizon;
   _Verticial = vertical;
}

IInvoker* CUIStaticText::SetPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

void CUIStaticText::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIStaticText* statictext = dynamic_cast<CUIStaticText*>( wnd );
}

void CUIStaticText::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo:
}

}
