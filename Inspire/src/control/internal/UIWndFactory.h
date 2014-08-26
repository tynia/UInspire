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

#include "InspireFreeList.h"
#include "UIStaticText.h"
#include "UIButton.h"
#include "UICheckBox.h"
#include "UIComboBox.h"
#include "UIEditBox.h"
#include "UIRichEditBox.h"
#include "UIImage.h"
#include "UIItem.h"
#include "UIMenu.h"
#include "UITree.h"
#include "UIScrollBar.h"
#include "UISlider.h"
#include "UIProgressBar.h"
#include "UIList.h"
#include "UICustomWnd.h"
#include "UIWnd.h"

INSPIRE_CLIENT_BENGIN
class CUIWndFactory
{
public:
   CUIWndFactory();
   ~CUIWndFactory();

   CUIWnd* AllocWndEntity( WndType wc );

   void DeallocWndEntity( IUIWnd* wnd );

private:
   InspireFreeList<CUIStaticText>   _mempool_stt;
   InspireFreeList<CUIButton>       _mempool_btn;
   InspireFreeList<CUICheckBox>     _mempool_chk;
   InspireFreeList<CUIComboBox>     _mempool_cbb;
   InspireFreeList<CUIEditBox>      _mempool_edb;
   InspireFreeList<CUIRichEditBox>  _mempool_reb;
   InspireFreeList<CUIImage>        _mempool_img;
   InspireFreeList<CUIItem>         _mempool_itm;
   InspireFreeList<CUIMenu>         _mempool_mun;
   InspireFreeList<CUITree>         _mempool_tre;
   InspireFreeList<CUIScrollBar>    _mempool_scl;
   InspireFreeList<CUISlider>       _mempool_sld;
   InspireFreeList<CUIProgressBar>  _mempool_pgb;
   InspireFreeList<CUIList>         _mempool_lst;
   InspireFreeList<CUICustomWnd>    _mempool_ctw;
   InspireFreeList<CUIWnd>          _mempool_wnd;
};
INSPIRE_CLIENT_END
#endif