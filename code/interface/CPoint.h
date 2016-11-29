#ifndef _UI_INSPIRE_POINT_H_
#define _UI_INSPIRE_POINT_H_

#include "import.h"

namespace inspire {

    class CPoint
    {
    public:
        CPoint(const int x, const int y);
        ~CPoint() {}

        void SetPoint(const int x, const int y);
        const int GetX() const { return _x; }
        const int GetY() const { return _y; }

        // translate windows point to point
        void TranslateToXPoint(const HWND* wnd, const POINT& pt);
        // translate point to windows point
        void TranslateToWindow(const HWND* wnd, POINT& pt);

    private:
        int _x;
        int _y;
    };
}
#endif
