/*******************************************************************************
   Copyright (C) 2015 tynia.

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
#ifndef _INSPIRE_XML_INTERFACE_ATTRIBUTE_H_
#define _INSPIRE_XML_INTERFACE_ATTRIBUTE_H_

#include "XMLBase.h"

namespace inspire {

class IXMLNode;
class IXMLDocument;

class INSPIRE_EXPORT_API IXMLAttribute : virtual public XMLBase
{
public:
   virtual ~IXMLAttribute() {}

   virtual IXMLDocument* GetDocument() const = 0;

   virtual void Append( IXMLAttribute* attri ) = 0;

   virtual IXMLAttribute* NextAttribute( const char* name = NULL ) const = 0;

   virtual IXMLAttribute* PrevAttribute( const char* name = NULL ) const = 0;

   virtual void LinkToNext( IXMLAttribute* attri ) = 0;

   virtual void LinkToPrev( IXMLAttribute* attri ) = 0;
};

}
#endif