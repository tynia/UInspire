#ifndef _UI_INSPIRE_X_POINT_H_
#define _UI_INSPIRE_X_POINT_H_

#include "definition.h"

namespace inspire {

    // x point is used for world(custom) coordinates
    // its origin is located at left-down of screen
    // 
    // however
    // the origin in windows coordinates is located at left-top
    // windows point is used for windows itself
    class XPoint
    {
    protected:
        int _x;
        int _y;

    public:
        XPoint() : _x(0), _y(0)
        {}

        XPoint(const int x, const int y) : _x(x), _y(y)
        {}

        XPoint(const XPoint& rhs) : _x(rhs._x), _y(rhs._y)
        {}

        virtual ~XPoint() {}

        void SetPoint(const int x, const int y)
        {
            _x = x;
            _y = y;
        }

        const int GetX() const { return _x; }
        const int GetY() const { return _y; }

        XPoint operator+ (const XPoint& rhs)
        {
            XPoint pt;
            pt._x = _x + rhs._x;
            pt._y = _y + rhs._y;
            return pt;
        }

        XPoint operator- (const XPoint& rhs)
        {
            XPoint pt;
            pt._x = _x - rhs._x;
            pt._y = _y - rhs._y;
            return pt;
        }

        XPoint operator= (const XPoint& rhs)
        {
            XPoint pt;
            pt._x = rhs._x;
            pt._y = rhs._y;
            return pt;
        }

        XPoint& operator+= (const XPoint& rhs)
        {
            _x += rhs._x;
            _y += rhs._y;
            return *this;
        }

        XPoint& operator-= (const XPoint& rhs)
        {
            _x -= rhs._x;
            _y -= rhs._y;
            return *this;
        }

        bool   operator== (const XPoint& rhs)
        {
            if (_x == rhs._x && _y == rhs._y)
                return true;
            return false;
        }
    };
}
#endif
