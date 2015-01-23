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
#include "IXMLNode.h"

namespace inspire {
class CKeyboardEvent;
class CMouseEvent;

class CUIWnd : virtual public IUIWnd
{
public:
   CUIWnd();
   virtual ~CUIWnd();

public:   ///< IUIWnd �ӿ�
   virtual const WndType GetWndType() const;

   virtual const _tchar* GetID() const;
   ///< �Ӵ������
   virtual IUIWnd* FindControl( const _tchar* id );
   ///< ���ڲ������
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
   @param fontName ������
   */
   virtual void SetFontID( const _tchar* fontid );

   virtual const _tchar* GetFontID() const;

   virtual void SetResourceID( const _tchar* id );

   virtual void ShowWindow( bool show );

   virtual bool IsShow() const;

   virtual void Draw();

   ///< ���ں���
   virtual IOperation* SetInitFunc( IOperation* oper );
   virtual IOperation* SetCloseFunc( IOperation* oper );
   virtual IOperation* SetEscapeFunc( IOperation* oper );
   virtual IOperation* SetMouseInFunc( IOperation* oper );
   virtual IOperation* SetMouseOutFunc( IOperation* oper );
   virtual IOperation* SetGetFocusFunc( IOperation* oper );
   virtual IOperation* SetLostFocusFunc( IOperation* oper );
   virtual IOperation* SetFocusChangeFunc( IOperation* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( XML::IXMLNode* node );
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
   
   ///< ��������
   WndType         _WndType;
   bool         _ThroughEvent;         ///< �Ƿ���������Ϣ.
//   bool         _CanChangeSize;         ///< �ܷ�ı䴰�ڴ�С
   int            _Zlevel;            ///< ����Z��㼶
   int            _Horizon;            ///< ����ˮƽ����
   int            _Verticial;            ///< ������ֱ����
   CPoint         _Position;            ///< ����λ��
   CRect         _Rect;               ///< ���ڴ�С
   _tstring      _ID;               ///< ����ID
   _tstring      _Caption;            ///< �������ݵ����֣�Button��StaticText��CheckBox���ã���
   _tstring      _FontID;            ///< ����ID
   _tstring      _ResourceID;         ///< ������ԴID
   _tstring      _Tooltips;            ///< ToolTips
   
   TiledMode      _TileMode;            ///< ƴ������
   CUIResourceData*_TileData;            ///< ����ƴ����Դ
   Tile         _TileHeadTail;         ///<
   Tile         _TileSize;            ///< Բ�Ǵ�С
   bool         _CanChangeSize;         ///< �ܷ�ı䴰�ڴ�С
   ///< ����״̬
   bool         _Active;
   bool         _ShowFlag;
   bool         _IsFocus;
   bool         _MouseIn;
   int            _TimeDelay;            ///< ��껬��ص����ӳ�ʱ��

   ///< �ص�����
   IOperation*      _InitOper;
   IOperation*      _CloseOper;
   IOperation*      _GetFocusOper;
   IOperation*      _LoseFocusOper;
   IOperation*      _EscapeOper;
   IOperation*      _FocusChangeOper;   ///< �����LoseFocusOper,ò�����û���ã��ȷ�������@
   IOperation*      _MonseInOper;
   IOperation*      _MonseOutOper;

   ///< ����
//    bool         _Moveable;
//    bool         _hotArea;
//   bool         _EnablePressDownSound;   ///< ����ʱ���Ƿ�����������ʱ��֧�֣�������Ҫ���ǵ����������
//    int            _hotArea_point[4];
//    _tstring      _SoundID;            ///< ����Ҫ���ŵ�����ID
//    _tstring      _ResourceID;         ///< ������ԴID
};

class ToolTipWnd : public CUIWnd
{

};

}

#endif
