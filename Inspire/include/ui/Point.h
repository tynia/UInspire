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
#ifndef _INSPIRE_POINT_H_
#define _INSPIRE_POINT_H_

#include "platform.h"

namespace inspire {

class INSPIRE_EXPORT_API CPoint
{
public:
   ///< 成员
   int x;
   int y;

   ///< 构造
   CPoint();
   CPoint( int xx, int yy );
   CPoint( const CPoint& pt );

   ///< 运算符
   const CPoint& operator= ( const CPoint& pt );
   const CPoint& operator+= ( const CPoint& pt );
   const CPoint operator- ( const CPoint& pt );
   const CPoint operator+ ( const CPoint& pt );

   void TranslateToXPoint( const HWND hWnd, const POINT& pt );
   void TranslateToWindow( const HWND hWnd, POINT& pt );
};

}
#endif