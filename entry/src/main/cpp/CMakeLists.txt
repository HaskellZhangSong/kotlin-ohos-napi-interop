# the minimum version of CMake.
cmake_minimum_required(VERSION 3.5.0)
project(KNTest)

set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(entry SHARED napi_init.cpp)

add_library(dynamic SHARED IMPORTED)
set_target_properties(dynamic
    PROPERTIES
    IMPORTED_LOCATION ${NATIVERENDER_ROOT_PATH}/libs/libdynamic.so)

target_link_libraries(entry PUBLIC libace_napi.z.so)
target_link_directories(entry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs)
target_link_libraries(entry PUBLIC dynamic libhilog_ndk.z.so)
