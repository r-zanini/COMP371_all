cmake_minimum_required(VERSION 3.8)

project(capsule01) # The name of your choice for the project comes here

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH
        /encs # For ENCS lab computers
        /opt/local # Macports
        )

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED
        #    HINTS /encs/pkg/glfw-3.3.4/root # ENCS installation of glfw
        HINTS "C:/Program Files (x86)/GLFW/lib/cmake/glfw3"
        )

# NOTE: ENCS glm installation is missing links to *.inl files so we need this line
#include_directories(/encs/pkg/glm-0.9.9.8/root/include)
include_directories("D:/Tools/GLM/glm")
include_directories("C:/Program Files (x86)/glew/include/")

add_executable(${PROJECT_NAME} capsule01.cpp) #The name of the cpp file and its path can vary

target_link_libraries(${PROJECT_NAME} OpenGL::GL "C:/Program Files (x86)/glew/lib/libglew32d.lib" glfw)
