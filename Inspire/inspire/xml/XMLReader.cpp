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
#include <iostream>
#include "XMLHelper.h"
#include "XMLReader.h"
#include "IXMLAttribute.h"
#include "IXMLNode.h"
#include "IXMLDocument.h"

namespace inspire {

XMLReader::XMLReader() : _parseOptions( PARSE_DEFAULT )
{
}

XMLReader::~XMLReader()
{

}

bool XMLReader::parse( char* data, IXMLDocument* doc )
{
   if ( data == NULL )
   {
      return false;
   }

   _xmlDoc = doc;
   // skip UTF-8 FEFF
   parseBOM( data );

   while( 1 )
   {
      skip( ESI_WhiteSpace, data );
      if ( *data == 0 )
      {
         break;
      }
      if ( *data == char( '<' ) )
      {
         ++data;
         if ( IXMLNode* node = parseNode( data ) )
         {
            _xmlDoc->appendChild( node );
         }
      }
      else
      {
         XML_PARSE_ERROR( "error xml begin", data );
      }
   }
   return true;
}

void XMLReader::parseBOM( char*& data )
{
   if ( static_cast<unsigned char>( data[0] ) == 0xEF && 
      static_cast<unsigned char>( data[1] ) == 0xBB && 
      static_cast<unsigned char>( data[2] ) == 0xBF )
   {
      data += 3;      // Skip utf-8 bom
   }
}

IXMLNode* XMLReader::parseNode( char*& data )
{
   switch ( data[0] )
   {
   case char( '?' ) :
      ++data;
      if ( ( data[0] == char( 'x' ) || data[0] == char( 'X' ) ) &&
         ( data[1] == char( 'm' ) || data[1] == char( 'M' ) ) &&
         ( data[2] == char( 'l' ) || data[2] == char( 'L' ) ) &&
         isWhiteSpace( data[3] ) )
      {
         data += 4;
         return parseDeclaration( data );
      }
      else
      {
         return parsePI( data );
      }
   case char( '!' ) :
      {
         switch( data[1] )
         {
         case char( '-' ) :
            if ( data[2] == char( '-' ) )
            {
               data += 3;
               return parseComment( data );
            }
            break;
         case char( '[' ) : //// '<![CDATA[' - cdata
            if ( data[2] == char( 'C' ) && data[3] == char( 'D' ) && data[4] == char( 'A' ) &&
               data[5] == char( 'T' ) && data[6] == char( 'A' ) && data[7] == char( '[' ) )
            {
               data += 8;
               return parseCData( data );
            }
            break;
         case char( 'D' ) :
            if ( data[2] == char( 'O' ) && data[3] == char( 'C' ) && data[4] == char( 'T' ) &&
               data[5] == char( 'Y' ) && data[6] == char( 'P' ) && data[7] == char( 'E' ) &&
               isWhiteSpace( data[8] ) )
            {
               data += 9;
               return parseDoctype( data );
            }
            break;
         }

         ++data;
         while( *data != char( '>' ) )
         {
            if ( *data == 0 )
            {
               XML_PARSE_ERROR( "unexpected end of data", data );
            }
            ++data;
         }
         ++data;
         return 0;
      }

   default:
      return parseElement( data );
   }
}

void XMLReader::parseAttribute( char*& data, IXMLNode* node )
{
   while ( isAttributeName( *data ) )
   {
      char* name = data;
      ++data;
      skip( ESI_AttributeName, data );
      if ( name == data )
      {
         XML_PARSE_ERROR( "must be attribute name", data );
      }
      IXMLAttribute* attri = _xmlDoc->allocAttribute();
      attri->setName( name, data - name );
      node->appendAttribute( attri );

      skip( ESI_WhiteSpace, data );
      if ( *data != char( '=' ) )
      {
         XML_PARSE_ERROR( "must be =", data );
      }
      ++data;

      if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
      {
         const_cast<char*>( attri->getName() )[attri->getNameSize()] = char( '\0' );
      }
      skip( ESI_WhiteSpace, data );
      char quote = *data;
      if ( quote != char( '\'' ) && quote != char( '"' ) )
      {
         XML_PARSE_ERROR( "must be \' / \"", data );
      }
      ++data;

      char* value = data;
      char* end;
      const int flag = _parseOptions & ~PARSE_NORMALIZE_WHITESPACE;
      if ( quote == char( '\'' ) )
      {
         end = skipAndExpandRefs( ESI_SingleQuote, ESI_PureSingleQuote, flag, data );
      }
      else
      {
         end = skipAndExpandRefs( ESI_DoubleQuote, ESI_PureDoubleQuote, flag, data );
      }
      attri->setValue( value, end - value );

      if ( *data != quote )
      {
         XML_PARSE_ERROR( "must be \' / \"", data );
      }
      ++data;

      if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
      {
          const_cast<char*>( attri->getValue() )[attri->getValueSize()] = char( '\0' );
      }

      skip( ESI_WhiteSpace, data );
   }
}

IXMLNode* XMLReader::parseDeclaration( char*& data )
{
   if ( !( _parseOptions & PARSE_DECLARATION_NODE ) )
   {
      while ( data[0] != char( '?' ) || data[1] != char( '>' ) )
      {
         if ( !data[0] )
         {
            // error. unexpected end of data
         }
         ++data;
      }
      data += 2;
      return 0;
   }

   IXMLNode* declaration = _xmlDoc->allocNode( XNT_DECLARATION );
   skip( ESI_WhiteSpace, data );
   parseAttribute( data, declaration );

   if ( data[0] != char( '?' ) || data[1] != char( '>' ) )
   {
      XML_PARSE_ERROR( "must be '>'", data );
   }
   data += 2;
   return declaration;
}

IXMLNode* XMLReader::parseComment( char*& data )
{
   if ( !( _parseOptions & PARSE_COMMENT_NODES ) )
   {
      while ( data[0] != char( '-' ) && data[1] != char( '-' ) || data[2] != char( '>' ) )
      {
         if ( !data[0] )
         {
            XML_PARSE_ERROR( "unexpected end of data", data );
         }
         ++data;
      }
      data += 3;
      return NULL;
   }

   char* value = data;
   while ( data[0] != char( '-' ) && data[1] != char( '-' ) || data[2] != char( '>' ) )
   {
      if ( !data[0] )
      {
         XML_PARSE_ERROR( "unexpected end of data", data );
      }
      ++data;
   }

   IXMLNode* comment = _xmlDoc->allocNode( XNT_COMMENT );
   comment->setValue( value, data - value );

   if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
   {
      *data = char( '\0' );
   }

   data += 3;
   return comment;
}

IXMLNode* XMLReader::parseElement( char*& data )
{
   IXMLNode* node = _xmlDoc->allocNode( XNT_ELEMENT );

   char* name = data;
   skip( ESI_NodeName, data );
   if ( data == name )
   {
      XML_PARSE_ERROR( "must be a node name", data );
   }

   node->setName( name, data - name );

   skip( ESI_WhiteSpace, data );

   parseAttribute( data, node );

   if ( *data == char( '>' ) )
   {
      ++data;
      parseNodeText( data, node );
   }
   else if ( *data == char( '/' ) )
   {
      ++data;
      if ( *data != char( '>' ) )
      {
         XML_PARSE_ERROR( "must be >", data );
      }
      ++data;
   }
   else
   {
      XML_PARSE_ERROR( "must be >", data );
   }

   if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
   {
      const_cast<char*>( node->getName() )[node->getNameSize()] = char( '\0' );
   }

   return node;
}

IXMLNode* XMLReader::parsePI( char*& data )
{
   if ( _parseOptions & PARSE_PI_NODES )
   {
      IXMLNode* pi_node = _xmlDoc->allocNode( XNT_PI );
      char* name = data;
      skip( ESI_NodeName, data );
      if ( data == name )
      {
         XML_PARSE_ERROR( "must be PI target", data );
      }
      pi_node->setName( name, data - name );

      skip( ESI_WhiteSpace, data );
      char* value = data;

      while( data[0] != char( '?' ) || data[1] == char( '>' ) )
      {
         if ( *data == char( '\0' ) )
         {
            XML_PARSE_ERROR( "unexpected end of data", data );
         }
         ++data;
      }
      pi_node->setValue( value, data - value );

      if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
      {
         const_cast<char*>( pi_node->getName() )[pi_node->getNameSize()] = char( '\0' );
         const_cast<char*>( pi_node->getValue() )[pi_node->getValueSize()] = char( '\0' );
      }
      data += 2;
      return pi_node;
   }
   else
   {
      while( data[0] != char( '?' ) || data[1] == char( '>' ) )
      {
         if ( *data == char( '\0' ) )
         {
            // error.. unexpected end of data
         }
         data += 2;
         return NULL;
      }
   }
   return NULL;
}

IXMLNode* XMLReader::parseCData( char*& data )
{
   if ( _parseOptions & PARSE_NO_DATA_NODES )
   {
      while ( data[0] != char( ']' ) || data[1] != char( ']' ) || data[2] != char( '>' ) )
      {
         if ( !data[0] )
         {
            XML_PARSE_ERROR( "unexpected end of data", data );
         }
         ++data;
      }
      data += 3;
      return NULL;
   }

   char* value = data;
   while ( data[0] != char( ']' ) || data[1] != char( ']' ) || data[2] != char( '>' ) )
   {
      if ( !data[0] )
      {
         XML_PARSE_ERROR( "unexpected end of data", data );
      }
      ++data;
   }

   IXMLNode* cdata = _xmlDoc->allocNode( XNT_CDATA );
   cdata->setValue( value, data - value );

   if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
   {
      *data = char( '\0' );
   }
   data += 3;
   return cdata;
}

IXMLNode* XMLReader::parseDoctype( char*& data )
{
   char* value = data;

   while( *data != char( '>' ) )
   {
      switch( *data )
      {
      case char( '[' ) :
         {
            ++data;
            int depth = 1;
            while( depth > 0 )
            {
               switch( *data )
               {
               case char( '[' ) :
                  ++depth;break;
               case char( ']' ) :
                  --depth; break;
               case char( '\0' ) :
                  XML_PARSE_ERROR( "unexpected end of data", data );
                  ;
               }
               ++data;
            }
            break;
         }
      case char( '\0' ) :
         {
            XML_PARSE_ERROR( "unexpected end of data", data );
         }
         break;

      default:
         ++data;
      }
   }

   if ( _parseOptions & PARSE_DOCTYPE_NODES )
   {
      IXMLNode* doctype = _xmlDoc->allocNode( XNT_DOCTYPE );
      doctype->setValue( value, data - value );

      if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
      {
         *data = char( '\0' );
      }
      data += 1;
      return doctype;
   }
   else
   {
      data += 1;
      return NULL;
   }
}

void XMLReader::parseNodeText( char*& data, IXMLNode* node )
{
   while ( 1 )
   {
      char* content_begin = data;
      skip( ESI_WhiteSpace, data );
      char nextChar = *data;
      
   finish :
      {
         switch( nextChar )
         {
         case char( '<' ) :
            if ( data[1] == char( '/' ) )
            {
               data += 2;
               if ( _parseOptions & PARSE_VALIDATE_END_TAG )
               {
                  char* name = data;
                  skip( ESI_NodeName, data );
                  if ( !compareString( node->getName(), node->getNameSize(), name, data - name ) )
                  {
                     XML_PARSE_ERROR( "invalid closing tag name.", data );
                  }
               }
               else
               {
                  skip( ESI_NodeName, data );
               }

               skip( ESI_WhiteSpace, data );
               if ( *data != char( '>' ) )
               {
                  XML_PARSE_ERROR( "must be >", data );
               }
               ++data;
               return;
            }
            else
            {
               ++data;
               if ( IXMLNode* child = parseNode( data ) )
               {
                  node->appendChild( child );
               }
               break;
            }
         case char( '\0' ) :
            {
               XML_PARSE_ERROR( "must be >", data );
            }
            break;
         default:
            nextChar = appendData( node, data, content_begin );
            goto finish;
         }
      }
   }
}

void XMLReader::skip( int skip_idx, char*& data )
{
   char* tmp = data;
   while( needSkip( skip_idx, *tmp ) )
   {
      ++tmp;
   }
   data = tmp;
}

char* XMLReader::skipAndExpandRefs( int skip_idx_1, int skip_idx_2, int flag, char*& data )
{
   if ( ( flag & PARSE_NO_ENTITY_TRANSLATION ) &&
      !( flag & PARSE_NORMALIZE_WHITESPACE )  &&
      !( flag & PARSE_TRIM_WHITESPACE ) )
   {
      skip( skip_idx_1, data );
      return data;
   }

   skip( skip_idx_2, data );

   char* src = data;
   char* dest = src;

   while( needSkip( skip_idx_1, *src ) )
   {
      if ( !( flag & PARSE_NO_ENTITY_TRANSLATION ) )
      {
         if ( src[0] == char( '&' ) )
         {
            switch( src[1] )
            {
            // &amp; &apos;
            case  char( 'a' ) :
               if ( src[2] == char( 'm' ) && src[3] == char( 'p' ) && src[4] == char( ';' ) )
               {
                  *dest = char( '&' );
                  ++dest;
                  src += 5;
                  continue;
               }
               if ( src[2] == char( 'p' ) && src[3] == char( 'o' ) && src[4] == char( 's' ) && src[5] == char( ';' ) )
               {
                  *dest = char( '\'' );
                  ++dest;
                  src += 6;
                  continue;
               }
               break;

            // &quot;
            case char( 'q' ) :
               if ( src[2] == char( 'u' ) && src[3] == char( 'o' ) && src[4] == char( 't' ) && src[5] == char( ';' ) )
               {
                  *dest = char( '"' );
                  ++dest;
                  src += 6;
                  continue;
               }
               break;

            // &gt;
            case char( 'g' ): 
               if ( src[2] == char( 't' ) && src[3] == char( ';' ) )
               {
                  *dest = char( '>' );
                  ++dest;
                  src += 4;
                  continue;
               }
               break;

            // &lt;
            case char( 'l' ): 
               if ( src[2] == char( 't' ) && src[3] == char( ';' ) )
               {
                  *dest = char( '<' );
                  ++dest;
                  src += 4;
                  continue;
               }
               break;

            // &#...; - assumes ASCII
            case char( '#' ): 
               if ( src[2] == char( 'x' ) )
               {
                  unsigned long code = 0;
                  src += 3;   // Skip &#x
                  while ( 1 )
                  {
                     unsigned char digit = XMLLookupTable::XMT_Digits[static_cast<unsigned char>( *src )];
                     if ( digit == 0xFF )
                        break;
                     code = code * 16 + digit;
                     ++src;
                  }
                  insertCodedChar( dest, code );    // Put character in output
               }
               else
               {
                  unsigned long code = 0;
                  src += 2;   // Skip &#
                  while ( 1 )
                  {
                     unsigned char digit = XMLLookupTable::XMT_Digits[static_cast<unsigned char>( *src )];
                     if ( digit == 0xFF )
                        break;
                     code = code * 10 + digit;
                     ++src;
                  }
                  insertCodedChar( dest, code );    // Put character in output
               }
               if ( *src == char( ';' ) )
               {
                  ++src;
               }
               else
               {
                  XML_PARSE_ERROR( "must be ;", data );
               }
               continue;

            default:
               break;
            }
         }   
      }
      
      if ( _parseOptions & PARSE_NORMALIZE_WHITESPACE )
      {
         if ( isWhiteSpace( *src ) )
         {
            *dest = char( ' ' );
            ++dest;
            ++src;
            while( isWhiteSpace( *src ) )
            {
               ++src;
            }
            continue;
         }
      }

      *dest++ = *src++;
   }

   data = src;
   return dest;
}

void XMLReader::insertCodedChar( char*& data, unsigned long code )
{
   if ( _parseOptions & PARSE_NO_UTF8 )
   {
      data[0] = static_cast<unsigned char>( code );
      data += 1;
   }
   else
   {
      if ( code < 0x80 )
      {
         data[0] = static_cast<unsigned char>( code );
         data += 1;
      }
      else if ( code < 0x800 )
      {
         data[1] = static_cast<unsigned char>( ( code | 0x80 ) & 0xBF );
         code >>= 6;
         data[0] = static_cast<unsigned char>( ( code | 0xC0 ) );
         data += 2;
      }
      else if ( code < 0x1000 )
      {
         data[2] = static_cast<unsigned char>( ( code | 0x80 ) & 0xBF );
         code >>= 6;
         data[1] = static_cast<unsigned char>( ( code | 0x80 ) & 0xBF );
         code >>= 6;
         data[0] = static_cast<unsigned char>( code | 0xE0 );
         data += 3;
      }
      else if ( code < 0x110000 )   // 4 byte sequence
      {
         data[3] = static_cast<unsigned char>( ( code | 0x80 ) & 0xBF );
         code >>= 6;
         data[2] = static_cast<unsigned char>( ( code | 0x80 ) & 0xBF );
         code >>= 6;
         data[1] = static_cast<unsigned char>( ( code | 0x80 ) & 0xBF );
         code >>= 6;
         data[0] = static_cast<unsigned char>( code | 0xF0 );
         data += 4;
      }
      else
      {
         XML_PARSE_ERROR( "invalid numeric char entity", data );
      }
   }
}

char XMLReader::appendData( IXMLNode* node, char*& data, char* start )
{
   if ( !( _parseOptions & PARSE_TRIM_WHITESPACE ) )
   {
      data = start;
   }

   char* value = data;
   char* end;
   if ( _parseOptions & PARSE_NORMALIZE_WHITESPACE )
   {
      end = skipAndExpandRefs( ESI_Text, ESI_Text_WS, _parseOptions, data );
   }
   else
   {
      end = skipAndExpandRefs( ESI_Text, ESI_Text_NONE_WS, _parseOptions, data );
   }
   
   if ( _parseOptions & PARSE_TRIM_WHITESPACE )
   {
      if ( _parseOptions & PARSE_NORMALIZE_WHITESPACE )
      {
         if ( *( end - 1 ) == char( ' ' ) )
         {
            --end;
         }
      }
      else
      {
         while( isWhiteSpace( *( end - 1 ) ) )
         {
            --end;
         }
      }
   }

   if ( !( _parseOptions & PARSE_NO_DATA_NODES ) )
   {
      IXMLNode* dataNode = _xmlDoc->allocNode( XNT_DATA );
      dataNode->setValue( value, end - value );
      node->appendChild( dataNode );
   }

   if ( !( _parseOptions & PARSE_NO_VALUE_ELEMENTS ) )
   {
      if ( node->getValue() == NULL )
      {
         node->setValue( value, end - value );
      }
   }
   if ( !( _parseOptions & PARSE_NO_STRING_TERMINATORS ) )
   {
      char ch = *data;
      *end = char( '\0' );
      return ch;
   }

   return *data;
}

}
