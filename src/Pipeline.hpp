#pragma once
#include "Queues.hpp"

 constexpr int OFFSETOF_COLOR = 3 * sizeof(float);
 constexpr int OFFSET_POS = 0;

 constexpr int OFFSETOF_TEXTCOORDS = (3 + 3) * sizeof(float);

namespace Pipeline
{   
    static VkPipeline graphicsPipeline;
    static VkCommandPool commandPool;
    static void createRenderPasses();
    static void createGraphicsPipelineLayout();
    static void createCommandPool();
VkVertexInputBindingDescription* getVertexInputBindingDescription();
    static VkVertexInputAttributeDescription*  getAttributeDescriptions();
};




 inline  VkVertexInputBindingDescription* Pipeline::getVertexInputBindingDescription()
    {
         VkVertexInputBindingDescription a {
                .binding=0,
//                    .stride(vertices.length/2)
//                    .stride(vertices.length/VERT_SIZE+1)
                .stride=32,
                .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
        };
        return &a;
    }

    inline VkVertexInputAttributeDescription*  Pipeline::getAttributeDescriptions()
    {

        VkVertexInputAttributeDescription attributeDescriptions[3];

        // Position
        VkVertexInputAttributeDescription* posDescription = &attributeDescriptions[0];
        posDescription->binding=0;
        posDescription->location=0;
        posDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
        posDescription->offset=OFFSET_POS;

        // Color
        VkVertexInputAttributeDescription* colorDescription = &attributeDescriptions[1];
        colorDescription->binding=0;
        colorDescription->location=1;
        colorDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
        colorDescription->offset=OFFSETOF_COLOR;

        // Texture coordinates
        VkVertexInputAttributeDescription* texCoordsDescription = &attributeDescriptions[2];
        texCoordsDescription->binding=0;
        texCoordsDescription->location=2;
        texCoordsDescription->format=VK_FORMAT_R32G32_SFLOAT;
        texCoordsDescription->offset=OFFSETOF_TEXTCOORDS;

//            memFree(attributeDescriptions);

        return attributeDescriptions;
    }

    