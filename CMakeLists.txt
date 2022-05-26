# Partially caniballised from vkGuide.net: 


cmake_minimum_required (VERSION 3.22)

project ("VkMod2")
# set(CMAKE_C_COMPILER_TARGET x86_64-w64-windows-gnu)
# set(CMAKE_CXX_COMPILER_TARGET x86_64-w64-windows-gnu)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set (CMAKE_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
#include_directories($ENV{VULKAN_SDK}/include)
#add_subdirectory(src)
set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR VK_NO_PROTOTYPES GLFW_INCLUDE_NONE TRACY_IMPORTS TRACY_ENABLE)

# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_CXX_20 ON CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_SIMD_AVX ON CACHE BOOL "" FORCE)
# set(GLM_TEST_ENABLE_SIMD_AVX2 ON CACHE BOOL "" FORCE)
# add_subdirectory(brcxxc ENABLE_EXPORTS)
add_executable(VkMod2)
target_link_options(VkMod2 PRIVATE -fsanitize=address,undefined -glldb)
message(STATUS "${CMAKE_CXX_COMPILE_FEATURES}")
message(STATUS "${CMAKE_C_COMPILE_FEATURES}")
target_compile_features(VkMod2 PRIVATE cxx_std_20)
target_compile_features(VkMod2 PRIVATE c_std_23)
# target_compile_definitions(VkMod2 PUBLIC VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR VK_NO_PROTOTYPES GLFW_INCLUDE_NONE TRACY_IMPORTS TRACY_ENABLE )
target_compile_options(VkMod2 PRIVATE -march=native -mtune=native -save-temps -masm=intel -glldb -fsanitize=address,undefined -Ofast -Wuninitialized -Weffc++)
# set(CMAKE_CXX_FLAGS "-std=c++20 -v -march=native -mtune=native -O0 -fuse-ld=lld -g -fverbose-asm -save-temps -masm=intel -Wall -Wextra -pthread -lpthread ")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_INIT} -march=native -mtune=native -Ofast -fno-plt -fmerge-all-constants -fno-exceptions -save-temps -masm=intel -fpic -fvisibility=hidden -pthread -lpthread")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_INIT} -std=c2x ${CMAKE_CXX_FLAGS}")
message(STATUS ${CMAKE_CXX_FLAGS_INIT})
message(STATUS ${CMAKE_CXX_FLAGS})
# Add source to this project's executable.
	target_sources(VkMod2 
		PRIVATE 
			"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Pipeline2.hpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/src/test.inl"
			# "${CMAKE_CURRENT_SOURCE_DIR}/src/ShaderSPIRVUtils.cpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/src/VkUtilsXBase.hpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/src/VkDev.hpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/src/Buffers.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Vks.tpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/tst.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Swapchain.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer2.hpp"
			# # "${CMAKE_CURRENT_SOURCE_DIR}/src/textTemp.cpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/src/VkUtils2.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/mat4.cpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/shaders/21_shader_ubo.frag"
			# "${CMAKE_CURRENT_SOURCE_DIR}/shaders/21_shader_ubo.vert"
			# "${CMAKE_CURRENT_SOURCE_DIR}/tracy/TracyClient.cpp"
			# "${CMAKE_CURRENT_SOURCE_DIR}/tracy/Tracy.hpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/fakeFBO.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/main2.cpp"
	)  


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_CXX_20 ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX2 ON CACHE BOOL "" FORCE)

include_directories(shaders)
add_subdirectory(glfw EXCLUDE_FROM_ALL)
add_subdirectory(glm EXCLUDE_FROM_ALL)
add_subdirectory(volk EXCLUDE_FROM_ALL)
# add_subdirectory(Tracy)
# add_subdirectory(sleef)
# add_subdirectory(brcxxc EXCLUDE_FROM_ALL)
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
# target_include_directories("${PROJECT_CURRENT_SOURCE_DIR}/third_party/stb_image" INTERFACE stb_image)
# target_link_libraries(VkMod2 stb_image)


#set(glfw3_DIR "GLFW_PATH" CACHE PATH "Path to GLFW")



message(STATUS ${CMAKE_COMMAND})

## TODO: make this recompile shader files if they are changed/do not match checksums instead of having to mnaully delete them each time
# file(GLOB_RECURSE GLSL_SOURCE_FILES
    # "${PROJECT_CURRENT_SOURCE_DIR}/shaders/*.frag"
    # "${PROJECT_CURRENT_SOURCE_DIR}/shaders/*.vert"
    # "${PROJECT_CURRENT_SOURCE_DIR}/shaders/*.comp"
    # )
function(Dump2 temp name)
	file(READ ${temp} content)
	set(content "unsigned int constexpr ${name}[] = ${content};")
	file(WRITE ${temp}.inl "${content}")
		
endfunction(Dump2)

## this function  is horribly broken and has multiple issues including:
	# not being able to enumertae files dynamically 
	# 
	# and failing to run before the formatting fixes are applied
	#
	# Implict depends is pointed to the .txt files and not the .hpp files,  
	# 		however the custom command cannot be run before the final .hpp files are created/generated 
	# 	    and custom commands cannot include CMake function and only command line output/commands
	# 	    this causes the build prcoes to fail unless a dummy .temp file is included beforehand and tehfore is not fit for purpose unelss this is fixed completely
	# 	an adiitonal isue that can ocur is that often the file is not egnerated in time before the compielr is called, causin a mising include compilation error to be incurred
	#	the current methdo to fix this is to generate the Cmakecache then run the build generator (e.g. Ninja) and then run Cmake again to finsh/compleet teh Cache before running teh final Build again
	find_program(GLSLC glslc)
function(CompileShaders SHADER name)
set(current-shader-path "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER}")
set(current-output-path "${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER}.inl")
	execute_process(
		COMMAND ${GLSLC} ${current-shader-path} -mfmt=c -O -o -
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
		OUTPUT_VARIABLE w
	)
	# file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER}.inl "${content}")
	
	# file(READ ${current-output-path} content)
	set(content "unsigned int constexpr ${name}[] = ${w};")
	file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/src/${SHADER}.inl "${content}")
	target_sources(VkMod2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/${SHADER}.inl")
endfunction(CompileShaders)

CompileShaders(21_shader_ubo.frag frag)
CompileShaders(21_shader_ubo.vert vert)
CompileShaders(shader_tempTst.vert vert2)
CompileShaders(shader_tempTst.frag frag2)
# Dump2(${CMAKE_CURRENT_SOURCE_DIR}/src/21_shader_ubo.frag.txt frag)
# Dump2(${CMAKE_CURRENT_SOURCE_DIR}/src/21_shader_ubo.vert.txt vert)
add_custom_target(
    Shaders 
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/21_shader_ubo.frag" "${CMAKE_CURRENT_SOURCE_DIR}/src/21_shader_ubo.vert"
    )
	
# Dump2()