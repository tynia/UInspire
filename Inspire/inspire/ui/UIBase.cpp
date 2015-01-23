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
#include "UIBase.h"
#include "IUIWnd.h"
#include "Inspire.h"

CUIBase::CUIBase( const _tchar* wndID, HWND hParentWnd , bool multiInstance )
: _hWnd( NULL )
, _hParentWnd( hParentWnd )
, _multiInstance( multiInstance )
, _style( WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN )
{
   _mainWnd = GetWindow( wndID );
   if ( _mainWnd == NULL )
   {
      LogError( "Cannot find UIWnd: %s", inspire::CharConverter( WndID ).GetUTF8() );
      __asm int 3;
      return;
   }

   if ( !InitWndInstance( WndID ) )
   {
      inspire::CharConverter con_id( WndID );
      LogError( "RegisterWndClass: %s fail...", con_id.GetUTF8() );
   }

   AttachRootWindow( WndID );
}

CUIBase::~CUIBase()
{
   _hParentWnd = NULL;
   if ( NULL != _hWnd )
   {
      _wndMgr->UnAttachWindow( this, _multiInstance );
      ::UnregisterClass( _mainWnd->GetID(), _wndMgr->GetAppInstance() );
      ::DestroyWindow( _hWnd );
      _hWnd = NULL;
   }
}

inspire::IUIWnd* CUIBase::GetMainWnd()
{
   return _mainWnd;
}

inspire::IUIWnd* CUIBase::GetWindow( const _tchar* wndid )
{
   inspire::IUIWnd* wnd = _wndMgr->GetWindow( wndid, _multiInstance );
   return wnd;
}

void CUIBase::AttachRootWindow( const _tchar* wndid )
{
   _wndMgr->AttachWindow( this, wndid, _multiInstance );
}

HWND CUIBase::GetWndHandler() const
{
   return _hWnd;
}

HWND CUIBase::GetParentHandler()
{
   return _hParentWnd;
}

inspire::IUIWndManager* CUIBase::GetIUIWndManager()
{
   return _wndMgr;;
}

void CUIBase::SetWndStyle( DWORD dwStyle )
{
   _style = dwStyle;
}

void CUIBase::ShowModalWnd()
{
   _modalWnd = true;
   _wndMgr->ShowModalWnd( _hWnd, _hParentWnd );
}

void CUIBase::HideModalWnd()
{
   _wndMgr->HideModalWnd( _hParentWnd );
   _modalWnd = false;
}

void CUIBase::Show()
{
   if ( NULL != _hWnd )
   {
      if ( NULL != _hParentWnd )
      {
         //::SetWindowPos( _hWnd, HWND_TOPMOST, )
      }
      ::ShowWindow( _hWnd, SW_SHOW );
   }

   if ( GetMainWnd() != NULL )
   {
      GetMainWnd()->ShowWindow( true );
   }
   OnShow();
}

void CUIBase::Hide()
{
   if ( NULL != _hWnd )
   {
      ::ShowWindow( _hWnd, SW_HIDE );
   }
   else
   {
      if ( GetMainWnd() != NULL )
      {
         if ( !GetMainWnd()->IsShow() )
         {
            return;
         }
         GetMainWnd()->ShowWindow( false );
      }
   }
   OnHide();
}

bool CUIBase::InitWndInstance( const _tchar* wndid )
{
   return _wndMgr->InitWndInstance( _mainWnd, _hWnd, _hParentWnd, _style );
}

void CUIBase::OnSize()
{

}