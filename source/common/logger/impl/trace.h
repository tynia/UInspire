#ifndef _INSPIRE_LOG_TRACE_H_
#define _INSPIRE_LOG_TRACE_H_

#include <ctime>
#include <windows.h>
#include "tracer.h"
#include "common/util.h"

const char* strType[] = {
    "Fatal",
    "Error",
    "Warning",
    "Info",
    "Debug"
};

inline const char* toString(int priority)
{
    if (priority < 0)
    {
        return "Invalid priority";
    }

    int idx = priority / 100;
    switch (idx)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return strType[idx];
    default:
        return strType[4];
    }

    return "Lucky to see the God";
}

inline void trace(int priority, const char* func, const char* file, const unsigned line, const char* fmt, ...)
{
    const static char *logFmt = \
        "%04d-%02d-%02d-%02d.%02d.%-25dLevel: %s\r\nPID: %-37lldTID:   %lld" \
        "\r\nFunction: %-32sLine:  %d\r\nFile: %s\r\nMessage:\r\n%s\r\n\r\n";

    struct tm otm;
    time_t tt = time(NULL);
    ::localtime_s(&otm, &tt);
    char info[LOG_BUFFER_SIZE] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(info, LOG_BUFFER_SIZE, fmt, ap);
    va_end(ap);

    char buffer[LOG_BUFFER_SIZE] = { 0 };
    inspire::__snprintf(buffer, LOG_BUFFER_SIZE, logFmt,
        otm.tm_year + 1900, otm.tm_mon + 1, otm.tm_mday,
        otm.tm_hour, otm.tm_min, otm.tm_sec, toString(priority),
        ::GetCurrentProcessId(), ::GetCurrentThreadId(),
        func, line, file, info);
    inspire::Tracer::instance()->WriteLog(priority, buffer);
}

inline void console(const char* fmt, ...)
{

    char info[LOG_BUFFER_SIZE] = { 0 };
    va_list ap;
    va_start(ap, fmt);
    inspire::Tracer::instance()->ConsoleOut(fmt, ap);
}

#endif