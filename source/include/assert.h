#ifndef _UI_INSPIRE_ASSERT_H_
#define _UI_INSPIRE_ASSERT_H_

#define __LOG_WRAPPER( LEVEL, fmt, ... )                       \
do                                                             \
{                                                              \
   inspire::Log( LEVEL, __FUNCTION__,                          \
                 __FILE__, __LINE__, fmt, ##__VA_ARGS__ ) ;    \
} while ( false )

#ifdef _DEBUG
#define INSPIRE_ASSERT( condition, fmt, ... )                  \
do                                                             \
{                                                              \
   if ( !condition )                                           \
   {                                                           \
      inspire::Log( inspire::PRIO_ERROR, __FUNCTION__,         \
                    __FILE__, __LINE__, fmt, ##__VA_ARGS__ ) ; \
      inspire::Panic() ;                                       \
   }                                                           \
} while ( false )
#else
#define INSPIRE_ASSERT( condition, fmt, ... )                  \
do                                                             \
{                                                              \
   if ( !condition )                                           \
   {}                                                          \
} while ( false )
#endif

/*
*@brief useful macro when log
**/
#define LogError( fmt, ... )                                   \
   __LOG_WRAPPER( inspire::PRIO_ERROR, fmt, ##__VA_ARGS__ )

#define LogDebug( fmt, ... )                                   \
   __LOG_WRAPPER( inspire::PRIO_DEBUG, fmt, ##__VA_ARGS__ )

#define LogWarning( fmt, ... )                                 \
   __LOG_WRAPPER( inspire::PRIO_WARNING, fmt, ##__VA_ARGS__ )

#define LogNotice( fmt, ... )                                  \
   __LOG_WRAPPER( inspire::PRIO_NOTICE, fmt, ##__VA_ARGS__ )

#define LogInfo( fmt, ... )                                    \
   __LOG_WRAPPER( inspire::PRIO_INFO, fmt, ##__VA_ARGS__ )

#endif
