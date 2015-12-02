cmake_minimum_required(VERSION 3.3)
project(Testat3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set(CORE_FILES src/Word.cpp src/Word.h src/Kwic.cpp src/Kwic.h)
set(CORE_FILES src/indexableSet.cpp src/indexableSet.h)
set(TEST_FILES test/test.cpp)
set(MAIN_FILES main.cpp)

add_library(${PROJECT_NAME}_lib ${CORE_FILES})

add_executable(${PROJECT_NAME}_main ${MAIN_FILES})
target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_lib)

include_directories("${PROJECT_NAME}_test" src ../cute)
add_executable("${PROJECT_NAME}_test" ${TEST_FILES})
target_link_libraries("${PROJECT_NAME}_test" ${PROJECT_NAME}_lib)
