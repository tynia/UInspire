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

#include "platform.h"
#include "Point.h"

namespace inspire {

class INSPIRE_EXPORT_API CRect
{
public:
   int left;
   int top;
   int right;
   int bottom;

   CRect();
   CRect( int l, int t, int r, int b );
   CRect( const CRect& rect );

   void Set( int l, int t, int r, int b );

   void Translate( int x, int y );

   int Width() const;

   int Height() const;

   bool PointInRect( const CPoint& point ) const;

   bool PointInRect( int x, int y ) const;

   void TranslateToXRect( HWND hWnd, const RECT& rect_in );

   void TranslateXRectToWindow( HWND hWnd, RECT& rect_out );
};

}