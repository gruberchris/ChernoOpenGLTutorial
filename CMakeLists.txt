cmake_minimum_required(VERSION 3.10)

# Set the project name and specify C++ as the language
project(ChernoOpenGLTutorial LANGUAGES CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get environment variables
set(GLFW_INCLUDE_DIRS $ENV{GLFW_INCLUDE_DIRS})
set(GLFW_LIBRARIES $ENV{GLFW_LIBRARIES})
set(GLEW_INCLUDE_DIRS $ENV{GLEW_INCLUDE_DIRS})
set(GLEW_LIBRARIES $ENV{GLEW_LIBRARIES})

# Print environment variables for debugging
message(STATUS "GLFW_INCLUDE_DIRS = ${GLFW_INCLUDE_DIRS}")
message(STATUS "GLFW_LIBRARIES = ${GLFW_LIBRARIES}")
message(STATUS "GLEW_INCLUDE_DIRS = ${GLEW_INCLUDE_DIRS}")
message(STATUS "GLEW_LIBRARIES = ${GLEW_LIBRARIES}")

# Collect all source files in src directory
file(GLOB SOURCE_FILES "src/*.cpp" "src/glad.c")

# Include directories from environment variables
include_directories(
        $ENV{GLFW_INCLUDE_DIRS}
        $ENV{GLEW_INCLUDE_DIRS}
)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link GLFW library from environment variable
target_link_libraries(${PROJECT_NAME}
        $ENV{GLFW_LIBRARIES}/libglfw.3.dylib
        $ENV{GLEW_LIBRARIES}/libGLEW.2.2.0.dylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
)

# Set compiler flags for macOS ARM64
if(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
endif()

# Copy the shaders directory to the output directory
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)
