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
#include "XMLHelper.h"
#include "IXMLNode.h"
#include "IXMLAttribute.h"

XML_BEGIN

std::size_t caculateLen( const char* pszString )
{
   const char* tmp = pszString;
   while ( *tmp )
   {
      ++tmp;
   }

   return tmp - pszString;
}

// 比较字符串
// 大小写敏感
bool compareString( const char* _First, std::size_t size_first, const char* _Second, std::size_t size_second )
{
   if ( size_first != size_second )
   {
      return false;
   }

   const char* end = _First + size_first;
   for ( ; _First < end; ++_First, ++_Second )
   {
      if ( *_First != *_Second )
      {
         return false;
      }
   }

   return true;
}

const unsigned char XMLLookupTable::XMT_Digits[256] = 
{
   //   0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 0
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 1
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 2
   0,  1,  2,  3,  4,  5,  6,  7,  8,  9,255,255,255,255,255,255,      // 3
   255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255,   // 4
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 5
   255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255,   // 6
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 7
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 8
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 9
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // A
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // B
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // C
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // D
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // E
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255      // F
};

bool isWhiteSpace( const char cch )
{
   if ( cch == char( ' ' )  ||
        cch == char( '\t' ) ||
        cch == char( '\n' ) ||
        cch == char( '\r' ) )
   {
      return true;
   }
   return false;
}

bool isNodeName( const char cch )
{
   if ( cch == char( '\n' ) ||
        cch == char( '\r' ) ||
        cch == char( '\t' ) ||
        cch == char( '/' )  ||
        cch == char( '\0' ) ||
        cch == char( '>' )  ||
        cch == char( ' ' )  ||
        cch == char( '?' )  )
   {
      return false;
   }
   return true;
}

