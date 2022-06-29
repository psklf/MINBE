#include "modules/log/log.h"

#include <stdio.h>
#include <stdarg.h>

#ifdef __ANDROID_API__
#include <android/log.h>
#endif

#if defined(MINBE_OSX) || defined(MINBE_LINUX)
void minbe::log::log_print(const char *format, ...) {
  printf("MINBE::");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n");
}
#endif

#ifdef MINBE_WINDOWS
void minbe::log::log_print(const char *format, ...) {
  printf("MINBE::");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n");
}
#endif


#ifdef __ANDROID_API__
void minbe::log::log_print(const char *format, ...) {
  va_list args;
  va_start(args, format);
  __android_log_vprint(ANDROID_LOG_DEBUG, "MINBE", format, args);
  va_end(args);
}
#endif
