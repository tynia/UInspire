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
#ifndef _INSPIRE_LOG_INTERFACE_H_
#define _INSPIRE_LOG_INTERFACE_H_

#include "LogBase.h"
INSPIRE_LOG_BENGIN
enum PRIORITY
{
   //数值越大，表示信息越繁琐
   PRIO_ALWAYS   = 0,               //总是打印
   PRIO_EMERG    = 100,             //紧急
   PRIO_FATAL    = 200,             //致命
   PRIO_CRITICAL = 300,             //关键
   PRIO_ERROR    = 400,             //错误
   PRIO_WARNING  = 500,             //警告
   PRIO_DEBUG    = 600,             //调试
   PRIO_NOTICE   = 700,             //注意，用于轻微异常，尤其是预期会经常出现的异常
   PRIO_INFO     = 800,             //信息

   PRIO_DEFAULT  = PRIO_DEBUG,      //默认是Debug优先级
   PRIO_LOG      = PRIO_CRITICAL,   //系统关键调用打印
};

class IInspireLog
{
public:
   ~IInspireLog() {}

   virtual bool isOpen() const = 0;
   virtual const int getPriority() const = 0;
   virtual const char* getCategory() const = 0;
   virtual void writeLog( int priority, const char* str ) = 0;
};

INSPIRE_LOG_END
#endif