bool isText( const char cch )
{
   if ( cch == char( '<' ) ||
        cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool isTextWithoutWhitespace( const char cch )
{
   if ( cch == char( '<' )  ||
        cch == char( '\0' ) ||
        cch == char( '&' )  )
   {
      return false;
   }
   return true;
}

bool isTextWithWhitespace( const char cch )
{
   if ( cch == char( '<' )  ||
        cch == char( '\0' ) ||
        cch == char( '&' )  ||
        cch == char( ' ' )  ||
        cch == char( '\n' ) ||
        cch == char( '\r' ) ||
        cch == char( '\t' ) )
   {
      return false;
   }
   return true;
}

bool isAttributeName( const char cch )
{
   if ( cch == char( '\n' ) ||
        cch == char( '\r' ) ||
        cch == char( '\t' ) ||
        cch == char( '/' )  ||
        cch == char( '<' )  ||
        cch == char( '>' )  ||
        cch == char( '=' )  ||
        cch == char( '?' )  ||
        cch == char( '!' )  ||
        cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool isSingleQuoteData( const char cch )
{
   if ( cch == char( '\'' ) ||
        cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool isPureSingleQuoteData( const char cch )
{
   if ( cch == char( '\'' ) ||
        cch == char( '\0' ) ||
        cch == char( '&' )  )
   {
      return false;
   }
   return true;
}

bool isDoubleQuoteData( const char cch )
{
   if ( cch == char( '\"' ) ||
        cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool isPureDoubleQuoteData( const char cch )
{
   if ( cch == char( '\"' ) ||
        cch == char( '\0' ) ||
        cch == char( '&' )  )
   {
      return false;
   }
   return true;
}

bool needSkip( int skip_idx, const char cch )
{
   switch( skip_idx )
   {
   case ESI_WhiteSpace :
      return isWhiteSpace( cch );
   case ESI_NodeName :
      return isNodeName( cch );
   case ESI_Text :
      return isText( cch );
   case ESI_Text_NONE_WS :
      return isTextWithoutWhitespace( cch );
   case ESI_Text_WS :
      return isTextWithWhitespace( cch );
   case ESI_AttributeName :
      return isAttributeName( cch );
   case ESI_SingleQuote :
      return isSingleQuoteData( cch );
   case ESI_PureSingleQuote :
      return isPureSingleQuoteData( cch );
   case ESI_DoubleQuote :
      return isDoubleQuoteData( cch );
   case ESI_PureDoubleQuote :
      return isPureDoubleQuoteData( cch );
   default:
      return 0;
   }
}

template<class OutIt>
OutIt printNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   switch ( node->getType() )
   {
   case XNT_DOCUMENT :
      out = printChildNode( out, node, WriteFlag, indent );
      break;
   case XNT_ELEMENT :
      out = printElementNode( out, node, WriteFlag, indent );
      break;
   case XNT_DATA :
      out = printDataNode( out, node, WriteFlag, indent );
      break;
   case XNT_CDATA :
      out = printCDataNode( out, node, WriteFlag, indent );
      break;
   case XNT_DECLARATION :
      out = printDeclaration( out, node, WriteFlag, indent );
      break;
   case XNT_COMMENT :
      out = printCommentNode( out, node, WriteFlag, indent );
      break;
   case XNT_DOCTYPE :
      out = printDoctypeNode( out, node, WriteFlag, indent );
      break;
   case XNT_PI :
      out = printPINode( out, node, WriteFlag, indent );
      break;
   default:
      //LogError( "unknown node type...", int( node->GetType() ) );
      break;
   }

   if ( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      *out = char( '\n' );
      ++out;
   }
   return out;
}

template<class OutIt>
OutIt printChildNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   for ( IXMLNode* child = node->firstChild(); child; child = child->nextSibling() )
   {
      out = printNode( out, child, WriteFlag, indent );
   }

   return out;
}

template<class OutIt>
OutIt printElementNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if ( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }
   *out = char( '<' ), ++out;
   out = copyChar( node->getName(), node->getName() + node->getNameSize(), out );
   out = printAttribute( out, node );

   if ( node->getValueSize() == 0 && !node->firstChild() )
   {
      *out = char( '/' ), ++out;
      *out = char( '>' ), ++out;
   }
   else
   {
      *out = char( '>' ), ++out;

      IXMLNode* child = node->firstChild();
      if ( !child )
      {
         out = copyAndExpandChar( node->getValue(), node->getValue() + node->getValueSize(), char( 0 ), out );
      }
      else if ( child->nextSibling() == NULL && child->getType() == XNT_DATA )
      {
         out = copyAndExpandChar( child->getValue(), child->getValue() + child->getValueSize(), char( 0 ), out );
      }
      else
      {
         if ( !( WriteFlag & PRINT_NO_INDENTING ) )
         {
            *out = char( '\n' ), ++out;
         }
         out = printChildNode( out, node, WriteFlag, indent + 1 );
         if ( !( WriteFlag & PRINT_NO_INDENTING ) )
         {
            out = fillChar( out, indent, char( '\t' ) );
         }
      }

      *out = char( '<' ), ++out;
      *out = char( '/' ), ++out;
      out = copyChar( node->getName(), node->getName() + node->getNameSize(), out );
      *out = char( '>' ), ++out;
   }

   return out;
}

template<class OutIt>
OutIt printDataNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }
   out = copyAndExpandChar( node->getValue(), node->getValue() + node->getValueSize(), char( 0 ), out );
   return out;
}

template<class OutIt>
OutIt printCDataNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }

   *out = char( '<' ); ++out;
   *out = char( '!' ); ++out;
   *out = char( '[' ); ++out;
   *out = char( 'C' ); ++out;
   *out = char( 'D' ); ++out;
   *out = char( 'A' ); ++out;
   *out = char( 'T' ); ++out;
   *out = char( 'A' ); ++out;
   *out = char( '[' ); ++out;
   out = copyChar( node->getValue(), node->getValue() + node->getValueSize(), out );
   *out = char( ']' ); ++out;
   *out = char( ']' ); ++out;
   *out = char( '>' ); ++out;
   return out;
}

template<class OutIt>
OutIt printDeclaration( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }

   *out = char( '<' ), ++out;
   *out = char( '?' ), ++out;
   *out = char( 'x' ), ++out;
   *out = char( 'm' ), ++out;
   *out = char( 'l' ), ++out;

   out = printAttribute( out, node );

   *out = char( '?' ), ++out;
   *out = char( '>' ), ++out;

   return out;
}

template<class OutIt>
OutIt printCommentNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }

   *out = char( '<' ), ++out;
   *out = char( '!' ), ++out;
   *out = char( '-' ), ++out;
   *out = char( '-' ), ++out;
   out = copyChar( node->getValue(), node->getValue() + node->getValueSize(), out );
   *out = char( '-' ), ++out;
   *out = char( '-' ), ++out;
   *out = char( '>' ), ++out;

   return out;
}

