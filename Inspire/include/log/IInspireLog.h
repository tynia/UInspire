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
   //��ֵԽ�󣬱�ʾ��ϢԽ����
   PRIO_ALWAYS   = 0,               //���Ǵ�ӡ
   PRIO_EMERG    = 100,             //����
   PRIO_FATAL    = 200,             //����
   PRIO_CRITICAL = 300,             //�ؼ�
   PRIO_ERROR    = 400,             //����
   PRIO_WARNING  = 500,             //����
   PRIO_DEBUG    = 600,             //����
   PRIO_NOTICE   = 700,             //ע�⣬������΢�쳣��������Ԥ�ڻᾭ�����ֵ��쳣
   PRIO_INFO     = 800,             //��Ϣ

   PRIO_DEFAULT  = PRIO_DEBUG,      //Ĭ����Debug���ȼ�
   PRIO_LOG      = PRIO_CRITICAL,   //ϵͳ�ؼ����ô�ӡ
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