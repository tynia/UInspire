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
#ifndef _INSPIRE_RENDER_H_
#define _INSPIRE_RENDER_H_

#include "platform.h"
#include "wnd.h"
namespace inspire {
enum RenderUID
{
   RUID_GDI = 0,
   RUID_D2D,
   RUID_D3D,
};

class INSPIRE_EXPORT_API IUIRender
{
public:
   virtual ~IUIRender() {};

   virtual bool InitUIRender() = 0;
   virtual void BeginDraw( const HWND hWnd ) = 0; 
   virtual void EndDraw() = 0;
   ///< rect
   virtual void DrawRectangle( const CRect& rect ) = 0;
   ///< texture
   virtual void DrawTexture( const CRect& rect ) = 0;
   ///< border
   virtual void DrawRectBorder( const CRect& rect ) = 0;
   ///< line
   virtual void DrawLine( CPoint& begin, CPoint& end ) = 0;
   ///< text
   virtual void TextOut( CRect& rect,  _tchar* text, DWORD dwTextColor ) = 0;
   ///< effect
   virtual void DrawEffect( const char* effect_path ) = 0;
   virtual void DrawEffect() = 0;

   virtual void Release() = 0;
};

}
#endif