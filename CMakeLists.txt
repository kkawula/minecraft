cmake_minimum_required(VERSION 3.27)
set(project_name "minecraft")

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)


add_executable(${project_name} main.cpp)


target_link_libraries(${project_name} PRIVATE glm::glm)
target_link_libraries(${project_name} PRIVATE glfw)

