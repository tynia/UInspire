#ifndef _INSPIRE_UTIL_H_
#define _INSPIRE_UTIL_H_

#include <stdio.h>
#include <stdarg.h>

namespace inspire {

#ifdef _DEBUG
    inline void Panic()
    {
        __asm int 3;
    }
#endif

    inline size_t __snprintf(char* buffer, size_t bufferLen, const char* fmt, ...)
    {
        va_list ap;
        size_t n;
        va_start(ap, fmt);
#ifdef _WINDOWS
        n = _vsnprintf_s(buffer, bufferLen, _TRUNCATE, fmt, ap);
#else
        n = vsnprintf(buffer, bufferLen, fmt, ap);
#endif
        va_end(ap);

        if (n < 0 || n >= bufferLen)
        {
            n = bufferLen - 1;
        }
        buffer[n] = '\0';
        return n;
    }
}
#endif
