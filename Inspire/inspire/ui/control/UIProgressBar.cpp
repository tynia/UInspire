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
#include "UIProgressBar.h"

namespace inspire {

CUIProgressBar::CUIProgressBar() : CUIWnd( EWT_PROGRESSBAR )
, _MaxValue( MAX_VALUE )
, _MinValue( MIN_VALUE )
, _CurrentValue( 0 )
{

}

CUIProgressBar::~CUIProgressBar()
{

}

void CUIProgressBar::Draw()
{

}

void CUIProgressBar::SetMaxValue( int max_value )
{
   _MaxValue = max_value;
}

void CUIProgressBar::SetMinValue( int min_value /*= 0*/ )
{
   _MinValue = min_value;
}

void CUIProgressBar::SetValue( int cur_value )
{
   _CurrentValue = cur_value;
}

const int CUIProgressBar::GetCurrentValue() const
{
   return _CurrentValue;
}

void CUIProgressBar::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIProgressBar* bar = dynamic_cast<CUIProgressBar*>( wnd );
   //todo:
}

void CUIProgressBar::ParseData( XML::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo:
}

}
