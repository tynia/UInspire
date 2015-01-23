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
#include "UIButton.h"

namespace inspire {
inspire::CUIButton::CUIButton() : CUIWnd( EWT_BUTTON )
, _Enable( true )
, _Flash( false )
, _PressDownOper( NULL )
{

}

CUIButton::~CUIButton()
{

}

void CUIButton::Draw( void )
{

}

bool CUIButton::ProcessEvent( CKeyboardEvent* kb_event )
{
   return false;
}

bool CUIButton::ProcessEvent( CMouseEvent* ms_event )
{
   return false;
}

void CUIButton::Enable()
{
   _Enable = true;
}

void CUIButton::Disable()
{
   _Enable = false;
}

bool CUIButton::IsEnable() const
{
   return _Enable;
}

void CUIButton::Flash( bool flash )
{
   _Flash = false;
}

bool CUIButton::IsFlash() const
{
   return _Flash;
}

IInvoker* CUIButton::SetPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

void CUIButton::CloneFrom( CUIWnd* wnd )
{
   //do nothing;
   CUIWnd::CloneFrom( wnd );

   CUIButton* btn = dynamic_cast<CUIButton*>( wnd );
   _Enable = btn->_Enable;
   _Flash = btn->_Flash;
}

void CUIButton::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   // todo:
}

}
