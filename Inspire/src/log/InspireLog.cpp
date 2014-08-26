#include "InspireLog.h"
#include "XMLDocument.h"

INSPIRE_LOG_BENGIN
// InspireLog 
InspireLog::InspireLog( const char* category, const char* filename, int priority )
: _priority( priority ),
  _isOpen( false ),
  _category( category ),
  _filename( filename )
{

}

InspireLog::~InspireLog()
{
   _category = "";
   _priority = 0;

   if ( _file.is_open() )
   {
      _isOpen = false;
      _file.close();
   }
}

const int InspireLog::getPriority() const
{
   return _priority;
}

const char* InspireLog::getCategory() const
{
   return _category.c_str();
}

bool InspireLog::isOpen() const
{
   return _isOpen;
}

bool InspireLog::open( int priority )
{
   if ( priority > _priority )
   {
      return false;
   }

   _file.open( _filename.c_str(), std::fstream::binary | std::fstream::app );
   if ( _file.fail() )
   {
      return false;
   }

   if ( _file.is_open() )
   {
      _isOpen = true;
   }

   _file.tellg();
   return _isOpen;
}

void InspireLog::close()
{
   _isOpen = false;
   _file.close();
}

void InspireLog::writeLog( int priority, const char* str )
{
   if ( !open( priority ) )
   {
      return;
   }

   _file << str << std::endl << std::endl;

   close();
}

///< LogManager
namespace
{
   static const std::string LogPath = "./Logs/";
}

InspireLogManager::InspireLogManager()
{
   _path = LogPath.c_str();
   init();
}

InspireLogManager::~InspireLogManager()
{
   std::vector<IInspireLog*>::iterator it = _categorys.begin();
   for ( ; it != _categorys.end(); ++it )
   {
      delete *it;
      ( *it ) = NULL;
   }
   _path = NULL;
}

InspireLogManager* InspireLogManager::Instance()
{
   static InspireLogManager _LogManager;
   return &_LogManager;
}

void InspireLogManager::init()
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
      XML::IXMLNode* node = root->firstChild( "logitem" );
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
               IInspireLog* log = new InspireLog( category, filename, prio );
               _categorys.push_back( log );
            }
            child = node->nextSibling( "item" );
         }
      }
   }
}

IInspireLog* InspireLogManager::getLogCategory( const char* category )
{
   std::vector<IInspireLog*>::iterator it = _categorys.begin();
   for ( ; it != _categorys.end(); ++it )
   {
      if ( 0 == strncmp( category, (*it)->getCategory(), 255 ) )
      {
         return ( *it );
      }
   }

   return NULL;
}
INSPIRE_LOG_END