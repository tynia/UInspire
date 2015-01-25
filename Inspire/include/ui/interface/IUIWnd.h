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
#ifndef _INSPIRE_IUI_WND_H_
#define _INSPIRE_IUI_WND_H_

#include "platform.h"
#include "CharConverter.h"
#include "Inspire.h"
#include "wnd.h"

namespace inspire {
class IInvoker;

struct ItemData
{
   int index;
   _tstring strItem;
   _tstring imgItem;
   IInvoker* oper;
};

typedef std::map<int, ItemData> ItemDataList;

enum TEXT_HORIZON_ALIGN
{
   THA_LEFT,      ///< 左对齐
   THA_CENTER,    ///< 中对齐
   THA_RIGHT,     ///< 右对齐
};

enum TEXT_VERTICAL_ALIGN
{
   TVA_TOP,      ///< 顶对齐
   TVA_CENTER,   ///< 中对齐
   TVA_BOTTOM,   ///< 底对齐
};

enum UIWndZLevel
{
   UIWZ_LEVEL_0 = 0,
   UIWZ_LEVEL_1,
   UIWZ_LEVEL_2,
   UIWZ_LEVEL_3,
   UIWZ_LEVEL_4,
   UIWZ_LEVEL_5,
   UIWZ_LEVEL_6,
   UIWZ_LEVEL_7,

   UIWZ_LEVEL_TOPMOST = UIWZ_LEVEL_7,
   UIWZ_LEVEL_BOTTOM  = UIWZ_LEVEL_0,
   UIWZ_LEVEL_NORMAL  = UIWZ_LEVEL_1,
   UIWZ_LEVEL_DEFAULT = UIWZ_LEVEL_0,
};

class INSPIRE_EXPORT_API IUIWnd
{
public:
   virtual ~IUIWnd() {};

   virtual const WndType GetWndType() const = 0;

   virtual const _tchar* GetID() const = 0;

   ///< 子窗口相关
   virtual IUIWnd* FindControl( const _tchar* id ) = 0;

   virtual int GetChildCount() const = 0;

   virtual void ReleaseChild( IUIWnd* child ) = 0;

   virtual void SetParent( IUIWnd* parent ) = 0;

   virtual IUIWnd* GetParent() = 0;

   virtual void SetRect( const CRect& rect ) = 0;

   virtual const CRect& GetRect() const = 0;

   virtual int GetWidth() const = 0;

   virtual int GetHeight() const = 0;

   virtual const _tchar* GetCaption() const = 0;

   virtual void SetResourceData( const CUIResourceData* resData ) = 0;

   virtual void SetToolTips( const _tchar *str ) = 0;

   virtual void SetPosition( int x, int y ) = 0;

   virtual const CPoint& GetPosition() const = 0;

   virtual const CPoint& GetAbsolutePosition() const = 0;

   virtual void CaptureMouse() = 0;

   virtual void ReleaseMouse() = 0;

   virtual bool IsFocus() const = 0;

   virtual void GetFocus() = 0;

   virtual void LostFocus() = 0;

   virtual int   GetZLevel() const = 0;

   virtual bool PointInWnd( const CPoint& pt ) const = 0;

   ///< 字体相关
   /**
   @brief 设置字体

         典型的字体名： 
         宋体#16#ab
         宋体#12#
         幼圆#16#a
         幼圆#14#b
         隶书#24#a

         字体名分为三段，段之间用 # 隔开：
         1．   字形名Face Name，对应Windows中的字体名
         2．   大小，像素单位
         3．   属性段，目前有两个属性值
         ( 1 ) a, 反走样( antialiasing )字体，显示效果较为柔和平滑，如果不指定此属性，则字形会比较尖锐，可能出现走样现象
         ( 2 ) b, 粗体( bold )，不指定此属性则为普通粗细
   @param fontid 字体id
   */
   virtual void SetFontID( const _tchar* fontid ) = 0;

   virtual const _tchar* GetFontID() const = 0;

//   virtual I_Font* GetCurrentFont( void ) const = 0;

   virtual void SetResourceID( const _tchar* id ) = 0;

   virtual void ShowWindow( bool show ) = 0;

   virtual bool IsShow() const = 0;

   virtual void Draw( void ) = 0;



   ///< 窗口函数
   virtual IInvoker* SetInitFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetCloseFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetEscapeFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetGetFocusFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetLostFocusFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetFocusChangeFunc( IInvoker* oper ) = 0;

   virtual IInvoker* SetMouseInFunc( IInvoker* oper ) = 0;
   virtual IInvoker* SetMouseOutFunc( IInvoker* oper ) = 0;
};

//////////////////////////////////////////////////////////////////////////
inline void GetErrorCtrl( void* tctrl, IUIWnd* wnd, const _tchar* id )
{
   if ( tctrl == NULL )
   {
      _tstring exception_express = L"Cannot find the control wnd named ";
      exception_express += id;
      exception_express += L" under the parent wnd:";
      exception_express += wnd->GetID();
      exception_express += L"\n";
      exception_express += L"### System will be interrupted";
      inspire::CharConverter con_exp( exception_express.c_str() );
      INSPIRE_ASSERT( ( con_exp.GetUTF8() && 0 ) );
   }
}
}
#endif