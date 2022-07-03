#include "VKI.hpp"
#include <cstddef>
#include <cstdint>

#include <ios>
#include <vector>
#include <iostream>
#include <minwindef.h>
#include <vulkan/vulkan_win32.h>
#include <windef.h>
#include <winuser.h>
#include <WindowsX.h>
#include "Vks.tpp"



inline namespace {
static constexpr char const * deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
      std::cout <<std::hex <<"0x"<< uMsg << "OK!" << "\n";
      std::cout <<std::dec <<"wParam"<<"0x"<< wParam << "OK!" << "\n";
      std::cout <<std::left <<"lParam"<<"0x"<< lParam << "OK!" << "\n";
      std::cout <<std::dec <<"W"<< (GET_X_LPARAM(lParam)) << "OK!" << "\n";
      std::cout <<std::dec <<"H"<< (GET_Y_LPARAM(lParam)) << "OK!" << "\n";
      VkInit::X=(GET_X_LPARAM(lParam));
      VkInit::Y=(GET_Y_LPARAM(lParam));

  switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        return 0;
    case WM_NCCREATE:
    
          std::cout << "NCCreate Window!" << "\n";
          return true;
    
    case WM_NCDESTROY:
    
      std::cout << "NCDestroy Window!" << "\n";
      return 0;
    case WM_INPUT:
    {
      std::cout << "INPUT!" << "\n";
      auto a =GET_RAWINPUT_CODE_WPARAM(wParam);
      std::cout << a << "\n";
      return 0;
    }
    case WM_CREATE:
       std::cout << "Create Window" << "\n";
       return true;
    case WM_NCACTIVATE:
       std::cout << "CreateActivat Window" << "\n";
      return(!wParam)?false: -1;
      return 1;
    case WM_SETCURSOR:
      return false;
    case WM_GETMINMAXINFO:
      return 0;
    case WM_NCCALCSIZE:
      if(wParam)
      {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
      }
      else return true;
    
    case WM_MOVE:
      std::cout << "MOVE!" << "\n";
      return true;
    
   

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
};

auto VkInit::init(HINSTANCE instance) const -> HWND
{

 

  
 WNDCLASS wc = { };
    wc.style=CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = instance;
    // wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = nullptr;//(HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "main";
    RegisterClass(&wc);
    auto w =CreateWindowEx(wc.style,
                                           "main",
                                           nullptr,
                                           NULL,
                                           0, 0,
                                           width, height,
                                           nullptr, // No parent window
                                           NULL, // No window menu
                                           instance,
                                           (LPVOID) nullptr);

    if (w == nullptr)
    {
        return nullptr;
    }

    ShowWindow(w, 10);

 
  std::cout << "OK!" << "\n";
  return  w;
};


auto VkInit::createInstance() const -> VkInstance
{
  VkInstance vki;
  std::cout <<  "Creating Instance"  << "\n";

  static constexpr auto valdFeatures       = { VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
                                                                   VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
                                                                   VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT };
  constexpr VkValidationFeaturesEXT             extValidationFeatures = {
                .sType                         = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                .enabledValidationFeatureCount = valdFeatures.size(),
                .pEnabledValidationFeatures    = valdFeatures.begin(),
  };
 
  constexpr VkApplicationInfo vkApplInfo 
  {
    VK_STRUCTURE_TYPE_APPLICATION_INFO,
     VK_NULL_HANDLE,
    "VKMod2",
    VK_MAKE_VERSION( 1, 3, 0 ),
    "No Engine",
    VK_MAKE_VERSION( 1, 3, 0 ),
    VK_API_VERSION_1_3
  };
  std::vector<const char *> extensions{ VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME};
  
  for(uint32_t i=0; i< extensions.size(); i++)
  {
    std::cout << extensions[i] << "\n";
  }
  
  if constexpr ( ENABLE_VALIDATION_LAYERS )
  {
    extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );
  }
  const VkInstanceCreateInfo InstCreateInfo 
  {
    .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext               =  ENABLE_VALIDATION_LAYERS ? &extValidationFeatures : nullptr,
    .pApplicationInfo        = &vkApplInfo,
   .enabledLayerCount   =  ENABLE_VALIDATION_LAYERS ? 1 : 0,
      .ppEnabledLayerNames = ENABLE_VALIDATION_LAYERS ? &validationLayers : nullptr,
    .enabledExtensionCount = static_cast<uint32_t>(( extensions.size() )),
    .ppEnabledExtensionNames = extensions.data(),

  };

  
 
  vkCreateInstance(&InstCreateInfo, nullptr, &vki);

  return vki;
 }
template <typename name>
auto  VkInit::vkEnumSet(auto aa) const
{
  uint32_t deviceCount;
  aa( instance, &deviceCount, nullptr ) ;

 
   std::vector<name> ppPhysicalDevicesdeviceCount(deviceCount);

  std::cout <<  "Enumerate Physical Device"  << "\n";
  aa( instance, &deviceCount, ppPhysicalDevicesdeviceCount.data() );
  return ppPhysicalDevicesdeviceCount;
}



 auto VkInit::doPhysicalDevice() const -> VkPhysicalDevice
 {
    std::cout << ( "Picking Physical Device" ) << "\n";
  return vkEnumSet<VkPhysicalDevice>(vkEnumeratePhysicalDevices)[0];
 }

