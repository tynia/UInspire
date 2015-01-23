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
#ifndef _INSPIRE_XML_NODE_BASE_H_
#define _INSPIRE_XML_NODE_BASE_H_

#include "XMLUtil.hpp"

namespace inspire {
class IXMLNode;
class IXMLNodeBase
{
public:
   IXMLNodeBase();

   IXMLNodeBase( const char* name, const char* value );

   virtual ~IXMLNodeBase();

   void setName( const char* name, const std::size_t len );

   const char* getName() const;

   const std::size_t getNameSize() const;

   void setValue( const char* value, const std::size_t len );

   const char* getValue() const;
   
   const std::size_t getValueSize() const;

   void setParent( IXMLNode* node );

   IXMLNode* getParent() const;

protected:
   char*       _name;
   char*       _value;
   std::size_t _nameSize;
   std::size_t _valueSize;
   IXMLNode*   _parent;
};
}
#endif