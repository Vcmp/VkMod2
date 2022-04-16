#pragma once
#include "Pipeline.hpp"
// #include "Queues.hpp"
// #include "SwapChainSupportDetails.hpp"
// #include "Texture.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

static inline const struct VkUtils2
{
  static constinit inline GLFWwindow *   window;
  static constinit inline GLFWmonitor *  monitor;
  static constinit inline VkInstance     vkInstance;
  static const std::vector<const char *> getRequiredExtensions();
  static VKAPI_ATTR VkBool32 VKAPI_CALL  debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT,
                                                        VkDebugUtilsMessageTypeFlagsEXT,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *,
                                                        void * );

  static VkResult createDebugUtilsMessengerEXT( const VkInstance, const VkDebugUtilsMessengerCreateInfoEXT * );

  static bool isDeviceSuitable( VkPhysicalDevice );
  static void checkDeviceExtensionSupport( VkPhysicalDevice );

  static const VkSurfaceFormatKHR querySwapChainSupport( VkPhysicalDevice );

  typedef VkResult( VKAPI_PTR * PFN_vkCreateDebugUtilsMessengerEXT2 )( VkInstance                                 instance,
                                                                       const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo,
                                                                       const VkAllocationCallbacks *              pAllocator,
                                                                       const VkDebugUtilsMessengerEXT *           pMessenger );

  //    private static final long[] pDebugMessenger = new long[1];
  //    X(),
  //    Y
  //    KEY(1)
  VkUtils2() __attribute__( ( cold ) )
  {
     VkUtils2::setupWindow();
  VkUtils2::createInstance();
  VkUtils2::setupDebugMessenger();
  VkUtils2::createSurface();
  VkUtils2::pickPhysicalDevice();
  // VkUtils2::createLogicalDevice();
  SwapChainSupportDetails::setupImageFormats();
  SwapChainSupportDetails::createSwapChain();
  SwapChainSupportDetails::createImageViews();
  PipelineX::createRenderPasses();
  // UniformBufferObject::createDescriptorSetLayout();
  PipelineX::createGraphicsPipelineLayout();
  Queues::createCommandPool();
  BuffersX::setupBuffers();
  SwapChainSupportDetails::createFramebuffers();

  // UniformBufferObject::createUniformBuffers();

  // UniformBufferObject::createDescriptorPool();
  // UniformBufferObject::createDescriptorSets();
  PipelineX::createCommandBuffers();
  }

  // static void extracted();
  static void setupWindow();

  static void createInstance();
  static void createSurface();
  static bool checkValidationLayerSupport();

  static constexpr void setupDebugMessenger();

  static void pickPhysicalDevice();
  static void createLogicalDevice();
  static void cleanup() __attribute__( ( cold ) );
  ~VkUtils2()
  {
     vkDeviceWaitIdle( Queues::device );
  vkUnmapMemory( Queues::device, UniformBufferObject::uniformBuffersMemory );
  vkDestroyCommandPool( Queues::device, (VkCommandPool)Queues::commandPool, nullptr );
  for ( auto framebuffer : SwapChainSupportDetails::swapChainFramebuffers )
  {
    vkDestroyFramebuffer( Queues::device, framebuffer, nullptr );
  }

  vkDestroyBuffer( Queues::device, BuffersX::vertexBuffer, nullptr );
  vkFreeMemory( Queues::device, BuffersX::vertexBufferMemory, nullptr );
  }
  // static void createSwapChain();
  // static void createImageViews();
  // static void createPipeLine();
} VKU2;

inline namespace
{}  // namespace