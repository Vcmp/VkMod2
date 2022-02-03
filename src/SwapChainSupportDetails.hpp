
#pragma once
#include "Queues.hpp"


inline namespace SwapChainSupportDetails {
static inline VkSurfaceCapabilitiesKHR capabilities{};

static inline VkImageLayout depthImageView;
static inline VkSwapchainKHR swapChain;
static inline uint32_t count;

static inline VkFormat swapChainImageFormat;
static inline VkImageView swapChainImageViews[Frames];
static inline VkRenderPass renderPass;
static inline VkExtent2D swapChainExtent;
static inline VkImage swapchainImages[Frames];
static inline VkFramebuffer swapChainFramebuffers[Frames];

inline uint32_t clamp(uint32_t min, uint32_t max, uint32_t value) {
  const uint32_t a = (max < value ? max : value);
  return (min > a ? min : a);
}
inline VkExtent2D chooseSwapExtent()
// todo: May not Detect Acutal Extent Correctly"
{
  if (capabilities.currentExtent.width != 0xFFFFFFFF) {
    return capabilities.currentExtent;
  }

  VkExtent2D actualExtent = {width, height};

  VkExtent2D minExtent = capabilities.minImageExtent;
  VkExtent2D maxExtent = capabilities.maxImageExtent;

  actualExtent.width =
      clamp(minExtent.width, maxExtent.width, actualExtent.width);
  actualExtent.height =
      clamp(minExtent.height, maxExtent.height, actualExtent.height);

  return actualExtent;
}

inline VkPresentModeKHR
chooseSwapPresentMode(const VkPresentModeKHR *availablePresentModes) {

  for (uint32_t i = 0; i < count; i++) {
    if (availablePresentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
      return availablePresentModes[i];
    }
  }

  return VK_PRESENT_MODE_FIFO_KHR;
}

inline VkSurfaceFormatKHR
chooseSwapSurfaceFormat(const VkSurfaceFormatKHR *formats) {

  {

    for (uint32_t i = 0; i < count; i++) {
      if (formats[i].format == VK_FORMAT_B8G8R8A8_SRGB &&
          formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
        return formats[i];
      }
    }
  }

  throw std::runtime_error("------------");
}

inline void querySwapChainSupport(VkSurfaceFormatKHR *formats,
                                  VkPresentModeKHR *presentModes) {

  if (count != 0) {
    vkGetPhysicalDeviceSurfaceFormatsKHR(Queues::physicalDevice, Queues::surface, &count,
                                         formats);
  }

  vkGetPhysicalDeviceSurfacePresentModesKHR(Queues::physicalDevice, Queues::surface, &count,
                                            nullptr);

  if (count != 0) {
    vkGetPhysicalDeviceSurfacePresentModesKHR(Queues::physicalDevice, Queues::surface, &count,
                                              presentModes);
  }
}

inline void createSwapChain() {
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Queues::physicalDevice, Queues::surface,
                                            &capabilities);

  vkGetPhysicalDeviceSurfaceFormatsKHR(Queues::physicalDevice, Queues::surface, &count,
                                       nullptr);
  VkSurfaceFormatKHR surfaceFormats[count];

  if (count != 0)
    vkGetPhysicalDeviceSurfaceFormatsKHR(Queues::physicalDevice, Queues::surface, &count,
                                         surfaceFormats);

  vkGetPhysicalDeviceSurfacePresentModesKHR(Queues::physicalDevice, Queues::surface, &count,
                                            nullptr);
  VkPresentModeKHR presentModes[count];
  if (count != 0)
    vkGetPhysicalDeviceSurfacePresentModesKHR(Queues::physicalDevice, Queues::surface, &count,
                                              presentModes);

  VkSurfaceFormatKHR surfaceFormat;
  for (const VkSurfaceFormatKHR &surfaceFormat1 : surfaceFormats) {
    if (surfaceFormat1.format == VK_FORMAT_B8G8R8A8_SRGB &&
        surfaceFormat1.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      surfaceFormat = surfaceFormat1;
      break;
    }
  }
  VkPresentModeKHR presentMode;
  for (const VkPresentModeKHR &presentMode1 : presentModes) {
    if (presentMode1 == VK_PRESENT_MODE_IMMEDIATE_KHR) {
      presentMode = presentMode1;
      break;
    } else
      presentMode = VK_PRESENT_MODE_FIFO_KHR;
  }

  // return VK_PRESENT_MODE_FIFO_KHR;

  VkExtent2D extent = SwapChainSupportDetails::chooseSwapExtent();
  uint32_t imageCount =
      (SwapChainSupportDetails::capabilities.minImageCount + 1);

  if (SwapChainSupportDetails::capabilities.maxImageCount > 0 &&
      imageCount > SwapChainSupportDetails::capabilities.maxImageCount) {
    imageCount = SwapChainSupportDetails::capabilities.maxImageCount;
  }

  std::cout << "ImageCount: " << imageCount << "\n";

  const uint32_t aa[] = {Queues::graphicsFamily, Queues::presentFamily};
  ;

  const VkSwapchainCreateInfoKHR createInfo{

      .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext = nullptr,
      .surface = Queues::surface,

      // Image settings
      .minImageCount = imageCount,
      .imageFormat = surfaceFormat.format,
      .imageColorSpace = surfaceFormat.colorSpace,
      .imageExtent = extent,
      .imageArrayLayers = 1,
      .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

      // if (graphicsFamily != presentFamily) {
      //     .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      //     .queueFamilyIndexCount = 2,
      //     .pQueueFamilyIndices = aa,
      // } else {
      .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      // .queueFamilyIndexCount = 0; // Optiona,
      // .pQueueFamilyIndices = nullptr; // Optiona,
      // }

      .preTransform = SwapChainSupportDetails::capabilities.currentTransform,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode = presentMode,
      .clipped = true,

      .oldSwapchain = VK_NULL_HANDLE};
  std::cout << device << "\n";

  // vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
  // auto xx=PFN_vkVoidFunction(swapChain);
  checkCall(vkCreateSwapchainKHR(
      device, &createInfo, nullptr,
      &swapChain));

  // checkCall(vkGetSwapchainImagesKHR(device, swapChain, &imageCount,
  // nullptr));

  // if(imageCount!=Frames)
  // {
  //     throw std::runtime_error("Swapchains not equal to allocated length: Bad
  //     SwapChain");
  // }
  checkCall(
      vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapchainImages));
  SwapChainSupportDetails::swapChainImageFormat = surfaceFormat.format;
  SwapChainSupportDetails::swapChainExtent = extent;
}

