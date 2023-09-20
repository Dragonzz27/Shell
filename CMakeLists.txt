cmake_minimum_required(VERSION 3.16)

project(shell)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/lib/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

link_directories(${PROJECT_SOURCE_DIR}/lib/lib/readline)

add_executable(shell ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE readline history tinfo)
