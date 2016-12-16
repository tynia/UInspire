#ifndef _INSPIRE_LOG_TRACER_H_
#define _INSPIRE_LOG_TRACER_H_

namespace inspire {

    class Tracer
    {
    public:
        static Tracer* instance(int priority, bool console = false);

        virtual void WriteLog(int priority, const char* data);

    protected:
        Tracer(int priority, bool console = false);
        virtual ~Tracer() {}

    protected:
        const char* _switch();

    private:
        Tracer(const Tracer& rhs);
        Tracer& operator= (const Tracer& rhs);

    private:
        bool _console;
        int  _priority;
        unsigned long long _timestamp;
        Tracer* _tracer;
    };
}

#endif