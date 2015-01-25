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
#ifndef _INSPIRE_XML_DOCUMENT_H_
#define _INSPIRE_XML_DOCUMENT_H_

#include "IXMLDocument.h"
#include "XMLNode.h"

namespace inspire {

class XMLBuffer;
class XMLWriter;
class XMLReader;
class IXMLAttribute;
class IXMLNode;

class XMLDocument : public XMLNode, public IXMLDocument
{
   friend std::ostream& operator<< ( std::ostream& os, IXMLNode* node );
public:
   XMLDocument();
   virtual ~XMLDocument();

   virtual const char* GetFileName() const
   {
      return _filename;
   }

   virtual bool LoadXML( const char* filename );
   virtual bool SaveXML();

   virtual IXMLNode* AllocNode( XMLNodeType nt, const char* name = NULL, const char* value = NULL );
   virtual IXMLAttribute* AllocAttribute( const char* name = NULL, const char* value = NULL );
   virtual char* AllocString( const char* str );

private:
   void ReadFile();

private:
   XMLBuffer*  _pool;
   XMLWriter*  _writer;
   XMLReader*  _reader;
   const char* _filename;
   char*       _data;
};

}
#endif