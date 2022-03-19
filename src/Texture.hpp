#pragma once

// #include "Buffers.hpp"
#include "Buffers.hpp"

#include <cstdint>

inline namespace Texture
{
  static constinit VkImage        vkImage;
  static constinit VkDeviceMemory vkAllocMemory;
  static VkFormat                 findDepthFormat();
  static void                     createImage( VkExtent2D, VkFormat, VkImageUsageFlagBits );
  static void                     transitionImageLayout( VkFormat, VkImageLayout, VkImageLayout );
  static void                     createImageView( VkFormat, VkImageAspectFlagBits, VkImageLayout );
};  // namespace Texture