template<class OutIt>
OutIt printDoctypeNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }

   *out = char( '<' ), ++out;
   *out = char( '!' ), ++out;
   *out = char( 'D' ), ++out;
   *out = char( 'O' ), ++out;
   *out = char( 'C' ), ++out;
   *out = char( 'T' ), ++out;
   *out = char( 'Y' ), ++out;
   *out = char( 'P' ), ++out;
   *out = char( 'E' ), ++out;
   *out = char( ' ' ), ++out;
   out = copyChar( node->getValue(), node->getValue() + node->getValueSize(), out );
   *out = char( '>' ), ++out;

   return out;
}

template<class OutIt>
OutIt printPINode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   if( !( WriteFlag & PRINT_NO_INDENTING ) )
   {
      out = fillChar( out, indent, char( '\t' ) );
   }

   *out = char( '<' ), ++out;
   *out = char( '?' ), ++out;
   out = copyChar( node->getName(), node->getName() + node->getNameSize(), out );
   *out = char( ' ' ), ++out;
   out = copyChar( node->getValue(), node->getValue() + node->getValueSize(), out );
   *out = char( '?' ), ++out;
   *out = char( '>' ), ++out;

   return out;
}

template<class OutIt>
OutIt printAttribute( OutIt out, IXMLNode* node )
{
   for ( IXMLAttribute* attri = node->firstAttribute(); attri; attri = attri->nextAttribute() )
   {
      if ( attri->getName() && attri->getValue() )
      {
         *out = char( ' ' ), ++out;
         out = copyChar( attri->getName(), attri->getName() + attri->getNameSize(), out );
         *out = char( '=' ), ++out;
         if ( findChar<char, char( '"' )>( attri->getValue(), attri->getValue() + attri->getValueSize() ) )
         {
            *out = char( '\'' ), ++out;
            out = copyAndExpandChar( attri->getValue(), attri->getValue() + attri->getValueSize(), char( '"' ), out );
            *out = char( '\'' ), ++out;
         }
         else
         {
            *out = char( '"' ), ++out;
            out = copyAndExpandChar( attri->getValue(), attri->getValue() + attri->getValueSize(), char( '\'' ), out );
            *out = char( '"' ), ++out;
         }
      }
   }

   return out;
}

template<class OutIt>
OutIt copyChar( const char* begin, const char* end, OutIt out )
{
   while( begin != end )
   {
      *out++ = *begin++;
   }
   return out;
}

template<class OutIt>
OutIt copyAndExpandChar( const char* begin, const char* end, char notepand, OutIt out )
{
   while( begin != end )
   {
      if ( *begin == notepand )
      {
         *out++ = *begin;
      }
      else
      {
         switch( *begin )
         {
            // *out++ = char( '&' );  -----> *out = char( '&' ); ++out;
         case char( '<' ) :
            {
               *out++ = char( '&' );
               *out++ = char( 'l' );
               *out++ = char( 't' );
               *out++ = char( ';' );
            }
            break;
         case char( '>' ) :
            {
               *out++ = char( '&' );
               *out++ = char( 'g' );
               *out++ = char( 't' );
               *out++ = char( ';' );
            }
            break;
         case char( '\'' ) :
            {
               *out++ = char( '&' );
               *out++ = char( 'a' );
               *out++ = char( 'p' );
               *out++ = char( 'o' );
               *out++ = char( 's' );
               *out++ = char( ';' );
            }
            break;
         case char( '"' ) :
            {
               *out++ = char( '&' );
               *out++ = char( 'q' );
               *out++ = char( 'u' );
               *out++ = char( 'o' );
               *out++ = char( 't' );
               *out++ = char( ';' );
            }
            break;
         case char( '&' ) :
            {
               *out++ = char( '&' );
               *out++ = char( 'a' );
               *out++ = char( 'm' );
               *out++ = char( 'p' );
               *out++ = char( ';' );
            }
            break;
         default:
            *out++ = *begin;
         }
      }
      ++begin;
   }
   return out;
}

template<class OutIt>
OutIt fillChar( OutIt out, int n, const char cch )
{
   for ( int idx = 0; idx < n; ++idx )
   {
      *out++ = cch;
   }
   return out;
}

template<class Ch, Ch cch>
bool findChar( const char* begin, const char* end )
{
   while ( begin != end )
   {
      if ( *begin++ == cch )
      {
         return true;
      }
   }
   return false;
}

void toStream( std::basic_ostream<char>& basic_os, IXMLNode* node )
{
   printNode( std::ostream_iterator<char>( basic_os ), node, PRINT_DEFAULT );
}

std::basic_ostream<char>& operator<< ( std::basic_ostream<char>& os, IXMLNode* node )
{
   toStream( os, node );
   return os;
}

XML_END