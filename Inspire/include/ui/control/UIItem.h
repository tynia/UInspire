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
#ifndef _INSPIRE_UI_ITEM_H_
#define _INSPIRE_UI_ITEM_H_

#include "IUIItem.h"
#include "UIWnd.h"

namespace inspire {

class CUIWnd;

class CUIItem : public CUIWnd, public IUIItem
{
public:
   CUIItem();
   virtual ~CUIItem();

   virtual void Draw();
   virtual void AddChildItem( int idx, const ItemData& childItem );
   virtual void RemoveChildItem( int index );
   virtual void SetItemText( const _tchar* text );
   virtual const _tchar* GetItemText() const;
   virtual void SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical );
   virtual void SetHeadImageResourceID( const _tchar* id );
   virtual void SetTailImageResourceID( const _tchar* id );
   virtual IInvoker* SetPressFunc( IInvoker* oper );
   virtual IInvoker* SetHeadPressFunc( IInvoker* oper );
   virtual IInvoker* SetTailPressFunc( IInvoker* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( inspire::IXMLNode* node );

protected:
   IInvoker*      _PressDownOper;
   IInvoker*      _HeadPressDownOper;
   IInvoker*      _TailPressDownOper;
   CRect         _RectHead;
   CRect         _RectTail;
   _tstring      _HeadResourceID;
   _tstring      _TailResourceID;

   ItemDataList   _ChildItemList;
};

}
#endif