
#ifndef TCPRELAY_UTILS_MACROS_H_
#define TCPRELAY_UTILS_MACROS_H_

#include <stddef.h>  // For size_t.
#include <string.h>  // For memcpy.

#include <errno.h>  // For errno.

#define ALLOW_UNUSED __attribute__((unused))

#define COMPILE_ASSERT(expr, msg) \
  typedef CompileAssert<(bool(expr))> msg[bool(expr) ? 1 : -1] ALLOW_UNUSED

template<typename T>
inline void ignore_result(const T&) {
}

template <typename T, size_t N>
char (&ArraySizeHelper(T (&array)[N]))[N];

#define arraysize(array) (sizeof(ArraySizeHelper(array)))

#define HANDLE_EINTR(x) ({ \
  typeof(x) eintr_wrapper_result; \
  do { \
    eintr_wrapper_result = (x); \
  } while (eintr_wrapper_result == -1 && errno == EINTR); \
  eintr_wrapper_result; \
})

#define IGNORE_EINTR(x) ({ \
  typeof(x) eintr_wrapper_result; \
  do { \
    eintr_wrapper_result = (x); \
    if (eintr_wrapper_result == -1 && errno == EINTR) { \
      eintr_wrapper_result = 0; \
    } \
  } while (0); \
  eintr_wrapper_result; \
})

#endif

