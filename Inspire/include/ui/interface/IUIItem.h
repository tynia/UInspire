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
   @brief ����ǰ���ͼƬ�Ĵ�����Դid
   @param ��Դid
   */
   virtual void SetHeadImageResourceID( const _tchar* id ) = 0;
   /**
   @brief ���ú����ͼƬ�Ĵ�����Դid������Menu��ʱ����չ�������ʾ����ͼ�꣩
   @param ��Դid
   */
   virtual void SetTailImageResourceID( const _tchar* id ) = 0;

   virtual IOperation* SetHeadPressFunc( IOperation* oper ) = 0;

   virtual IOperation* SetTailPressFunc( IOperation* oper ) = 0;

   virtual IOperation* SetPressFunc( IOperation* oper ) = 0;
};
}
#endif