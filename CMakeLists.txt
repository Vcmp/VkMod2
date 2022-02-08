# Partially caniballised from vkGuide.net: 


cmake_minimum_required (VERSION 3.22)

project ("VkMod2")

# set(CMAKE_C_COMPILER_TARGET x86_64-windows-gnu)
# set(CMAKE_CXX_COMPILER_TARGET x86_64-windows-gnu)
set(CLANG_DEFAULT_CXX_STDLIB=libc++)
# set(CLANG_DEFAULT_RTLIB=compiler-rt)
# set(CMAKE_EXE_LINKER_FLAGS_INIT "-fuse-ld=lld")
# set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")
# set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set(CLANG 1)
	else()
	set(GCC 1)
endif()

# set(CMAKE_CXX_FLAGS "-std=c++20 -v -march=native -mtune=native -O0 -fuse-ld=lld -g -fverbose-asm -save-temps -masm=intel -Wall -Wextra -pthread -lpthread ")
set(CMAKE_CXX_FLAGS "-std=c++20 -v -march=native -mtune=native -Ofast -ferror-limit=128 -g -fverbose-asm -save-temps -masm=intel -fvisibility=hidden -fno-semantic-interposition -frename-registers -pthread -lpthread ")

find_package(Vulkan REQUIRED)


#add_subdirectory(third_party)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
#include_directories($ENV{VULKAN_SDK}/include)
#add_subdirectory(src)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)
add_subdirectory(glm)
# Add source to this project's executable.

add_executable(VkMod2
	src/main.cpp
	src/VkUtils2.hpp   
	src/renderer2.hpp   
	)
   
   # set_target_properties (VkMod2 PROPERTIES CXX_STANDARD 20)
   # target_compile_options(${PROJECT_NAME} INTERFACE "/Zc:__cplusplus")
   # target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
#set_property(TARGET VkMod2 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:vulkan_guide>")
target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb_image")
# target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm")
# target_include_directories(VkMod2 PUBLIC "$ENV{VULKAN_SDK}/Include")
# target_include_directories("${PROJECT_SOURCE_DIR}/third_party/stb_image" INTERFACE stb_image)
# target_link_libraries(VkMod2 stb_image)


#set(glfw3_DIR "GLFW_PATH" CACHE PATH "Path to GLFW")



target_link_libraries(VkMod2 Vulkan::Vulkan glfw glm)

add_dependencies(VkMod2 Shaders)



find_program(GLSLC glslc HINTS $ENV{VULKAN_SDK}/Bin/)

## TODO: make this recompile shader files if they are changed/do not match checksums instead of having to mnaully delete them each time
file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/shaders/*.comp"
    )

## iterate each shader
foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_SOURCE_DIR}/bin/shaders/${FILE_NAME}.spv")
  message(STATUS ${GLSL})
  ##execute glslang command to compile that specific shader
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSLC} ${GLSL} -O -o ${SPIRV}
    DEPENDS "${PROJECT_SOURCE_DIR}/bin/shaders/")
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )
