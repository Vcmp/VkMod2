
#include "VkUtilsXBase.hpp"


//Was being quite silly anf fogt/did nt replaise that it is in aftc accpeble/even good rpatcie to iclude Heards Quelitlaly,icnlien.nSres,chais.Senu as long as impeltaions/translation units to not Overlap/Overide Eahc other and/or reudent;need/elss ?Excessive Linoing takes palces and taranltios,tcoep.moame sanoot be mitiagedenagtaited/handled/ienatces/Dlelaiatve/reonee\bd/impelmated 

static constexpr struct Queues
{
  static inline VkCommandPool               commandPool;
  static inline VkCommandPool               commandPool2;
  static inline VkPhysicalDevice            physicalDevice;
  static inline VkDevice                    device;
  static inline bool                        a = false;
  static inline uint32_t                    graphicsFamily;
  static inline uint32_t                    transferFamily;
  static inline VkQueue                     GraphicsQueue;
  static inline VkQueue                     TransferQueue[2];
  static constexpr VkCommandBufferBeginInfo vkCommandBufferBeginInfo = { .sType = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),
                                                                         .pNext = VK_NULL_HANDLE,
                                                                         .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };
  static inline VkSurfaceKHR                surface;
  static inline VkCommandBuffer             commandBuffer;
  constexpr static const VkSubmitInfo       submitInfo1 = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = VK_NULL_HANDLE, .commandBufferCount = ( 1 ), .pCommandBuffers = &commandBuffer
  };

  static void createCommandPool();
  static void beginSingleTimeCommands();
  static void endSingleTimeCommands();
  template <typename X, typename T>
  static constexpr auto clPPPI3A( const auto * __restrict__ pStrct, const char * __restrict__ a )
  {
    // const VkDevice aa = volkGetLoadedDevice();
    X object;
    T( vkGetDeviceProcAddr( Queues::device, a ) )( Queues::device, pStrct, nullptr, &object );
    return object;
  }
} inline const queues;

