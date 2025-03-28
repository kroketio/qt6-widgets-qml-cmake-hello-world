include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

function(print_cmake_summary)
    message(STATUS "====== SUMMARY")
    message(STATUS "[+] ${CMAKE_PROJECT_NAME} VERSION: ${CMAKE_PROJECT_VERSION}")
    if(STATIC)
        message(STATUS "[+] STATIC: yes")
    else()
        message(STATUS "[+] STATIC: no")
    endif()
    message(STATUS "[+] arch: ${ARCH_ID}")

    if(GIT_FOUND)
        execute_process(COMMAND git rev-parse "HEAD" WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE GIT_HEAD OUTPUT_STRIP_TRAILING_WHITESPACE)
        execute_process(COMMAND git rev-parse --abbrev-ref HEAD WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE GIT_BRANCH OUTPUT_STRIP_TRAILING_WHITESPACE)
        message(STATUS "[+] Git")
        message(STATUS "  - head: ${GIT_HEAD}")
        message(STATUS "  - branch: ${GIT_BRANCH}")
    endif()

    message(STATUS "[+] PNG")
    message(STATUS "  - include: ${PNG_INCLUDE_DIR}")
    message(STATUS "  - libs: ${PNG_LIBRARIES}")

    message(STATUS "[+] OpenSSL")
    message(STATUS "  - version: ${OPENSSL_VERSION}")
    message(STATUS "  - include: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "  - libs: ${OPENSSL_LIBRARIES}")

#    message(STATUS "[+] Boost")
#    message(STATUS "  - version: ${Boost_VERSION}")
#    message(STATUS "  - dirs: ${Boost_INCLUDE_DIRS}")
#    message(STATUS "  - libs: ${Boost_LIBRARIES}")

    if(C_SECURITY_FLAGS)
        message(STATUS "C security hardening flags: ${C_SECURITY_FLAGS}")
    endif()
    if(CXX_SECURITY_FLAGS)
        message(STATUS "C++ security hardening flags: ${CXX_SECURITY_FLAGS}")
    endif()
    if(LD_SECURITY_FLAGS)
        message(STATUS "linker security hardening flags: ${LD_SECURITY_FLAGS}")
    endif()
endfunction()

macro(install_with_directory)
    set(optionsArgs "")
    set(oneValueArgs "DESTINATION")
    set(multiValueArgs "FILES")
    cmake_parse_arguments(CAS "${optionsArgs}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    foreach(FILE ${CAS_FILES})
        get_filename_component(DIR ${FILE} DIRECTORY)
        INSTALL(FILES ${FILE} DESTINATION ${CAS_DESTINATION}/${DIR})
    endforeach()
endmacro(install_with_directory)

function(set_arch_id)
    # possible values: amd64, x86, aarch64
    set(_ARCH_ID ${CMAKE_SYSTEM_PROCESSOR})
    string(TOLOWER ${_ARCH_ID} _ARCH_ID)

    if(_ARCH_ID STREQUAL "x86_64")
        set(_ARCH_ID "amd64")
    elseif(_ARCH_ID STREQUAL "i386")
        set(_ARCH_ID "x86")
    elseif(_ARCH_ID STREQUAL "aarch64")
        set(_ARCH_ID "arm64")
    endif()

    #set_property(GLOBAL PROPERTY ARCH_ID "${_ARCH_ID}")
    set(ARCH_ID ${_ARCH_ID} PARENT_SCOPE)
endfunction()