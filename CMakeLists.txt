cmake_minimum_required(VERSION 3.17)

project(shell)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/lib/include)

aux_source_directory(src SRC_LIST)

file(GLOB LIB_READLINE ${PROJECT_SOURCE_DIR}/lib/lib/readline/*)

link_directories(${PROJECT_SOURCE_DIR}/lib/lib/readline)

add_executable(shell ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE readline history tinfo)
