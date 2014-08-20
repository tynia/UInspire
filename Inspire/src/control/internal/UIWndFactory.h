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
#ifndef _INSPIRE_WINDOW_FACTORY_H_
#define _INSPIRE_WINDOW_FACTORY_H_

#include "SimpleMemoryPool.h"

INSPIRE_CLIENT_BENGIN
class CUIWndFactory
{
public:
   CUIWndFactory();
   ~CUIWndFactory();

   CUIWnd* AllocWndEntity( WndType wc );

   void DeallocWndEntity( IUIWnd* wnd );

private:
   simple_pool<CUIStaticText>   _mempool_stt;
   simple_pool<CUIButton>      _mempool_btn;
   simple_pool<CUICheckBox>   _mempool_chk;
   simple_pool<CUIComboBox>   _mempool_cbb;
   simple_pool<CUIEditBox>      _mempool_edb;
   simple_pool<CUIRichEditBox>   _mempool_reb;
   simple_pool<CUIImage>      _mempool_img;
   simple_pool<CUIItem>      _mempool_itm;
   simple_pool<CUIMenu>      _mempool_mun;
   simple_pool<CUITree>      _mempool_tre;
   simple_pool<CUIScrollBar>   _mempool_scl;
   simple_pool<CUISlider>      _mempool_sld;
   simple_pool<CUIProgressBar>   _mempool_pgb;
   simple_pool<CUIList>      _mempool_lst;
   simple_pool<CUICustomWnd>   _mempool_ctw;
   simple_pool<CUIWnd>         _mempool_wnd;
};
INSPIRE_CLIENT_END
#endif