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
#ifndef _INSPIRE_XML_HELPER_H_
#define _INSPIRE_XML_HELPER_H_

#include "XMLUtil.h"
XML_BEGIN
std::size_t caculateLen( const char* pszString );


bool compareString( const char* first, std::size_t szFirst,
                    const char* second, std::size_t szSecond );

bool isWhiteSpace( const char cch );

bool isNodeName( const char cch );

bool isText( const char cch );

bool isTextWithoutWhitespace( const char cch );

bool isTextWithWhitespace( const char cch );

bool isAttributeName( const char cch );

bool isSingleQuoteData( const char cch );

bool isPureSingleQuoteData( const char cch );

bool isDoubleQuoteData( const char cch );

bool isPureDoubleQuoteData( const char cch );

bool needSkip( int skip_idx, const char cch );

class IXMLNode;
///< print 
template<class OutIt>
OutIt printNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent = 0 );

template<class OutIt>
OutIt printChildNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printElementNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printDataNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printCDataNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printDeclaration( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printCommentNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printDoctypeNode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printPINode( OutIt out, IXMLNode* node, const int WriteFlag, int indent );

template<class OutIt>
OutIt printAttribute( OutIt out, IXMLNode* node );

template<class OutIt>
OutIt copyChar( const char* begin, const char* end, OutIt out );

template<class OutIt>
OutIt copyAndExpandChar( const char* begin, const char* end, char notepand, OutIt out );

template<class OutIt>
OutIt fillChar( OutIt out, int n, const char cch );

template<class Ch, Ch cch>
bool findChar( const char* begin, const char* end );

void toStream( std::basic_ostream<char>& basic_os, IXMLNode* node );

std::ostream& operator<< ( std::ostream& os, IXMLNode* node );

//////////////////////////////////////////////////////////////////////////
//< simple exception

#include <exception>    // For std::exception
#define XML_PARSE_ERROR( what, where ) throw parse_exception( what, where )

class parse_exception : public std::exception
{
public:
   parse_exception( const char* what, void* where ) :
      _what( what ),
      _where( where )
   {
   }

   virtual const char* what() const throw()
   {
      return _what;
   }

   char* where() const
   {
      return reinterpret_cast<char*>( _where );   
   }

private:
   const char* _what;
   void*       _where;
};

XML_END
#endif