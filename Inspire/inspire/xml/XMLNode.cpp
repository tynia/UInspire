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
#include <string>
#include "XMLNode.h"
#include "XMLDocument.h"
#include "XMLAttribute.h"
#include "XMLHelper.h"

namespace inspire {
XMLNode::XMLNode( XMLNodeType nt ) : XMLBase(),
   _type( nt ),
   _firstChild( NULL ),
   _prevNode( NULL ),
   _nextNode( NULL ),
   _firstAttri( NULL )
{

}

XMLNode::XMLNode( XMLNodeType nt, const char* name, const char* value ) : XMLBase( name, value )
{
   _type = nt;
   _firstChild = NULL;
   _prevNode = NULL;
   _nextNode = NULL;
}

XMLNode::~XMLNode()
{
   _firstChild = NULL;
   _prevNode = NULL;
   _nextNode = NULL;
   _firstAttri = NULL;
}

IXMLDocument* XMLNode::GetDocument() const
{
   IXMLNode* node = XMLBase::GetParent(); 
   while ( node->GetParent() )
   {
      node = node->GetParent();
   }

   return ( node->GetType() == XNT_DOCUMENT ) ? dynamic_cast<IXMLDocument*>( node ) : NULL;
}

const std::size_t XMLNode::GetChildNum() const
{
   std::size_t count = 0;
   for ( IXMLNode* child = _firstChild; child; child = child->NextSibling() )
   {
      ++count;
   }
   return count;
}

IXMLNode* XMLNode::Clone()
{
   return NULL;
}

IXMLNode* XMLNode::Clone( IXMLNode* node )
{
   return NULL;
}

IXMLNode* XMLNode::PrevNode() const
{
   return _prevNode;
}

IXMLNode* XMLNode::NextNode() const
{
   return _nextNode;
}

void XMLNode::LinkToPrev( IXMLNode* node )
{
   _nextNode = node;
}

void XMLNode::LinkToNext( IXMLNode* node )
{
   _prevNode = node;
}

IXMLNode* XMLNode::FirstChild( const char* name )
{
   if ( name )
   {
      for ( IXMLNode* node = _firstChild; node; node->NextSibling( name ) )
      {
         if( Equals( name, Length( name ), node->GetName(), node->GetNameSize() ) )
         {
            return node;
         }
      }

      return NULL;
   }

   return _firstChild;
}

IXMLNode* XMLNode::NextSibling( const char* name )
{
   if ( name )
   {
      for ( IXMLNode* node = _nextNode; node; node = node->NextNode() )
      {
         if ( Equals( name, Length( name ), node->GetName(), node->GetNameSize() ) )
         {
            return node;
         }
      }

      return NULL;
   }
   
   return _nextNode;
}

void XMLNode::AppendChild( IXMLNode* add_node )
{
   add_node->SetParent( this );
   if ( _firstChild )
   {
      IXMLNode* node = _firstChild;
      while ( node->NextNode() )
      {
         node = node->NextNode();
      }
      node->LinkToPrev( add_node );
   }
   else
   {
      _firstChild = add_node;
   }
}

void XMLNode::InsertChild( IXMLNode* _Where, IXMLNode* add_node, bool behind/* = true*/ )
{
   add_node->SetParent( this );

   if ( behind )
   {
      IXMLNode* next_node = _Where->NextNode();
      if ( next_node )
      {
         add_node->LinkToPrev( next_node );
         next_node->LinkToNext( add_node );

         _Where->LinkToPrev( add_node );
         add_node->LinkToNext( _Where );
      }
      else
      {
         _Where->LinkToPrev( add_node );
         add_node->LinkToNext( _Where );
      }
   }
   else
   {
      IXMLNode* prev_node = _Where->PrevNode();
      if ( prev_node )
      {
         add_node->LinkToNext( prev_node );
         prev_node->LinkToPrev( add_node );

         add_node->LinkToPrev( _Where );
         _Where->LinkToNext( _Where );
      }
      else
      {
         add_node->LinkToPrev( _Where );
         _Where->LinkToNext( _Where );

         _firstChild = add_node;
      }
   }
}

void XMLNode::RemoveChild( IXMLNode* _Where )
{
   IXMLNode* prev_node = _Where->PrevNode();
   IXMLNode* next_node = _Where->NextNode();

   if ( prev_node )
   {
      prev_node->LinkToPrev( next_node );
   }
   else
   {
      _firstChild = next_node;
   }

   if ( next_node )
   {
      next_node->LinkToNext( prev_node );
   }

   _Where->SetParent( NULL );
}

void XMLNode::RemoveAllChild()
{
   for ( IXMLNode* node = _firstChild; node; node = node->NextNode() )
   {
      node->SetParent( NULL );
      node->RemoveAllChild();
      node->RemoveAllAttribute();
   }
   _firstChild = NULL;
}

// ElementÏà¹Ø
void XMLNode::SetAttribute( const char* name, const char* value )
{
   if ( name == NULL )
   {
      return;
   }

   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->NextAttribute() )
   {
      if ( Equals( name, Length( name ), attri->GetName(), attri->GetNameSize() ) )
      {
         attri->SetValue( value, Length( value ) );
         return;
      }
   }
}

