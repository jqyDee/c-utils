cmake_minimum_required(VERSION 3.10)

project(
  c-utils
  VERSION 1.0.1
  DESCRIPTION "Matti Fischbach c-utils")

set(SOURCES src/logger.c src/vulkan.c)
set(HEADERS utils/logger.h utils/defs.h utils/vulkan.h)

include(GNUInstallDirs)

find_package(Vulkan REQUIRED)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
                                                 PUBLIC_HEADER utils/utils.h)

target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE utils ${Vulkan_INCLUDE_DIRS})

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/utils)

# add_executable(tests tests/test.c ${SOURCES}) target_include_directories(tests
# PRIVATE include) target_compile_options(tests PRIVATE -v -Wall -Wextra)
