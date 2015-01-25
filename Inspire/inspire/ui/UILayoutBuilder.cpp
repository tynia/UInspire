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
#include "UILayoutBuilder.h"
#include "XMLDocument.h"
#include "IUIWndManager.h"
#include "UIWndFactory.h"

namespace inspire {
CUILayoutBuilder::CUILayoutBuilder(IUIWndManager* wndmng) : _IUIWndMng(wndmng)
{

}

CUILayoutBuilder::~CUILayoutBuilder()
{

}

void CUILayoutBuilder::ParseLayout()
{
   inspire::XMLDocument doc;
   bool ret = doc.LoadXML("index.xml");
   if (!ret)
   {
      //can not find ui layout index file.
      return;
   }

   inspire::IXMLNode* node = doc.FirstChild("Layout");
   if (node)
   {
      inspire::IXMLNode* child = node->FirstChild("index");
      while (child)
      {
         const char* layout = child->GetValue();
         if (layout)
         {
            ParseLayoutFile(layout);
         }
         child = child->NextSibling("index");
      }
   }
}

void CUILayoutBuilder::ParseLayoutFile(const char* layout)
{
   inspire::XMLDocument uilayout;
   uilayout.LoadXML(layout);

   CUIWnd* wnd = NULL;
   inspire::IXMLNode* windows = uilayout.FirstChild("Windows");
   if (windows)
   {
      inspire::IXMLNode* wndnode = windows->FirstChild("Window");
      while (wndnode)
      {
         const char* str_class_index = wndnode->GetAttributeValue("Class");
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

            const char* multiInstance = wndnode->GetAttributeValue("MultiInstance");
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
         wndnode = wndnode->NextSibling("Window");
      }
   }
}

void CUILayoutBuilder::ParseCommonWndData( IUIWnd* wnd, inspire::IXMLNode* node )
{
   
}

void CUILayoutBuilder::ParseControl( IUIWnd* wnd, inspire::IXMLNode* node )
{
   inspire::IXMLNode* controls = node->FirstChild("Controls");
   if (controls)
   {
      inspire::IXMLNode* ctrl_node = controls->FirstChild("Control");
      while (ctrl_node)
      {
         const char* ctrl_class = ctrl_node->GetAttributeValue("Class");
         if (ctrl_class)
         {
            WndType wt = (WndType)atoi(ctrl_class);
            IUIWnd* ctrl = _Factory->AllocWndEntity(wt);
            ParseControlData(ctrl, ctrl_node);
            ctrl->SetParent(wnd);
         }
         ctrl_node = controls->NextSibling("Control");
      }
   }
}

void CUILayoutBuilder::ParseControlData( IUIWnd* wnd, inspire::IXMLNode* node )
{
   inspire::IXMLNode* node_detail = node->FirstChild("HAlign");
   if (node_detail)
   {
      const char* str_horizon = node_detail->GetValue();
      if (str_horizon)
      {
         int horizon = atoi(str_horizon);
      }
   }

   node_detail = node->FirstChild("VAlign");
   if (node_detail)
   {
      const char* str_vertical = node_detail->GetValue();
      if (str_vertical)
      {
         int horizon = atoi(str_vertical);
      }
   }

   node_detail = node->FirstChild("Caption");
   if (node_detail)
   {
      const char* str_caption = node_detail->GetValue();
      inspire::CharConverter con(str_caption);
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

}
