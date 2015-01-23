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
#include "UIWndManager.h"
#include "UIWnd.h"
#include "UIWndFactory.h"
#include "UIRenderFactory.h"
#include "UIBase.h"
#include "IUIRender.h"
#include <XMLDocument.h>

namespace inspire {
CUIWndManager* CUIWndManager::static_Instance = NULL;
CUIWndManager::CUIWndManager()
{
   static_Instance = this;
   _Factory = new CUIWndFactory();
   bool bsuc = CUIRenderFactory::Instance()->QueryInterface( RUID_GDI, ( void** )&_UIRender );
   if ( !bsuc )
   {
      LogError( "QueryInterface( RUID_GDI, ( void** )&_UIRender ) cannot find render instance" );
   }
}

CUIWndManager::~CUIWndManager()
{
   if ( _Factory )
   {
      delete _Factory;
      _Factory = NULL;
   }

   if ( _UIRender )
   {
      CUIRenderFactory::Instance()->Release( RUID_GDI );
   }
}

void CUIWndManager::PushToWndContainer( CUIWnd* wnd )
{
   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      if ( wnd->GetZLevel() == level_idx )
      {
         CUIBase* uibase = NULL;
         _UIWndContainer[level_idx].insert( std::make_pair( wnd, uibase ) );
         return;
      }
   }
}

void CUIWndManager::PopFromWndContainer( CUIBase* uibase )
{
   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      WndContainer::iterator iter = _UIWndContainer[level_idx].begin();
      WndContainer::iterator it_end = _UIWndContainer[level_idx].end();
      for ( ; iter != it_end; ++iter )
      {
         if ( iter->second == uibase )
         {
            iter->second = NULL;
            _UIWndContainer[level_idx].erase( iter );
            return;
         }
      }
   }
}

void CUIWndManager::PushToMultiInstanceWndContainer( CUIWnd* wnd )
{
   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      if ( wnd->GetZLevel() == level_idx )
      {
         CUIBase* uibase = NULL;
         _UIMultiInstanceWndContainer[level_idx].insert( std::make_pair( wnd, uibase ) );
         return;
      }
   }
}

void CUIWndManager::PopFromMultiInstanceWndContainer( CUIBase* uibase )
{
   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      MultiInstanceWndContainer::iterator iter = _UIMultiInstanceWndContainer[level_idx].begin();
      MultiInstanceWndContainer::iterator it_end = _UIMultiInstanceWndContainer[level_idx].end();
      for ( ; iter != it_end; ++iter )
      {
         if ( iter->second == uibase )
         {
            iter->second = NULL;
            DeallocWndEntity( iter->first );
            _UIMultiInstanceWndContainer[level_idx].erase( iter );
            return;
         }
      }
   }
}

void CUIWndManager::AttachWindow( CUIBase* const uibase, const _tchar* wndid, bool multiInstance )
{
   LIB_ASSERT( uibase );

   if ( multiInstance )
   {
      for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
      {
         MultiInstanceWndContainer::iterator iter = _UIMultiInstanceWndContainer[level_idx].begin();
         MultiInstanceWndContainer::iterator it_end = _UIMultiInstanceWndContainer[level_idx].end();
         for ( ; iter != it_end; ++iter )
         {
            if ( iter->second == NULL )
            {
               CUIWnd* wnd = iter->first;
               if ( wnd->GetID() == wndid )
               {
                  CUIBase*& ref_uibase = iter->second;
                  CloneMultiInstanceWnd( wnd );
                  ref_uibase = uibase;
                  return;
               }
            }
         }
      }
   }

   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      WndContainer::iterator iter = _UIWndContainer[level_idx].begin();
      WndContainer::iterator it_end = _UIWndContainer[level_idx].end();
      for ( ; iter != it_end; ++iter )
      {
         IUIWnd* wnd = iter->first;
         if ( wnd->GetID() == wndid )
         {
            iter->second = uibase;
         }
      }
   }

   // log error...can not find window wndid
}

