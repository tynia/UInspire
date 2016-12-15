#ifndef _UI_INSPIRE_X_RECT_H_
#define _UI_INSPIRE_X_RECT_H_

#include "definition.h"

namespace inspire {

    struct XRect
    {
    protected:
        uint _left;
        uint _right;
        uint _top;
        uint _bottom;

    public:
        XRect() : _left(0), _right(0), _top(0), _bottom(0)
        {}

        XRect(const uint l, const uint r, const uint t, const uint b) : _left(l), _right(r), _top(t), _bottom(b)
        {}

        XRect(const XRect& rhs) : _left(rhs._left), _right(rhs._right), _top(rhs._top), _bottom(rhs._bottom)
        {}

        virtual ~XRect() {}

        void SetRect(const uint l, const uint r, const uint t, const uint b)
        {
            _left = l;
            _right = r;
            _top = t;
            _bottom = b;
        }
    };
}
#endif
