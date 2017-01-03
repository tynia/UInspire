#include "tracer.h"
#include "common/util.h"
#include <ctime>
#include <iostream>
#include "common/CharConverter.h"

namespace inspire {

    Tracer::Tracer(const int priority) : _priority(priority), _timestamp(0)
    {
    }

    Tracer::~Tracer()
    {
        _priority = 0;
        _timestamp = 0;

        if (NULL != _filename)
        {
           delete[] _filename;
           _filename = NULL;
        }
    }

    Tracer* Tracer::instance(const int priority)
    {
        static Tracer tracer(priority);
        return &tracer;
    }

    void Tracer::WriteLog(const int priority, const char* data)
    {
        if (priority > _priority)
        {
            ConsoleOut("priority is higher than system, skip to log it");
        }

        if (NULL == _filename)
        {
           _gen();
        }

        // OPEN FILE
        CharConvertor conn(_filename);
        ::CreateFile(conn.toString(),  )
        // IF NOT EXIST, CREATE IT
        // WRITE LOG
        // CLOSE
    }

    void Tracer::ConsoleOut(const char* fmt, ...)
    {
        char info[LOG_BUFFER_SIZE] = { 0 };
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(info, LOG_BUFFER_SIZE, fmt, ap);
        va_end(ap);

        // TODO
    }

    const char* Tracer::_gen()
    {
        struct tm otm;
        time_t tt = time(NULL);
#ifdef _WINDOWS
        ::localtime_s(&otm, &tt);
#else
        ::localtime_r(&tt, &otm);
#endif
        int year = otm.tm_year + 1900;
        int mon = otm.tm_mon + 1;
        int mday = otm.tm_mday;
        int hour = otm.tm_hour;
        int min = otm.tm_min;
        int sec = otm.tm_sec;

        _filename = new char[LOG_FILE_NAME_SIZE];
        memset(_filename, 0, LOG_FILE_NAME_SIZE);
        inspire::__snprintf(_filename, LOG_FILE_NAME_SIZE,
           "%04d-%02d-%02d-%02d.%02d.%02d.log",
           otm.tm_year + 1900, otm.tm_mon + 1, otm.tm_mday,
           otm.tm_hour, otm.tm_min, otm.tm_sec);

        return _filename;
    }
}