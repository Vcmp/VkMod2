#pragma once

#include <volk.h>


//https://old.reddit.com/r/vulkan/comments/tr5gl0/new_vulkan_extension_for_reducing_draw_time/

#ifndef VK_EXT_graphics_pipeline_library
constexpr auto VK_EXT_graphics_pipeline_library = 1;
constexpr auto VK_EXT_GRAPHICS_PIPELINE_LIBRARY_SPEC_VERSION               = 1;
constexpr auto VK_EXT_GRAPHICS_PIPELINE_LIBRARY_EXTENSION_NAME            =  "VK_EXT_graphics_pipeline_library";
constexpr auto VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_FEATURES_EXT =(static_cast<VkStructureType>(1000320000));
constexpr auto VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GRAPHICS_PIPELINE_LIBRARY_PROPERTIES_EXT =(static_cast<VkStructureType>(1000320001));
constexpr auto VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_LIBRARY_CREATE_INFO_EXT  =(static_cast<VkStructureType>(1000320002));
constexpr auto VK_PIPELINE_CREATE_RETAIN_LINK_TIME_OPTIMIZATION_INFO_BIT_EXT =(static_cast<VkPipelineCreateFlagBits>(0x00800000));
constexpr auto VK_PIPELINE_CREATE_LINK_TIME_OPTIMIZATION_BIT_EXT            =(static_cast<VkPipelineCreateFlagBits>(0x00000400));
#define VK_PIPELINE_LAYOUT_CREATE_INDEPENDENT_SETS_BIT_EXT           =((VkPipelineLayoutCreateFlagBits)0x00000002);

 constexpr struct VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT {
    VkStructureType                       sType;
    const void*                           pNext;
    VkBool32                              graphicsPipelineLibrary;
} __attribute__((aligned(16))) __attribute__((packed)) VkPhysicalDeviceGraphicsPipelineLibraryFeaturesEXT{};

typedef struct VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT {
    VkStructureType                       sType;
    const void*                           pNext;
    VkBool32                              graphicsPipelineLibraryFastLinking;
    VkBool32                              graphicsPipelineLibraryIndependentInterpolationDecoration;
} VkPhysicalDeviceGraphicsPipelineLibraryPropertiesEXT;

typedef VkFlags VkGraphicsPipelineLibraryFlagsEXT;

typedef struct VkGraphicsPipelineLibraryCreateInfoEXT {
    VkStructureType                       sType;
    const void*                           pNext;
    VkGraphicsPipelineLibraryFlagsEXT     flags;
} __attribute__((aligned(16))) __attribute__((packed)) VkGraphicsPipelineLibraryCreateInfoEXT;

typedef enum VkGraphicsPipelineLibraryFlagBitsEXT {
    VK_GRAPHICS_PIPELINE_LIBRARY_VERTEX_INPUT_INTERFACE_BIT_EXT = 0x00000001,
    VK_GRAPHICS_PIPELINE_LIBRARY_PRE_RASTERIZATION_SHADERS_BIT_EXT = 0x00000002,
    VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_SHADER_BIT_EXT = 0x00000004,
    VK_GRAPHICS_PIPELINE_LIBRARY_FRAGMENT_OUTPUT_INTERFACE_BIT_EXT = 0x00000008,
    VK_GRAPHICS_PIPELINE_LIBRARY_FLAG_BITS_MAX_ENUM_EXT = 0x7FFFFFFF
} VkGraphicsPipelineLibraryFlagBitsEXT;

typedef enum VkPipelineLayoutCreateFlagBits {
    VK_PIPELINE_LAYOUT_CREATE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
} VkPipelineLayoutCreateFlagBits;
#endif  /* !defined(VK_EXT_graphics_pipeline_library) */