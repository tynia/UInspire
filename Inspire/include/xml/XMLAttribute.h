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
#ifndef _INSPIRE_XML_ATTRIBUTE_H_
#define _INSPIRE_XML_ATTRIBUTE_H_

#include "XMLBase.h"
#include "IXMLAttribute.h"

namespace inspire {
class IXMLNode;
class IXMLDocument;

class XMLAttribute : virtual public IXMLAttribute
{
public:
   XMLAttribute();
   XMLAttribute( const char* name, const char* value );
   ~XMLAttribute();

   virtual IXMLDocument* GetDocument() const;

   virtual void Append( IXMLAttribute* attri );

   virtual IXMLAttribute* NextAttribute( const char* name = NULL ) const;
   virtual IXMLAttribute* PrevAttribute( const char* name = NULL ) const;

   virtual void LinkToNext( IXMLAttribute* attri );
   virtual void LinkToPrev( IXMLAttribute* attri );

private:
   IXMLAttribute*   _prev;
   IXMLAttribute*   _next;
};
}
#endif