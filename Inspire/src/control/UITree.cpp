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
#include "UITree.h"
#include "UIItem.h"
#include "UIInvoker.h"

INSPIRE_CLIENT_BENGIN

CUITree::CUITree() : CUIWnd( EWT_TREE )
, _MultiChildCheck( false )
, _Check( false )
, _PressDownOper( NULL )
, _DoubleClickOper( NULL )
{
}

CUITree::~CUITree()
{

}

void CUITree::AddChild( ItemData child )
{

}

void CUITree::RemoveChild( const _tchar* child_id )
{

}

void CUITree::RemoveChild( const int index )
{

}

void CUITree::SetMultiChildNodeCheck( bool multi_check )
{
   _MultiChildCheck = multi_check;
}

void CUITree::Check( bool check )
{
   _Check = check;
}

bool CUITree::IsCheck()
{
   return _Check;
}

IOperation* CUITree::SetDoubleClickFunc( IOperation* oper )
{
   IOperation* oldoper = _DoubleClickOper;
   _DoubleClickOper = oper;
   return oldoper;
}

IOperation* CUITree::SetPressFunc( IOperation* oper )
{
   IOperation* oldoper = _PressDownOper;
   _PressDownOper = oper;
   return oldoper;
}

void CUITree::CloneFrom( CUIWnd* wnd )
{
   CUIWnd::CloneFrom( wnd );

   CUITree* tree = dynamic_cast<CUITree*>( wnd );
   //todo:
}

void CUITree::ParseData( XML::IXMLNode* node )
{
   CUIWnd::ParseData( node );
   //todo:
}

INSPIRE_CLIENT_END
