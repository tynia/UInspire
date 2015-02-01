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
#ifndef _INSPIRE_HELPER_H_
#define _INSPIRE_HELPER_H_

#include "UIInvoker.h"

///< invoker begin
template<class TObj>
class Invoker : public IInvoker
{
public:
   typedef void ( TObj::*TFunc )( inspire::IUIWnd*, const inspire::EventArg& );
   struct closure
   {
      TObj*   _Obj;
      TFunc   _Func;
   };

   Invoker( TObj* obj, TFunc func )
   {
      _closure._Obj = obj;
      _closure._Func = func;
   }

   Invoker( const Invoker& ci )
   {
      _closure._Obj = ci._closure._Obj;
      _closure._Func = ci._closure._Func;
   }

   bool Equel( TObj* obj, TFunc func )
   {
      if ( _closure._Obj == obj && _closure._Func == func )
      {
         return true;
      }
      return false;
   }

   virtual void Invoke( inspire::IUIWnd* wnd, const inspire::EventArg& arg )
   {
      ( _closure._Obj->*_closure._Func )( wnd, arg );
   }

private:
   closure   _closure;
};

template<class TObj, class TWnd>
inline void InitControl( TObj* obj, TWnd*& wnd, inspire::IUIWnd* parentWnd,
                                                const std::wstring& id )
{
   wnd = obj->GetControl<TWnd>( parentWnd, id.c_str() );
}

template<class TObj, class TWnd>
inline void InitControl( TObj* obj, TWnd*& wnd, const std::wstring& id )
{
   InitControl( obj, wnd, obj->GetMainWnd(), id );
}

template<class TObj, class TWnd, class TAttacher>
inline void InitControl( TObj* obj, TWnd*& wnd, inspire::IUIWnd* parentWnd,
                         const std::wstring& id, TAttacher* attacher )
{
   InitControl( obj, wnd, parentWnd, id.c_str() );
   attacher->AttachInvoker( obj, wnd );
   attacher->Release();
}

template<class TObj, class TWnd, class TAttacher>
inline void DECLARE_MESSAGE_HANDLER( TObj* obj, TWnd* wnd, TAttacher* attacher )
{
   //scoped_ptr<TAttacher> sp( attacher );
   attacher->AttachInvoker( obj, wnd );
   attacher->Release();
}

#define DECLARE_DELEGATE( FuncName, AttacherName )                            \
template<class TObj>                                                          \
class AttacherName                                                            \
{                                                                             \
public:                                                                       \
   typedef void ( TObj::*TFunc )( inspire::IUIWnd*,                           \
                                  const inspire::EventArg& );                 \
   AttacherName( TFunc func )                                                 \
   {                                                                          \
      _Func = func;                                                           \
   }                                                                          \
                                                                              \
   ~AttacherName()                                                            \
   {                                                                          \
      _Func = NULL;                                                           \
   }                                                                          \
                                                                              \
   void Release()                                                             \
   {                                                                          \
      delete this;                                                            \
   }                                                                          \
                                                                              \
   template<class TWnd>                                                       \
   void AttachInvoker( TObj* obj, TWnd* wnd )                                 \
   {                                                                          \
      IInvoker* _invoker = MakeInvoker( obj, _Func );                         \
      if ( _invoker )                                                         \
      {                                                                       \
         wnd->FuncName( _invoker );                                           \
      }                                                                       \
   }                                                                          \
                                                                              \
public:                                                                       \
   TFunc   _Func;                                                             \
};                                                                            \
                                                                              \
template<class TObj>                                                          \
inline AttacherName<TObj>*                                                    \
FuncName( void (TObj::*func)( inspire::IUIWnd*,                               \
                              const inspire::EventArg& ) )                    \
{                                                                             \
   return new AttacherName<TObj>( func );                                     \
}                                                                             \

#define DECLARE_CALLBACK( name )   DECLARE_DELEGATE( name, name##Attacher )

DECLARE_CALLBACK( SetPressFunc )
DECLARE_CALLBACK( SetTextChangeFunc )
DECLARE_CALLBACK( SetItemChangeFunc )

///< invoker end
//////////////////////////////////////////////////////////////////////////
#endif
