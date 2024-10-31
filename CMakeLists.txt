cmake_minimum_required(VERSION 3.15)
project(gerene
  VERSION 0.1.0
  LANGUAGES CXX)

cmake_policy(SET CMP0169 OLD)  # 3.28
set(CMAKE_VERBOSE_MAKEFILE ON)
include(CMakePrintHelpers)
include(GNUInstallDirs)
cmake_print_variables(CMAKE_INSTALL_PREFIX)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
cmake_print_variables(CMAKE_BUILD_TYPE)
set(CMAKE_CXX_FLAGS_DEV "-O2 -g")

set(CMAKE_INSTALL_NAME_DIR ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

find_package(wtl 0.9.1)
find_package(clippson 0.8.8)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_subdirectory(src)

target_compile_options(${PROJECT_NAME} INTERFACE
  -Wall -Wextra -pedantic
  $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},x86_64>:-march=native>
  $<$<STREQUAL:${CMAKE_SYSTEM_PROCESSOR},arm64>:-march=armv8.3-a+sha3>
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE wtl::wtl clippson::clippson)

option(BUILD_EXECUTABLE "Build executable file" ON)
if(BUILD_EXECUTABLE)
  add_executable(${PROJECT_NAME}-exe src/main.cpp)
  target_link_libraries(${PROJECT_NAME}-exe PRIVATE ${PROJECT_NAME} wtl::wtl)
  find_package(ZLIB)
  if(ZLIB_FOUND)
    target_compile_definitions(${PROJECT_NAME}-exe PRIVATE ZLIB_FOUND)
    target_link_libraries(${PROJECT_NAME}-exe PRIVATE ZLIB::ZLIB)
  endif()
  set_target_properties(${PROJECT_NAME}-exe PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
  )
  install(TARGETS ${PROJECT_NAME}-exe)
endif()

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-config
)
install(DIRECTORY src/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.hpp"
)

set(config_destination ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}-config
  DESTINATION ${config_destination}
  NAMESPACE ${PROJECT_NAME}::
)

set(version_file ${PROJECT_NAME}-config-version.cmake)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${version_file}
  COMPATIBILITY AnyNewerVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${version_file}
  DESTINATION ${config_destination}
)

include(CTest)
if(BUILD_TESTING AND ${CMAKE_SOURCE_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
  add_subdirectory(test)
endif()
