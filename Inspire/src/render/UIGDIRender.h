#ifndef _XDUI_UI_RENDER_GDI_H_
#define _XDUI_UI_RENDER_GDI_H_

#include "../../interface/render/IUIRender.h"

XDUI_CLIENT_BENGIN
class CUIRenderGDI : public IUIRender
{
public:
   static IUIRender* Instance();

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

   HDC      _hDC;   ///< 绘制的目标窗口上下文
   HWND   _hWnd;   ///< 绘制的目标窗口句柄

};
XDUI_CLIENT_END
#endif