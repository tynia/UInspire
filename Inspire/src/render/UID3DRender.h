#ifndef _XDUI_UI_D3D_RENDER_H_
#define _XDUI_UI_D3D_RENDER_H_

#include "IUIRender.h"
#include <d2d1.h>
INSPIRE_CLIENT_BENGIN
class CUID3DRender : public IUIRender
{
public:
   CUID3DRender();
   virtual ~CUID3DRender();
   virtual bool InitUIRender(HWND hWnd);
   virtual void BeginDraw();
   virtual void EndDraw();
   ///< 绘制图片区域
   virtual void DrawRect(const CRect& rect);
   ///< 绘制边框的发光效果
   virtual void DrawRectBorder(const CRect& rect);
   ///< 绘制线条
   virtual void DrawLine();
   ///< 绘制文字
   virtual void DrawText(const _tchar* text);
   virtual void TextOut(const CRect& rect, const _tchar* text);
   virtual void DrawEffect(const char* effect_path);
   virtual void DrawEffect();

private:
   void Cleanup();
private:
   ID2D1Factory*         _D2D1Factory;
   ID2D1HwndRenderTarget*   _RenderTarget;
   ID2D1SolidColorBrush*   _ColorBrush;
   HWND               _hTargetWnd;
   RECT               _RenderRect;
};
INSPIRE_CLIENT_END
#endif