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
#ifndef _INSPIRE_UI_INPUT_MANAGER_H_
#define _INSPIRE_UI_INPUT_MANAGER_H_

#include "UIWndEvent.h"

INSPIRE_CLIENT_BENGIN
class CInputManager/* : public IInputManager*/
{
public:
   CInputManager();
   virtual ~CInputManager();

   virtual CInputEvent* GenerateEvent( HWND hWnd, InputEventID id, int modifierKey, CPoint& pos, CPoint& relPos, int wheel );

   virtual CInputEvent* GenerateEvent( HWND hWnd, InputEventID id, int modifierKey, int key );

   virtual void DeGenerateEvent( CInputEvent*& event );
};
INSPIRE_CLIENT_END
#endif