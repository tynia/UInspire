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

#include "FreeList.h"

namespace inspire {

class IUIStaticText;
class IUIButton;
class IUICheckBox;
class IUIComboBox;
class IUIEditBox;
class IUIRichEditBox;
class IUIImage;
class IUIItem;
class IUIMenu;
class IUITree;
class IUIScrollBar;
class IUISlider;
class IUIProgressBar;
class IUIList;
class IUICustomWnd;
class IUIWnd;

class CUIWndFactory
{
public:
   CUIWndFactory();
   ~CUIWndFactory();

   IUIWnd* AllocWndEntity( WndType wc );

   void DeallocWndEntity( IUIWnd* wnd );

private:
   FreeList<IUIStaticText>   _mempool_stt;
   FreeList<IUIButton>       _mempool_btn;
   FreeList<IUICheckBox>     _mempool_chk;
   FreeList<IUIComboBox>     _mempool_cbb;
   FreeList<IUIEditBox>      _mempool_edb;
   FreeList<IUIRichEditBox>  _mempool_reb;
   FreeList<IUIImage>        _mempool_img;
   FreeList<IUIItem>         _mempool_itm;
   FreeList<IUIMenu>         _mempool_mun;
   FreeList<IUITree>         _mempool_tre;
   FreeList<IUIScrollBar>    _mempool_scl;
   FreeList<IUISlider>       _mempool_sld;
   FreeList<IUIProgressBar>  _mempool_pgb;
   FreeList<IUIList>         _mempool_lst;
   FreeList<IUICustomWnd>    _mempool_ctw;
   FreeList<IUIWnd>          _mempool_wnd;
};
}
#endif