IXMLAttribute* XMLNode::FirstAttribute( const char* name/* = NULL*/ )
{
   if ( name )
   {
      for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->NextAttribute() )
      {
         if ( Equals( name, Length( name ), attri->GetName(), attri->GetNameSize() ) )
         {
            return attri;
         }
      }
      //LogError( "cannot find attribute [ ", name, " ]" );
      return NULL;
   }

   return _firstAttri;
}

IXMLAttribute* XMLNode::GetAttribute( const char* name )
{
   if ( name == NULL )
   {
      return NULL;
   }

   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->NextAttribute() )
   {
      if ( Equals( name, Length( name ), attri->GetName(), attri->GetNameSize() ) )
      {
         return attri;
      }
   }

   //LogError( "cannot find attribute [ ", name, " ]" );
   return NULL;
}

const char* XMLNode::GetAttributeValue( const char* name )
{
   if ( name == NULL )
   {
      return NULL;
   }

   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->NextAttribute() )
   {
      if ( Equals( name, Length( name ), attri->GetName(), attri->GetNameSize() ) )
      {
         return attri->GetValue();
      }
   }

   //LogError( "cannot find attribute [ ", name, " ]" );
   return NULL;
}

void XMLNode::AppendAttribute( IXMLAttribute* add_attri )
{
   add_attri->SetParent( this );

   if ( _firstAttri )
   {
      IXMLAttribute* attri = _firstAttri;
      while ( attri->NextAttribute() )
      {
         attri = attri->NextAttribute();
      }
      attri->Append( add_attri );
   }
   else
   {
      _firstAttri = add_attri;
   }
}

void XMLNode::InsertAttribute( IXMLAttribute* _Where, IXMLAttribute* add_attri, bool behind/* = true*/ )
{
   add_attri->SetParent( this );

   if ( behind )
   {
      IXMLAttribute* next_attri = _Where->NextAttribute();
      if ( next_attri )
      {
         next_attri->LinkToPrev( add_attri );
         add_attri->LinkToNext( next_attri );

         add_attri->LinkToPrev( _Where );
         _Where->LinkToNext( add_attri );
      }
      else
      {
         add_attri->LinkToPrev( _Where );
         _Where->LinkToNext( add_attri );
      }
   }
   else
   {
      IXMLAttribute* prev_attri = _Where->PrevAttribute();
      if ( prev_attri )
      {
         prev_attri->LinkToNext( add_attri );
         add_attri->LinkToPrev( prev_attri );

         add_attri->LinkToNext( _Where );
         _Where->LinkToPrev( add_attri );
      }
      else
      {
         add_attri->LinkToNext( _Where );
         _Where->LinkToPrev( add_attri );

         _firstAttri = add_attri;
      }
   }
}

void XMLNode::RemoveAttribute( IXMLAttribute* _Where )
{
   IXMLAttribute* prev_attri = _Where->PrevAttribute();
   IXMLAttribute* next_attri = _Where->NextAttribute();
   if ( prev_attri )
   {
      prev_attri->LinkToNext( next_attri );
   }
   else
   {
      _firstAttri = next_attri;
   }
   
   if ( next_attri )
   {
      next_attri->LinkToPrev( prev_attri );
   }

   _Where->SetParent( NULL );
}

void XMLNode::RemoveAllAttribute()
{
   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->NextAttribute() )
   {
      attri->SetParent( NULL );
   }
   _firstAttri = NULL;
}

}
