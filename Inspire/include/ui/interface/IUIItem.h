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
#ifndef _INSPIRE_IUI_ITEM_H_
#define _INSPIRE_IUI_ITEM_H_

#include "IUIWnd.h"

namespace inspire {
class IUIImage;

class INSPIRE_EXPORT_API IUIItem : virtual public IUIWnd
{
public:
   virtual ~IUIItem() {};

   virtual void AddChildItem( int idx, const ItemData& childItem ) = 0;

   virtual void RemoveChildItem( int index ) = 0;

   virtual void SetItemText( const _tchar* text ) = 0;

   virtual const _tchar* GetItemText() const = 0;

   virtual void SetTextAlign( TEXT_HORIZON_ALIGN horizon, TEXT_VERTICAL_ALIGN vertical ) = 0;
   /**
   @brief 设置前面的图片的窗口资源id
   @param 资源id
   */
   virtual void SetHeadImageResourceID( const _tchar* id ) = 0;
   /**
   @brief 设置后面的图片的窗口资源id（用于Menu的时候，有展开项的提示三角图标）
   @param 资源id
   */
   virtual void SetTailImageResourceID( const _tchar* id ) = 0;

   virtual IInvoker* SetHeadPressFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetTailPressFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetPressFunc( IInvoker* oper ) = 0;
};
}
#endif