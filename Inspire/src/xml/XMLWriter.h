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
#ifndef _INSPIRE_XML_WRITER_H_
#define _INSPIRE_XML_WRITER_H_

#include "XMLUtil.h"
#include <ostream>
XML_BEGIN

class IXMLNode;

class XMLWriter
{
public:
   XMLWriter();
   ~XMLWriter();

   bool toStream( std::basic_ostream<char>& basic_os, XML::IXMLNode* doc_node );
};

XML_END
#endif