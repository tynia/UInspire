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
#include "UILayoutBuilder.h"
#include "XMLDocument.h"
#include "IUIWndManager.h"
#include "UIWndFactory.h"

INSPIRE_CLIENT_BENGIN
CUILayoutBuilder::CUILayoutBuilder(IUIWndManager* wndmng) : _IUIWndMng(wndmng)
{

}

CUILayoutBuilder::~CUILayoutBuilder()
{

}

void CUILayoutBuilder::ParseLayout()
{
   XML::XMLDocument doc;
   bool ret = doc.load("index.xml");
   if (!ret)
   {
      //can not find ui layout index file.
      return;
   }

   XML::IXMLNode* node = doc.firstChild("Layout");
   if (node)
   {
      XML::IXMLNode* child = node->firstChild("index");
      while (child)
      {
         const char* layout = child->getValue();
         if (layout)
         {
            ParseLayoutFile(layout);
         }
         child = child->nextSibling("index");
      }
   }
}

void CUILayoutBuilder::ParseLayoutFile(const char* layout)
{
   XML::XMLDocument uilayout;
   uilayout.load(layout);

   CUIWnd* wnd = NULL;
   XML::IXMLNode* windows = uilayout.firstChild("Windows");
   if (windows)
   {
      XML::IXMLNode* wndnode = windows->firstChild("Window");
      while (wndnode)
      {
         const char* str_class_index = wndnode->getAttributeValue("Class");
         if (str_class_index)
         {
            WndType wt = (WndType)atoi(str_class_index);
#ifndef _DEBUG
            if (GetClassNameFromWndClass(wt) != 0)
            {
               //error...root wnd must be Window!
               __asm int 3;
            }
#endif // !_DEBUG
            wnd = _Factory->AllocWndEntity(wt);
            ParseCommonWndData(wnd, wndnode);
            wnd->SetParent(NULL);

            const char* multiInstance = wndnode->getAttributeValue("MultiInstance");
            int val = atoi(multiInstance);
            if (val != 0)
            {
               //_IUIWndMng->PushToMultiInstanceWndContainer(wnd, NULL);
            }
            else
            {
               //_IUIWndMng->PushToWndContainer(wnd);
            }
         }
         wndnode = wndnode->nextSibling("Window");
      }
   }
}

void CUILayoutBuilder::ParseCommonWndData( IUIWnd* wnd, XML::IXMLNode* node )
{
   
}

void CUILayoutBuilder::ParseControl( IUIWnd* wnd, XML::IXMLNode* node )
{
   XML::IXMLNode* controls = node->firstChild("Controls");
   if (controls)
   {
      XML::IXMLNode* ctrl_node = controls->firstChild("Control");
      while (ctrl_node)
      {
         const char* ctrl_class = ctrl_node->getAttributeValue("Class");
         if (ctrl_class)
         {
            WndType wt = (WndType)atoi(ctrl_class);
            IUIWnd* ctrl = _Factory->AllocWndEntity(wt);
            ParseControlData(ctrl, ctrl_node);
            ctrl->SetParent(wnd);
         }
         ctrl_node = controls->nextSibling("Control");
      }
   }
}

void CUILayoutBuilder::ParseControlData( IUIWnd* wnd, XML::IXMLNode* node )
{
   XML::IXMLNode* node_detail = node->firstChild("HAlign");
   if (node_detail)
   {
      const char* str_horizon = node_detail->getValue();
      if (str_horizon)
      {
         int horizon = atoi(str_horizon);
      }
   }

   node_detail = node->firstChild("VAlign");
   if (node_detail)
   {
      const char* str_vertical = node_detail->getValue();
      if (str_vertical)
      {
         int horizon = atoi(str_vertical);
      }
   }

   node_detail = node->firstChild("Caption");
   if (node_detail)
   {
      const char* str_caption = node_detail->getValue();
      INSPIRE_INTERNAL::CharConverter con(str_caption);
      //todo
      //wnd->SetID(con.GetUnicode());
   }
}

CUIWnd* CUILayoutBuilder::MakeClone(CUIWnd* wnd)
{
   CUIWnd* new_wnd = _Factory->AllocWndEntity(wnd->GetWndType());
   new_wnd->CloneFrom(wnd);

   return new_wnd;
}

void CUILayoutBuilder::CloneRootWnd( CUIWnd* wnd )
{
   CUIWnd* new_wnd = MakeClone(wnd);

   //_IUIWndMng->PushToMultiInstanceWndContainer(new_wnd, NULL);
}

CUIWnd* CUILayoutBuilder::AllocWndEntity( WndType wt )
{
   return _Factory->AllocWndEntity(wt);
}

INSPIRE_CLIENT_END
