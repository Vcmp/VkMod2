#pragma once

#include "SwapChainSupportDetails.hpp"

#include <immintrin.h>

#define GLM_FORCE_LEFT_HANDED

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"


// = (&set + sizeof(set));

// Can't use inetrnal Linkage anyMore unfortuately due to need to link to Main/Pooled/Addregated Implemenaion/.CPP File
struct BuffersX
{
  static  inline __m256*  data = nullptr;  // Similar to the Hardcodes Address Field in the Memory Allocation
                                                  // System used in the Java Version
  static inline  VkPhysicalDeviceMemoryProperties memProperties; //May Cause alignment problems

  static constinit inline VkBuffer       vertexBuffer;
  // static constinit inline VkBuffer       vertexBufferTemp;
  static constinit inline VkDeviceMemory vertexBufferMemory;
  // static constinit inline VkDeviceMemory vertexBufferMemorytemp;

  static constinit inline VkBuffer       Bufferstaging;
  static constinit inline VkDeviceMemory stagingBufferMemory;

  static constinit inline VkBuffer       indexBuffer;
  static constinit inline VkDeviceMemory indexBufferMemory;

  static inline constexpr float x         = 0;
  static inline constexpr float y         = 1;
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
    0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20,
  };

  static constexpr size_t sizedsf    = sizeof( vectBuf );
  static constexpr size_t sizedsfIdx = sizeof( idxBuf );

  static void copyBuffer( VkBuffer &, const size_t );

  // static VkOffset2D set{.x = 0, .y = 0};

  static VkEvent vkEvent;

  // inline VkPipelineLayout vkLayout;

  static uint32_t findMemoryType( uint32_t, VkMemoryPropertyFlagBits );
  static void     createVkEvents();
  static void     setupBuffers();
  static void     createSetBuffer( VkMemoryPropertyFlagBits, VkBuffer &, VkBufferUsageFlagBits, size_t, VkDeviceMemory & );

};  // namespace BuffersX

inline namespace
{

  const glm::mat4 viewproj = glm::perspectiveLH_ZO( glm::radians( 45.0F ) * -1, width / static_cast<float>( height ), 1.7F, 90.0F ) *
                       glm::lookAtLH( glm::vec3( 2.0F, 2.0F, 2.0F ), glm::vec3( 0.0F, 0.0F, 0.0F ), glm::vec3( 0.0F, 0.0F, 1.0F ) );
  ;
  // glm::mat4 rot;
  static const __m256     viewproj2x = *(const __m256 *)(&viewproj);
  static constexpr __m128 axvZXLI    = __extension__( __m128 ){ /*  -1, -1, -1, -1,  */ 0x80000000, 0x80000000, 0x80000000, 0x80000000 };

};  // namespace

// static inline struct alignas( ( 64 ) ) UBO
// {
//   glm::mat4 model = viewproj;
//   // mat4 Trans;
// } ubo;
struct textTemp
{
    // static constexpr VkDevice &aa= Queues::device;
    VkPipelineShaderStageCreateInfo vkShaderStages[2];
    VkPipeline x;
    VkCommandPool p;
    textTemp()
    {
      

      constexpr VkCommandPoolCreateInfo VkPC{
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .pNext = nullptr,
        .queueFamilyIndex = 0

      };
      vkCreateCommandPool(Queues::device, &VkPC, nullptr, &p);

      VkCommandBufferAllocateInfo a{
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .pNext=nullptr,
        .commandPool = p,
        .level=VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandBufferCount=1,
      };
      vkAllocateCommandBuffers(Queues::device, &a, &comBuffer);
    }
    
   
    void doBuffers();
    void initPipelineCustom();
    void voidrecComBufferSub(int i);

    VkCommandBuffer comBuffer; void vkMappedCopy(VkDeviceMemory&, size_t, const float[], __m256*, VkBuffer&);

    VkBuffer VertexTemp;
    VkDeviceMemory VertexTempMem;
    
    VkBuffer stagingBuffer2;
    VkDeviceMemory stagingBufferMemory2;

    static constexpr float Vktemp[] = {
       1.f, 1.f, 0.f, 1.f, 0.0f,
	    -1.f, 1.f, 0.f, 1.f, 0.0f,
	    0.f, -1.f, 0.f, 1.f, 0.0f,
    };



};