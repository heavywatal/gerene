execute_process(
  COMMAND git describe --always --dirty
  OUTPUT_VARIABLE GIT_DESCRIBE
  ERROR_QUIET
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(GIT_DESCRIBE)
  set(PROJECT_VERSION ${GIT_DESCRIBE})
endif()
message(STATUS "PROJECT_VERSION: ${PROJECT_VERSION}")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/config.cpp.in
  ${CMAKE_CURRENT_SOURCE_DIR}/config.cpp @ONLY
)

cmake_policy(SET CMP0076 NEW)
target_sources(${PROJECT_NAME} PRIVATE
  config.cpp
  gene.cpp
  individual.cpp
  population.cpp
  program.cpp
)
