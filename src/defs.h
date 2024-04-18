#ifndef DEFS_H
#define DEFS_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ASSERT(_e, ...)                                                        \
  if (!(_e)) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

// -----------------------------
// DEFINITIONS
// -----------------------------
// constants
#define PI 3.14159265
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)

// float
typedef float f32;
typedef double f64;

// int
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// size
typedef size_t usize;
typedef ssize_t isize;

// vectors
typedef struct v2f_s {
  f32 x, y;
} v2f;
typedef struct v2i_s {
  i32 x, y;
} v2i;

typedef struct v3f_s {
  f32 x, y, z;
} v3f;
typedef struct v3i_s {
  i32 x, y, z;
} v3i;

typedef struct v4f_s {
  f32 x, y, z, w;
} v4f;
typedef struct v4i_s {
  i32 x, y, z, w;
} v4i;

// -----------------------------
// MATH
// -----------------------------
#define min(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a), _b = (b);                                          \
    _a < _b ? _a : _b;                                                         \
  })

#define max(a, b)                                                              \
  ({                                                                           \
    __typeof__(a) _a = (a), _b = (b);                                          \
    _a > _b ? _a : _b;                                                         \
  })

#define clamp(x, mi, ma) (min(max(x, mi), ma))

// geometry
#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_r) ((_r) * (180.0f / PI))

// -----------------------------
// VECTOR
// -----------------------------

// vec2 format
#define V2F_FMT "{ %f, %f }"
#define V2I_FMT "{ %d, %d }"
#define V2_MEMS(v) (v).x, (v).y

// vec2 conversion
#define v2f_to_v2i(v)                                                          \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    (v2i){_v.x, _v.y};                                                         \
  })

#define v2i_to_v2f(v)                                                          \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    (v2f){_v.x, _v.y};                                                         \
  })

// vec2 math
#define v2_add(v0, v1)                                                         \
  ({                                                                           \
    const __typeof__(v0) _v0 = (v0);                                           \
    const __typeof__(v1) _v1 = (v1);                                           \
    (v2f){(_v0.x + _v1.x), (_v0.y + _v1.y)};                                   \
  })

#define v2_dot(v0, v1)                                                         \
  ({                                                                           \
    const __typeof__(v0) _v0 = (v0);                                           \
    const __typeof__(v1) _v1 = (v1);                                           \
    (_v0.x * _v1.x) + (_v0.y * _v1.y);                                         \
  })

#define v2_length(v)                                                           \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    sqrtf(v2_dot(_v, _v));                                                     \
  })

#define v2_normalize(v)                                                        \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    const f32 length = v2_length(_v);                                          \
    (__typeof__(_v)){_v.x / length, _v.y / length};                            \
  })

#define v2_scale(v, m)                                                         \
  ({                                                                           \
    const __typeof__(v) _v = (v);                                              \
    const f32 _m = (m);                                                        \
    (v2f){_m * _v.x, _m * _v.y};                                               \
  })

// vec3 format
#define V3F_FMT "{ %f, %f, %f }"
#define V3I_FMT "{ %d, %d, %d }"
#define V3_MEMS(v) (v).x, (v).y, (v).z

// vec3 conversions
#define v3f_to_v3i(v)                                                          \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    (v3i){_v.x, _v.y, _v.z};                                                   \
  })

#define v3i_to_v3f(v)                                                          \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    (v3f){_v.x, _v.y, _v.z};                                                   \
  })

// vec3 math
#define v3_add(v0, v1)                                                         \
  ({                                                                           \
    const __typeof__(v0) _v0 = (v0);                                           \
    const __typeof__(v1) _v1 = (v1);                                           \
    (v3f){(_v0.x + _v1.x), (_v0.y + _v1.y), (_v0.z + _v1.z)};                  \
  })

#define v3_dot(v0, v1)                                                         \
  ({                                                                           \
    const __typeof__(v0) _v0 = (v0);                                           \
    const __typeof__(v1) _v1 = (v1);                                           \
    (_v0.x * _v1.x) + (_v0.y * _v1.y) + (_v0.z * _v1.z);                       \
  })

#define v3_length(v)                                                           \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    sqrtf(v3_dot(_v, _v));                                                     \
  })

#define v3_normalize(v)                                                        \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    const f32 length = v3_length(_v);                                          \
    (__typeof__(_v)){_v.x / length, _v.y / length, _v.z / length};             \
  })

#define v3_scale(v, m)                                                         \
  ({                                                                           \
    const __typeof__(v) _v = (v);                                              \
    const f32 _m = (m);                                                        \
    (v3f){_m * _v.x, _m * _v.y, _m * _v.z};                                    \
  })

// vec4 format
#define V4F_FMT "{ %f, %f, %f, %f }"
#define V4I_FMT "{ %d, %d, %d, %d }"
#define V4_MEMS(v) (v).x, (v).y, (v).z, (v).w

// vec4 conversions
#define v4f_to_v4i(v)                                                          \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    (v4i){_v.x, _v.y, _v.z, _v.w};                                             \
  })

#define v4i_to_v4f(v)                                                          \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    (v4f){_v.x, _v.y, _v.z, _v.w};                                             \
  })

// vec4 math
#define v4_add(v0, v1)                                                         \
  ({                                                                           \
    const __typeof__(v0) _v0 = (v0);                                           \
    const __typeof__(v1) _v1 = (v1);                                           \
    (v4f){(_v0.x + _v1.x), (_v0.y + _v1.y), (_v0.z + _v1.z), (v0.w + _v1.w)};  \
  })

#define v4_dot(v0, v1)                                                         \
  ({                                                                           \
    const __typeof__(v0) _v0 = (v0);                                           \
    const __typeof__(v1) _v1 = (v1);                                           \
    (_v0.x * _v1.x) + (_v0.y * _v1.y) + (_v0.z * _v1.z) + (_v0.w * _v1.w);     \
  })

#define v4_length(v)                                                           \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    sqrtf(v4_dot(_v, _v));                                                     \
  })

#define v4_normalize(v)                                                        \
  ({                                                                           \
    __typeof__(v) _v = (v);                                                    \
    const f32 length = v4_length(_v);                                          \
    (__typeof__(_v)){(_v.x / length), (_v.y / length), (_v.z / length),        \
                     (_v.w / length)};                                         \
  })

#define v4_scale(v, m)                                                         \
  ({                                                                           \
    const __typeof__(v) _v = (v);                                              \
    const f32 _m = (m);                                                        \
    (v4f){_m * _v.x, _m * _v.y, _m * _v.z};                                    \
  })

#endif /* DEFS_H */
