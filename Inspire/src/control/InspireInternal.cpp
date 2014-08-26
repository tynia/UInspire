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
#include "InspireInternal.h"

INSPIRE_CLIENT_BENGIN
CPoint::CPoint()
{

}

CPoint::CPoint( int xx, int yy ) : x( xx ), y( yy )
{

}

CPoint::CPoint( const CPoint& pt ) : x( pt.x ), y( pt.y )
{

}

const CPoint& CPoint::operator= ( const CPoint& pt )
{
   x = pt.x;
   y = pt.y;
   return ( *this );
}

const CPoint& CPoint::operator+= ( const CPoint& pt )
{
   x += pt.x;
   y += pt.y;
   return ( *this );
}

const CPoint CPoint::operator- ( const CPoint& pt )
{
   return ( CPoint( x - pt.x, y - pt.y ) );
}
const CPoint CPoint::operator+ ( const CPoint& pt )
{
   return ( CPoint( x + pt.x, y + pt.y ) );
}

void CPoint::TranslateToXPoint( __in const HWND hWnd, __in const POINT& pt )
{
   int win_x = pt.x;   ///< Windows 客户区域x坐标
   int win_y = pt.y;   ///< Windows 客户区域y坐标

   RECT rect;
   ::GetWindowRect( hWnd, &rect );
   ///< 转换成自己的坐标系
   x = win_x;
   y = ( rect.top - rect.bottom ) - win_y;
}

void CPoint::TranslateToWindow( __in const HWND hWnd, __inout POINT& pt )
{
   RECT rect;
   ::GetWindowRect( hWnd, &rect );

   pt.x = x;
   pt.y = ( rect.top - rect.bottom ) - y;
}
//////////////////////////////////////////////////////////////////////////
///< CRect
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

void CRect::TranslateToXRect( __in HWND hWnd, __in const RECT& rect_in )
{
   RECT rect;
   ::GetWindowRect( hWnd, &rect );

   left = rect.left;
   right = rect.right;
   bottom = ( rect.top - rect.bottom ) - rect_in.bottom;
   top = ( rect.top - rect.bottom ) - rect_in.top;
}

void CRect::TranslateXRectToWindow( __in HWND hWnd, __out RECT& rect_out )
{
   RECT rect;
   ::GetWindowRect( hWnd, &rect );

   rect_out.left = left;
   rect_out.right = right;
   rect_out.bottom = ( rect.top - rect.bottom ) - bottom;
   rect_out.top = ( rect.top - rect.bottom ) - top;
}

INSPIRE_CLIENT_END