cmake_minimum_required(VERSION 3.10)

project(shell)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(include)

aux_source_directory(src SRC_LIST)

add_executable(shell ${SRC_LIST})