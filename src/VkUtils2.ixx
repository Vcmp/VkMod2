#pragma once

#include "Pipeline.hpp"
#include "Queues.hpp"
#include "SwapChainSupportDetails.hpp"
#include "Texture.hpp"
#include "UniformBufferObject.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// #include <stdint.h>

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
    extracted();
  }

  static void extracted();
  static void setupWindow();

  static void createInstance();
  static void createSurface();
  static bool checkValidationLayerSupport();

  static void setupDebugMessenger();

  static void pickPhysicalDevice();
  static void createLogicalDevice();
  static void cleanup() __attribute__( ( cold ) );
  ~VkUtils2()
  {
    cleanup();
  }
  // static void createSwapChain();
  // static void createImageViews();
  // static void createPipeLine();
} VKU2;