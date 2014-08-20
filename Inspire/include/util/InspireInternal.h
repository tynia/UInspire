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
#ifndef _INSPIRE_INTERNAL_H_
#define _INSPIRE_INTERNAL_H_

#include "Inspire.h"

INSPIRE_CLIENT_BENGIN

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

///< 有必要把Point类做成模板吗？
class INSPIRE_LIB_API CPoint
{
public:
   ///< 成员
   int x;
   int y;

   ///< 构造
   CPoint();
   CPoint( int xx, int yy );
   CPoint( const CPoint& pt );

   ///< 运算符
   const CPoint& operator= ( const CPoint& pt );
   const CPoint& operator+= ( const CPoint& pt );
   const CPoint operator- ( const CPoint& pt );
   const CPoint operator+ ( const CPoint& pt );

   void TranslateToXPoint( __in const HWND hWnd, __in const POINT& pt );
   void TranslateToWindow( __in const HWND hWnd, __inout POINT& pt );
};
///< Tile 等也用的是同样的数据结构，不愿写了，就typedef了
typedef CPoint Tile;

class INSPIRE_LIB_API CRect
{
public:
   int left;
   int top;
   int right;
   int bottom;

   CRect();
   CRect( int l, int t, int r, int b );
   CRect( const CRect& rect );

   void Set( int l, int t, int r, int b );

   void Translate( int x, int y );

   int Width() const;

   int Height() const;

   bool PointInRect( const CPoint& point ) const;

   bool PointInRect( int x, int y ) const;

   /*
    *@brief Window的Rect转换成把自己的rect
   */
   void TranslateToXRect( __in HWND hWnd, __in const RECT& rect_in );

   /*
    *@brief 把自己的rect转换成Window的Rect （注意，不是Screen的）
   */
   void TranslateXRectToWindow( __in HWND hWnd, __out RECT& rect_out );
};

///< 扩展的内存配分和释放函数
typedef void* ( alloc )( std::size_t size );
typedef void  ( free )( void* ptr );

INSPIRE_CLIENT_END
#endif