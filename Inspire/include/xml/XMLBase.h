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
#ifndef _INSPIRE_XML_BASE_DEFINITION_H_
#define _INSPIRE_XML_BASE_DEFINITION_H_

#include "platform.h"

namespace inspire {

const int PARSE_NO_DATA_NODES             = 0x1;
const int PARSE_NO_VALUE_ELEMENTS         = 0x2;
const int PARSE_NO_STRING_TERMINATORS     = 0x4;
const int PARSE_NO_ENTITY_TRANSLATION     = 0x8;
const int PARSE_NO_UTF8                   = 0x10;
const int PARSE_DECLARATION_NODE          = 0x20;
const int PARSE_COMMENT_NODES             = 0x40;
const int PARSE_DOCTYPE_NODES             = 0x80;
const int PARSE_PI_NODES                  = 0x100;
const int PARSE_VALIDATE_END_TAG          = 0x200;
const int PARSE_TRIM_WHITESPACE           = 0x400;
const int PARSE_NORMALIZE_WHITESPACE      = 0x800;
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
   XNT_DOCUMENT = 0,    ///< 文件类型，没有名字和值
   XNT_ELEMENT,         ///< 元素类型，有名字和值（有属性）
   XNT_DATA,            ///< DATA类型，没有名字，有值
   XNT_CDATA,           ///< CDATA类型，没有名字，有值
   XNT_COMMENT,         ///< 注释类型，没有名字，有注释内容
   XNT_DECLARATION,     ///< 声明类型，没有名字，有属性（版本，编码类型等）
   XNT_DOCTYPE,         ///< DOCTYPE类型，没有名字，有DOCTYPE内容
   XNT_PI,              ///< Processing instruction 执行说明
};

typedef void* ( alloc )( std::size_t size );
typedef void  ( free )( void* ptr );

enum SkipIndex
{
   ESI_WhiteSpace = 0,
   ESI_NodeName,
   ESI_Text,
   ESI_Text_NONE_WS,
   ESI_Text_WS,
   ESI_AttributeName,
   ESI_SingleQuote,
   ESI_PureSingleQuote,
   ESI_DoubleQuote,
   ESI_PureDoubleQuote
};

struct XMLLookupTable
{
   static const unsigned char XMT_Whitespace[256];
   static const unsigned char XMT_Node_Name[256];
   static const unsigned char XMT_Text[256];
   static const unsigned char XMT_Text_With_Whitespace[256];
   static const unsigned char XMT_Text_Without_Whitespace[256];
   static const unsigned char XMT_Attribute_Name[256];
   static const unsigned char XMT_Attribute_Data_1[256];
   static const unsigned char XMT_Attribute_Data_1_Pure[256];
   static const unsigned char XMT_Attribute_Data_2[256];
   static const unsigned char XMT_Attribute_Data_2_Pure[256];
   static const unsigned char XMT_Digits[256];
};

class IXMLNode;
class INSPIRE_EXPORT_API XMLBase
{
public:
   XMLBase();

   XMLBase( const char* name, const char* value );

   virtual ~XMLBase();

   void setName( const char* name, const std::size_t len );

   const char* getName() const;

   const std::size_t getNameSize() const;

   void setValue( const char* value, const std::size_t len );

   const char* getValue() const;

   const std::size_t getValueSize() const;

   void setParent( IXMLNode* node );

   IXMLNode* getParent() const;

protected:
   char*       _name;
   char*       _value;
   std::size_t _nameSize;
   std::size_t _valueSize;
   IXMLNode*   _parent;
};

}

#endif