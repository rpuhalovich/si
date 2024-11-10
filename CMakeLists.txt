cmake_minimum_required(VERSION 3.28.3...3.28.3)
project(si C)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG -Wall -Wextra -Wpedantic -Werror")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DRELEASE -O3")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")

# exe
file(GLOB_RECURSE src ${SRC_DIR}/*.c ${SRC_DIR}/*.h)
add_executable(${PROJECT_NAME} ${src})

# raylib
target_link_libraries(${PROJECT_NAME} ${EXTERN_DIR}/raylib/lib/libraylib.a)
target_link_libraries(${PROJECT_NAME} "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERN_DIR}/raylib/include)
