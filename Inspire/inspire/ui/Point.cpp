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
#include "Point.h"

namespace inspire {

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

void CPoint::TranslateToXPoint( const HWND hWnd, const POINT& pt )
{
   int win_x = pt.x;   ///< x point of Windows
   int win_y = pt.y;   ///< y point of Windows

   RECT rect;
   ::GetWindowRect( hWnd, &rect );
   ///< translate to point of inspire
   x = win_x;
   y = ( rect.top - rect.bottom ) - win_y;
}

void CPoint::TranslateToWindow( const HWND hWnd, POINT& pt )
{
   RECT rect;
   ::GetWindowRect( hWnd, &rect );

   pt.x = x;
   pt.y = ( rect.top - rect.bottom ) - y;
}

}