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
#ifndef _INSPIRE_XML_NODE_H_
#define _INSPIRE_XML_NODE_H_

#include "XMLBase.h"
#include "IXMLNode.h"

XML_BEGIN
class IXMLDocument;
class IXMLAttribute;
enum XMLNodeType;

class XMLNode : virtual public IXMLNode
{
public:
   XMLNode( XMLNodeType nt = XNT_ELEMENT );
   XMLNode( XMLNodeType nt, const char* name, const char* value );
   virtual ~XMLNode();

   virtual const XMLNodeType getType() const
   {
      return _type;
   }

   virtual IXMLDocument* getDocument() const;

   virtual const std::size_t getChildNum() const;

   virtual IXMLNode* clone();

   virtual IXMLNode* clone( IXMLNode* node );

   virtual IXMLNode* firstChild( const char* name = NULL );
   virtual IXMLNode* nextSibling( const char* name = NULL );
   virtual void appendChild( IXMLNode* child );
   virtual void insertChild( IXMLNode* wh, IXMLNode* child, bool behind = true );
   virtual void removeChild( IXMLNode* wh );
   virtual void removeAllChild();

   virtual IXMLNode* prevNode() const;
   virtual IXMLNode* nextNode() const;

   virtual void setAttribute( const char* name, const char* value );
   virtual IXMLAttribute* firstAttribute( const char* name = NULL );
   virtual IXMLAttribute* getAttribute( const char* name );
   virtual const char* getAttributeValue( const char* name );
   virtual void appendAttribute( IXMLAttribute* attri );
   virtual void insertAttribute( IXMLAttribute* wh, IXMLAttribute* attri, bool behind = true );
   virtual void removeAttribute( IXMLAttribute* wh );
   virtual void removeAllAttribute();

protected:
   virtual void linkToPrev( IXMLNode* next_node );
   virtual void linkToNext( IXMLNode* prev_node );

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
XML_END
#endif