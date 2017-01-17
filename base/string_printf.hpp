#pragma once
#include <string>
#include <cstdio>
#include <cstring>
#include <stdarg.h>
namespace base {
namespace {
  inline void StringAppendV(std::string* dst, const char* format, va_list ap) {
    char space[1024];

    va_list backup_ap;
    va_copy(backup_ap, ap);
    int result = vsnprintf(space, sizeof(space), format, backup_ap);
    va_end(backup_ap);

    if ((result >= 0) && (result < static_cast<int>(sizeof(space)))) {
      dst->append(space, result);
      return;
    }

    int length = sizeof(space);
    while (true) {
      if (result < 0) {
        length *= 2;
      } else {
        length = result+1;
      }
      char* buf = new char[length];

      va_copy(backup_ap, ap);
      result = vsnprintf(buf, length, format, backup_ap);
      va_end(backup_ap);

      if ((result >= 0) && (result < length)) {
        // It fit
        dst->append(buf, result);
        delete[] buf;
        return;
      }
      delete[] buf;
    }
  }
}

inline std::string StringPrintf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  std::string result;
  StringAppendV(&result, format, ap);
  va_end(ap);
  return result;
}
}
