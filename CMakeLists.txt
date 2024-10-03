cmake_minimum_required(VERSION 3.28.3...3.28.3)
project(TestRayLib C)
set(CMAKE_C_STANDARD 17)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(EXTERN_DIR "${CMAKE_SOURCE_DIR}/extern")

# exe
file(GLOB_RECURSE src ${SRC_DIR}/*.c ${SRC_DIR}/*.h)
add_executable(${PROJECT_NAME} ${src})

# raylib
target_link_libraries(${PROJECT_NAME} ${EXTERN_DIR}/raylib-5.0_macos/lib/libraylib.a)
target_link_libraries(${PROJECT_NAME} "-framework OpenGL -framework IOKit -framework CoreVideo -framework Cocoa")
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERN_DIR}/raylib-5.0_macos/include)

# raygui
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERN_DIR}/raygui-4.0/src)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERN_DIR}/raygui-4.0/styles)
