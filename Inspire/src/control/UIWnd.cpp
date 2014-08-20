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
#include "UIWnd.h"
#include "../include/.hWndEvent.h"
#include "../UIWndManager.h"

INSPIRE_CLIENT_BENGIN
CUIWnd::CUIWnd()
: _WndType( EWT_WND )
, _ShowFlag( false )
, _ThroughEvent( false )
, _MonseInOper( NULL )
, _MonseOutOper( NULL )
{

}

CUIWnd::CUIWnd( WndType wndtype )
: _WndType( wndtype )
{

}

CUIWnd::~CUIWnd()
{

}

const WndType CUIWnd::GetWndType() const
{
   return _WndType;
}

bool CUIWnd::DispatchToChild( CKeyboardEvent* kb_event )
{
   return false;
}

bool CUIWnd::DispatchToChild( CMouseEvent* ms_event )
{
   return false;
}

bool CUIWnd::ProcessEvent( CKeyboardEvent* kb_event )
{
   return false;
}

bool CUIWnd::ProcessEvent( CMouseEvent* ms_event )
{
   return false;
}

const _tchar* CUIWnd::GetID() const
{
   return _ID.c_str();
}

///< 子窗口相关
IUIWnd* CUIWnd::FindControl( const _tchar* id )
{
   return NULL;
}

int CUIWnd::GetChildCount() const
{
   return _ChildCount;
}

void CUIWnd::ReleaseChild( IUIWnd* child )
{

}

void CUIWnd::SetParent( IUIWnd* parent )
{
   _Parent = parent;
}

IUIWnd* CUIWnd::GetParent()
{
   return _Parent;
}

void CUIWnd::SetRect( const CRect& rect )
{
   _Rect.Set( rect.left, rect.top, rect.right, rect.bottom );
}

const CRect& CUIWnd::GetRect() const
{
   return _Rect;
}

int CUIWnd::GetWidth() const
{
   return _Rect.Width();
}

int CUIWnd::GetHeight() const
{
   return _Rect.Height();
}

const _tchar* CUIWnd::GetCaption() const
{
   return _Caption.c_str();
}

void CUIWnd::SetResourceData( const CUIResourceData* resData )
{
   _TileData->_ImageResource = resData->_ImageResource;
   _TileData->_ResourceID = resData->_ResourceID;
   if ( !_TileData->_ImageResource )
   {
      for ( int idx = 0; idx < UIT_COUNT; ++idx )
      {
         _TileData->tagTileResourceData[idx] = resData->tagTileResourceData[idx];
      }
   }
}

void CUIWnd::SetToolTips( const _tchar* tips )
{
   _Tooltips = tips;
}

void CUIWnd::SetPosition( int x, int y )
{
   _Position.x = x;
   _Position.y = y;
}

const CPoint& CUIWnd::GetPosition() const
{
   return _Position;
}

const CPoint& CUIWnd::GetAbsolutePosition() const
{
   return _Position;
}

void CUIWnd::CaptureMouse()
{

}

void CUIWnd::ReleaseMouse()
{

}

bool CUIWnd::IsFocus() const
{
   return _IsFocus;
}

void CUIWnd::GetFocus()
{
   _IsFocus = true;
}

void CUIWnd::LostFocus()
{
   _IsFocus = false;
}

bool CUIWnd::PointInWnd( const CPoint& pt ) const
{
   if ( ( pt.y < _Rect.right && pt.y > _Rect.left ) && ( pt.x < _Rect.top && pt.x > _Rect.bottom ) )
   {
      return true;
   }
   return false;
}

int   CUIWnd::GetZLevel() const
{
   return _Zlevel;
}

void CUIWnd::SetFontID( const _tchar* fontid )
{
   _FontID = fontid;
}

const _tchar* CUIWnd::GetFontID() const
{
   return _FontID.c_str();
}

void CUIWnd::SetResourceID( const _tchar* id )
{
   _ResourceID = id;
}

void CUIWnd::ShowWindow( bool show )
{
   _ShowFlag = show;
}

bool CUIWnd::IsShow() const
{
   return _ShowFlag;
}

void CUIWnd::Draw( void )
{

}

