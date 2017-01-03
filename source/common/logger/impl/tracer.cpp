#include "tracer.h"

namespace inspire {

    Tracer::Tracer(const int priority) : _priority(priority), _timestamp(0)
    {
    }

    Tracer::~Tracer()
    {
        _priority = 0;
        _timestamp = 0;
    }

    Tracer* Tracer::instance(const int priority)
    {
        static Tracer tracer(priority);
        return &tracer;
    }

    void Tracer::WriteLog(const int priority, const char* data)
    {

    }
}