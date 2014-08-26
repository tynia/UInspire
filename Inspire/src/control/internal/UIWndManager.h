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
#ifndef _INSPIRE_UI_WND_MANAGER_H_
#define _INSPIRE_UI_WND_MANAGER_H_

#include "IUIWnd.h"
#include "IXMLNode.h"
#include "IUIWndManager.h"

class CUIBase;

INSPIRE_CLIENT_BENGIN
class CUIWndFactory;
class IUIRender;
class CInputManager;
class CEventQueue;
class CUIWnd;

#define LOWWORD( l )   ( ( WORD )( ( ( DWORD_PTR )( l ) ) & 0xffff ) )
#define HIGHWORD( l )   ( ( WORD )( ( ( ( DWORD_PTR )( l ) ) >> 16 ) & 0xffff ) )
#define GET_X_LPARAM( lp ) ( ( int )( short )LOWWORD( lp ) )
#define GET_Y_LPARAM( lp ) ( ( int )( short )HIGHWORD( lp ) )

class CUIWndManager : public IUIWndManager
{
public:
   virtual ~CUIWndManager();

   virtual void AttachWindow( CUIBase* const uibase, const _tchar* wndid, bool multiInstance );

   virtual void UnAttachWindow( CUIBase* const uibase, bool multiInstance );

   virtual IUIWnd* GetWindow( const _tchar* wndid, bool multiInstance );

   virtual IUIWnd* AllocWndEntity( WndType wt );

   virtual void DeallocWndEntity( IUIWnd* wnd );

   virtual IUIRender* GetIUIRender();

   virtual void SetAppInstance( HINSTANCE& hInstance );

   virtual const HINSTANCE GetAppInstance() const;

   virtual bool InitWndInstance( IUIWnd* initWnd, HWND& hInitWnd, const HWND& hPareant, DWORD style );

   virtual void ShowModalWnd( const HWND& hWnd, const HWND& hParent );

   virtual void HideModalWnd( const HWND& hParent );

   virtual void PushToEventQueue( const MSG& uMsg ) {};

public:
   CUIWnd* MakeClone( CUIWnd* wnd );
   static CUIWndManager* Instance();
   void Release();

private:
   void PushToWndContainer( CUIWnd* wnd );
   void PopFromWndContainer( CUIBase* uibase );
   void PushToMultiInstanceWndContainer( CUIWnd* wnd );
   void PopFromMultiInstanceWndContainer( CUIBase* uibase );
   void CloneMultiInstanceWnd( CUIWnd* wnd );
   void ParseLayout();
   void ParseLayoutFile( const char* layout_file );
   void ParseControl( CUIWnd* wnd, XML::IXMLNode* node );

private:
   CUIBase* GetUIBase( const HWND& hWnd );
   void Draw( const HWND& hWnd, INSPIRE_CLIENT::IUIWnd* wnd );

private:
   LRESULT OnNCHitTest( HWND hWnd, WPARAM wParam, LPARAM lParam );

private:
   static LRESULT CALLBACK __WindowProcess( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
   ATOM RegisterWndClass( IUIWnd* wnd );
   void RunMessageLoop();
   bool PreTranslateMsg( PMSG pMsg );

private:
   CUIWndManager(); ///< everyone should not new it.
   
   static CUIWndManager* static_Instance;
   static int const MAX_MULTI_INSTANCE_WND_COUNT = 20;
   HINSTANCE      _hInstance;
   IUIRender*      _UIRender;
   CUIWndFactory*   _Factory;
   CInputManager*   _InputMng;
   CEventQueue*   _EventQueue;

   static const int ZlevelCount = UIWZ_LEVEL_TOPMOST - UIWZ_LEVEL_BOTTOM;
   typedef std::map<CUIWnd*, CUIBase*> WndContainer;
   WndContainer            _UIWndContainer[ZlevelCount];      ///< 只有一个实例的普通窗口
   typedef std::map<CUIWnd*, CUIBase*> MultiInstanceWndContainer;      ///< 有多个实例的窗口
   MultiInstanceWndContainer   _UIMultiInstanceWndContainer[ZlevelCount];
};

INSPIRE_CLIENT_END
#endif