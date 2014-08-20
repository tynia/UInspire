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
#ifndef _INSPIRE_IUI_WNDMANAGER_H_
#define _INSPIRE_IUI_WNDMANAGER_H_

#include "Inspire.h"
class CUIBase;

INSPIRE_CLIENT_BENGIN

class IUIWnd;
class CUIWnd;
class IUIRender;
enum WndType;

class INSPIRE_LIB_API IUIWndManager
{
public:
   virtual ~IUIWndManager() {};

   ///< 找底层窗口，用于窗口初始化的时候，注册具有多个实例的窗口
   virtual void AttachWindow( CUIBase* const uibase, const _tchar* wndid, bool multiInstance ) = 0;

   virtual void UnAttachWindow( CUIBase* const uibase, bool multiInstance ) = 0;

   ///< 找底层窗口，用于窗口初始化的时候，注册窗口
   virtual IUIWnd* GetWindow( const _tchar* wndid, bool multiInstance ) = 0;

   virtual IUIWnd* AllocWndEntity( WndType wt ) = 0;

   virtual void DeallocWndEntity( IUIWnd* wnd ) = 0;

   virtual IUIRender* GetIUIRender() = 0;

   virtual void SetAppInstance( HINSTANCE& hInstance ) = 0;

   virtual const HINSTANCE GetAppInstance() const = 0;

   virtual bool InitWndInstance( IUIWnd* initWnd, HWND& hInitWnd, const HWND& hPareant, DWORD style ) = 0;

   virtual void ShowModalWnd( const HWND& hWnd, const HWND& hParent ) = 0;

   virtual void HideModalWnd( const HWND& hParent ) = 0;

   virtual void PushToEventQueue( const MSG& uMsg ) = 0;
};

INSPIRE_CLIENT_END
#endif