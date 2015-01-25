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
#ifndef _INSPIRE_XML_NODE_H_
#define _INSPIRE_XML_NODE_H_

#include "XMLBase.h"
#include "IXMLNode.h"

namespace inspire {

class IXMLDocument;
class IXMLAttribute;
enum XMLNodeType;

class XMLNode : virtual public IXMLNode
{
public:
   XMLNode( XMLNodeType nt = XNT_ELEMENT );
   XMLNode( XMLNodeType nt, const char* name, const char* value );
   virtual ~XMLNode();

   virtual const XMLNodeType GetType() const
   {
      return _type;
   }

   virtual IXMLDocument* GetDocument() const;

   virtual const std::size_t GetChildNum() const;

   virtual IXMLNode* Clone();

   virtual IXMLNode* Clone( IXMLNode* node );

   virtual IXMLNode* FirstChild( const char* name = NULL );
   virtual IXMLNode* NextSibling( const char* name = NULL );
   virtual void AppendChild( IXMLNode* child );
   virtual void InsertChild( IXMLNode* wh, IXMLNode* child, bool behind = true );
   virtual void RemoveChild( IXMLNode* wh );
   virtual void RemoveAllChild();

   virtual IXMLNode* PrevNode() const;
   virtual IXMLNode* NextNode() const;

   virtual void SetAttribute( const char* name, const char* value );
   virtual IXMLAttribute* FirstAttribute( const char* name = NULL );
   virtual IXMLAttribute* GetAttribute( const char* name );
   virtual const char* GetAttributeValue( const char* name );
   virtual void AppendAttribute( IXMLAttribute* attri );
   virtual void InsertAttribute( IXMLAttribute* wh, IXMLAttribute* attri, bool behind = true );
   virtual void RemoveAttribute( IXMLAttribute* wh );
   virtual void RemoveAllAttribute();

protected:
   virtual void LinkToPrev( IXMLNode* node );
   virtual void LinkToNext( IXMLNode* node );

private:
   XMLNode( const IXMLNode& node );
   void operator= ( const XMLNode& node );

private:
   XMLNodeType    _type;
   IXMLNode*      _firstChild;
   IXMLNode*      _prevNode;
   IXMLNode*      _nextNode;
   IXMLAttribute* _firstAttri;
};
}
#endif