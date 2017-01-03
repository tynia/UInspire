#ifndef _INSPIRE_LOG_TRACER_H_
#define _INSPIRE_LOG_TRACER_H_

#define LOG_BUFFER_SIZE 4096
#define LOG_FILE_NAME_SIZE 256

namespace inspire {

    enum {
        PRIO_FATAL = -1,
        PRIO_ERROR = 100,
        PRIO_WARNING = 200,
        PRIO_INFO = 300,
        PRIO_DEBUG = 400,

        // use for system logger
        PRIO_TRACE = 401,
        PRIO_RELEASE = 301
    };

    class Tracer
    {
    public:
#ifdef _DEBUG
        static Tracer* instance(const int priority = PRIO_TRACE);
#else
        static Tracer* instance(const int priority = PRIO_RELEASE);
#endif
        virtual void WriteLog(const int priority, const char* data);

        virtual void ConsoleOut(const char* fmt, ...);

    protected:
        Tracer(const int priority);
        virtual ~Tracer() {}

    protected:
        const char* _gen();

    private:
        Tracer(const Tracer& rhs);
        Tracer& operator= (const Tracer& rhs);

    private:
        int  _priority;
        unsigned long long _timestamp;
        char* _filename;
    };
}

#endif