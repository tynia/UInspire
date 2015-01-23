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
#include "UIItem.h"
#include "UIWndManager.h"
#include "UIImage.h"

namespace inspire {

CUIItem::CUIItem() : CUIWnd( EWT_ITEM )
, _PressDownOper( NULL )
, _HeadPressDownOper( NULL )
, _TailPressDownOper( NULL )
, _RectHead( 0, 0, 0, 0 )
, _RectTail( 0, 0, 0, 0 )
, _HeadResourceID( L"" )
, _TailResourceID( L"" )
{

}

CUIItem::~CUIItem()
{
}

void CUIItem::Draw()
{

}

void CUIItem::AddChildItem( int idx, const ItemData& childItem )
{
   ItemDataList::iterator it = _ChildItemList.begin();
   for ( ; it != _ChildItemList.end(); ++it )
   {
      if ( it->first == idx )
      {
         //error...
      }
   }

   _ChildItemList.insert( make_pair( idx, childItem ) );
}

void CUIItem::RemoveChildItem( int index )
{
   ItemDataList::iterator it = _ChildItemList.begin();
   for ( ; it != _ChildItemList.end(); ++it )
   {
      if ( it->first == index )
      {
         _ChildItemList.erase( it );
         return;
      }
   }

   //error..cannot find..
}

void CUIItem::SetItemText( const _tchar* text )
{
   SetCaption( text );
}

const _tchar* CUIItem::GetItemText() const
{
   return GetCaption();
}

void CUIItem::SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical )
{
   _Horizon = horizon;
   _Verticial = vertical;
}

void CUIItem::SetHeadImageResourceID( const _tchar* id )
{
   _HeadResourceID = id;
}

void CUIItem::SetTailImageResourceID( const _tchar* id )
{
   _TailResourceID = id;
}

IInvoker* CUIItem::SetPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

IInvoker* CUIItem::SetHeadPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _HeadPressDownOper;
   _HeadPressDownOper = oper;
   return oldoper;
}

IInvoker* CUIItem::SetTailPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _TailPressDownOper;
   _TailPressDownOper = oper;
   return oldoper;
}

void CUIItem::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIItem* item = dynamic_cast<CUIItem*>( wnd );
   //todo:
}

void CUIItem::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo
}

}
