cmake_minimum_required(VERSION 3.10)
project(c_cli C)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/cli_parser/cli_parser.c
    ${SOURCE_DIR}/shared/logger/logger.c
    ${SOURCE_DIR}/configuration/configuration.c
)

add_executable(c_cli ${SOURCES})

target_include_directories(c_cli PRIVATE
    ${SOURCE_DIR}
    ${SOURCE_DIR}/cli_parser
    ${SOURCE_DIR}/configuration
    ${SOURCE_DIR}/shared
    ${SOURCE_DIR}/shared/logger
)