void CUIWndManager::UnAttachWindow( CUIBase* const uibase, bool multiInstance )
{
   if ( multiInstance )
   {
      PopFromMultiInstanceWndContainer( uibase );
      return;
   }

   PopFromWndContainer( uibase );
}

IUIWnd* CUIWndManager::GetWindow( const _tchar* wndid, bool multiInstance )
{
   if ( multiInstance )
   {
      for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
      {
         MultiInstanceWndContainer::iterator iter = _UIMultiInstanceWndContainer[level_idx].begin();
         MultiInstanceWndContainer::iterator it_end = _UIMultiInstanceWndContainer[level_idx].end();
         for ( ; iter != it_end; ++iter )
         {
            IUIWnd* wnd = iter->first;
            if ( iter->second == NULL && wnd->GetID() == wndid )
            {
               return wnd;
            }
         }
      }
   }

   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      WndContainer::iterator iter = _UIWndContainer[level_idx].begin();
      WndContainer::iterator it_end = _UIWndContainer[level_idx].end();
      for ( ; iter != it_end; ++iter )
      {
         IUIWnd* wnd = iter->first;
         if ( wnd->GetID() == wndid )
         {
            return wnd;
         }
      }
   }

   return NULL;
}

CUIBase* CUIWndManager::GetUIBase( const HWND& hWnd )
{
   CUIBase* uibase = NULL;

   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      MultiInstanceWndContainer::iterator iter = _UIMultiInstanceWndContainer[level_idx].begin();
      MultiInstanceWndContainer::iterator it_end = _UIMultiInstanceWndContainer[level_idx].end();
      for ( ; iter != it_end; ++iter )
      {
         if ( !( iter->second->GetWndHandler() == hWnd ) )
         {
            uibase = iter->second;
            return uibase;
         }
      }
   }

   for ( int level_idx = 0; level_idx < ZlevelCount; ++level_idx )
   {
      WndContainer::iterator iter = _UIWndContainer[level_idx].begin();
      WndContainer::iterator it_end = _UIWndContainer[level_idx].end();
      for ( ; iter != it_end; ++iter )
      {
         uibase = iter->second;
         return uibase;
      }
   }

   return NULL;
}

IUIWnd* CUIWndManager::AllocWndEntity( WndType wt )
{
   return _Factory->AllocWndEntity( wt );
}

void CUIWndManager::DeallocWndEntity( IUIWnd* wnd )
{
   _Factory->DeallocWndEntity( wnd );
}

IUIRender* CUIWndManager::GetIUIRender()
{
   return _UIRender;
}

void CUIWndManager::SetAppInstance( HINSTANCE& hInstance )
{
   _hInstance = hInstance;
}

const HINSTANCE CUIWndManager::GetAppInstance() const
{
   return _hInstance;
}

bool CUIWndManager::InitWndInstance( IUIWnd* initWnd, HWND& hInitWnd, const HWND& hPareant, DWORD style )
{
   if ( !RegisterWndClass( initWnd ) )
   {
      LogError( "RegisterWndClass %s fail", inspire::CharConverter( initWnd->GetID() ).GetUTF8() );
      return false;
   }

   inspire::CRect rect = initWnd->GetRect();
   int cx = 0;
   int cy = 0;
   if ( hPareant )
   {
      inspire::IUIWnd* wnd = GetUIBase( hPareant )->GetMainWnd();
      cx = wnd->GetRect().Width();
      cy = wnd->GetRect().Height();
   }
   else
   {
      cx = ::GetSystemMetrics( SM_CXFULLSCREEN );
      cy = ::GetSystemMetrics( SM_CYFULLSCREEN );
   }

   int posx = ( cx - rect.Width() ) / 2;
   int posy = ( cy - rect.Height() ) / 2;
   hInitWnd = ::CreateWindow( initWnd->GetID(),
      NULL,
      style,/*WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,*/
      posx,
      posy,
      rect.Width(),
      rect.Height(),
      hPareant,
      NULL,
      _hInstance,
      NULL );

   if ( hInitWnd )
   {
      __asm int 3;
      return false;
   }

   ::ShowWindow( hInitWnd, SW_HIDE );
   ::UpdateWindow( hInitWnd );

   RunMessageLoop();
   return true;
}

