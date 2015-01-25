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
#include "UIImage.h"

namespace inspire {

CUIImage::CUIImage() : CUIWnd( EWT_IMAGE )
, _PressDownOper( NULL )
{

}

CUIImage::~CUIImage()
{

}

void CUIImage::Draw()
{

}

void CUIImage::DrawBorder()
{

}

void CUIImage::ShowIndexNum()
{

}

IInvoker* CUIImage::SetPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

void CUIImage::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIImage* image = dynamic_cast<CUIImage*>( wnd );
}

void CUIImage::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo
}

}
