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
#include "UIRenderFactory.h"
#include "UIGDIRender.h"

INSPIRE_CLIENT_BENGIN
CUIRenderFactory::CUIRenderFactory()
{

}

CUIRenderFactory::~CUIRenderFactory()
{
   
}

CUIRenderFactory* CUIRenderFactory::Instance()
{
   static CUIRenderFactory render;
   return &render;
}

bool CUIRenderFactory::QueryInterface( const RenderUID ruid, void** ppvObject )
{
   bool success = false;
   switch ( ruid )
   {
   case RUID_D2D:
      //todo:
      //ppvObject = ( void** )new CUID2DRender();
      break;
   case RUID_D3D:
      //todo:
      //ppvObject = ( void** )new CUID3DRender();
      break;
   default:
      if ( _Render == NULL )
      {
         _Render = CUIRenderGDI::Instance();
         if ( _Render == NULL )
         {
            return false;
         }
      }
      break;
   }

   ppvObject = ( void** )&_Render;
   if ( ppvObject != NULL )
   {
      success = true;
   }

   return success;
}

void CUIRenderFactory::Release( const RenderUID ruid )
{
   bool success = false;
   switch ( ruid )
   {
   case RUID_D2D:
      //todo:
      //ppvObject = ( void** )new CUID2DRender();
      break;
   case RUID_D3D:
      //todo:
      //ppvObject = ( void** )new CUID3DRender();
      break;
   default:
      if ( _Render != NULL )
      {
         _Render->Release();
         _Render = NULL;
      }
   }
   
}

INSPIRE_CLIENT_END