void CUIWndManager::ShowModalWnd( const HWND& hWnd, const HWND& hParent )
{
   if ( hParent )
   {
      ::EnableWindow( hParent, FALSE );
   }
   ::SetFocus( hWnd );
   ::SetActiveWindow( hWnd );
}

void CUIWndManager::HideModalWnd( const HWND& hParent )
{
   if ( hParent )
   {
      ::EnableWindow( hParent, TRUE );
      ::SetFocus( hParent );
      ::SetActiveWindow( hParent );
   }
}

CUIWnd* CUIWndManager::MakeClone( CUIWnd* wnd )
{
   CUIWnd* new_wnd = _Factory->AllocWndEntity( wnd->GetWndType() );
   new_wnd->CloneFrom( wnd );

   return new_wnd;
}

void CUIWndManager::CloneMultiInstanceWnd( CUIWnd* wnd )
{
   CUIWnd* new_wnd = MakeClone( wnd );

   PushToMultiInstanceWndContainer( new_wnd );
}

void CUIWndManager::ParseLayout()
{
   XML::IXMLDocument* doc = new XML::XMLDocument();
   bool ret = doc->load( "index.xml" );
   if ( !ret )
   {
      //can not find ui layout index file.
      delete doc;
      doc = NULL;
      return;
   }

   XML::IXMLNode* node = doc->firstChild( "Layout" );
   if ( node )
   {
      XML::IXMLNode* child = node->firstChild( "index" );
      while ( child )
      {
         const char* layout = child->getValue();
         if ( layout )
         {
            ParseLayoutFile( layout );
         }
         child = child->nextSibling( "index" );
      }
   }

   delete doc;
   doc = NULL;
}

void CUIWndManager::ParseLayoutFile( const char* layout_file )
{
   XML::IXMLDocument* uilayout = new XML::XMLDocument();
   uilayout->load( layout_file );

   CUIWnd* wnd = NULL;
   XML::IXMLNode* windows = uilayout->firstChild( "Windows" );
   if ( windows )
   {
      XML::IXMLNode* wndnode = windows->firstChild( "Window" );
      while ( wndnode )
      {
         const char* str_class_index = wndnode->getAttributeValue( "Class" );
         if ( str_class_index )
         {
            WndType wt = ( WndType )atoi( str_class_index );
#ifndef _DEBUG
            if ( GetClassNameFromWndClass( wt ) != 0 )
            {
               //error...root wnd must be Window!
               __asm int 3;
            }
#endif // !_DEBUG
            wnd = _Factory->AllocWndEntity( wt );
            wnd->ParseData( wndnode );
            ParseControl( wnd, wndnode );
            wnd->SetParent( NULL );

            const char* multiInstance = wndnode->getAttributeValue( "MultiInstance" );
            int val = atoi( multiInstance );
            if ( val != 0 )
            {
               PushToMultiInstanceWndContainer( wnd );
            }
            else
            {
               PushToWndContainer( wnd );
            }
         }
         wndnode = wndnode->nextSibling( "Window" );
      }
   }
}

