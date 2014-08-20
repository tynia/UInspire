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
#include "UIRichEditBox.h"

INSPIRE_CLIENT_BENGIN

CUIRichEditBox::CUIRichEditBox() : CUIWnd( EWT_RICHEDITBOX )
, _Enable( true )
, _SingleLine( false )
, _TextChangeOper( NULL )
, _HorizonCenter( false )
, _VerticeCenter( false )
{

}

CUIRichEditBox::~CUIRichEditBox()
{

}

void CUIRichEditBox::Draw()
{

}

void CUIRichEditBox::SetText( const _tchar* text )
{
   _Caption = text;
}

void CUIRichEditBox::Enable()
{
   _Enable = false;
}

void CUIRichEditBox::Disable()
{
   _Enable = true;
}

bool CUIRichEditBox::IsEnable() const
{
   return _Enable;
}

void CUIRichEditBox::SetSingleLine( bool single_line )
{
   _SingleLine = single_line;
}


void CUIRichEditBox::SetHorizonCenter( bool h_center )
{
   _HorizonCenter = h_center;
}

void CUIRichEditBox::SetVerticeCenter( bool v_center )
{
   _VerticeCenter = v_center;
}

IOperation* CUIRichEditBox::SetTextChangeFunc( IOperation* oper )
{
   IOperation* oldoper = _TextChangeOper;
   _TextChangeOper = oper;
   return oldoper;
}

void CUIRichEditBox::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIRichEditBox* richedit = dynamic_cast<CUIRichEditBox*>( wnd );
   _SingleLine = richedit->_SingleLine;
   _Enable = richedit->_Enable;
}

void CUIRichEditBox::ParseData( XML::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo:
}

INSPIRE_CLIENT_END
