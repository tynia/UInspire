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
#include <fstream>
#include "XMLDocument.h"
#include "XMLBufferPool.h"
#include "XMLNode.h"
#include "XMLReader.h"
#include "XMLWriter.h"

namespace inspire {

XMLDocument::XMLDocument() : XMLNode( XNT_DOCUMENT ), _filename( NULL ), _data( NULL )
{
   _writer = new XMLWriter();
   _reader = new XMLReader();
   _pool = new XMLBufferPool();
}

XMLDocument::~XMLDocument()
{
   _pool->release();

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

bool XMLDocument::load( const char* filename )
{
   if ( filename == NULL )
   {
      //SystemError( "filename is NULL..", LOG_END );
      return false;
   }
   _filename = filename;
   _reader->setParseOptions( PARSE_FULL );
   readFile();
   return _reader->parse( _data, this );
}

void XMLDocument::readFile()
{
   std::fstream instream;
   instream.open( _filename, std::fstream::binary | std::fstream::in );
   if ( instream.fail() )
   {
      //SystemError( "cannot find file...", _File, LOG_END );
      return;
   }

   instream.unsetf( ios::skipws );
   instream.seekg( 0, ios::end );
   std::size_t len = instream.tellg();
   instream.seekg( 0 );

   _data = (char*)_pool->alloc( len + 1);
   instream.read( _data, len );
   _data[len] = '\0';

   instream.close();
}

bool XMLDocument::save()
{
   bool suc = false;
   std::ofstream outstream;
   outstream.open( _filename, ios::out | ios::binary );
   if ( !outstream.fail() )
   {
      IXMLDocument* ixmldoc = this;
      suc = _writer->toStream( outstream, ixmldoc/*this*/ );
   }
   outstream.close();
   return suc;
}

IXMLNode* XMLDocument::allocNode( XMLNodeType nt, const char* name/* = NULL*/, const char* value/* = NULL*/ )
{
   return _pool->allocNode( nt, name, value );
}

IXMLAttribute* XMLDocument::allocAttribute( const char* name/* = NULL*/, const char* value/* = NULL*/ )
{
   return _pool->allocAttribute( name, value );
}

char* XMLDocument::allocString( const char* str )
{
   return _pool->allocString( str );
}
}
