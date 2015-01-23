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
#ifndef _INSPIRE_UI_SCROLLBAR_H_
#define _INSPIRE_UI_SCROLLBAR_H_

#include "IUIScrollBar.h"
#include "UIWnd.h"

namespace inspire {

class CUIWnd;

class CUIScrollBar : public CUIWnd, public IUIScrollBar
{
public:
   CUIScrollBar();
   virtual ~CUIScrollBar();

   virtual void Draw();
   virtual void Enable();

   virtual void Disable();

   virtual bool IsEnable();

   virtual void SetScrollRange( int max_range );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( XML::IXMLNode* node );

protected:
   bool      _Enable;
   int         _MaxRange;
   int         _CurrentPos;
   CRect      _RectPrev;
   CRect      _RectNext;
   _tstring   _PrevResourceID;
   _tstring   _NextResourceID;

private:
   static int const MAX_RANGE = 100;
};

}
#endif