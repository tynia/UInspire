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
#include "XMLBase.h"

XML_BEGIN

XMLBase::XMLBase() :
_name( NULL ),
_nameSize( 0 ),
_value( NULL ),
_valueSize( 0 ),
_parent( NULL )
{

}

XMLBase::XMLBase( const char* name, const char* value )
{
   _name = const_cast<char*>( name );
   _value = const_cast<char*>( value );
   _parent = NULL;
}

XMLBase::~XMLBase()
{

}

void XMLBase::setName( const char* name, const std::size_t len )
{
   _name = const_cast<char*>( name );
   _nameSize = len;
}

const char* XMLBase::getName() const
{
   return _name;
}

const std::size_t XMLBase::getNameSize() const
{
   return _nameSize;
}

void XMLBase::setValue( const char* value, const std::size_t len )
{
   _value = const_cast<char*>( value );
   _valueSize = len;
}

const char* XMLBase::getValue() const
{
   return _value;
}

const std::size_t XMLBase::getValueSize() const
{
   return _valueSize;
}

void XMLBase::setParent( IXMLNode* node )
{
   _parent = node;
}

IXMLNode* XMLBase::getParent() const
{
   return _parent;
}

XML_END