inline void createImageViews() {
  std::cout << ("Creating Image Views") << "\n";
  int i = 0;
  for (const VkImage &swapchainImage : swapchainImages) {
    VkImageViewCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = swapChainImageFormat;

    //     createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    // createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    // createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    //     createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    createInfo.image = swapchainImage;

    clPPPI(&createInfo, "vkCreateImageView",
           &SwapChainSupportDetails::swapChainImageViews
               [i++]); // BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
  }
}

inline void createFramebuffers() {
 
  VkFramebufferCreateInfo framebufferCreateInfo = {};
  framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferCreateInfo.renderPass = renderPass;
  framebufferCreateInfo.width = swapChainExtent.width;
  framebufferCreateInfo.height = swapChainExtent.height;
  framebufferCreateInfo.layers = 1;

  framebufferCreateInfo.attachmentCount =
      1; //(framebufferCreateInfo.address(), (attachments).remaining());
         //    framebufferCreateInfo.pAttachments= swapChainImageViews;
  for (size_t i = 0; i < Frames; i++) {
    
    framebufferCreateInfo.pAttachments = &swapChainImageViews[i];
   

    clPPPI(&framebufferCreateInfo, "vkCreateFramebuffer",
           &swapChainFramebuffers[i]);
  }
 
}

}; 
