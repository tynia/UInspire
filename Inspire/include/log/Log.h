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
#ifndef _INSPIRE_LOG_HPP_
#define _INSPIRE_LOG_HPP_

#include "ILog.h"
X_LOG_BENGIN
class InspireLog : public IInspireLog
{
public:
   InspireLog( const char* category, int priority = PRIO_DEBUG );
   virtual ~InspireLog();

   virtual bool IsOpen() const;
   virtual const int GetPriority() const;
   virtual const char* GetCategory() const;
   virtual void WriteLog( const char* category, int priority, const char* str );

protected:
   bool Open( int priority );
   void Close();

private:
   typedef std::string Category;
   typedef int Priority;
   Category     _category;
   Priority     _priority;
   bool         _isOpen;
   std::fstream _filename;
};

class InspireLogManager
{
public:
   InspireLogManager();
   virtual ~InspireLogManager();

   static InspireLogManager* Instance();

   IInspireLog* GetLogCategory( const char* category );

private:
   void Init();

private:
   const char*               _LogPath;
   std::vector<IInspireLog*> _LogCateGory;
};
X_LOG_END
#endif