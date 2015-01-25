/*******************************************************************************
   Copyright (C) 2015 tynia.

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
#include "UIComboBox.h"

namespace inspire {
CUIComboBox::CUIComboBox() : CUIWnd( EWT_COMBOBOX )
, _Editable( false )
, _CurrentItem( 0 )
, _PressDownOper( NULL )
, _ItemChangeOper( NULL )
, _TextChangeOper( NULL )
{

}

CUIComboBox::~CUIComboBox()
{

}

void CUIComboBox::Draw()
{

}

void CUIComboBox::AddItem( ItemData& item, int index )
{
   ItemDataList::iterator it = _ItemDataList.begin();
   for ( ; it != _ItemDataList.end(); ++it )
   {
      if ( it->index == item.index )
      {
         //log error...
         return;
      }
   }

   _ItemDataList.push_back( item );
}

void CUIComboBox::RemoveItem( int index )
{
   ItemDataList::iterator it = _ItemDataList.begin();
   for ( ; it != _ItemDataList.end(); ++it )
   {
      if ( it->index == index )
      {
         _ItemDataList.erase( it );
         return;
      }
   }

   // log error
}

void CUIComboBox::Clear()
{
   _ItemDataList.clear();
}

void CUIComboBox::SetCurrentItem( int index )
{
   _CurrentItem = index;
}

const int CUIComboBox::GetCurrentItem() const
{
   return _CurrentItem;
}

void CUIComboBox::SetEditEnable( bool enable )
{
   _Editable = enable;
}

void CUIComboBox::SetEditText( const _tchar* text )
{
   SetCaption( text );
}

IInvoker* CUIComboBox::SetPressFunc( IInvoker* oper )
{
   IInvoker* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

IInvoker* CUIComboBox::SetItemChangeFunc( IInvoker* oper )
{
   IInvoker* oldoper = _ItemChangeOper;
   _ItemChangeOper = oper;
   return oldoper;
}

IInvoker* CUIComboBox::SetTextChangeFunc( IInvoker* oper )
{
   IInvoker* oldoper = _TextChangeOper;
   _TextChangeOper = oper;
   return oldoper;
}

const int CUIComboBox::GetCurrentItemID() const
{
   return _ItemDataList[_CurrentItem].index;
}

int CUIComboBox::GetItemCount() const
{
   return _ItemDataList.size();
}

const ItemData& CUIComboBox::GetCurrentItemData() const
{
   return _ItemDataList[_CurrentItem];
}

void CUIComboBox::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUIComboBox* combo = dynamic_cast<CUIComboBox*>( wnd );
   _Editable = combo->_Editable;
}

void CUIComboBox::ParseData( inspire::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   // todo:
}

}
