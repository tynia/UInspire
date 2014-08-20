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
#ifndef _INSPIRE_IUI_WND_EVENT_H_
#define _INSPIRE_IUI_WND_EVENT_H_

#include "InspireInternal.h"
INSPIRE_CLIENT_BENGIN
class IUIWnd;

struct EventArg
{
   typedef int Index;
   IUIWnd*   _Sender;
   IUIWnd*   _Reciever;
   Index   _Idx;
};

enum InputEventType
{
   IET_INVALID_EVENT = -1,   ///< 非法事件
   IET_KEYBOARD_EVENT = 0,   ///< 键盘事件
   IET_MOUSE_EVENT,      ///< 鼠标事件
};

enum MouseKey
{
   MK_LEFT_BUTTON = 0,
   MK_RIGHT_BUTTON,
   MK_MIDDLE_BUTTON,
};

enum InputEventID
{
   /**
    @键盘事件
   **/
   IE_KEY_ENVENT_BEGIN = 100,
   IE_KEY_DOWN = IE_KEY_ENVENT_BEGIN,
   IE_KEY_UP,
   IE_KEY_CLICK,
   IE_KEY_CHAR,
   IE_KEY_EVENT_END = IE_KEY_CHAR,

   /**
    @鼠标事件
   **/
   IE_MOUSE_EVENT_BEGIN = 200,
   IE_MOUSE_LEFT_DOWN,
   IE_MOUSE_LEFT_UP,
   IE_MOUSE_LEFT_CLICK,
   IE_MOUSE_LEFT_DOUBLE_CLICK,
   IE_MOUSE_RIGHT_DOWN,
   IE_MOUSE_RIGHT_UP,
   IE_MOUSE_RIGHT_CLICK,
   IE_MOUSE_MID_DOWN,
   IE_MOUSE_MID_UP,
   IE_MOUSE_DRAG,
   IE_MOUSE_ENTER,
   IE_MOUSE_EXIT,
   IE_MOUSE_WHEEL,
   IE_MOUSE_EVENT_END = IE_MOUSE_WHEEL
};

enum 
{
   SHIFT_MASK        = 1 << 0,
   LEFT_SHIFT_MASK   = 1 << 1,
   RIGHT_SHIFT_MASK  = 1 << 2,
   CTRL_MASK         = 1 << 3,
   LEFT_CTRL_MASK    = 1 << 4,
   RIGHT_CTRL_MASK   = 1 << 5,
   ALT_MASK          = 1 << 6,
   LEFT_ALT_MASK     = 1 << 7,
   RIGHT_ALT_MASK    = 1 << 8,

   LEFT_BUTTON_MASK  = 1 << 9,
   MID_BUTTON_MASK   = 1 << 10,
   RIGHT_BUTTON_MASK = 1 << 11
};

class CInputEvent
{
public:
   CInputEvent( HWND hWnd, InputEventID id, int modifiedkey )
      : _TargethWnd( hWnd )
      , _EventID( id )
      , _ModifiedKey( modifiedkey )
   {};

   ~CInputEvent()
   {
      _TargethWnd = NULL;
   };

   const HWND GetTarget() const
   {
      return _TargethWnd;
   };

   InputEventID GetEventID() const
   {
      return _EventID;
   };

   int GetModifiedKey() const
   {
      return _ModifiedKey;
   };

   bool IsSHIFTDown() const
   {
      return ( ( _ModifiedKey & SHIFT_MASK ) != 0 );
   };

   bool IsLEFTSHIFTDown() const
   {
      return ( ( _ModifiedKey & LEFT_SHIFT_MASK ) != 0 );
   };

   bool IsRIGHTSHIFTDown() const
   {
      return ( ( _ModifiedKey & RIGHT_SHIFT_MASK ) != 0 );
   };

   bool IsCTRLDown() const
   {
      return ( ( _ModifiedKey & CTRL_MASK ) != 0 );
   };

   bool IsLEFTCTRLDown() const
   {
      return ( ( _ModifiedKey & LEFT_CTRL_MASK ) != 0 );
   };

   bool IsRIGHTCTRLDown() const
   {
      return ( ( _ModifiedKey & RIGHT_CTRL_MASK ) != 0 );
   };

   bool IsALTDown() const
   {
      return ( ( _ModifiedKey & ALT_MASK ) != 0 );
   };

   bool IsLEFTALTDown() const
   {
      return ( ( _ModifiedKey & LEFT_ALT_MASK ) != 0 );
   };

   bool IsRIGHTALTDown() const
   {
      return ( ( _ModifiedKey & RIGHT_ALT_MASK ) != 0 );
   };

   bool IsLEFTBTNDown() const
   {
      return ( ( _ModifiedKey & LEFT_BUTTON_MASK ) != 0 );
   };

   bool IsMIDBTNDown() const
   {
      return ( ( _ModifiedKey & MID_BUTTON_MASK ) != 0 );
   };

   bool IsRIGHTBTNDown() const
   {
      return ( ( _ModifiedKey & RIGHT_BUTTON_MASK ) != 0 );
   };

   InputEventType GetEventType() const
   {
      if ( _EventID >= IE_KEY_ENVENT_BEGIN && _EventID <= IE_KEY_EVENT_END )
      {
         return IET_KEYBOARD_EVENT;
      }
      else if ( _EventID >= IE_MOUSE_EVENT_BEGIN && _EventID <= IE_MOUSE_EVENT_END )
      {
         return IET_MOUSE_EVENT;
      }

      return IET_INVALID_EVENT;
   };
protected:
   HWND         _TargethWnd;
   InputEventID   _EventID;
   int            _ModifiedKey;
};

///< 键盘事件
class CKeyboardEvent : public CInputEvent
{
public:
   CKeyboardEvent( HWND hWnd, InputEventID id, int modifiedkey, int key, int time = 0 )
      : CInputEvent( hWnd, id, modifiedkey )
      , _Key( key )
      , _Time( time )
   {};

   ~CKeyboardEvent(){};

   int GetKey() const
   {
      return _Key;
   };

   int GetTime() const
   {
      return _Time;
   };

protected:
   int      _Key;
   int      _Time;
};

///< 鼠标事件
class CMouseEvent : public CInputEvent
{
public:
   CMouseEvent( HWND hWnd, InputEventID id, int modifiedkey, CPoint& pos, CPoint& relpos, int wheel )
      : CInputEvent( hWnd, id, modifiedkey )
      , _Position( pos )
      , _RelativePos( relpos )
      , _Wheel( wheel )
   {};

   ~CMouseEvent(){};

   const CPoint& GetPositon() const
   {
      return _Position;
   };

   const CPoint& GetRelativePosition() const
   {
      return _RelativePos;
   };

   const int GetWheel() const
   {
      return _Wheel;
   };

protected:
   CPoint   _Position;
   CPoint   _RelativePos;
   int      _Wheel;
};

typedef std::queue<CInputEvent*> EventQueue;
class CEventQueue
{
public:
   CEventQueue()
   {

   }

   ~CEventQueue()
   {

   }

   void Push( CInputEvent* event )
   {
      _EventQueue.push( event );
   }

   CInputEvent* Pop()
   {
      if ( !_EventQueue.empty() )
      {
         CInputEvent* event = _EventQueue.front();
         _EventQueue.pop();
         return event;
      }
      return NULL;
   }

   int Size() const
   {
      return _EventQueue.size();
   }

private:
   EventQueue   _EventQueue;
};

INSPIRE_CLIENT_END
#endif