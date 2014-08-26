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
#ifndef _INSPIRE_UI_TREE_H_
#define _INSPIRE_UI_TREE_H_

#include "IUITree.h"
#include "UIWnd.h"
#include "UIWndEvent.h"

INSPIRE_CLIENT_BENGIN

class CUIWnd;

class CUITree : public CUIWnd, public IUITree
{
public:
   CUITree();
   virtual ~CUITree();

   virtual void AddChild( ItemData child );
   virtual void RemoveChild( const _tchar* child_id );
   virtual void RemoveChild( const int index );
   virtual void SetMultiChildNodeCheck( bool multi_check );
   virtual void Check( bool check );
   virtual bool IsCheck();

   virtual IOperation*   SetDoubleClickFunc( IOperation* oper );
   virtual IOperation* SetPressFunc( IOperation* oper );

public:
   virtual void CloneFrom( CUIWnd* wnd );
   virtual void ParseData( XML::IXMLNode* node );

private:
   void OnRootItemPressed( IUIWnd* wnd, const EventArg& arg );

protected:
   typedef CUITree UITreeNode;
   IOperation*      _PressDownOper;
   IOperation*      _DoubleClickOper;
   bool         _Check;
   bool         _MultiChildCheck;

   std::vector<UITreeNode*> _ChildNode;
};

INSPIRE_CLIENT_END
#endif