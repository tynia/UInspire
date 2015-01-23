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
#ifndef _INSPIRE_XML_INTERFACE_DOCUMENT_H_
#define _INSPIRE_XML_INTERFACE_DOCUMENT_H_

#include "IXMLNode.h"

namespace inspire {

class IXMLAttribute;

class INSPIRE_EXPORT_API IXMLDocument : virtual public IXMLNode
{
public:
   virtual ~IXMLDocument() {}

   virtual const char* getFileName() const = 0;

   virtual bool load( const char* filename ) = 0;

   virtual bool save() = 0;

   virtual IXMLNode* allocNode( XMLNodeType nt, const char* name = NULL, const char* value = NULL ) = 0;

   virtual IXMLAttribute* allocAttribute( const char* name = NULL, const char* value = NULL ) = 0;

   virtual char* allocString( const char* str ) = 0;
};
}
#endif