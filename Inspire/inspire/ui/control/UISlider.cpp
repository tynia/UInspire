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
#include "UISlider.h"

namespace inspire {

CUISlider::CUISlider() : CUIWnd( EWT_SLIDER )
, _Enable( true )
, _MaxStep( MAX_STEP )
, _MaxValue( MAX_VALUE )
, _CurrentValue( 0 )
{

}

CUISlider::~CUISlider()
{

}

void CUISlider::Draw()
{

}

void CUISlider::Enable()
{
   _Enable = true;
}

void CUISlider::Disable()
{
   _Enable = false;
}

bool CUISlider::IsEnable() const
{
   return _Enable;
}

void CUISlider::SetChangeStep( int step )
{
   _MaxStep = step;
}

void CUISlider::SetMaxValue( int max_value )
{
   _MaxValue = max_value;
}

const int CUISlider::GetCurrentValue() const
{
   return _CurrentValue;
}

void CUISlider::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUISlider* slider = dynamic_cast<CUISlider*>( wnd );
   //todo:
}

void CUISlider::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo:
}

}
