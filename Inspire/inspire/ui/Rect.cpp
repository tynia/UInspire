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
#include "Rect.h"

namespace inspire {

CRect::CRect()
{

}

CRect::CRect( int l, int t, int r, int b )
{
   Set( l, t, r, b );
}

CRect::CRect( const CRect& rect )
{
   left = rect.left;
   top = rect .top;
   right = rect.right;
   bottom = rect.bottom;
}

void CRect::Set( int l, int t, int r, int b )
{
   left = l;
   top = t;
   right = r;
   bottom = b;
}

void CRect::Translate( int x, int y )
{
   left += x;
   top += y;
   right += x;
   bottom += y;
}

int CRect::Width() const
{
   return right - left;
}

int CRect::Height() const
{
   return top - bottom;
}

bool CRect::PointInRect( const CPoint& point ) const
{
   return PointInRect( point.x, point.y );
}

bool CRect::PointInRect( int x, int y ) const
{
   if ( x < left )
      return false;
   if ( x > right )
      return false;
   if ( y > top )
      return false;
   if ( y < bottom )
      return false;

   return true;
}

void CRect::TranslateToXRect( HWND hWnd, const RECT& rect_in )
{
   RECT rect;
   ::GetWindowRect( hWnd, &rect );

   left = rect.left;
   right = rect.right;
   bottom = ( rect.top - rect.bottom ) - rect_in.bottom;
   top = ( rect.top - rect.bottom ) - rect_in.top;
}

void CRect::TranslateXRectToWindow( HWND hWnd, RECT& rect_out )
{
   RECT rect;
   ::GetWindowRect( hWnd, &rect );

   rect_out.left = left;
   rect_out.right = right;
   rect_out.bottom = ( rect.top - rect.bottom ) - bottom;
   rect_out.top = ( rect.top - rect.bottom ) - top;
}

}