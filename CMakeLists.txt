cmake_minimum_required(VERSION 3.8)

project(Soviet_Calculator
        LANGUAGES CXX)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(INCLUDE_DIR ${PROJECT_BINARY_DIR}/../include)
aux_source_directory(src SRC_LIST)

add_executable(calc ${SRC_LIST})

find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    # and for each of your dependent executable/library targets:
    target_link_libraries(calc
                          PRIVATE ${wxWidgets_LIBRARIES}
                          PRIVATE m)
endif()

target_include_directories(calc
                           PRIVATE ${INCLUDE_DIR})
