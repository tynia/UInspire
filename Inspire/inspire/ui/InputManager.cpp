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
#include "InputManager.h"

namespace inspire {
CInputManager::CInputManager()
{

}

CInputManager::~CInputManager()
{

}

CInputEvent* CInputManager::GenerateEvent( HWND hWnd, InputEventID id,
                                           int modifierKey, CPoint& pos,
                                           CPoint& relPos, int wheel )
{
   CInputEvent* input_event = new CMouseEvent( hWnd, id, modifierKey, pos, relPos, wheel );
   if ( input_event )
   {
      return input_event;
   }
   return NULL;
}

CInputEvent* CInputManager::GenerateEvent( HWND hWnd, InputEventID id, int modifierKey, int key )
{
   CInputEvent* input_event = new CKeyboardEvent( hWnd, id, modifierKey, key );
   if ( input_event )
   {
      return input_event;
   }
   /// should not process to here.
   return NULL;
}

void CInputManager::DeGenerateEvent( CInputEvent*& input_event )
{
   delete input_event;
   input_event = NULL;
}

}
