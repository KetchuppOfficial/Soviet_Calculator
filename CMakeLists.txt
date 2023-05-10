project(teachable_dictionary)
cmake_minimum_required (VERSION 3.22.1 FATAL_ERROR)

set (PROJECT_NAME teachable_dictionary)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)

set(TEACHABLE_DICTIONARY_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TEACHABLE_DICTIONARY_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/teachable_dictionary.cpp)

set(PROGRAM_NAME dictionary_manager)
set(MAIN_PROGRAM_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PROJECT_PARRENT_PATH)

include_directories (include hash_table/include work_with_byte_files/include ${PROJECT_PARRENT_PATH}/queue/list/include)
add_definitions(-DPROJECT_DIR_PATH=\"${CMAKE_SOURCE_DIR}\")

add_library (${PROJECT_NAME} STATIC ${TEACHABLE_DICTIONARY_SOURCE})
add_subdirectory (work_with_byte_files)
target_link_libraries (${PROJECT_NAME} PUBLIC work_with_bytes)

add_compile_options(-g -Wall -pthread)

#main
add_executable (${PROGRAM_NAME} ${MAIN_PROGRAM_SOURCE})
target_link_libraries (${PROGRAM_NAME} PUBLIC ${PROJECT_NAME})

add_custom_target (run_${PROGRAM_NAME} 
    COMMENT "Running " ${PROGRAM_NAME}
    COMMAND ./${PROGRAM_NAME}
)
add_dependencies (run_${PROGRAM_NAME} ${PROGRAM_NAME})


#clang-tidy
option(CLANG_TIDY "Include clang-tidy" OFF)
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message (clang-tidy " from " ${CMAKE_SOURCE_DIR}/.clang-tidy)
    
    set (CMAKE_CXX_CLANG_TIDY
        "clang-tidy;-format-style=file:${CMAKE_SOURCE_DIR}/.clang-tidy;-checks=*"
    )
endif()

#clang-format
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    message (clang-format " from " ${CMAKE_SOURCE_DIR}/.clang-format)

    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
    add_custom_target(
        clang_format
        COMMAND clang-format
        -i
        -style=file:${CMAKE_SOURCE_DIR}/.clang-format
        ${ALL_SOURCE_FILES}
    )
endif()

#sanitizers
option(ADD_SANITIZERS "Build with sanitizers" ON)
if (ADD_SANITIZERS)
    message ("Build with sanitizers")

    add_compile_options (-fsanitize=address -fsanitize=undefined)
    set_target_properties (${PROJECT_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    set_target_properties (${PROGRAM_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif ()

add_subdirectory (tests)
add_subdirectory (hash_table)
