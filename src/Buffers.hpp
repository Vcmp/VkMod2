#pragma once

#include "SwapChainSupportDetails.hpp"
#include "Queues.hpp"


// = (&set + sizeof(set));

inline namespace BuffersX {

static inline void* data = nullptr;
// static inline void* data2 = nullptr;

static inline VkBuffer vertexBuffer;
static inline VkDeviceMemory vertexBufferMemory;

static inline VkBuffer Bufferstaging;
static inline VkDeviceMemory stagingBufferMemory;

static inline VkBuffer indexBuffer;
static inline VkDeviceMemory indexBufferMemory;



inline namespace 
{
  static constexpr float vectBuf[]=
  {
     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f
    
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f
  };
  static constexpr short idxBuf[]=
  {
       0, 1, 2, 2, 3, 0,
       4, 5, 6, 6, 7, 4
  };
  constexpr size_t vecSizsed=24;//(sizeof(vectBuf)/(sizeof(float)));
  constexpr size_t sizedsf=sizeof(vectBuf);
  constexpr size_t sizedsfIdx=sizeof(idxBuf);
  // inline void mapBuf(const float& ,const VkDeviceMemory&,  const size_t&);
  
  static void copyBuffer(VkBuffer&, const size_t);
};



// static VkOffset2D set{.x = 0, .y = 0};

static VkEvent vkEvent;

// inline VkPipelineLayout vkLayout;

static uint32_t findMemoryType(VkPhysicalDevice, uint32_t,
                               VkMemoryPropertyFlagBits);
static void createVkEvents();
static void setupBuffers();
static void createSetBuffer(VkMemoryPropertyFlagBits, VkBuffer&, VkBufferUsageFlagBits, size_t, VkDeviceMemory&);


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

  

    inline void BuffersX::copyBuffer(VkBuffer &dst, const size_t sized)
    {
       VkCommandBuffer commandBuffer = beginSingleTimeCommands();
      const VkBufferCopy vkBufferCopy{
                .srcOffset=0,
                .dstOffset=0,
                .size=sized,
      };
        // MemSysm.Memsys2.free(vkBufferCopy);
        vkCmdCopyBuffer(commandBuffer, Bufferstaging, dst, 1, &vkBufferCopy);
        endSingleTimeCommands(commandBuffer);
    }

    

    inline void BuffersX::setupBuffers()
    {
      
     
      VkBufferUsageFlagBits x1 = (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT);
      VkMemoryPropertyFlagBits p1 = (VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
      createSetBuffer(p1, vertexBuffer, x1, sizedsf, vertexBufferMemory);
      // vertexBufferMemory=createBuffer2(p1, vertexBuffer);
      
      VkBufferUsageFlagBits x2 = (VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
      constexpr VkMemoryPropertyFlagBits p = (VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
      createSetBuffer(p, Bufferstaging, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, sizedsf, stagingBufferMemory);      

      // stagingBufferMemory= createBuffer2(p, Bufferstaging);
      VkBufferUsageFlagBits x3=(VkBufferUsageFlagBits)(VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT);
       createSetBuffer(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, x3, sizedsfIdx, indexBufferMemory);


      vkMapMemory(device, stagingBufferMemory, 0, sizedsf, 0, &data);
          {
              memcpy(data, vectBuf, sizedsf);
          }
          vkUnmapMemory(device, stagingBufferMemory);
              BuffersX::copyBuffer(vertexBuffer, sizedsf);
      
      
          vkMapMemory(device, stagingBufferMemory, 0, sizedsfIdx, 0, &data);
          {
          memcpy(data, idxBuf, sizedsfIdx);

          }
          vkUnmapMemory(device, stagingBufferMemory);
          copyBuffer(indexBuffer, sizedsfIdx);
         


      //   {
      //   }
      //   vkUnmapMemory(device, stagingBufferMemory);

      
 
    }




    inline void BuffersX::createSetBuffer(VkMemoryPropertyFlagBits properties, VkBuffer &currentBuffer, VkBufferUsageFlagBits usage, size_t sized, VkDeviceMemory &vertexBufferMemory)
    {
          const VkBufferCreateInfo allocateInfo ={
                .sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
                .size=sized,
                .usage=usage,
                .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
        };

       clPPPI(&allocateInfo, "vkCreateBuffer", &currentBuffer);

       VkMemoryRequirements memRequirements;
      vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);


        VkMemoryAllocateInfo allocateInfo1 = {
                .sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
                .allocationSize=memRequirements.size,
                .memoryTypeIndex=findMemoryType(Queues::physicalDevice, memRequirements.memoryTypeBits, properties),
        };
//           
        clPPPI(&allocateInfo1, "vkAllocateMemory", &vertexBufferMemory);
       
        checkCall(vkBindBufferMemory(device, currentBuffer, vertexBufferMemory, 0));
        //memPutLong( device.address(), a);
    }