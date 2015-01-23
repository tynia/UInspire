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
#ifndef _INSPIRE_XML_INTERFACE_NODE_H_
#define _INSPIRE_XML_INTERFACE_NODE_H_

#include "XMLBase.h"

namespace inspire {
class IXMLAttribute;
class IXMLDocument;

class INSPIRE_EXPORT_API IXMLNode : virtual public XMLBase
{
public:

   virtual ~IXMLNode() {}

   virtual const XMLNodeType getType() const = 0;

   virtual IXMLDocument* getDocument() const = 0;

   virtual IXMLNode* firstChild( const char* name = NULL ) = 0;

   virtual IXMLNode* nextSibling( const char* name = NULL ) = 0;

   virtual const std::size_t getChildNum() const = 0;

   virtual IXMLNode* clone() = 0;

   virtual IXMLNode* clone( IXMLNode* node ) = 0;

   virtual void appendChild( IXMLNode* child ) = 0;

   virtual void insertChild( IXMLNode* wh, IXMLNode* child, bool behind = true ) = 0;

   virtual void removeChild( IXMLNode* wh ) = 0;

   virtual void removeAllChild() = 0;

   virtual IXMLNode* prevNode() const = 0;

   virtual IXMLNode* nextNode() const = 0;

   virtual void linkToPrev( IXMLNode* next ) = 0;

   virtual void linkToNext( IXMLNode* prev ) = 0;

   virtual void setAttribute( const char* name, const char* value ) = 0;

   virtual IXMLAttribute* firstAttribute( const char* name = NULL ) = 0;

   virtual IXMLAttribute* getAttribute( const char* name ) = 0;

   virtual const char* getAttributeValue( const char* name ) = 0;

   virtual void appendAttribute( IXMLAttribute* add_attri ) = 0;

   virtual void insertAttribute( IXMLAttribute* _Where, IXMLAttribute* add_attri, bool behind = true ) = 0;

   virtual void removeAttribute( IXMLAttribute* _Where ) = 0;

   virtual void removeAllAttribute() = 0;
};
}
#endif