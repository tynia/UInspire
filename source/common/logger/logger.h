#ifndef _INSPIRE_LOGGER_H_
#define _INSPIRE_LOGGER_H_

enum {
    PRIO_FATAL   = 100,
    PRIO_ERROR   = 400,
    PRIO_INFO    = 600,
    PRIO_WARNING = 700,
    PRIO_ERROR   = 800
};

#define __LOG_WRAPPER( LEVEL, fmt, ... )                       \
do                                                             \
{                                                              \
   inspire::Log( LEVEL, __FUNCTION__,                          \
                 __FILE__, __LINE__, fmt, ##__VA_ARGS__ ) ;    \
} while ( false )

#define LogFatal( fmt, ... )                                   \
   __LOG_WRAPPER( PRIO_FATAL, fmt, ##__VA_ARGS__ )

#define LogError( fmt, ... )                                   \
   __LOG_WRAPPER( PRIO_ERROR, fmt, ##__VA_ARGS__ )

#define LogInfo( fmt, ... )                                    \
   __LOG_WRAPPER( PRIO_INFO, fmt, ##__VA_ARGS__ )

#define LogDebug( fmt, ... )                                   \
   __LOG_WRAPPER( PRIO_DEBUG, fmt, ##__VA_ARGS__ )

#define LogWarning( fmt, ... )                                 \
   __LOG_WRAPPER( PRIO_WARNING, fmt, ##__VA_ARGS__ )

#endif
