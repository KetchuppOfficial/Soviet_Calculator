project(commands)
cmake_minimum_required (VERSION 3.22.1 FATAL_ERROR)

set (PROJECT_NAME commands)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER clang++)

set(PROGRAM_NAME commands)
set(SOURCE_TEST ${CMAKE_CURRENT_SOURCE_DIR}/commands/tests/commands_tests.cpp)

add_library (memory STATIC ${CMAKE_CURRENT_SOURCE_DIR}/memory/src/memory.cpp)
include_directories(memory/include)
add_library (${PROJECT_NAME} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/commands/src/commands.cpp)
target_link_libraries (${PROJECT_NAME} PUBLIC memory)

add_compile_options(-g -Wall -pthread)

#tests
option(TESTING "Include testing" ON)
if (TESTING)
    message ("Include " ${PROJECT_NAME} " testing")

    find_package (GTest REQUIRED)
    include_directories (${GTEST_INCLUDE_DIRS})

    include_directories(${PROJECT_NAME}/include)
    add_executable (${PROJECT_NAME}_tests ${SOURCE_TEST})
    
    if (ADD_SANITIZERS)
        set_target_properties (${PROJECT_NAME}_tests PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    endif()
    
    target_link_libraries (${PROJECT_NAME}_tests PUBLIC GTest::GTest GTest::Main ${PROJECT_NAME})
       
    enable_testing ()

    add_custom_target (run_${PROJECT_NAME}_tests 
        COMMENT "Running " ${PROJECT_NAME} "_tests"
        COMMAND ./${PROJECT_NAME}_tests
    )
    add_dependencies (run_${PROJECT_NAME}_tests ${PROJECT_NAME}_tests)
endif ()

#sanitizers
option(ADD_SANITIZERS "Build with sanitizers" ON)
if (ADD_SANITIZERS)
    message ("Build with sanitizers")

    add_compile_options (-fsanitize=address -fsanitize=undefined)
    set_target_properties (${PROJECT_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    set_target_properties (memory PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
    set_target_properties (${PROGRAM_NAME} PROPERTIES LINK_FLAGS "-fsanitize=address -fsanitize=undefined")
endif ()
