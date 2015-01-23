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
#ifndef _INSPIRE_UI_WND_H_
#define _INSPIRE_UI_WND_H_

#include "IUIWnd.h"

namespace inspire {
class CKeyboardEvent;
class CMouseEvent;
class IXMLNode;

class CUIWnd : virtual public IUIWnd
{
public:
   CUIWnd();
   virtual ~CUIWnd();

public:   ///< IUIWnd 接口
   virtual const WndType GetWndType() const;

   virtual const _tchar* GetID() const;
   ///< 子窗口相关
   virtual IUIWnd* FindControl( const _tchar* id );
   ///< 窗口操作相关
   virtual int GetChildCount() const;

   virtual void ReleaseChild( IUIWnd* child );

   virtual void SetParent( IUIWnd* parent );

   virtual IUIWnd* GetParent();

   virtual void SetRect( const CRect& rect );

   virtual const CRect& GetRect() const;

   virtual int GetWidth() const;

   virtual int GetHeight() const;

   virtual const _tchar* CUIWnd::GetCaption() const;

   virtual void SetResourceData( const CUIResourceData* resData );

   virtual void SetToolTips( const _tchar* str );

   virtual void SetPosition( int x, int y );

   virtual const CPoint& GetPosition() const;

   virtual const CPoint& GetAbsolutePosition() const;

   virtual void CaptureMouse();

   virtual void ReleaseMouse();

   virtual bool IsFocus() const;

   virtual void GetFocus();

   virtual void LostFocus();

   virtual bool PointInWnd( const CPoint& pt ) const;

   virtual int   GetZLevel() const;
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
   @param fontName 字体名
   */
   virtual void SetFontID( const _tchar* fontid );

   virtual const _tchar* GetFontID() const;

   virtual void SetResourceID( const _tchar* id );

   virtual void ShowWindow( bool show );

   virtual bool IsShow() const;

   virtual void Draw();

   ///< 窗口函数
   virtual IInvoker* SetInitFunc( IInvoker* oper );
   virtual IInvoker* SetCloseFunc( IInvoker* oper );
   virtual IInvoker* SetEscapeFunc( IInvoker* oper );
   virtual IInvoker* SetMouseInFunc( IInvoker* oper );
   virtual IInvoker* SetMouseOutFunc( IInvoker* oper );
   virtual IInvoker* SetGetFocusFunc( IInvoker* oper );
   virtual IInvoker* SetLostFocusFunc( IInvoker* oper );
   virtual IInvoker* SetFocusChangeFunc( IInvoker* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( inspire::IXMLNode* node );
   virtual void AddChild( CUIWnd* child );
   virtual void RemoveChild( CUIWnd* child );
   virtual void RemoveChild( const _tchar* id );
   virtual void Remove();

   virtual bool ProcessEvent( CKeyboardEvent* kb_event );
   virtual bool ProcessEvent( CMouseEvent* ms_event );

protected:
   CUIWnd( WndType wndtype );

   void SetID( const _tchar* id );
   void SetZLevel( const int zlevel );
   void SetCaption( const _tchar* caption );

   bool DispatchToChild( CKeyboardEvent* kb_event );
   bool DispatchToChild( CMouseEvent* ms_event );

protected:
   typedef std::vector<CUIWnd*> WndContainer;
   WndContainer   _ChildWndContainer;
   int            _ChildCount;
   IUIWnd*         _Parent;
   IUIWnd*         _FocusWnd;
   IUIWnd*         _MouseOverWnd;
   
   ///< 窗口属性
   WndType         _WndType;
   bool         _ThroughEvent;         ///< 是否接受鼠标消息.
//   bool         _CanChangeSize;         ///< 能否改变窗口大小
   int            _Zlevel;            ///< 窗口Z轴层级
   int            _Horizon;            ///< 文字水平对齐
   int            _Verticial;            ///< 文字竖直对齐
   CPoint         _Position;            ///< 窗口位置
   CRect         _Rect;               ///< 窗口大小
   _tstring      _ID;               ///< 窗口ID
   _tstring      _Caption;            ///< 窗口内容的名字（Button，StaticText，CheckBox可用？）
   _tstring      _FontID;            ///< 字体ID
   _tstring      _ResourceID;         ///< 窗口资源ID
   _tstring      _Tooltips;            ///< ToolTips
   
   TiledMode      _TileMode;            ///< 拼接类型
   CUIResourceData*_TileData;            ///< 窗口拼接资源
   Tile         _TileHeadTail;         ///<
   Tile         _TileSize;            ///< 圆角大小
   bool         _CanChangeSize;         ///< 能否改变窗口大小
   ///< 窗口状态
   bool         _Active;
   bool         _ShowFlag;
   bool         _IsFocus;
   bool         _MouseIn;
   int            _TimeDelay;            ///< 鼠标滑入回调的延迟时间

   ///< 回调操作
   IInvoker*      _InitOper;
   IInvoker*      _CloseOper;
   IInvoker*      _GetFocusOper;
   IInvoker*      _LoseFocusOper;
   IInvoker*      _EscapeOper;
   IInvoker*      _FocusChangeOper;   ///< 如果有LoseFocusOper,貌似这个没有用，先放在这里@
   IInvoker*      _MonseInOper;
   IInvoker*      _MonseOutOper;

   ///< 备用
//    bool         _Moveable;
//    bool         _hotArea;
//   bool         _EnablePressDownSound;   ///< 按下时候是否有声音（暂时不支持，但是需要考虑到这种情况）
//    int            _hotArea_point[4];
//    _tstring      _SoundID;            ///< 窗口要播放的声音ID
//    _tstring      _ResourceID;         ///< 窗口资源ID
};

class ToolTipWnd : public CUIWnd
{

};

}

#endif
