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
#include "UIEditBox.h"

INSPIRE_CLIENT_BENGIN

CUIEditBox::CUIEditBox() : CUIWnd( EWT_EDITBOX )
, _TextChangeOper( NULL )
{

}

CUIEditBox::~CUIEditBox()
{

}

void CUIEditBox::Draw()
{

}

void CUIEditBox::Clear()
{
   SetCaption( NULL );
}

void CUIEditBox::SetText( const _tchar* text )
{
   SetCaption( text );
}

const _tchar* CUIEditBox::GetText() const
{
   return GetCaption();
}

void CUIEditBox::SetMaxInputLength( int len )
{
   _MaxInputLength = len;
}

void CUIEditBox::Enable()
{
   _Enable = true;
}

void CUIEditBox::Disable()
{
   _Enable = false;
}

bool CUIEditBox::IsEnable() const
{
   return _Enable;
}

void CUIEditBox::ShowCurser( bool show /*= true*/ )
{
   _ShowCurser = show;
}

void CUIEditBox::SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical )
{

}

IOperation* CUIEditBox::SetTextChangeFunc( IOperation* oper )
{
   IOperation* oldoper = _TextChangeOper;
   _TextChangeOper = oper;
   return oldoper;
}

void CUIEditBox::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIEditBox* edit = dynamic_cast<CUIEditBox*>( wnd );
   _ShowCurser = edit->_ShowCurser;
   _Enable = edit->_Enable;
   _MaxInputLength = edit->_MaxInputLength;
   _xOffset = edit->_xOffset;
   _yOffset = edit->_yOffset;
}

void CUIEditBox::ParseData( XML::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   // todo:
}

INSPIRE_CLIENT_END
