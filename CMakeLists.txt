cmake_minimum_required(VERSION 3.5)

project(project1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")

include_directories(
  include
)

add_executable(
  ${PROJECT_NAME}
  src/main.c
  src/cbmp.c
)

add_executable(
  decode
  src/decode.c
  src/cbmp.c
)