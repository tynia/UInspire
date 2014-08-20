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
#ifndef _INSPIRE_UI_BASE_H_
#define _INSPIRE_UI_BASE_H_

#include "IUIWndManager.h"
#include "InspireUtil.h"

class INSPIRE_CLIENT::IUIWnd ;

class INSPIRE_LIB_API CUIBase
{
public:
   CUIBase( const _tchar* WndID, HWND hParentWnd = NULL, bool MultiInstance = false );
   virtual ~CUIBase();

public:
   INSPIRE_CLIENT::IUIWnd* GetMainWnd();
   void Show();
   void Hide();

   template<class TControl>
   static TControl* GetControl( INSPIRE_CLIENT::IUIWnd* wnd, const wchar_t* id )
   {
      TControl* ctrl = dynamic_cast<TControl*>( wnd->FindControl( id ) );
#ifdef _DEBUG
      GetErrorCtrl( ctrl, wnd, id );
#endif
      return ctrl;
   }

   ///< 获取自己窗口中的子控件
   template<class TControl>
   TControl* GetControl( const wchar_t* id )
   {
      if ( _mainWnd == NULL )
      {
         return NULL;
      }
      return GetControl<TControl>( _mainWnd, id );
   }

   HWND GetWndHandler() const;
   
public:
   ///< 某些Windows消息的处理，由继承自CUIBase的子类处理
   virtual void OnSize();

protected:
   INSPIRE_CLIENT::IUIWnd* GetWindow( const _tchar* wndid );
   void AttachRootWindow( const _tchar* wndid );
   HWND GetParentHandler();
   INSPIRE_CLIENT::IUIWndManager* GetIUIWndManager();

   void SetWndStyle( DWORD dwStyle );
   /**
   * NOTICE:!! modal wnd must be a root wnd.
   * show modal wnd 
   */
   void ShowModalWnd();
   void HideModalWnd();

   virtual void OnShow()
   {
      //do nothing
   }

   virtual void OnHide()
   {
      //do nothing
   }

private:
   bool InitWndInstance( const _tchar* wndid );

private:
   INSPIRE_CLIENT::IUIWndManager* _IUIWndManger;
   INSPIRE_CLIENT::IUIWnd*        _mainWnd;
   HWND                  _hParentWnd;
   HWND                  _hWnd;
   bool                  _multiInstance;
   bool                  _modalWnd;
   DWORD                 _style;
   //////////////////////////////////////////////////////////////////////////
protected:
   ///获取逻辑主接口
   void GetLogicMain()
   {};
};
#endif