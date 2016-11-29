#ifndef _UI_INTERFACE_WND_H_
#define _UI_INTERFACE_WND_H_

#include "import.h"

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

        virtual bool IsShow() const = 0;

        virtual void Draw() = 0;

        virtual void SetTooltips(const char* caption) = 0;

        virtual void SetPosition(int x, int y) = 0;

        virtual const CPoint& GetPosition() const = 0;

        virtual void SetRect(const CRect& rect) = 0;

        virtual const CRect& GetRection() const = 0;

        // resource
        virtual void SetResourceID(const char* id) = 0;

        virtual void SetFontID(const char* id) = 0;
    };
}
#endif