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
#include "UICheckBox.h"

namespace inspire {
CUICheckBox::CUICheckBox() : CUIWnd( EWT_CHECKBOX )
, _Enable( true )
, _Flash( false )
, _PressDownOper( NULL )
{

}

CUICheckBox::~CUICheckBox()
{

}

void CUICheckBox::Draw()
{

}

bool CUICheckBox::ProcessEvent( CKeyboardEvent* kb_event )
{
   return false;
}

bool CUICheckBox::ProcessEvent( CMouseEvent* ms_event )
{
   return false;
}

void CUICheckBox::Check( bool check )
{
   _Check = check;
}

bool CUICheckBox::IsCheck() const
{
   return _Check;
}

void CUICheckBox::Enable()
{
   _Enable = true;
}

void CUICheckBox::Disable()
{
   _Enable = false;
}

bool CUICheckBox::IsEnable() const
{
   return _Enable;
}

void CUICheckBox::Flash( bool flash )
{
   _Flash = flash;
}

bool CUICheckBox::IsFlash() const
{
   return _Flash;
}

IInvoker* CUICheckBox::SetPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

void CUICheckBox::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUICheckBox* checkbox = dynamic_cast<CUICheckBox*>( wnd );
   _Check = checkbox->_Check;
   _Enable = checkbox->_Enable;
   _Flash = checkbox->_Flash;
   _xOffset = checkbox->_xOffset;
   _yOffset = checkbox->_yOffset;
}

void CUICheckBox::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   // todo:
}

}