auto VkInit::createSurface(HINSTANCE inst) const -> VkSurfaceKHR
{
    VkSurfaceKHR surface;
  std::cout << ( "Creating Surface" ) << "\n";
  VkWin32SurfaceCreateInfoKHR createSurfaceInfo = {};
  createSurfaceInfo.sType                       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createSurfaceInfo.hwnd                        = window;
  createSurfaceInfo.hinstance                   = inst;
  createSurfaceInfo.pNext                       = VK_NULL_HANDLE;

  vkCreateWin32SurfaceKHR( instance, &createSurfaceInfo, nullptr, &surface);
  return surface;
}

VkDevice VkInit::doDevice()
{
   std::cout << "Creating Logical Device"  << "\n";
uint32_t graphicsFamily;
uint32_t transferFamily;
  uint32_t pQueueFamilyPropertyCount;
  vkGetPhysicalDeviceQueueFamilyProperties( physdevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE );

  VkQueueFamilyProperties uniqueQueueFamilies[pQueueFamilyPropertyCount];
  vkGetPhysicalDeviceQueueFamilyProperties( physdevice, &pQueueFamilyPropertyCount, uniqueQueueFamilies );

  
  // todo: Likley/Prop won't work with AMD properly and/or specific GPUs with differing Queue Family layouts
  for ( uint32_t i = 0; VkQueueFamilyProperties const & uniqueQueue : uniqueQueueFamilies )
  {
    std::cout << ( uniqueQueue.queueCount ) << "\n";
    if ( ( uniqueQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT ) )
    {
      graphicsFamily = i;
      continue;
    }
    // Check that Video Tranfer Queues are not Accidentally selected if the Vulkan beta Drivers from Nvidia are used
    // VkBool32 presentSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR(physdevice, i);
    
    if ( uniqueQueue.queueFlags & VK_QUEUE_TRANSFER_BIT && !vkGetPhysicalDeviceWin32PresentationSupportKHR(physdevice, i) )
    {
      transferFamily = i;
      break;
    }

    i++;
  }
  std::cout << "Using: " << graphicsFamily << "-->" << transferFamily << "\n";

  constexpr float priority = 1.0f;
  uint32_t        pIx      = 0;

  VkDeviceQueueCreateInfo GQ{};

  GQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  GQ.queueFamilyIndex = graphicsFamily;
  GQ.queueCount       = 1;
  GQ.pQueuePriorities = &priority;
  GQ.flags            = 0;
  GQ.pNext            = VK_NULL_HANDLE;

  VkDeviceQueueCreateInfo PQ{};

  PQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  PQ.queueFamilyIndex = transferFamily;
  PQ.queueCount       = 1;
  PQ.pQueuePriorities = &priority;
  PQ.flags            = 0;
  PQ.pNext            = VK_NULL_HANDLE;
  
  

  const auto queueCreateInfos = { GQ, PQ };

  static VkPhysicalDeviceVulkan13Features vk13F
  {
    .sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
    .pNext=nullptr,
    .synchronization2=true,
  };


  static VkPhysicalDeviceVulkan12Features deviceVulkan12Features = {
    .sType                           = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
    .pNext                           = &vk13F,
    .descriptorBindingPartiallyBound = true,
    .imagelessFramebuffer            = true,

  };

  static constexpr VkPhysicalDeviceFeatures deviceFeatures = {};

  VkPhysicalDeviceFeatures2 deviceFeatures2 = { .sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                                                .pNext    = &deviceVulkan12Features,
                                                /* .features = deviceFeatures */ };


  vkGetPhysicalDeviceFeatures2( physdevice, &deviceFeatures2 );


  const VkDeviceCreateInfo createInfo      = {
  .sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
  .pNext                   = &deviceFeatures2,
  .queueCreateInfoCount    = 2,
  .pQueueCreateInfos       = queueCreateInfos.begin(),
  .ppEnabledLayerNames =   ENABLE_VALIDATION_LAYERS  ? &validationLayers : nullptr,
  .enabledExtensionCount   = 1,
  .ppEnabledExtensionNames = ( &deviceExtensions ),
  .pEnabledFeatures = nullptr,
  };
  VkDevice device;
  if ( !deviceVulkan12Features.imagelessFramebuffer )
  {
     std::runtime_error( "Failed Enumeration!" );
  }
  
  
  vkCreateDevice( physdevice, &createInfo, VK_NULL_HANDLE, &device ) ;

  vkGetDeviceQueue(device, 0, 0, &GraphicsQueue );
  // vkGetDeviceQueue(device, 0, 0, &PresentQueue );
  vkGetDeviceQueue(device, 1, 0, &TransferQueue );
  // Queues::device=device;
  return device;
}