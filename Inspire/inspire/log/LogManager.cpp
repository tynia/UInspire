#include "platform.h"
#include "LogManager.h"
#include "XMLNode.h"
#include "XMLDocument.h"
#include "LogFile.h"

namespace inspire {

LogManager::LogManager() : _path(NULL)
{
   _path = LOG_PATH;
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
   XMLDocument doc;
   bool ret = doc.load("config.xml");
   if (!ret)
   {
      __asm int 3;
      return;
   }
   
   IXMLNode* root = doc.firstChild("config");
   if (root)
   {
      IXMLNode* node = root->firstChild("logs");
      if (node)
      {
         IXMLNode* child = node->firstChild("item");
         while (child)
         {
            const char* category = child->getAttributeValue("category");
            const char* filename = child->getAttributeValue("filename");
            const char* priority = child->getAttributeValue("priority");
            int prio = atoi(priority);
            if (category)
            {
               LogFile* log = new LogFile(filename, prio);
               //_categorys.push_back(log);
            }
            child = node->nextSibling("item");
         }
      }
   }
}

}