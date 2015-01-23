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
#include "XMLAttribute.h"
#include "IXMLDocument.h"
#include "XMLHelper.h"

namespace inspire {
XMLAttribute::XMLAttribute() : XMLBase(), _prev( NULL ), _next( NULL )
{
   
}

XMLAttribute::XMLAttribute( const char* name, const char* value )
   : XMLBase( name, value ), _prev( NULL ), _next( NULL )
{

}

XMLAttribute::~XMLAttribute()
{

}

IXMLDocument* XMLAttribute::getDocument() const
{
   IXMLNode* node = getParent();
   while ( node->getParent() )
   {
      node = node->getParent();
   }

   return node->getType() == XNT_DOCUMENT ? dynamic_cast<IXMLDocument*>( node ) : NULL;
}

void XMLAttribute::append( IXMLAttribute* attri )
{
   _next = attri;
}

IXMLAttribute* XMLAttribute::nextAttribute( const char* name ) const
{
   if ( name )
   {
      for ( IXMLAttribute* attri = _next; attri; attri = attri->nextAttribute( name ) )
      {
         if ( compareString( name, caculateLen( name ),
                             attri->getName(), attri->getNameSize() ) )
         {
            return attri;
         }
      }
      return NULL;
   }

   return getParent() ? _next : NULL;
}

IXMLAttribute* XMLAttribute::prevAttribute( const char* name ) const
{
   if ( name )
   {
      for ( IXMLAttribute* attri = _prev; attri; attri = attri->prevAttribute( name ) )
      {
         if ( compareString( name, caculateLen( name ),
                             attri->getName(), attri->getNameSize() ) )
         {
            return attri;
         }
      }
      return NULL;
   }

   return getParent() ? _prev : NULL;
}

void XMLAttribute::linkToNext( IXMLAttribute* attri )
{
   _next = attri;
}

void XMLAttribute::linkToPrev( IXMLAttribute* attri )
{
   _prev = attri;
}

}
