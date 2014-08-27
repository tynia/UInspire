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
#ifndef _INSPIRE_UI_LAYOUT_BUILDER_H_
#define _INSPIRE_UI_LAYOUT_BUILDER_H_

#include "Inspire.h"
#include "XMLUtil.h"
class XML::IXMLNode;

INSPIRE_CLIENT_BENGIN
class IUIWndManager;
class IUIWnd;
class CUIWnd;
class CUIWndFactory;
enum WndType;

class CUILayoutBuilder
{
public:
   CUILayoutBuilder(IUIWndManager* wnd_mng);
   ~CUILayoutBuilder();

   CUIWnd* MakeClone(CUIWnd* wnd);
   void CloneRootWnd(CUIWnd* wnd);
   CUIWnd* AllocWndEntity(WndType wt);

   void ParseLayout();

private:
   void ParseLayoutFile(const char* layout_file);
   void ParseCommonWndData(IUIWnd* wnd, XML::IXMLNode* node);
   void ParseControl( IUIWnd* wnd, XML::IXMLNode* node );
   void ParseControlData(IUIWnd* wnd, XML::IXMLNode* node);

private:
   ///< control data.

private:
   IUIWndManager*   _IUIWndMng;
   CUIWndFactory*   _Factory;
};

INSPIRE_CLIENT_END
#endif