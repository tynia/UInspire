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
#include "UIScrollBar.h"

namespace inspire {

CUIScrollBar::CUIScrollBar() : CUIWnd( EWT_SCROLLBAR )
, _Enable( true )
, _MaxRange( MAX_RANGE )
, _RectPrev( 0, 0, 0, 0 )
, _RectNext( 0, 0, 0, 0 )
, _PrevResourceID( L"" )
, _NextResourceID( L"" )
{

}

CUIScrollBar::~CUIScrollBar()
{

}

void CUIScrollBar::Draw()
{

}

void CUIScrollBar::Enable()
{
   _Enable = true;
}

void CUIScrollBar::Disable()
{
   _Enable = false;
}

bool CUIScrollBar::IsEnable()
{
   return _Enable;
}

void CUIScrollBar::SetScrollRange( int max_range )
{
   _MaxRange = max_range;
}

void CUIScrollBar::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIScrollBar* scrollbar = dynamic_cast<CUIScrollBar*>( wnd );
   //todo:
}

void CUIScrollBar::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo
}

}
