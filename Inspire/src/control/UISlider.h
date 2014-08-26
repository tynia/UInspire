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
#ifndef _INSPIRE_UI_SLIDER_H_
#define _INSPIRE_UI_SLIDER_H_

#include "IUISlider.h"
#include "UIWnd.h"

INSPIRE_CLIENT_BENGIN

class CUISlider : public CUIWnd, public IUISlider
{
public:
   CUISlider();
   virtual ~CUISlider();

   virtual void Draw();

   virtual void Enable();

   virtual void Disable();

   virtual bool IsEnable() const;

   virtual void SetChangeStep( int step );

   virtual void SetMaxValue( int max_value );

   virtual const int GetCurrentValue() const;

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( XML::IXMLNode* node );

protected:
   bool      _Enable;
   int         _MaxStep;
   int         _MaxValue;
   int         _CurrentValue;

   static int const MAX_STEP = 5;
   static int const MAX_VALUE = 100;
};

INSPIRE_CLIENT_END
#endif