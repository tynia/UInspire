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
#include <string>
#include "XMLNode.h"
#include "XMLDocument.h"
#include "XMLAttribute.h"
#include "XMLHelper.h"

XML_BEGIN
XMLNode::XMLNode( XMLNodeType nt ) :   XMLBase(),
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

IXMLDocument* XMLNode::getDocument() const
{
   IXMLNode* node = XMLBase::getParent(); 
   while ( node->getParent() )
   {
      node = node->getParent();
   }

   return ( node->getType() == XNT_DOCUMENT ) ? dynamic_cast<IXMLDocument*>( node ) : NULL;
}

const std::size_t XMLNode::getChildNum() const
{
   std::size_t count = 0;
   for ( IXMLNode* child = _firstChild; child; child = child->nextSibling() )
   {
      ++count;
   }
   return count;
}

IXMLNode* XMLNode::clone()
{
   return NULL;
}

IXMLNode* XMLNode::clone( IXMLNode* node )
{
   return NULL;
}

IXMLNode* XMLNode::prevNode() const
{
   return _prevNode;
}

IXMLNode* XMLNode::nextNode() const
{
   return _nextNode;
}

void XMLNode::linkToPrev( IXMLNode* next_node )
{
   _nextNode = next_node;
}

void XMLNode::linkToNext( IXMLNode* prev_node )
{
   _prevNode = prev_node;
}

IXMLNode* XMLNode::firstChild( const char* name )
{
   if ( name )
   {
      for ( IXMLNode* node = _firstChild; node; node->nextSibling( name ) )
      {
         if( compareString( name, caculateLen( name ), node->getName(), node->getNameSize() ) )
         {
            return node;
         }
      }
      //LogError( "cannot find node [ ", name, " ]" );
      return NULL;
   }

   return _firstChild;
}

IXMLNode* XMLNode::nextSibling( const char* name )
{
   if ( name )
   {
      for ( IXMLNode* node = _nextNode; node; node = node->nextNode() )
      {
         if ( compareString( name, caculateLen( name ), node->getName(), node->getNameSize() ) )
         {
            return node;
         }
      }

      return NULL;
   }
   
   return _nextNode;
}

void XMLNode::appendChild( IXMLNode* add_node )
{
   add_node->setParent( this );
   if ( _firstChild )
   {
      IXMLNode* node = _firstChild;
      while ( node->nextNode() )
      {
         node = node->nextNode();
      }
      node->linkToPrev( add_node );
   }
   else
   {
      _firstChild = add_node;
   }
}

void XMLNode::insertChild( IXMLNode* _Where, IXMLNode* add_node, bool behind/* = true*/ )
{
   add_node->setParent( this );

   if ( behind )
   {
      IXMLNode* next_node = _Where->nextNode();
      if ( next_node )
      {
         add_node->linkToPrev( next_node );
         next_node->linkToNext( add_node );

         _Where->linkToPrev( add_node );
         add_node->linkToNext( _Where );
      }
      else
      {
         _Where->linkToPrev( add_node );
         add_node->linkToNext( _Where );
      }
   }
   else
   {
      IXMLNode* prev_node = _Where->prevNode();
      if ( prev_node )
      {
         add_node->linkToNext( prev_node );
         prev_node->linkToPrev( add_node );

         add_node->linkToPrev( _Where );
         _Where->linkToNext( _Where );
      }
      else
      {
         add_node->linkToPrev( _Where );
         _Where->linkToNext( _Where );

         _firstChild = add_node;
      }
   }
}

void XMLNode::removeChild( IXMLNode* _Where )
{
   IXMLNode* prev_node = _Where->prevNode();
   IXMLNode* next_node = _Where->nextNode();

   if ( prev_node )
   {
      prev_node->linkToPrev( next_node );
   }
   else
   {
      _firstChild = next_node;
   }

   if ( next_node )
   {
      next_node->linkToNext( prev_node );
   }

   _Where->setParent( NULL );
}

