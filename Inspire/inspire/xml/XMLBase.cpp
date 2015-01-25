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
#include "XMLBase.h"

namespace inspire {

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

void XMLBase::SetName( const char* name, const std::size_t len )
{
   _name = const_cast<char*>( name );
   _nameSize = len;
}

const char* XMLBase::GetName() const
{
   return _name;
}

const std::size_t XMLBase::GetNameSize() const
{
   return _nameSize;
}

void XMLBase::SetValue( const char* value, const std::size_t len )
{
   _value = const_cast<char*>( value );
   _valueSize = len;
}

const char* XMLBase::GetValue() const
{
   return _value;
}

const std::size_t XMLBase::GetValueSize() const
{
   return _valueSize;
}

void XMLBase::SetParent( IXMLNode* node )
{
   _parent = node;
}

IXMLNode* XMLBase::GetParent() const
{
   return _parent;
}

}
