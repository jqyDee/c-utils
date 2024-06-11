#include "logger.h"

#define LOGGER_TEST_PATH "./test.log"

// TODO: Write defs.h test

static int logger_test_level() {
  DEB("level: %d", DEBUG);
  LOG("level: %d", INFO);
  WARN("level: %d", WARNING);
  ERR("level: %d", ERROR);
  return 0;
}

static int logger_tests() {
  while (1) {
    for (int i = DEBUG; i <= ERROR; i++) {
      logger_init(i, LOGGER_TEST_PATH);
      logger_test_level();
      logger_deinit();
    }
  }
  return 0;
}

int main() {
  logger_tests();
  return 0;
}
