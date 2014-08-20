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
#ifndef _INSPIRE_XML_READER_H_
#define _INSPIRE_XML_READER_H_

#include "XMLUtil.h"

XML_BEGIN

class IXMLDocument;
class IXMLNode;

class XMLReader
{
public:
   XMLReader();
   ~XMLReader();

   bool parse( char* data, IXMLDocument* doc );

   void setParseOptions( int parseOptions )
   {
      _parseOptions = parseOptions;
   }

private:
   void parseBOM( char*& data );
   IXMLNode* parseNode( char*& data );
   IXMLNode* parseDeclaration( char*& data );
   IXMLNode* parseComment( char*& data );
   IXMLNode* parseElement( char*& data );
   IXMLNode* parsePI( char*& data );
   IXMLNode* parseCData( char*& data );
   IXMLNode* parseDoctype( char*& data );

   void parseAttribute( char*& data, IXMLNode* node );
   void parseNodeText( char*& data, IXMLNode* node );
   
   char appendData( IXMLNode* node, char*& data, char* start );

   void skip( int skip_idx, char*& data );

   char* skipAndExpandRefs( int skip_idx_1, int skip_idx_2, int flag, char*& data );
   void insertCodedChar( char*& data, unsigned long code );

private:
   int            _parseOptions;
   IXMLDocument*  _xmlDoc;
};

XML_END
#endif