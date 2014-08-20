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

CUIBase::CUIBase( const _tchar* WndID, HWND hParentWnd , bool multiInstance )
: _hWnd( NULL )
, _hParentWnd( hParentWnd )
, _multiInstance( multiInstance )
, _style( WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN )
{
   _mainWnd = GetWindow( WndID );
   if ( _mainWnd == NULL )
   {
      LogError( "Cannot find UIWnd: %s", INSPIRE_INTERNAL::CharConverter( WndID ).GetUTF8() );
      __asm int 3;
      return;
   }

   if ( !InitWndInstance( WndID ) )
   {
      INSPIRE_INTERNAL::CharConverter con_id( WndID );
      LogError( "RegisterWndClass: %s fail...", con_id.GetUTF8() );
   }

   AttachRootWindow( WndID );
}

CUIBase::~CUIBase()
{
   _hParentWnd = NULL;
   if ( NULL != _hWnd )
   {
      _IUIWndManger->UnAttachWindow( this, _multiInstance );
      ::UnregisterClass( _mainWnd->GetID(), _IUIWndManger->GetAppInstance() );
      ::DestroyWindow( _hWnd );
      _hWnd = NULL;
   }
}

INSPIRE_CLIENT::IUIWnd* CUIBase::GetMainWnd()
{
   return _mainWnd;
}

INSPIRE_CLIENT::IUIWnd* CUIBase::GetWindow( const _tchar* wndid )
{
   INSPIRE_CLIENT::IUIWnd* wnd = _IUIWndManger->GetWindow( wndid, _multiInstance );
   return wnd;
}

void CUIBase::AttachRootWindow( const _tchar* wndid )
{
   _IUIWndManger->AttachWindow( this, wndid, _multiInstance );
}

HWND CUIBase::GetWndHandler() const
{
   return _hWnd;
}

HWND CUIBase::GetParentHandler()
{
   return _hParentWnd;
}

INSPIRE_CLIENT::IUIWndManager* CUIBase::GetIUIWndManager()
{
   return _IUIWndManger;;
}

void CUIBase::SetWndStyle( DWORD dwStyle )
{
   _style = dwStyle;
}

void CUIBase::ShowModalWnd()
{
   _modalWnd = true;
   _IUIWndManger->ShowModalWnd( _hWnd, _hParentWnd );
}

void CUIBase::HideModalWnd()
{
   _modalWnd = false;
   _IUIWndManger->HideModalWnd( _hParentWnd );
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
   return _IUIWndManger->InitWndInstance( _mainWnd, _hWnd, _hParentWnd, _style );
}

void CUIBase::OnSize()
{

}