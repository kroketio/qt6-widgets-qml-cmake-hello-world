SET(CMAKE_OSX_ARCHITECTURES "arm64")
set(ARM ON)
set(ARM_ID "armv8-a")
SET(LLVM_ENABLE_PIC OFF)
SET(LLVM_ENABLE_PIE OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -D_GNU_SOURCE -fvisibility=default -march=armv8-a+crypto -mfix-cortex-a53-835769")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -D_GNU_SOURCE -fvisibility=default -march=armv8-a+crypto -mfix-cortex-a53-835769")

execute_process(COMMAND brew --prefix openssl OUTPUT_VARIABLE OPENSSL_ROOT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND brew --prefix boost OUTPUT_VARIABLE BOOST_ROOT OUTPUT_STRIP_TRAILING_WHITESPACE)

find_library(IOKIT_LIBRARY IOKit)
