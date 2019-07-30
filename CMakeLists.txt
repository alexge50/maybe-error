cmake_minimum_required(VERSION 3.8)
project(MaybeError)

set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

add_library(MaybeError INTERFACE)
target_include_directories(
        MaybeError INTERFACE
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)

install(
        TARGETS MaybeError
        EXPORT MaybeError-config)

install(
        EXPORT MaybeError-config
        NAMESPACE alx::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MaybeError)

install(
        DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/)