# Partially caniballised from vkGuide.net: 


cmake_minimum_required (VERSION 3.22)

project ("VkMod2")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
#include_directories($ENV{VULKAN_SDK}/include)
#add_subdirectory(src)
set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR VK_NO_PROTOTYPES GLFW_INCLUDE_NONE)

# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_CXX_20 ON CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_SIMD_AVX ON CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_SIMD_AVX2 ON CACHE BOOL "" FORCE)

add_executable(VkMod2 "")

message(STATUS "${CMAKE_CXX_COMPILE_FEATURES}")
message(STATUS "${CMAKE_C_COMPILE_FEATURES}")
target_compile_features(VkMod2 PRIVATE cxx_std_23)
target_compile_features(VkMod2 PRIVATE c_std_23)
# set(CMAKE_CXX_FLAGS "-std=c++20 -v -march=native -mtune=native -O0 -fuse-ld=lld -g -fverbose-asm -save-temps -masm=intel -Wall -Wextra -pthread -lpthread ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -march=native -mtune=native -Ofast -fverbose-asm -save-temps -masm=intel -ftime-trace -fvisibility=hidden -fno-semantic-interposition -pthread -lpthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT} -std=c2x -ftime-trace ${CMAKE_CXX_FLAGS}")


# Add source to this project's executable.

	target_sources(VkMod2 
		PRIVATE 
			"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	)  

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw EXCLUDE_FROM_ALL)
add_subdirectory(glm EXCLUDE_FROM_ALL)
add_subdirectory(volk EXCLUDE_FROM_ALL)
# add_subdirectory(sleef EXCLUDE_FROM_ALL)
	
target_link_libraries(VkMod2 PRIVATE volk glfw glm)

# add_dependencies(VkMod2 Shaders)


# find_package(Vulkan REQUIRED)

#add_subdirectory(third_party)


   
   # set_target_properties (VkMod2 PROPERTIES CXX_STANDARD 20)
   # target_compile_options(${PROJECT_NAME} INTERFACE "/Zc:__cplusplus")
   # target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
#set_property(TARGET VkMod2 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:vulkan_guide>")
# target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb_image")
# target_include_directories(VkMod2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm")
# target_include_directories(VkMod2 PUBLIC "$ENV{VULKAN_SDK}/Include")
# target_include_directories("${PROJECT_SOURCE_DIR}/third_party/stb_image" INTERFACE stb_image)
# target_link_libraries(VkMod2 stb_image)


#set(glfw3_DIR "GLFW_PATH" CACHE PATH "Path to GLFW")






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
