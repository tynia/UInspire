#ifndef _UI_INSPIRE_COORDINATES_H_
#define _UI_INSPIRE_COORDINATES_H_

#include "interface/ui/XPoint.h"
#include "interface/ui/XRect.h"
#include "interface/ui/IUIWnd.h"

namespace inspire {

    // steps to translate point from relative world coordinates into windows coordinates
    // 1. translate x point from relative world coordinates into absolute world coordinates
    // 2. translate x point from absolute world coordinates into absolute windows coordinates
    // 3. translate POINT from absolute windows coordinates into relative windows coordinates(with window handle)
    inline XPoint toXScreen(IUIWnd* wnd, const XPoint& pt)
    {
        XPoint absolute = wnd->GetAbsolutePosition();
        absolute += pt;
        return absolute;
    }
    inline XPoint ScreenPoint2XPoint(const POINT& pt);
    inline POINT XPoint2ScreenPoint(const XPoint& pt);
    inline XPoint ClinetPoint2XPoint(const POINT& pt);
    inline POINT XPoint2ClientPoint(const XPoint& pt);
}
#endif