IOperation* CUIWnd::SetInitFunc( IOperation* oper )
{
   IOperation* oldoper = _InitOper;
   _InitOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetCloseFunc( IOperation* oper )
{
   IOperation* oldoper = _CloseOper;
   _CloseOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetEscapeFunc( IOperation* oper )
{
   IOperation* oldoper = _EscapeOper;
   _EscapeOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetMouseInFunc( IOperation* oper )
{
   IOperation* oldoper = _MonseInOper;
   _MonseInOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetMouseOutFunc( IOperation* oper )
{
   IOperation* oldoper = _MonseOutOper;
   _MonseOutOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetGetFocusFunc( IOperation* oper )
{
   IOperation* oldoper = _GetFocusOper;
   _GetFocusOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetLostFocusFunc( IOperation* oper )
{
   IOperation* oldoper = _LoseFocusOper;
   _LoseFocusOper = oper;
   return oldoper;
}

IOperation* CUIWnd::SetFocusChangeFunc( IOperation* oper )
{
   IOperation* oldoper = _FocusChangeOper;
   _FocusChangeOper = oper;
   return oldoper;
}

void CUIWnd::CloneFrom( CUIWnd* wnd )
{
   _WndType = wnd->_WndType;
   _ThroughEvent = wnd->_ThroughEvent;
   _FontID = wnd->_FontID;
   _ID = wnd->_ID;
   _Rect = wnd->_Rect;
   _Position = wnd->_Position;
   _Caption = wnd->_Caption;
   _Horizon = wnd->_Horizon;
   _Verticial = wnd->_Verticial;
   _Zlevel = wnd->_Zlevel;
   _ResourceID = wnd->_ResourceID;
   _ShowFlag = wnd->_ShowFlag;

   _TileMode = wnd->_TileMode;
   _TileData = wnd->_TileData;
   _TileSize = wnd->_TileSize;
   _CanChangeSize = wnd->_CanChangeSize;
//   _Moveable = wnd->_Moveable;

   if ( !_ChildWndContainer.empty() )
   {
      CUIWndManager* wnd_mng = CUIWndManager::Instance();
      if ( wnd_mng )
      {
         WndContainer::const_iterator cit = wnd->_ChildWndContainer.begin();
         for ( ; cit != wnd->_ChildWndContainer.end(); ++cit )
         {
            CUIWnd* new_wnd = wnd_mng->MakeClone( ( *cit ) );
            AddChild( new_wnd );
         }
      }
   }
}

void CUIWnd::ParseData( XML::IXMLNode* node )
{
   XML::IXMLNode* node_detail = node->FirstChild( "ID" );
   if ( node_detail )
   {
      const char* str_wndid = node_detail->GetValue();
      INSPIRE_CLIENT::CharConverter con( str_wndid );
      _ID = con.GetUnicode();
   }

   node_detail = node->FirstChild( "Position" );
   if ( node_detail )
   {
      const char* str_position = node_detail->GetValue();
      CPoint pt;
      sscanf_s( str_position, "%d %d", &pt.x, &pt.y );
      SetPosition( pt.x, pt.y );
   }

   node_detail = node->FirstChild( "Rect" );
   if ( node_detail )
   {
      const char* str_rect = node_detail->GetValue();
      CRect rect;
      sscanf_s( str_rect, "%d %d %d %d", &rect.left, &rect.top, &rect.right, &rect.bottom );
      SetRect( rect );
   }

   node_detail = node->FirstChild( "TileMode" );
   if ( node_detail )
   {
      const char* str_tile = node_detail->GetValue();
      int tilemode;
      sscanf_s( str_tile, "%d", &tilemode );
      _TileMode = ( TiledMode )tilemode;
   }

   node_detail = node->FirstChild( "Tile" );
   if ( node_detail )
   {
      const char* str_tile = node_detail->GetValue();
      Tile tile;
      sscanf_s( str_tile, "%d %d", &tile.x, &tile.y );
   }

   node_detail = node->FirstChild( "TileHeadTail" );
   if ( node_detail )
   {
      const char* str_tile = node_detail->GetValue();
      Tile tileheadtail;
      sscanf_s( str_tile, "%d %d", &tileheadtail.x, &tileheadtail.y );
      _TileHeadTail = tileheadtail;
   }

   node_detail = node->FirstChild( "TileSize" );
   if ( node_detail )
   {
      const char* str_tile = node_detail->GetValue();
      Tile tilesize;
      sscanf_s( str_tile, "%d %d", &tilesize.x, &tilesize.y );
      _TileSize = tilesize;
   }

   node_detail = node->FirstChild( "ZLevel" );
   if ( node_detail )
   {
      const char* str_zlevel = node_detail->GetValue();
      int zlevel = atoi( str_zlevel );
      _Zlevel = zlevel;
   }

   node_detail = node->FirstChild( "ResourceID" );
   if ( node_detail )
   {
      const char* str_resid = node_detail->GetValue();
      CharConverter con( str_resid );
      _ResourceID = con.GetUnicode();
   }
}

void CUIWnd::AddChild( CUIWnd* child )
{
   _ChildWndContainer.push_back( child );
   child->SetParent( this );
}

void CUIWnd::RemoveChild( CUIWnd* child )
{
   WndContainer::iterator it = _ChildWndContainer.begin();
   for ( ; it != _ChildWndContainer.end(); ++it )
   {
      if ( ( *it ) == child )
      {
         ( *it )->SetParent( NULL );
         _ChildWndContainer.erase( it );
         return;
      }
   }
}

void CUIWnd::RemoveChild( const _tchar* id )
{
   WndContainer::iterator it = _ChildWndContainer.begin();
   for ( ; it != _ChildWndContainer.end(); ++it )
   {
      if ( ( *it )->GetID() == id )
      {
         ( *it )->SetParent( NULL );
         _ChildWndContainer.erase( it );
         return;
      }
   }
}

void CUIWnd::Remove()
{

}

void CUIWnd::SetID( const _tchar* id )
{
   _ID = id;
}

void CUIWnd::SetZLevel( const int zlevel )
{
   _Zlevel = zlevel;
}

void CUIWnd::SetCaption( const _tchar* caption )
{
   _Caption = caption;
}

INSPIRE_CLIENT_END
