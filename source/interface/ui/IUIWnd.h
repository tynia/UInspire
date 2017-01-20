#ifndef _UI_INSPIRE_INTERFACE_WND_H_
#define _UI_INSPIRE_INTERFACE_WND_H_

#include "interface/definition.h"
#include "XPoint.h"
#include "XRect.h"

namespace inspire {

    enum WndType
    {
        EWT_WND = 0,
        EWT_BUTTON,
        EWT_CHECKBOX,
        EWT_EDITBOX,
        EWT_IMAGE,
        EWT_STATICTEXT,
        EWT_COMBOBOX,
        EWT_PROGRESSBAR,
        EWT_RICHEDITBOX,
        EWT_ITEM,
        EWT_LIST,
        EWT_MENU,
        EWT_SCROLLBAR,
        EWT_SLIDER,
        EWT_TREE,
        EWT_CUSTOMWND,
    };

    class IUIWnd
    {
    public:
        ~IUIWnd() {}

        virtual const WndType GetWndType() const = 0;

        virtual const char* GetID() const = 0;

        virtual int GetChildCount() const = 0;

        virtual const char* GetCaption() const = 0;

        virtual const char* SetCaption(const char* caption) = 0;

        virtual void ShowWindow() = 0;

        virtual void Hide() = 0;

        virtual void OnShow() = 0;

        virtual void OnHide() = 0;

        virtual bool IsShow() const = 0;

        virtual void Draw() = 0;

        virtual void SetTooltips(const char* tips) = 0;

        virtual IUIWnd* GetParentWnd() = 0;

        virtual void SetPosition(int x, int y) = 0;

        virtual const XPoint& GetPosition() const = 0;

        virtual const XPoint& GetAbsolutePosition() const = 0;

        virtual void SetRect(const XRect& rect) = 0;

        virtual const XRect& GetRect() const = 0;

        virtual bool PointInWnd(const XPoint& pt) const = 0;

        // resource
        virtual void SetResourceID(const char* id) = 0;

        virtual void SetFontID(const char* id) = 0;
    };
}
#endif