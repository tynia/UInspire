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
#ifndef _INSPIRE_IUI_WND_H_
#define _INSPIRE_IUI_WND_H_

#include "platform.h"
#include "CharConverter.h"
#include "Inspire.h"
#include "wnd.h"

namespace inspire {
class IOperation;

struct ItemData
{
   int index;
   _tstring strItem;
   _tstring imgItem;
   IOperation* oper;
};

typedef std::map<int, ItemData> ItemDataList;

enum TEXT_HORIZON_ALIGN
{
   THA_LEFT,      ///< �����
   THA_CENTER,    ///< �ж���
   THA_RIGHT,     ///< �Ҷ���
};

enum TEXT_VERTICAL_ALIGN
{
   TVA_TOP,      ///< ������
   TVA_CENTER,   ///< �ж���
   TVA_BOTTOM,   ///< �׶���
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

   ///< �Ӵ������
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

   ///< �������
   /**
   @brief ��������

         ���͵��������� 
         ����#16#ab
         ����#12#
         ��Բ#16#a
         ��Բ#14#b
         ����#24#a

         ��������Ϊ���Σ���֮���� # ������
         1��   ������Face Name����ӦWindows�е�������
         2��   ��С�����ص�λ
         3��   ���ԶΣ�Ŀǰ����������ֵ
         ( 1 ) a, ������( antialiasing )���壬��ʾЧ����Ϊ���ƽ���������ָ�������ԣ������λ�Ƚϼ��񣬿��ܳ�����������
         ( 2 ) b, ����( bold )����ָ����������Ϊ��ͨ��ϸ
   @param fontid ����id
   */
   virtual void SetFontID( const _tchar* fontid ) = 0;

   virtual const _tchar* GetFontID() const = 0;

//   virtual I_Font* GetCurrentFont( void ) const = 0;

   virtual void SetResourceID( const _tchar* id ) = 0;

   virtual void ShowWindow( bool show ) = 0;

   virtual bool IsShow() const = 0;

   virtual void Draw( void ) = 0;



   ///< ���ں���
   virtual IOperation* SetInitFunc( IOperation* oper ) = 0;

   virtual IOperation* SetCloseFunc( IOperation* oper ) = 0;

   virtual IOperation* SetEscapeFunc( IOperation* oper ) = 0;

   virtual IOperation* SetGetFocusFunc( IOperation* oper ) = 0;

   virtual IOperation* SetLostFocusFunc( IOperation* oper ) = 0;

   virtual IOperation* SetFocusChangeFunc( IOperation* oper ) = 0;

   virtual IOperation* SetMouseInFunc( IOperation* oper ) = 0;
   virtual IOperation* SetMouseOutFunc( IOperation* oper ) = 0;
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