

#include <initializer_list>
#include <vulkan/vulkan_core.h>
#include <immintrin.h>

struct Buffer
{
        VkPhysicalDeviceMemoryProperties memProperties; //May Cause alignment problems

   static inline __m256 * data = nullptr;
    VkBuffer buffer;
    VkDeviceMemory BufMemory;
      static constexpr float x         = 0;
  static constexpr float y         = 1;
    static constexpr float buffAbs[]={
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
    Buffer()
    {
        commandPool=createCommandPool();
        commandBuffer= genCommandBuffer();
        setupBuffers();
    } ;
    // explicit Buffer(std::initializer_list<float> a): buffAbs(a){};

    VkBuffer       Bufferstaging;
    VkDeviceMemory stagingBufferMemory;
    void setupBuffers();
    void createSetBuffer(VkMemoryPropertyFlagBits properties, VkBuffer & currentBuffer, VkBufferUsageFlagBits usage, size_t sized, VkDeviceMemory & vertexBufferMemory );
    static constexpr size_t sizedsf    = sizeof(buffAbs) ;
    void copyBuffer( VkBuffer & dst, const size_t sized );
    void vkMappedCopy(VkDeviceMemory &Staging, size_t size, const auto* srcVectBuffs, __m256 *data, VkBuffer& Temp);
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkCommandBuffer genCommandBuffer();
    VkCommandPool createCommandPool();
    void beginSingleTimeCommands();
    void endSingleTimeCommands();
    uint32_t findMemoryType( uint32_t typeFilter, VkMemoryPropertyFlagBits properties );


} ;