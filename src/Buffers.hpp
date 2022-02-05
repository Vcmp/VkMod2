#pragma once

#include "Queues.hpp"
#include "SwapChainSupportDetails.hpp"

// = (&set + sizeof(set));

inline namespace BuffersX
{

  static inline void * data = nullptr;  // Similar to the Hardcodes Address Field in the Memory Allocation
                                        // System used in the Java Version

  static inline VkBuffer       vertexBuffer;
  static inline VkDeviceMemory vertexBufferMemory;

  static inline VkBuffer       Bufferstaging;
  static inline VkDeviceMemory stagingBufferMemory;

  static inline VkBuffer       indexBuffer;
  static inline VkDeviceMemory indexBufferMemory;

  inline namespace
  {
    inline constexpr float        x         = 0;
    inline constexpr float        y         = 1;
    static inline constexpr float vectBuf[] = {
      /*0  -->*/ x,  x, x, 1, 0, 0,
      /*1  -->*/ y,  y, x, x, y, x,
      /*2  -->*/ y,  y, x, x, x, y,
      /*3  -->*/ x,  y, x, y, y, y,

      /*4  -->*/ x,  x, y, y, x, x,
      /*5  -->*/ y,  x, y, x, y, x,
      /*6  -->*/ y,  y, y, x, x, y,
      /*7  -->*/ x,  y, y, y, y, y,

      /*8  -->*/ x,  x, x, y, x, x,
      /*9  -->*/ y,  x, x, x, y, x,
      /*10  -->*/ y, x, y, x, x, y,
      /*11  -->*/ x, x, y, y, y, y,

      /*12  -->*/ x, y, y, y, x, x,
      /*13  -->*/ y, y, y, x, y, x,
      /*14  -->*/ y, y, x, x, x, y,
      /*15  -->*/ x, y, x, y, y, y,

      /*16  -->*/ x, x, y, y, x, x,
      /*17  -->*/ x, y, y, x, y, x,
      /*18  -->*/ x, y, x, x, x, y,
      /*19  -->*/ x, x, x, y, y, y,

      /*20  -->*/ y, x, x, y, x, x,
      /*21  -->*/ y, y, x, x, y, x,
      /*22  -->*/ y, y, y, x, x, y,
      /*23  -->*/ y, x, y, y, y, y,

    };
    static constexpr short idxBuf[] = {
      0,  1,  2,  2,  3,  0,  4,  5,  6,  6,  7,  4,  8,  9,  10, 10, 11, 8,
      12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20,
    };

    constexpr size_t sizedsf    = sizeof( vectBuf );
    constexpr size_t sizedsfIdx = sizeof( idxBuf );

    static void copyBuffer( VkBuffer &, const size_t );
  }  // namespace

  // static VkOffset2D set{.x = 0, .y = 0};

  static VkEvent vkEvent;

  // inline VkPipelineLayout vkLayout;

  static uint32_t findMemoryType( VkPhysicalDevice, uint32_t, VkMemoryPropertyFlagBits );
  static void     createVkEvents();
  static void     setupBuffers();
  static void createSetBuffer( VkMemoryPropertyFlagBits, VkBuffer &, VkBufferUsageFlagBits, size_t, VkDeviceMemory & );

};  // namespace BuffersX

inline uint32_t
  BuffersX::findMemoryType( VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlagBits properties )
{
  VkPhysicalDeviceMemoryProperties memProperties = {};
  vkGetPhysicalDeviceMemoryProperties( physicalDevice, &memProperties );
  for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
  {
    if ( ( typeFilter & ( 1 << i ) ) != 0 && ( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
    {
      return i;
    }
  }

  throw std::runtime_error( "Failed to find suitable memory type" );
}

inline void BuffersX::createVkEvents()
{
  VkEventCreateInfo vkEventCreateInfo = {};
  vkEventCreateInfo.sType             = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
  vkEventCreateInfo.pNext             = nullptr;

  clPPPI( &vkEventCreateInfo, "vkCreateEvent", &vkEvent );
}

inline void BuffersX::copyBuffer( VkBuffer & dst, const size_t sized )
{
  Queues::beginSingleTimeCommands();
  const VkBufferCopy vkBufferCopy{
    .srcOffset = 0,
    .dstOffset = 0,
    .size      = sized,
  };
  // MemSysm.Memsys2.free(vkBufferCopy);
  vkCmdCopyBuffer( queues.commandBuffer, Bufferstaging, dst, 1, &vkBufferCopy );
  Queues::endSingleTimeCommands();
}

inline void BuffersX::setupBuffers()
{
  auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
                                                VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT );
  VkMemoryPropertyFlagBits p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p1, vertexBuffer, x1, sizedsf, vertexBufferMemory );
  // vertexBufferMemory=createBuffer2(p1, vertexBuffer);

  auto x2 =
    static_cast<VkBufferUsageFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT );
  constexpr auto p =
    static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT );
  createSetBuffer( p, Bufferstaging, x2, sizedsf, stagingBufferMemory );

  // stagingBufferMemory= createBuffer2(p, Bufferstaging);
  auto x3 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
                                                VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT );
  createSetBuffer( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, x3, sizedsfIdx, indexBufferMemory );

  vkMapMemory( device, stagingBufferMemory, 0, sizedsf, 0, &data );
  {
    memcpy( data, vectBuf, sizedsf );
  }

  BuffersX::copyBuffer( vertexBuffer, sizedsf );

  {
    memcpy( data, idxBuf, sizedsfIdx );
  }
  vkUnmapMemory( device, stagingBufferMemory );
  copyBuffer( indexBuffer, sizedsfIdx );
}

inline void BuffersX::createSetBuffer( VkMemoryPropertyFlagBits properties,
                                       VkBuffer &               currentBuffer,
                                       VkBufferUsageFlagBits    usage,
                                       size_t                   sized,
                                       VkDeviceMemory &         vertexBufferMemory )
{
  const VkBufferCreateInfo allocateInfo = {
    .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .pNext       = nullptr,
    .size        = sized,
    .usage       = usage,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
  };

  clPPPI( &allocateInfo, "vkCreateBuffer", &currentBuffer );

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements( device, currentBuffer, &memRequirements );

  VkMemoryAllocateInfo allocateInfo1 = {
    .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext           = nullptr,
    .allocationSize  = memRequirements.size,
    .memoryTypeIndex = findMemoryType( Queues::physicalDevice, memRequirements.memoryTypeBits, properties ),
  };
  //
  clPPPI( &allocateInfo1, "vkAllocateMemory", &vertexBufferMemory );

  checkCall( vkBindBufferMemory( device, currentBuffer, vertexBufferMemory, 0 ) );
  // memPutLong( device.address(), a);
}