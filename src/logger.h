#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>
#include <stdlib.h>

#define MAX_BUF 1024

#define ASSERT(_e, ...)                                                        \
  if (!(_e)) {                                                                 \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  }

typedef enum { DEBUG, INFO, WARNING, ERROR } LOG_LEVEL;

void logger_init(LOG_LEVEL base_level, char *base_fpath);
void logger_log(LOG_LEVEL log_level, const char *log_fname, const size_t line,
                const char *fmt, ...);
void logger_deinit(void);

#define DEB(...) logger_log(DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG(...) logger_log(INFO, __FILE__, __LINE__, __VA_ARGS__)
#define WARN(...) logger_log(WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define ERR(...) logger_log(ERROR, __FILE__, __LINE__, __VA_ARGS__)

#endif /* LOGGER_H */
