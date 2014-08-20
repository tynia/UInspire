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

   HDC      _hDC;   ///< ���Ƶ�Ŀ�괰��������
   HWND   _hWnd;   ///< ���Ƶ�Ŀ�괰�ھ��

};
XDUI_CLIENT_END
#endif