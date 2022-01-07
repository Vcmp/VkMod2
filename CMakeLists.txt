# CMakeList.txt : CMake project for vulkan_guide, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.17)

project ("VkMod2")

set(-std=c++20 -v -march=native -mtune=native -fverbose-asm -save-temps -masm=intel -fuse-ld -Wall -Wextra -pthread -lpthread)

find_package(Vulkan REQUIRED)

add_subdirectory(third_party)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#add_subdirectory(src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw-3.3.6)
# Add source to this project's executable.

add_executable(VkMod2
    src/main.cpp
   )

#set_property(TARGET VkMod2 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:vulkan_guide>")

target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
#target_link_libraries(vulkan_guide vkbootstrap vma glm tinyobjloader imgui stb_image)


#set(glfw3_DIR "GLFW_PATH" CACHE PATH "Path to GLFW")



target_link_libraries(VkMod2 Vulkan::Vulkan glfw)

add_dependencies(VkMod2 Shaders)



find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

## find all the shader files under the shaders folder
file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/shaders/*.comp"
    )

## iterate each shader
foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILE_NAME}.spv")
  message(STATUS ${GLSL})
  ##execute glslang command to compile that specific shader
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )
