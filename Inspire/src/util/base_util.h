#ifndef _XDUI_BASE_UTIL_H_
#define _XDUI_BASE_UTIL_H_

#include "xdui_definition.h"
#include "../interface/log/LogHelper.h"

inline void AssertFail( const char* file, const int line, const char* exp )
{
   FILE* fp = fopen( "assert.log", "a" );
   if( fp )
   {
      long cur_size = ftell( fp );
      if( cur_size > ( 1<<30 ) )
      {
         fclose( fp );
         fp = fopen( "assert.log","w" );
      }
      if( fp )
      {
         printf(      "Assertion Failed: File: %s, line: %d\nexpression: %s\n", file, line, exp );
         fprintf( fp, "Assertion Failed: File: %s, line: %d\nexpression: %s\n", file, line, exp );
         fclose( fp );
      }
   }

   __asm int 3;
}

#ifndef LIB_ASSERT
#   ifdef _DEBUG
      #define LIB_ASSERT( exp ) ( int )(  ( exp ) || ( AssertFail( __FILE__, __LINE__, #exp ), 0 )  )
#   else
      #define LIB_ASSERT( exp ) (  ( int ) 1  )
#   endif
#endif

/// assert always even though project under Release!!
#define SYSTEM_ASSERT( exp ) ( int )(  ( exp ) || ( AssertFail( __FILE__, __LINE__, #exp ), 0 )  )

DEFINE_LOG_WRAPPER( KeyInvoke, "SystemLog.log", X_LOG::PRIO_LOG )
DEFINE_LOG_WRAPPER( LogError, "XMLParseLog.log", X_LOG::PRIO_ERROR )
DEFINE_LOG_WRAPPER( SystemError, "SystemLog.log", X_LOG::PRIO_FATAL )

XDUI_CLIENT_BENGIN
enum WndType
{
   EWT_WND = 0,
   EWT_BUTTON,
   EWT_CHECKBOX,
   EWT_EDITBOX,
   EWT_IMAGE,
   EWT_STATICTEXT,
   EWT_COMBOBOX,
   EWT_PROGRESSBAR,
   EWT_RICHEDITBOX,
   EWT_ITEM,
   EWT_LIST,
   EWT_MENU,
   EWT_SCROLLBAR,
   EWT_SLIDER,
   EWT_TREE,
   EWT_CUSTOMWND,
};

struct tagAlign
{
   int x;
   int y;
};
typedef tagAlign CUIAlign;

enum UITile
{
   UIT_TOP_LEFT = 0,
   UIT_TOP_CENTER,
   UIT_TOP_RIGHT,
   UIT_CENTER_LEFT,
   UIT_CENTER_CENTER,
   UIT_CENTER_RIGHT,
   UIT_BOTTOM_LEFT,
   UIT_BOTTOM_CENTER,
   UIT_BOTTOM_RIGHT,

   UIT_COUNT,
};

typedef struct tagResourceData
{
   bool _ImageResource;
   std::string _ResourceID;
   std::string tagTileResourceData[UIT_COUNT];
} CUIResourceData;

enum TiledMode
{
   ETM_NULL = 0,
   ETM_VERTICAL_HEAD_TAIL,  ///< 竖直三段拼接
   ETM_HIRIZON_HEAD_TAIL,   ///< 水平三段拼接
};

inline const _tchar* GetClassNameFromWndClass( WndType wc )
{
   switch ( wc )
   {
   case EWT_WND :
      return L"Window";
   case EWT_BUTTON :
      return L"Button";
   case EWT_CHECKBOX :
      return L"CheckBox";
   case EWT_EDITBOX :
      return L"EditBox";
   case EWT_IMAGE :
      return L"Image";
   case EWT_STATICTEXT :
      return L"StaticText";
   case EWT_COMBOBOX :
      return L"ComboBox";
   case EWT_PROGRESSBAR :
      return L"ProgressBar";
   case EWT_RICHEDITBOX :
      return L"RichEditBox";
   case EWT_ITEM :
      return L"Item";
   case EWT_LIST :
      return L"List";
   case EWT_MENU :
      return L"Menu";
   case EWT_SCROLLBAR :
      return L"ScrollBar";
   case EWT_SLIDER :
      return L"Slider";
   case EWT_CUSTOMWND :
      return L"CustomWnd";
   default:
      return L"Error";
   }
}

inline std::string ItoA( int i )
{
   char buff[32];
   sprintf( buff, "%d", i );
   return buff;
}

typedef long long int64;
typedef unsigned long long uint64;

inline std::string ItoA(  int64 i  )
{
   char buf[64] = { 0 };

#ifndef _IN_WINDOWS_32_PLATFORM_
   sprintf(  buf, "%I64d", i  );
#else
   sprintf(  buf, "%lld", i  );
#endif

   return buf;
}

XDUI_CLIENT_END
#endif