void CUIWndManager::ParseControl( CUIWnd* wnd, XML::IXMLNode* node )
{
   XML::IXMLNode* controls = node->firstChild( "Controls" );
   if ( controls )
   {
      XML::IXMLNode* ctrl_node = controls->firstChild( "Control" );
      while ( ctrl_node )
      {
         const char* ctrl_class = ctrl_node->getAttributeValue( "Class" );
         if ( ctrl_class )
         {
            WndType wt = ( WndType )atoi( ctrl_class );
            CUIWnd* ctrl = _Factory->AllocWndEntity( wt );
            if ( ctrl )
            {
               ctrl->ParseData( ctrl_node );
               ParseControl( ctrl, ctrl_node );
               wnd->AddChild( ctrl );
               ctrl->SetParent( wnd );
            }
         }
         ctrl_node = controls->nextSibling( "Control" );
      }
   }
}

CUIWndManager* CUIWndManager::Instance()
{
   static CUIWndManager instance;
   return &instance;
}

void CUIWndManager::Release()
{
   delete this;
}

ATOM CUIWndManager::RegisterWndClass( IUIWnd* wnd )
{
   WNDCLASSEX wc = { 0 };
   wc.cbSize = sizeof( WNDCLASSEX );
   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = CUIWndManager::__WindowProcess;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = _hInstance;
   wc.hIcon = NULL;
   wc.hCursor = NULL;
   wc.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
   wc.lpszMenuName = NULL;
   wc.lpszClassName = wnd->GetID();
   wc.hIconSm = NULL;

   return ::RegisterClassEx( &wc );
}

void CUIWndManager::RunMessageLoop()
{
   MSG msg = { 0 };
   while ( true )
   {
      if ( ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
      {
         if ( msg.message == WM_QUIT )
         {
            break;
         }

         if ( !PreTranslateMsg( &msg ) )
         {
            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );
         }
      }
      else
      {
         ::WaitMessage();
      }
   }
}

bool CUIWndManager::PreTranslateMsg( PMSG pMsg )
{
   bool hHandled = false;
   if ( pMsg->message == WM_KEYDOWN )
   {
      switch ( pMsg->wParam )
      {
      case VK_ESCAPE :
         {
            hHandled = true;
         }
         break;
      default:
         break;
      }
   }

   return hHandled;
}

LRESULT CALLBACK CUIWndManager::__WindowProcess( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
   switch ( uMsg )
   {
   case WM_CREATE :
      {
         CUIBase* uibase = static_Instance->GetUIBase( hWnd );
         ::SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>( uibase ) );
      }
      break;
   case WM_SIZE :
      {
         CUIBase* uibase = reinterpret_cast<CUIBase*>( ::GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
         if ( uibase != NULL )
         {
            uibase->OnSize();
         }
      }
      break;
   case WM_NCHITTEST :
      {
         static_Instance->OnNCHitTest( hWnd, wParam, lParam );
      }
      break;
   case WM_MOUSEMOVE :
      {

      }
      break;
   case WM_LBUTTONUP :
      {

      }
      break;
   case WM_LBUTTONDBLCLK :
      {

      }
      break;
   case WM_RBUTTONUP :
      {

      }
      break;
   case WM_PAINT :
      {
         inspire::IUIWnd* wnd = static_Instance->GetUIBase( hWnd )->GetMainWnd();
         LIB_ASSERT( wnd );
         static_Instance->Draw( hWnd, wnd );
#ifdef _DEBUG
         //todo: 打印debug信息，坐标窗口 ID等
#endif
      }
      break;
   default:
      return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
   }
   return S_OK;
}

void CUIWndManager::Draw( const HWND& hWnd, inspire::IUIWnd* wnd )
{
   SYSTEM_ASSERT( _UIRender );

   _UIRender->BeginDraw( hWnd );
   wnd->Draw();
   _UIRender->EndDraw();
}

LRESULT CUIWndManager::OnNCHitTest( HWND hWnd, WPARAM wParam, LPARAM lParam )
{
   POINT pt_win;
   pt_win.x = GET_X_LPARAM( lParam );
   pt_win.y = GET_Y_LPARAM( lParam );

   CPoint pt;
   pt.TranslateToXPoint( hWnd, pt_win );

   return HTCLIENT;
}

}
