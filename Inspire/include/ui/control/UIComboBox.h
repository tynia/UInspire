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
#ifndef _INSPIRE_UI_COMBOBOX_H_
#define _INSPIRE_UI_COMBOBOX_H_

#include "IUIComboBox.h"
#include "UIWnd.h"

namespace inspire {
class CUIWnd;

enum CMBState
{
   CMBS_NORMAL,
   CMBS_EXPAND,
};

class CUIComboBox : public CUIWnd, public IUIComboBox
{
public:
   CUIComboBox();
   virtual ~CUIComboBox();

   virtual void Draw();

   virtual void AddItem( ItemData& item, int index );

   virtual void RemoveItem( int index );

   virtual void Clear();

   virtual void SetCurrentItem( int index );

   virtual const int GetCurrentItem() const;

   virtual void SetEditEnable( bool enable );

   virtual void SetEditText( const _tchar* info );

   ///< 窗口回调函数
   virtual IInvoker*   SetPressFunc( IInvoker* oper );
   virtual IInvoker* SetItemChangeFunc( IInvoker* oper );
   virtual IInvoker* SetTextChangeFunc( IInvoker* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( inspire::IXMLNode* node );

private:
   const int GetCurrentItemID() const;
   int GetItemCount() const;
   const ItemData& GetCurrentItemData() const;
   
protected:
   typedef std::vector<ItemData> ItemDataList;
   ItemDataList   _ItemDataList;
   
   int            _CurrentItem;
   bool         _Editable;

   IInvoker*      _PressDownOper;
   IInvoker*      _ItemChangeOper;
   IInvoker*      _TextChangeOper;
};

}
#endif