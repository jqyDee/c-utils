#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// OFF      =  -1
// DEBUG    =   0
// INFO     =   1
// WARNING  =   2
// ERROR    =   3
static int active_level = -1;

// if NULL: no file logging (Default)
static char *logfile_path = NULL;

static const char *LOG_LEVEL_STRINGS[4] = {
    "[DEBUG]",
    "[LOG]",
    "[WARNING]",
    "[ERROR]",
};

static void add_time_to_string(char *string) {
  // add time
  time_t rawtime;
  struct tm *timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(string, sizeof(char *) * MAX_BUF, "[%H:%M:%S]", timeinfo);
}

static void add_info_to_string(char *string, LOG_LEVEL log_level,
                               const char *log_fname, const size_t line) {
  // add level
  strcat(string, LOG_LEVEL_STRINGS[log_level]);

  // add filename and linenumber
  size_t size = snprintf(NULL, 0, "[%s:%zu]", log_fname, line);
  char src[size + 1];
  snprintf(src, size + 1, "[%s:%zu]", log_fname, line);
  strcat(string, src);
}

static void add_frmt_to_string(char *string, const char *fmt, va_list fargv) {
  // add fmt
  size_t size = snprintf(NULL, 0, fmt, fargv);
  char src[size + 1];
  vsnprintf(src, size + 1, fmt, fargv);
  strcat(string, src);

  // add newline to end
  if (string[strlen(string) - 1] != '\n') {
    strcat(string, "\n");
  }
}

void logger_log(LOG_LEVEL log_level, const char *log_fname, const size_t line,
                const char *fmt, ...) {
  ASSERT(active_level != -1, "error: logger not initialized\n");
  if ((int)log_level < active_level)
    return;

  char string[MAX_BUF] = {0};
  va_list fargv;
  va_start(fargv, fmt);

  add_time_to_string(string);
  add_info_to_string(string, log_level, log_fname, line);
  add_frmt_to_string(string, fmt, fargv);

  // init terminal ptr
  FILE *tptr = stdout;
  if (log_level == ERROR) {
    tptr = stderr;
  }
  // output to stdout/stderr
  fprintf(tptr, "%s", string);

  // init file ptr
  if (logfile_path) {
    FILE *fptr = fopen(logfile_path, "a");
    ASSERT(fptr, "error: couldn't open log file\n")
    // output to file
    fprintf(fptr, "%s", string);
    fclose(fptr);
  }
}

void logger_init(LOG_LEVEL base_level, char *base_fpath) {
  ASSERT(active_level == -1, "error; logger can only be initialized once\n");

  active_level = base_level;
  if (base_fpath != NULL) {
    logfile_path = base_fpath;
  }
}

void logger_deinit(void) {
  ASSERT(active_level != -1, "error: no Logger initialized\n")
  WARN("logger deinitialized");

  active_level = -1;
  logfile_path = NULL;
}
