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
#ifndef _INSPIRE_XML_BASE_DEFINITION_H_
#define _INSPIRE_XML_BASE_DEFINITION_H_

#include "platform.h"

namespace inspire {

const int PARSE_NO_DATA_NODES             = 0x00000001 << 0;
const int PARSE_NO_VALUE_ELEMENTS         = 0x00000001 << 1;
const int PARSE_NO_STRING_TERMINATORS     = 0x00000001 << 3;
const int PARSE_NO_ENTITY_TRANSLATION     = 0x00000001 << 4;
const int PARSE_NO_UTF8                   = 0x00000001 << 5;
const int PARSE_DECLARATION_NODE          = 0x00000001 << 6;
const int PARSE_COMMENT_NODES             = 0x00000001 << 7;
const int PARSE_DOCTYPE_NODES             = 0x00000001 << 8;
const int PARSE_PI_NODES                  = 0x00000001 << 9;
const int PARSE_VALIDATE_END_TAG          = 0x00000001 << 10;
const int PARSE_TRIM_WHITESPACE           = 0x00000001 << 11;
const int PARSE_NORMALIZE_WHITESPACE      = 0x00000001 << 12;
const int PARSE_DEFAULT                   = 0;
const int PARSE_FASTEST                   = PARSE_NO_STRING_TERMINATORS |
                                            PARSE_NO_ENTITY_TRANSLATION |
                                            PARSE_NO_DATA_NODES;

const int PARSE_DESTRUCTIVE               = PARSE_NO_STRING_TERMINATORS |
                                            PARSE_NO_ENTITY_TRANSLATION;

const int PARSE_FULL                      = PARSE_DECLARATION_NODE |
                                            PARSE_COMMENT_NODES |
                                            PARSE_DOCTYPE_NODES |
                                            PARSE_PI_NODES |
                                            PARSE_VALIDATE_END_TAG;

const int PRINT_NO_INDENTING              = 0x1;
const int PRINT_DEFAULT                   = 0;

enum XMLNodeType
{
   XNT_DOCUMENT = 0,
   XNT_ELEMENT,
   XNT_DATA,
   XNT_CDATA,
   XNT_COMMENT,
   XNT_DECLARATION,
   XNT_DOCTYPE,
   XNT_PI,
};

enum XMLSkipType
{
   WHITE_SPACE = 0,
   NODE_NAME,
   TEXT,
   TEXT_NONE_WS,
   TEXT_WITH_WS,
   ATTRI_NAME,
   SINGLE_QUOTE,
   PURE_SINGLE_QUOTE,
   DOUBLE_QUOTE,
   PURE_DOUBLE_QUOTE
};

struct XML
{
   static const unsigned char DIGITAL[256];
};

class IXMLNode;
class INSPIRE_EXPORT_API XMLBase
{
public:
   XMLBase();

   XMLBase( const char* name, const char* value );

   virtual ~XMLBase();

   void SetName( const char* name, const std::size_t len );

   const char* GetName() const;

   const std::size_t GetNameSize() const;

   void SetValue( const char* value, const std::size_t len );

   const char* GetValue() const;

   const std::size_t GetValueSize() const;

   void SetParent( IXMLNode* node );

   IXMLNode* GetParent() const;

protected:
   char*       _name;
   char*       _value;
   std::size_t _nameSize;
   std::size_t _valueSize;
   IXMLNode*   _parent;
};

}

#endif