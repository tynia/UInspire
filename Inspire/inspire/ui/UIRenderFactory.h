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
#ifndef _INSPIRE_UI_RENDER_FACTORY_H_
#define _INSPIRE_UI_RENDER_FACTORY_H_

#include "IUIRender.h"
#include "noncopyable.h"

namespace inspire {
class CUIRenderFactory : public noncopyable
{
public:
   ~CUIRenderFactory();

   static CUIRenderFactory* Instance();
   bool QueryInterface( const RenderUID ruid, void** ppvObject );

   void Release( const RenderUID ruid );

private:
   CUIRenderFactory();
   static int const RENDER_SUPPORT_COUNT = 4;
   IUIRender* _Render;
};
}
#endif