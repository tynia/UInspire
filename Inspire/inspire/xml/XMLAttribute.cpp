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

IXMLDocument* XMLAttribute::GetDocument() const
{
   IXMLNode* node = GetParent();
   while ( node->GetParent() )
   {
      node = node->GetParent();
   }

   return node->GetType() == XNT_DOCUMENT ? dynamic_cast<IXMLDocument*>( node ) : NULL;
}

void XMLAttribute::Append( IXMLAttribute* attri )
{
   _next = attri;
}

IXMLAttribute* XMLAttribute::NextAttribute( const char* name ) const
{
   if ( name )
   {
      for ( IXMLAttribute* attri = _next; attri; attri = attri->NextAttribute( name ) )
      {
         if ( Equals( name, Length( name ),
                             attri->GetName(), attri->GetNameSize() ) )
         {
            return attri;
         }
      }
      return NULL;
   }

   return GetParent() ? _next : NULL;
}

IXMLAttribute* XMLAttribute::PrevAttribute( const char* name ) const
{
   if ( name )
   {
      for ( IXMLAttribute* attri = _prev; attri; attri = attri->PrevAttribute( name ) )
      {
         if ( Equals( name, Length( name ),
                             attri->GetName(), attri->GetNameSize() ) )
         {
            return attri;
         }
      }
      return NULL;
   }

   return GetParent() ? _prev : NULL;
}

void XMLAttribute::LinkToNext( IXMLAttribute* attri )
{
   _next = attri;
}

void XMLAttribute::LinkToPrev( IXMLAttribute* attri )
{
   _prev = attri;
}

}
