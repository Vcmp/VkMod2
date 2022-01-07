
# # Add source to this project's executable.
# add_executable(vulkan_guide
    # main.cpp
   # )


# set_property(TARGET vulkan_guide PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:vulkan_guide>")

# target_include_directories(vulkan_guide PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
# #target_link_libraries(vulkan_guide vkbootstrap vma glm tinyobjloader imgui stb_image)

# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# #set(glfw3_DIR "GLFW_PATH" CACHE PATH "Path to GLFW")

# add_subdirectory(glfw-3.3.6.bin.WIN64)

# target_link_libraries(vulkan_guide Vulkan::Vulkan glfw)

# add_dependencies(vulkan_guide Shaders)
