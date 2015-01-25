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

   virtual const XMLNodeType GetType() const = 0;

   virtual IXMLDocument* GetDocument() const = 0;

   virtual IXMLNode* FirstChild( const char* name = NULL ) = 0;

   virtual IXMLNode* NextSibling( const char* name = NULL ) = 0;

   virtual const std::size_t GetChildNum() const = 0;

   virtual IXMLNode* Clone() = 0;

   virtual IXMLNode* Clone( IXMLNode* node ) = 0;

   virtual void AppendChild( IXMLNode* child ) = 0;

   virtual void InsertChild( IXMLNode* wh, IXMLNode* child, bool behind = true ) = 0;

   virtual void RemoveChild( IXMLNode* wh ) = 0;

   virtual void RemoveAllChild() = 0;

   virtual IXMLNode* PrevNode() const = 0;

   virtual IXMLNode* NextNode() const = 0;

   virtual void LinkToPrev( IXMLNode* next ) = 0;

   virtual void LinkToNext( IXMLNode* prev ) = 0;

   virtual void SetAttribute( const char* name, const char* value ) = 0;

   virtual IXMLAttribute* FirstAttribute( const char* name = NULL ) = 0;

   virtual IXMLAttribute* GetAttribute( const char* name ) = 0;

   virtual const char* GetAttributeValue( const char* name ) = 0;

   virtual void AppendAttribute( IXMLAttribute* add_attri ) = 0;

   virtual void InsertAttribute( IXMLAttribute* _Where, IXMLAttribute* add_attri, bool behind = true ) = 0;

   virtual void RemoveAttribute( IXMLAttribute* _Where ) = 0;

   virtual void RemoveAllAttribute() = 0;
};
}
#endif