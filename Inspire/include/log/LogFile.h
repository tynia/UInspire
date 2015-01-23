#ifndef _INSPIRE_LOG_FILE_H_
#define _INSPIRE_LOG_FILE_H_

#include "log/LogHelper.h"
#include "log/log.h"

namespace inspire {

class LogFile
{
public:
   LogFile( const char* filename, int priority = PRIO_DEBUG );
   virtual ~LogFile();

   virtual void WriteLog( int priority, const char* str );

private:
   int  _priority;
   char _filename[ MAX_LOG_FILE_NAME + 1 ] ;
};

}
#endif