void XMLNode::removeAllChild()
{
   for ( IXMLNode* node = _firstChild; node; node = node->nextNode() )
   {
      node->setParent( NULL );
      node->removeAllChild();
      node->removeAllAttribute();
   }
   _firstChild = NULL;
}

// ElementÏà¹Ø
void XMLNode::setAttribute( const char* name, const char* value )
{
   if ( name == NULL )
   {
      return;
   }

   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->nextAttribute() )
   {
      if ( compareString( name, caculateLen( name ), attri->getName(), attri->getNameSize() ) )
      {
         attri->setValue( value, caculateLen( value ) );
         return;
      }
   }
}

IXMLAttribute* XMLNode::firstAttribute( const char* name/* = NULL*/ )
{
   if ( name )
   {
      for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->nextAttribute() )
      {
         if ( compareString( name, caculateLen( name ), attri->getName(), attri->getNameSize() ) )
         {
            return attri;
         }
      }
      //LogError( "cannot find attribute [ ", name, " ]" );
      return NULL;
   }

   return _firstAttri;
}

IXMLAttribute* XMLNode::getAttribute( const char* name )
{
   if ( name == NULL )
   {
      return NULL;
   }

   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->nextAttribute() )
   {
      if ( compareString( name, caculateLen( name ), attri->getName(), attri->getNameSize() ) )
      {
         return attri;
      }
   }

   //LogError( "cannot find attribute [ ", name, " ]" );
   return NULL;
}

const char* XMLNode::getAttributeValue( const char* name )
{
   if ( name == NULL )
   {
      return NULL;
   }

   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->nextAttribute() )
   {
      if ( compareString( name, caculateLen( name ), attri->getName(), attri->getNameSize() ) )
      {
         return attri->getValue();
      }
   }

   //LogError( "cannot find attribute [ ", name, " ]" );
   return NULL;
}

void XMLNode::appendAttribute( IXMLAttribute* add_attri )
{
   add_attri->setParent( this );

   if ( _firstAttri )
   {
      IXMLAttribute* attri = _firstAttri;
      while ( attri->nextAttribute() )
      {
         attri = attri->nextAttribute();
      }
      attri->append( add_attri );
   }
   else
   {
      _firstAttri = add_attri;
   }
}

void XMLNode::insertAttribute( IXMLAttribute* _Where, IXMLAttribute* add_attri, bool behind/* = true*/ )
{
   add_attri->setParent( this );

   if ( behind )
   {
      IXMLAttribute* next_attri = _Where->nextAttribute();
      if ( next_attri )
      {
         next_attri->linkToPrev( add_attri );
         add_attri->linkToNext( next_attri );

         add_attri->linkToPrev( _Where );
         _Where->linkToNext( add_attri );
      }
      else
      {
         add_attri->linkToPrev( _Where );
         _Where->linkToNext( add_attri );
      }
   }
   else
   {
      IXMLAttribute* prev_attri = _Where->prevAttribute();
      if ( prev_attri )
      {
         prev_attri->linkToNext( add_attri );
         add_attri->linkToPrev( prev_attri );

         add_attri->linkToNext( _Where );
         _Where->linkToPrev( add_attri );
      }
      else
      {
         add_attri->linkToNext( _Where );
         _Where->linkToPrev( add_attri );

         _firstAttri = add_attri;
      }
   }
}

void XMLNode::removeAttribute( IXMLAttribute* _Where )
{
   IXMLAttribute* prev_attri = _Where->prevAttribute();
   IXMLAttribute* next_attri = _Where->nextAttribute();
   if ( prev_attri )
   {
      prev_attri->linkToNext( next_attri );
   }
   else
   {
      _firstAttri = next_attri;
   }
   
   if ( next_attri )
   {
      next_attri->linkToPrev( prev_attri );
   }

   _Where->setParent( NULL );
}

void XMLNode::removeAllAttribute()
{
   for ( IXMLAttribute* attri = _firstAttri; attri; attri = attri->nextAttribute() )
   {
      attri->setParent( NULL );
   }
   _firstAttri = NULL;
}

XML_END
