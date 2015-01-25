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
#ifndef _INSPIRE_WND_H_
#define _INSPIRE_WND_H_

#include "platform.h"

namespace inspire {

enum WndType
{
   EWT_WND = 0,
   EWT_BUTTON,
   EWT_CHECKBOX,
   EWT_EDITBOX,
   EWT_IMAGE,
   EWT_STATICTEXT,
   EWT_COMBOBOX,
   EWT_PROGRESSBAR,
   EWT_RICHEDITBOX,
   EWT_ITEM,
   EWT_LIST,
   EWT_MENU,
   EWT_SCROLLBAR,
   EWT_SLIDER,
   EWT_TREE,
   EWT_CUSTOMWND,
};

struct tagAlign
{
   int x;
   int y;
};
typedef tagAlign CUIAlign;

enum UITile
{
   UIT_TOP_LEFT = 0,
   UIT_TOP_CENTER,
   UIT_TOP_RIGHT,
   UIT_CENTER_LEFT,
   UIT_CENTER_CENTER,
   UIT_CENTER_RIGHT,
   UIT_BOTTOM_LEFT,
   UIT_BOTTOM_CENTER,
   UIT_BOTTOM_RIGHT,

   UIT_COUNT,
};

typedef struct tagResourceData
{
   bool _ImageResource;
   std::string _ResourceID;
   std::string tagTileResourceData[UIT_COUNT];
} CUIResourceData;

enum TiledMode
{
   ETM_NULL = 0,
   ETM_VERTICAL_HEAD_TAIL,  ///< 竖直三段拼接
   ETM_HIRIZON_HEAD_TAIL,   ///< 水平三段拼接
};

inline const _tchar* GetClassNameFromWndClass( WndType wc )
{
   switch ( wc )
   {
   case EWT_WND :
      return L"Window";
   case EWT_BUTTON :
      return L"Button";
   case EWT_CHECKBOX :
      return L"CheckBox";
   case EWT_EDITBOX :
      return L"EditBox";
   case EWT_IMAGE :
      return L"Image";
   case EWT_STATICTEXT :
      return L"StaticText";
   case EWT_COMBOBOX :
      return L"ComboBox";
   case EWT_PROGRESSBAR :
      return L"ProgressBar";
   case EWT_RICHEDITBOX :
      return L"RichEditBox";
   case EWT_ITEM :
      return L"Item";
   case EWT_LIST :
      return L"List";
   case EWT_MENU :
      return L"Menu";
   case EWT_SCROLLBAR :
      return L"ScrollBar";
   case EWT_SLIDER :
      return L"Slider";
   case EWT_CUSTOMWND :
      return L"CustomWnd";
   default:
      return L"Error";
   }
}

}
#endif