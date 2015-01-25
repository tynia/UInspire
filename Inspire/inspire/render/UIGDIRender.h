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
   ///< ����ͼƬ����
   virtual void DrawTexture( const CRect& rect );
   ///< ���Ʊ߿�ķ���Ч��
   virtual void DrawRectBorder( const CRect& rect );
   ///< ��������
   virtual void DrawLine( CPoint& begin, CPoint& end );
   ///< ��������
   virtual void TextOut( CRect& rect, _tchar* text, DWORD dwTextColor );
   ///< ������Ч
   virtual void DrawEffect( const char* effect_path );
   virtual void DrawEffect();

   virtual void Release();

private:
   CUIRenderGDI();
   ~CUIRenderGDI();

   HDC    _hDC;   ///< ���Ƶ�Ŀ�괰��������
   HWND   _hWnd;  ///< ���Ƶ�Ŀ�괰�ھ��

};
}
#endif