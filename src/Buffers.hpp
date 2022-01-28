#pragma once

#include "SwapChainSupportDetails.hpp"


// = (&set + sizeof(set));

inline namespace BuffersX {

static inline void* data = nullptr;

static inline VkBuffer vertexBuffer;
static inline VkDeviceMemory vertexBufferMemory;

static constexpr float vectBuf[]=
{
  0.0f, -0.5f, 1.0f, 1.0f, 1.0f,  
  0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f 
};
constexpr size_t sizedsf=sizeof(vectBuf);

static constexpr short idxBuf[]=
{

};



static VkOffset2D set{.x = 0, .y = 0};

static VkEvent vkEvent;

// inline VkPipelineLayout vkLayout;
static VkDeviceMemory createBuffer2(VkMemoryPropertyFlagBits properties, VkBuffer &currentBuffer);
static void setBuffer(VkBufferUsageFlagBits, size_t, VkBuffer&);
static uint32_t findMemoryType(VkPhysicalDevice, uint32_t,
                               VkMemoryPropertyFlagBits);
static void createVkEvents();
static void createVertexBuffer();

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
  setBuffer(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, sizedsf, vertexBuffer);

  


  VkMemoryPropertyFlagBits p = (VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
  vertexBufferMemory=createBuffer2(p, vertexBuffer);

// VkMemoryAllocateInfo allocInfo{
// .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
// .allocationSize = memRequirements.size,
// .memoryTypeIndex = findMemoryType(physicalDevice, memRequirements.memoryTypeBits, p),
// };

// clPPPI(&allocInfo, "vkBindBufferMemory", &vertexBufferMemory);
 
  vkMapMemory(device, vertexBufferMemory, 0, sizedsf, 0, &data);
        {
            memcpy(data, vectBuf, sizedsf);
            //                GLU2.theGLU.wrap()

        }
        vkUnmapMemory(device, vertexBufferMemory);

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
        vkGetBufferMemoryRequirements(device, currentBuffer, &memRequirements);


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