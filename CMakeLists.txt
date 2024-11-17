cmake_minimum_required(VERSION 3.28.3...3.28.3)
project(si C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DRELEASE -O3")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")

# exe
file(GLOB_RECURSE src ${SRC_DIR}/*.c ${SRC_DIR}/*.h)
add_executable(${PROJECT_NAME} ${src})

# google test
include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/b514bdc898e2951020cbdca1304b75f5950d1f59.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

file(GLOB_RECURSE test_files ${TEST_DIR}/*.cc)
add_executable(app_tests ${test_files})
target_link_libraries(app_tests GTest::gtest_main)
target_include_directories(app_tests PUBLIC ${SRC_DIR})

include(GoogleTest)
gtest_discover_tests(app_tests)

# raylib
target_link_libraries(${PROJECT_NAME} ${EXTERN_DIR}/raylib/lib/libraylib.a)
target_link_libraries(${PROJECT_NAME} "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERN_DIR}/raylib/include)

target_link_libraries(app_tests ${EXTERN_DIR}/raylib/lib/libraylib.a)
target_link_libraries(app_tests "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
target_include_directories(app_tests PUBLIC ${EXTERN_DIR}/raylib/include)
