cmake_minimum_required(VERSION 3.22)
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/cmake")
project(hello
  VERSION "1.0.0"
  DESCRIPTION "hello world"
  LANGUAGES CXX
)
message(STATUS "Initiating compile using CMake ${CMAKE_VERSION}")  # add cmake/ directory as cmake module path

option(STATIC "Link libraries statically, requires static Qt" OFF)
if(STATIC)
    include(platform_static)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_VERBOSE_MAKEFILE on)
set(THREADS_PREFER_PTHREAD_FLAG ON)
include(FindCcache)
include(functions)

find_package(Git)
find_package(Threads)
find_package(PNG REQUIRED)

# CMake build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  message(STATUS "Setting default build type: ${CMAKE_BUILD_TYPE}")
endif()
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_LOWER)

# OpenSSL
if(APPLE AND NOT OPENSSL_ROOT_DIR)
    execute_process(COMMAND brew --prefix openssl OUTPUT_VARIABLE OPENSSL_ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()
find_package(OpenSSL REQUIRED)
message(STATUS "OpenSSL: Version ${OPENSSL_VERSION}")
message(STATUS "OpenSSL: include dir at ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL: libraries at ${OPENSSL_LIBRARIES} ${OPENSSL_SSL_LIBRARIES}")

add_subdirectory(src)

set_target_properties(hello PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS hello EXPORT HelloTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/hello/
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/hello/
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/hello/)

print_cmake_summary()