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
#ifndef _INSPIRE_XML_READER_H_
#define _INSPIRE_XML_READER_H_

#include "platform.h"

namespace inspire {

class IXMLDocument;
class IXMLNode;

class XMLReader
{
public:
   XMLReader();
   ~XMLReader();

   bool Parse( char* data, IXMLDocument* doc );

   void SetParseOptions( int parseOptions )
   {
      _parseOptions = parseOptions;
   }

private:
   void ParseBOM( char*& data );
   IXMLNode* ParseNode( char*& data );
   IXMLNode* ParseDeclaration( char*& data );
   IXMLNode* ParseComment( char*& data );
   IXMLNode* ParseElement( char*& data );
   IXMLNode* ParsePI( char*& data );
   IXMLNode* ParseCData( char*& data );
   IXMLNode* ParseDoctype( char*& data );

   void ParseAttribute( char*& data, IXMLNode* node );
   void ParseNodeText( char*& data, IXMLNode* node );
   
   char AppendData( IXMLNode* node, char*& data, char* start );

   void Skip( int SKIP_TYPE, char*& data );

   char* SkipAndExpandRefs( int SKIP_TYPE_1, int SKIP_TYPE_2, int flag, char*& data );
   void InsertCodedChar( char*& data, unsigned long code );

private:
   int            _parseOptions;
   IXMLDocument*  _xmlDoc;
};

}
#endif