/*******************************************************************************
   Copyright (C) 2014 tynia.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.
   
   Any problem, please ping xduilib@gmail.com, free service may be supported.
*******************************************************************************/
#ifndef _INSPIRE_LOG_H_
#define _INSPIRE_LOG_H_

#include "IInspireLog.h"
INSPIRE_LOG_BENGIN
class InspireLog : virtual public IInspireLog
{
public:
   InspireLog( const char* category, const char* filename, int priority = PRIO_DEBUG );
   virtual ~InspireLog();

   virtual bool isOpen() const;
   virtual const int getPriority() const;
   virtual const char* getCategory() const;
   virtual void writeLog( int priority, const char* str );

protected:
   bool open( int priority );
   void close();

private:
   int          _priority;
   bool         _isOpen;
   std::string  _category;
   std::string  _filename ;
   std::fstream _file;
};

class InspireLogManager
{
public:
   InspireLogManager();
   virtual ~InspireLogManager();

   static InspireLogManager* Instance();

   IInspireLog* getLogCategory( const char* category );

private:
   void init();

private:
   const char*               _path;
   std::vector<IInspireLog*> _categorys;
};
INSPIRE_LOG_END
#endif