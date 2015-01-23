#include "LogFile.h"

namespace inspire {

LogFile::LogFile( const char* filename, int priority ) : _priority( priority )
{
   memset( _filename, 0, MAX_LOG_FILE_NAME + 1 ) ;
   memcpy( _filename, filename, MAX_LOG_FILE_NAME ) ;
}

void LogFile::WriteLog( int priority, const char* str )
{
   if ( priority <= _priority )
   {
      return;
   }

   std::fstream file( _filename, std::ios::out | std::ios::app ) ;
   if ( file.is_open() )
   {
      file.tellg();
      file.write( str, strlen( str ) ) ;
      file.close();
   }
}

}