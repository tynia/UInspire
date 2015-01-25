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
#include <fstream>
#include "XMLDocument.h"
#include "XMLBuffer.h"
#include "XMLNode.h"
#include "XMLReader.h"
#include "XMLWriter.h"

namespace inspire {

XMLDocument::XMLDocument() : XMLNode( XNT_DOCUMENT ), _filename( NULL ), _data( NULL )
{
   _writer = new XMLWriter();
   _reader = new XMLReader();
   _pool = new XMLBuffer();
}

XMLDocument::~XMLDocument()
{
   _pool->Release();

   if ( _writer )
   {
      delete _writer;
      _writer = NULL;
   }

   if ( _reader )
   {
      delete _reader;
      _reader = NULL;
   }

   if ( _pool )
   {
      delete _pool;
      _pool = NULL;
   }

   if ( _data )
   {
      delete [] _data;
      _data = NULL;
   }

   _filename = NULL;
}

bool XMLDocument::LoadXML( const char* filename )
{
   if ( filename == NULL )
   {
      //SystemError( "filename is NULL..", LOG_END );
      return false;
   }
   _filename = filename;
   _reader->SetParseOptions( PARSE_FULL );
   ReadFile();
   return _reader->Parse( _data, this );
}

void XMLDocument::ReadFile()
{
   std::fstream instream;
   instream.open( _filename, std::fstream::binary | std::fstream::in );
   if ( instream.fail() )
   {
      //SystemError( "cannot find file...", _File, LOG_END );
      return;
   }

   instream.unsetf( std::ios::skipws );
   instream.seekg( 0, std::ios::end );
   std::size_t len = instream.tellg();
   instream.seekg( 0 );

   _data = (char*)_pool->alloc( len + 1);
   instream.read( _data, len );
   _data[len] = '\0';

   instream.close();
}

bool XMLDocument::SaveXML()
{
   bool suc = false;
   std::ofstream outstream;
   outstream.open( _filename, std::ios::out | std::ios::binary );
   if ( !outstream.fail() )
   {
      IXMLDocument* ixmldoc = this;
      suc = _writer->toStream( outstream, ixmldoc );
   }
   outstream.close();
   return suc;
}

IXMLNode* XMLDocument::AllocNode( XMLNodeType nt, const char* name, const char* value )
{
   return _pool->AllocNode( nt, name, value );
}

IXMLAttribute* XMLDocument::AllocAttribute( const char* name, const char* value )
{
   return _pool->AllocAttribute( name, value );
}

char* XMLDocument::AllocString( const char* str )
{
   return _pool->AllocString( str );
}
}
