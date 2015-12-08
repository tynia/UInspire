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
#ifndef _XDUI_UI_RENDER_GDI_H_
#define _XDUI_UI_RENDER_GDI_H_

#include "IUIRender.h"

namespace inspire {
class CUIRenderGDI : public IUIRender
{
public:
   static IUIRender* Instance() {return NULL;};

   ///< IUIRender interface
   virtual bool InitUIRender();
   virtual void BeginDraw( const HWND hWnd );
   virtual void EndDraw();
   virtual void DrawRectangle( const CRect& rect );
   ///< 绘制图片区域
   virtual void DrawTexture( const CRect& rect );
   ///< 绘制边框的发光效果
   virtual void DrawRectBorder( const CRect& rect );
   ///< 绘制线条
   virtual void DrawLine( CPoint& begin, CPoint& end );
   ///< 绘制文字
   virtual void TextOut( CRect& rect, _tchar* text, DWORD dwTextColor );
   ///< 绘制特效
   virtual void DrawEffect( const char* effect_path );
   virtual void DrawEffect();

   virtual void Release();

private:
   CUIRenderGDI();
   ~CUIRenderGDI();

   HDC    _hDC;   ///< 绘制的目标窗口上下文
   HWND   _hWnd;  ///< 绘制的目标窗口句柄

};
}
#endif