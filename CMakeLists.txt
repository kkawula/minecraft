cmake_minimum_required(VERSION 3.22)
set(project_name "minecraft")
project(${project_name})

set(VCPKG_ROOT_DIR "./vcpkg")
# Below variable should determine the target platform by itself, but it doesn't work sometimes, so choose yours.
set(VCPKG_TARGET_TRIPLET "x64-osx")
#set(VCPKG_TARGET_TRIPLET "x64-windows")
#set(VCPKG_TARGET_TRIPLET "x64-linux")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/share/glm")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/share/opengl")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/share/glad")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/share/glfw3")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/share/glew")


find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)


set(SOURCE_FILES
        src/main.cpp
        src/window/window.cpp
        src/config.h
        src/world/Block.h
        src/world/BlockType.h
        src/world/Block.cpp
)

add_executable(${project_name} ${SOURCE_FILES})

target_include_directories(${project_name} PRIVATE
        ${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/include
)

target_link_directories(${project_name} PRIVATE
        ${VCPKG_ROOT_DIR}/installed/${VCPKG_TARGET_TRIPLET}/lib
)

target_link_libraries(${project_name} PRIVATE OpenGL::GL)
target_link_libraries(${project_name} PRIVATE glm::glm)
target_link_libraries(${project_name} PRIVATE glfw)
target_link_libraries(${project_name} PRIVATE glad)
target_link_libraries(${project_name} PRIVATE GLEW::GLEW)



