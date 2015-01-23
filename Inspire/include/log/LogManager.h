#ifndef _INSPIRE_LOG_MANAGER_H_
#define _INSPIRE_LOG_MANAGER_H_

#include "noncopyable.h"

namespace inspire {

static const char* LOG_PATH = "./Logs/";

class LogManager : public noncopyable
{
public:
   virtual ~LogManager();
   static LogManager* Instance();

private:
   void init();

private:
   const char* _path;
};

}

#endif