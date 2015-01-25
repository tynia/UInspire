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
#include "UIWndFactory.h"
#include "wnd.h"
#include "IUIWnd.h"
namespace inspire {
CUIWndFactory::CUIWndFactory()
{

}

CUIWndFactory::~CUIWndFactory()
{

}

IUIWnd* CUIWndFactory::AllocWndEntity( WndType wt )
{
   IUIWnd* new_wnd = NULL;
   switch ( wt )
   {
   case EWT_WND :
      new_wnd = _mempool_wnd.alloc();
      break;
   case EWT_BUTTON :
      new_wnd = _mempool_btn.alloc();
      break;
   case EWT_CHECKBOX :
      new_wnd = _mempool_chk.alloc();
      break;
   case EWT_EDITBOX :
      new_wnd = _mempool_edb.alloc();
      break;
   case EWT_IMAGE :
      new_wnd = _mempool_img.alloc();
      break;
   case EWT_STATICTEXT :
      new_wnd = _mempool_stt.alloc();
      break;
   case EWT_COMBOBOX :
      new_wnd = _mempool_cbb.alloc();
      break;
   case EWT_PROGRESSBAR :
      new_wnd = _mempool_pgb.alloc();
      break;
   case EWT_RICHEDITBOX :
      new_wnd = _mempool_reb.alloc();
      break;
   case EWT_ITEM :
      new_wnd = _mempool_itm.alloc();
      break;
   case EWT_LIST :
      new_wnd = _mempool_lst.alloc();
      break;
   case EWT_MENU :
      new_wnd = _mempool_mun.alloc();
      break;
   case EWT_SCROLLBAR :
      new_wnd = _mempool_scl.alloc();
      break;
   case EWT_SLIDER :
      new_wnd = _mempool_sld.alloc();
      break;
   case EWT_TREE :
      new_wnd = _mempool_tre.alloc();
      break;
   case EWT_CUSTOMWND :
      new_wnd = _mempool_ctw.alloc();
      break;
   default:
      //log error..
      break;
   }
   return new_wnd;
}

void CUIWndFactory::DeallocWndEntity( IUIWnd* wnd )
{
   WndType wt = wnd->GetWndType();
   switch ( wt )
   {
   case EWT_WND :
      _mempool_wnd.dealloc( wnd );
      break;
   case EWT_BUTTON :
      _mempool_btn.dealloc( wnd );
      break;
   case EWT_CHECKBOX :
      _mempool_chk.dealloc( wnd );
      break;
   case EWT_EDITBOX :
      _mempool_edb.dealloc( wnd );
      break;
   case EWT_IMAGE :
      _mempool_img.dealloc( wnd );
      break;
   case EWT_STATICTEXT :
      _mempool_stt.dealloc( wnd );
      break;
   case EWT_COMBOBOX :
      _mempool_cbb.dealloc( wnd );
      break;
   case EWT_PROGRESSBAR :
      _mempool_pgb.dealloc( wnd );
      break;
   case EWT_RICHEDITBOX :
      _mempool_reb.dealloc( wnd );
      break;
   case EWT_ITEM :
      _mempool_itm.dealloc( wnd );
      break;
   case EWT_LIST :
      _mempool_lst.dealloc( wnd );
      break;
   case EWT_MENU :
      _mempool_mun.dealloc( wnd );
      break;
   case EWT_SCROLLBAR :
      _mempool_scl.dealloc( wnd );
      break;
   case EWT_SLIDER :
      _mempool_sld.dealloc( wnd );
      break;
   case EWT_TREE :
      _mempool_tre.dealloc( wnd );
      break;
   case EWT_CUSTOMWND :
      _mempool_ctw.dealloc( wnd );
      break;
   default:
      //log error..
      break;
   }
}

}
