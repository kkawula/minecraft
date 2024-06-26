cmake_minimum_required(VERSION 3.22)
set(project_name "minecraft")
project(${project_name})


set(VCPKG_ROOT_DIR "./vcpkg")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(VCPKG_TARGET_TRIPLET "x64-windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(VCPKG_TARGET_TRIPLET "x64-linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(VCPKG_TARGET_TRIPLET "x64-osx")
else()
    message(FATAL_ERROR "Unsupported operating system: ${CMAKE_SYSTEM_NAME}")
endif()

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
        src/libs/stb_image.h
        src/utils/Texture.cpp
        src/utils/VertexArray.h
        src/utils/VertexBuffer.h
        src/Window.cpp
        src/Window.h
        src/render/Renderer.cpp
        src/render/Renderer.h
        src/world/World.cpp
        src/world/World.h
        src/world/Block.cpp
        src/world/Block.h
        src/world/Chunk.h
        src/mesh/Mesh.cpp
        src/config.h
        src/render/ChunkRenderer.cpp
        src/render/ChunkRenderer.h
        src/mesh/ChunkMeshGenerator.cpp
        src/mesh/ChunkMeshGenerator.h
        src/mesh/MeshAtlas.h
        src/utils/FileSystem.cpp
        src/utils/FileSystem.h
        src/ChunkManager.cpp
        src/ChunkManager.h
        src/physics/AABB.h
        src/physics/AABB.h
        src/Entity.h
        src/player/Player.cpp
        src/player/Player.h
        src/input/Keyboard.cpp
        src/input/Keyboard.h
        src/input/Mouse.cpp
        src/input/Mouse.h

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

set(SHADER_DIR "${CMAKE_SOURCE_DIR}/src/res/shaders")
set(TEXTURE_DIR "${CMAKE_SOURCE_DIR}/src/res/images")

set(RESOURCE_OUTPUT_DIR "${CMAKE_BINARY_DIR}/res")

add_custom_command(
        TARGET ${project_name} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} "${RESOURCE_OUTPUT_DIR}/shaders"
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${TEXTURE_DIR} "${RESOURCE_OUTPUT_DIR}/images"
        COMMENT "Copying resources to build directory"
)


if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ADDITIONAL_LIB_1_SRC "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/debug/bin/glfw3.dll")
    set(ADDITIONAL_LIB_2_SRC "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows/debug/bin/glew32d.dll")
    set(ADDITIONAL_FILE_DST "${CMAKE_BINARY_DIR}")

    add_custom_command(
            TARGET ${project_name} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${ADDITIONAL_LIB_1_SRC} ${ADDITIONAL_FILE_DST}
            COMMAND ${CMAKE_COMMAND} -E copy ${ADDITIONAL_LIB_2_SRC} ${ADDITIONAL_FILE_DST}
            COMMENT "Copying additional file for Windows"
    )
endif()