cmake_minimum_required(VERSION 3.10)
project(c_cli C)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES
    ${SOURCE_DIR}/main.c
    ${SOURCE_DIR}/cli_parser/cli_parser.c
    ${SOURCE_DIR}/shared/logger/logger.c
    ${SOURCE_DIR}/configuration/configuration.c
    ${SOURCE_DIR}/file_operations/f_collect/f_collect.c
    ${SOURCE_DIR}/file_operations/f_data/f_data.c
    ${SOURCE_DIR}/file_operations/f_collect/f_matcher/f_matcher.c
    ${SOURCE_DIR}/file_operations/f_collect/f_matcher/f_matcher_regex/f_m_regex.c
    ${SOURCE_DIR}/file_operations/f_collect/f_matcher/f_matcher_extension/f_m_extension.c
    ${SOURCE_DIR}/configuration/module_handler.c
    ${SOURCE_DIR}/file_operations/f_xml/f_xml_accessor.c
)
find_package(LibXml2)

add_executable(c_cli ${SOURCES})
target_link_libraries(c_cli PRIVATE regex)
if(LibXml2_FOUND)
    target_link_libraries(c_cli PRIVATE LibXml2::LibXml2)
endif()

target_include_directories(c_cli PRIVATE
    ${SOURCE_DIR}
    ${SOURCE_DIR}/cli_parser
    ${SOURCE_DIR}/configuration
    ${SOURCE_DIR}/shared
    ${SOURCE_DIR}/shared/logger
    ${SOURCE_DIR}/file_operations/f_collect
    ${SOURCE_DIR}/file_operations/f_data
    ${SOURCE_DIR}/file_operations/f_collect/f_matcher
    ${SOURCE_DIR}/file_operations/f_collect/f_matcher/f_matcher_regex
    ${SOURCE_DIR}/file_operations/f_collect/f_matcher/f_matcher_extension
    ${SOURCE_DIR}/file_operations/f_xml
)