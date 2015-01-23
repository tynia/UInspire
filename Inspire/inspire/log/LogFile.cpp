#include <fstream>
#include "log/Log.h"
#include "xml/XMLDocument.h"
#include "log/LogHelper.h"

namespace inspire {

// InspireLog 
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

///< LogManager
namespace
{
   
}

LogManager::LogManager() : _path( NULL )
{
   _path = LOG_PATH ;
   init();
}

LogManager::~LogManager()
{
   _path = NULL;
}

LogManager* LogManager::Instance()
{
   static LogManager _LogManager;
   return &_LogManager;
}

void LogManager::init()
{
   XML::XMLDocument doc;
   bool ret = doc.load( "config.xml" );
   if ( !ret )
   {
      __asm int 3;
      return;
   }
   
   XML::IXMLNode* root = doc.firstChild( "config" );
   if ( root )
   {
      XML::IXMLNode* node = root->firstChild( "logs" );
      if ( node )
      {
         XML::IXMLNode* child = node->firstChild( "item" );
         while( child )
         {
            const char* category = child->getAttributeValue( "category" );
            const char* filename = child->getAttributeValue( "filename" );
            const char* priority = child->getAttributeValue( "priority" );
            int prio = atoi( priority );
            if ( category )
            {
               LogFile* log = new LogFile( category, filename, prio );
               _categorys.push_back( log );
            }
            child = node->nextSibling( "item" );
         }
      }
   }
}

}