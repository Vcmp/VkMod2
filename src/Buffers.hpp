#pragma once

#include "SwapChainSupportDetails.hpp"
#include "src/Buffers.hpp"
#include <cstddef>
#include <vulkan/vulkan_core.h>


// = (&set + sizeof(set));

inline namespace BuffersX {

static inline void* data = nullptr;

static inline VkBuffer vertexBuffer;
static inline VkDeviceMemory vertexBufferMemory;

static inline VkBuffer Bufferstaging;
static inline VkDeviceMemory stagingBufferMemory;





inline namespace 
{
static constexpr float vectBuf[]=
{
    0.0f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f,-0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 10.5f,-1.0f, 0.0f, 1.0f, 1.0f
};static constexpr short idxBuf[]=
{

};
constexpr size_t sizedsf=sizeof(vectBuf);
inline void mapBuf(const float& ,const VkDeviceMemory&,  const size_t&);
inline void mapBuf(const float &mainVertbuf,const VkDeviceMemory& memBuf,  const size_t& sizsedf)
{
        vkMapMemory(device, memBuf, 0, sizsedf, 0, &data);
        {
            memcpy(data, &mainVertbuf, sizsedf);
            //                GLU2.theGLU.wrap()

        }
        vkUnmapMemory(device, memBuf);
}
}



static VkOffset2D set{.x = 0, .y = 0};

static VkEvent vkEvent;

// inline VkPipelineLayout vkLayout;
static VkDeviceMemory createBuffer2(VkMemoryPropertyFlagBits properties, VkBuffer &currentBuffer);
static void setBuffer(VkBufferUsageFlagBits, size_t, VkBuffer&);
static uint32_t findMemoryType(VkPhysicalDevice, uint32_t,
                               VkMemoryPropertyFlagBits);
static void createVkEvents();
static void createVertexBuffer();
static void createStagingBuffer();
static void copyBuffer(VkBuffer&, VkBuffer&, size_t);

}; // namespace BuffersX

inline uint32_t BuffersX::findMemoryType(VkPhysicalDevice physicalDevice,
                                         uint32_t typeFilter,
                                         VkMemoryPropertyFlagBits properties) {
  VkPhysicalDeviceMemoryProperties memProperties = {};
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((typeFilter & (1 << i)) != 0 &&
        (memProperties.memoryTypes[i].propertyFlags & properties) ==
            properties) {

      return i;
    }
  }

  throw std::runtime_error("Failed to find suitable memory type");
}

inline void BuffersX::createVkEvents() {

  VkEventCreateInfo vkEventCreateInfo = {};
  vkEventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;

  clPPPI(&vkEventCreateInfo, "vkCreateEvent", &vkEvent);
}

inline void BuffersX::createVertexBuffer()
{
  // constexpr size_t size =sizeof(vectBuf);
    VkBufferUsageFlagBits x = (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

  setBuffer(x, sizedsf, vertexBuffer);

  


  VkMemoryPropertyFlagBits p = (VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
  vertexBufferMemory=createBuffer2(p, vertexBuffer);

// VkMemoryAllocateInfo allocInfo{
// .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
// .allocationSize = memRequirements.size,
// .memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, p),
// };

// clPPPI(&allocInfo, "vkBindBufferMemory", &vertexBufferMemory);
 
    //  BuffersX::mapBuf(*vectBuf, vertexBufferMemory, sizedsf);

}

inline void BuffersX::createStagingBuffer()
{
  setBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT, sizedsf, Bufferstaging);
  constexpr VkMemoryPropertyFlagBits p = (VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
  stagingBufferMemory= createBuffer2(p, Bufferstaging);

  BuffersX::mapBuf(*vectBuf, stagingBufferMemory, sizedsf);

  BuffersX::copyBuffer(Bufferstaging, vertexBuffer, sizedsf);

}



 inline void BuffersX::setBuffer(VkBufferUsageFlagBits usage, size_t size, VkBuffer &a)
    {
        VkBufferCreateInfo allocateInfo ={
                .sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                .size=size,
                .usage=usage,
                .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
        };

       clPPPI(&allocateInfo, "vkCreateBuffer", &a);
        //nmemFree(allocateInfo);
    }


  inline VkDeviceMemory BuffersX::createBuffer2(VkMemoryPropertyFlagBits properties, VkBuffer &currentBuffer)
    {

        //long vkMemoryRequirements = VkUtils2.MemSysm.malloc(VkMemoryRequirements.SIZEOF);
 VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);


        VkMemoryAllocateInfo allocateInfo1 = {
                .sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .allocationSize=memRequirements.size,
                .memoryTypeIndex=findMemoryType(physicalDevice, memRequirements.memoryTypeBits, properties),
        };
//            nmemFree(vkMemoryRequirements);
        VkDeviceMemory vertexBufferMemory;
        clPPPI(&allocateInfo1, "vkAllocateMemory", &vertexBufferMemory);
       
        vkBindBufferMemory(device, currentBuffer, vertexBufferMemory, 0);
        //memPutLong( device.address(), a);
        return vertexBufferMemory;

    }

    inline void BuffersX::copyBuffer(VkBuffer &src, VkBuffer &dst, size_t sized)
    {
       VkCommandBuffer commandBuffer = beginSingleTimeCommands();
      const VkBufferCopy vkBufferCopy{
                .srcOffset=0,
                .dstOffset=0,
                .size=sized,
      };
        // MemSysm.Memsys2.free(vkBufferCopy);
        vkCmdCopyBuffer(commandBuffer, src, dst, 1, &vkBufferCopy);
        endSingleTimeCommands(commandBuffer);
    }