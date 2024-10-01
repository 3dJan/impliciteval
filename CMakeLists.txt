cmake_minimum_required(VERSION 3.10)


if(DEFINED ENV{VCPKG_ROOT} AND NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# Set the project name
project(ImplicitEval)

# Use file globbing to find all .cpp files in the src directory
file(GLOB SOURCES src/*.cpp)

# Find the lib3mf package
find_package(lib3mf REQUIRED)

# Add an executable
add_executable(impliciteval ${SOURCES})

# Link the lib3mf library to the executable
target_link_libraries(impliciteval PRIVATE lib3mf::lib3mf)