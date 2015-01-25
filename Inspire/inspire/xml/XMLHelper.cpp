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
#include "XMLHelper.h"
#include "IXMLNode.h"
#include "IXMLAttribute.h"

namespace inspire {

std::size_t Length( const char* str )
{
   const char* tmp = str;
   while ( *tmp )
   {
      ++tmp;
   }

   return tmp - str;
}

bool Equals( const char* first, std::size_t szFirst, const char* second, std::size_t szSecond )
{
   if ( szFirst != szSecond )
   {
      return false;
   }

   const char* end = first + szFirst;
   for ( ; first < end; ++first, ++second )
   {
      if ( *first != *second )
      {
         return false;
      }
   }

   return true;
}

const unsigned char XML::DIGITAL[256] = 
{
   //   0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 0
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 1
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,   // 2
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9,255,255,255,255,255,255,   // 3
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
   255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255    // F
};

bool IsWhiteSpace( const char cch )
{
   if ( cch == char( ' ' )  || cch == char( '\t' ) ||
        cch == char( '\n' ) || cch == char( '\r' ) )
   {
      return true;
   }
   return false;
}

bool IsNameText( const char cch )
{
   if ( cch == char( '\n' ) || cch == char( '\r' ) ||
        cch == char( '\t' ) || cch == char( '/' )  ||
        cch == char( '\0' ) || cch == char( '>' )  ||
        cch == char( ' ' )  || cch == char( '?' )  )
   {
      return false;
   }
   return true;
}

bool IsText( const char cch )
{
   if ( cch == char( '<' ) || cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool IsTextNoneWS( const char cch )
{
   if ( cch == char( '<' )  || cch == char( '\0' ) || cch == char( '&' )  )
   {
      return false;
   }
   return true;
}

bool IsTextWithWS( const char cch )
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

bool IsAttriName( const char cch )
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

bool IsSingleQuote( const char cch )
{
   if ( cch == char( '\'' ) ||
        cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool IsPureSingleQuote( const char cch )
{
   if ( cch == char( '\'' ) ||
        cch == char( '\0' ) ||
        cch == char( '&' )  )
   {
      return false;
   }
   return true;
}

bool IsDoubleQuote( const char cch )
{
   if ( cch == char( '\"' ) || cch == char( '\0' ) )
   {
      return false;
   }
   return true;
}

bool IsPureDoubleQuote( const char cch )
{
   if ( cch == char( '\"' ) || cch == char( '\0' ) || cch == char( '&' ) )
   {
      return false;
   }
   return true;
}

bool NeedSkip( int SKIP_TYPE, const char cch )
{
   switch( SKIP_TYPE )
   {
   case WHITE_SPACE :
      return IsWhiteSpace( cch );
   case NODE_NAME :
      return IsNameText( cch );
   case TEXT :
      return IsText( cch );
   case TEXT_NONE_WS :
      return IsTextNoneWS( cch );
   case TEXT_WITH_WS :
      return IsTextWithWS( cch );
   case ATTRI_NAME :
      return IsAttriName( cch );
   case SINGLE_QUOTE :
      return IsSingleQuote( cch );
   case PURE_SINGLE_QUOTE :
      return IsPureSingleQuote( cch );
   case DOUBLE_QUOTE :
      return IsDoubleQuote( cch );
   case PURE_DOUBLE_QUOTE :
      return IsPureDoubleQuote( cch );
   default:
      return 0;
   }
}

template<class OutIt>
OutIt printNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent )
{
   switch ( node->GetType() )
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
   for ( IXMLNode* child = node->FirstChild(); child; child = child->NextSibling() )
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
   out = copyChar( node->GetName(), node->GetName() + node->GetNameSize(), out );
   out = printAttribute( out, node );

   if ( node->GetValueSize() == 0 && !node->FirstChild() )
   {
      *out = char( '/' ), ++out;
      *out = char( '>' ), ++out;
   }
   else
   {
      *out = char( '>' ), ++out;

      IXMLNode* child = node->FirstChild();
      if ( !child )
      {
         out = copyAndExpandChar( node->GetValue(), node->GetValue() + node->GetValueSize(), char( 0 ), out );
      }
      else if ( child->NextSibling() == NULL && child->GetType() == XNT_DATA )
      {
         out = copyAndExpandChar( child->GetValue(), child->GetValue() + child->GetValueSize(), char( 0 ), out );
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
      out = copyChar( node->GetName(), node->GetName() + node->GetNameSize(), out );
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
   out = copyAndExpandChar( node->GetValue(), node->GetValue() + node->GetValueSize(), char( 0 ), out );
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
   out = copyChar( node->GetValue(), node->GetValue() + node->GetValueSize(), out );
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
   out = copyChar( node->GetValue(), node->GetValue() + node->GetValueSize(), out );
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
   out = copyChar( node->GetValue(), node->GetValue() + node->GetValueSize(), out );
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
   out = copyChar( node->GetName(), node->GetName() + node->GetNameSize(), out );
   *out = char( ' ' ), ++out;
   out = copyChar( node->GetValue(), node->GetValue() + node->GetValueSize(), out );
   *out = char( '?' ), ++out;
   *out = char( '>' ), ++out;

   return out;
}

template<class OutIt>
OutIt printAttribute( OutIt out, IXMLNode* node )
{
   for ( IXMLAttribute* attri = node->FirstAttribute(); attri; attri = attri->NextAttribute() )
   {
      if ( attri->GetName() && attri->GetValue() )
      {
         *out = char( ' ' ), ++out;
         out = copyChar( attri->GetName(), attri->GetName() + attri->GetNameSize(), out );
         *out = char( '=' ), ++out;
         if ( findChar<char, char( '"' )>( attri->GetValue(), attri->GetValue() + attri->GetValueSize() ) )
         {
            *out = char( '\'' ), ++out;
            out = copyAndExpandChar( attri->GetValue(), attri->GetValue() + attri->GetValueSize(), char( '"' ), out );
            *out = char( '\'' ), ++out;
         }
         else
         {
            *out = char( '"' ), ++out;
            out = copyAndExpandChar( attri->GetValue(), attri->GetValue() + attri->GetValueSize(), char( '\'' ), out );
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

}
